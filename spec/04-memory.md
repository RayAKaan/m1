# Memory Model — [Unnamed Language]

## 1. Memory from Logic

There is no garbage collector. There is no `malloc`/`free`. Memory is derived from linear logic: **allocate when a proposition becomes true, deallocate when it is consumed**. Every memory operation is a logical operation. The compiler determines lifetimes at compile time.

## 2. The Three Usage Modalities

```
Linear<T>       // must be used exactly once
Affine<T>       // must be used at most once
Persistent<T>   // may be used any number of times (immutable)
```

These are NOT annotations. They are logical types. The type IS the memory contract.

| Modality | Lifetime | Copyable | Example |
|----------|----------|----------|---------|
| Linear | Unique ownership, exactly one use | No | File handle, DB connection |
| Affine | Unique ownership, zero or one use | No | Optional resource, received message |
| Persistent | Shared, any number of uses | Yes (immutable ref) | Configuration, cached data |

## 3. Allocation and Deallocation Rules

### 3.1 Fundamental Principle

```
A value of type T becomes true (allocated) when:
    A proposition of type T is proved

A value of type T becomes false (deallocated) when:
    The proposition of type T is consumed
    (used as a proof in another proposition)
```

### 3.2 Linear Values: Exactly One Use

```
x : Linear<T>

// x must be used EXACTLY ONCE in the program
// After the use, x is consumed (deallocated)
// Using x again is a logical contradiction
// The program CANNOT be written that way

Example:

    let handle : Linear<FileHandle> = open_file("data.txt")
    let content : FileContent = read_all(handle)    // handle consumed here
    // handle is deallocated. Cannot be used again.
    // read_all returned the content; handle is logically consumed.

    // This would be a compile error:
    let again = read_all(handle)    // ERROR: handle is already consumed
```

### 3.3 Affine Values: At Most One Use

```
x : Affine<T>

// x may be used AT MOST ONCE
// After use, x is consumed (deallocated)
// x may also be discarded (not used at all)
// Discarding an affine value is valid

Example:

    let msg : Affine<Message> = receive(channel)
    match should_process {
        true  → let result = process(msg)    // msg consumed
        false → skip                         // msg discarded (valid)
    }
```

### 3.4 Persistent Values: Any Number of Uses

```
x : Persistent<T>

// x may be used any number of times
// x is never consumed (immutable shared reference)
// Lifetime: scope-based (last use determines deallocation)

Example:

    let config : Persistent<Config> = load_config()
    let a = process_with(config)     // config still available
    let b = also_process_with(config) // config still available
    // config deallocated after last use
```

### 3.5 Promotion Between Modalities

```
Linear(T) → Affine(T)     // safe: "exactly once" implies "at most once"
Affine(T) → Linear(T)     // UNSAFE: "at most once" might be zero
Linear(T) → Persistent(T) // never: linear is unique, persistent is shared
```

Promotion is explicit:
```
let handle : Linear<FileHandle> = ...
let opt_handle : Affine<FileHandle> = upcast(handle)
// opt_handle can be discarded; handle's "exactly once" constraint is lost
// valid ONLY if no other use of handle exists
```

## 4. Memory Graph

### 4.1 Graph Structure

The compiler builds a memory graph from the proposition dependency graph:

```
Node = proposition (value)
Edge = "consumes" (one proposition consumes another)

Properties:
    Linear<T> nodes:   exactly one outgoing consume edge
    Affine<T> nodes:   zero or one outgoing consume edge
    Persistent<T> nodes: zero or more outgoing reference edges (not consume)
```

### 4.2 Consumption Tracking

```
For each Linear<T> value v:
    1. Find all uses of v
    2. Exactly ONE use must be a consumption
    3. Other uses are compile errors

For each Affine<T> value v:
    1. Find all uses of v
    2. At MOST ONE use may be a consumption
    3. Zero uses is valid (discard)
    4. Two or more consumptive uses is a compile error

For each Persistent<T> value v:
    1. Find all uses of v
    2. No restriction on number of uses
    3. No consumption (all uses are shared references)
```

### 4.3 Consumption Graph Compile-Time Analysis

```
// The compiler builds and checks this graph at compile time.
// Every path through the program is analyzed.

fn process_handle(h : Linear<Handle>) → Result:
    match random_bool():
        true  → consume(h)     // path 1: consumed
        false → consume(h)     // path 2: also consumed
    // All paths consume exactly once ✓

fn bad_handle(h : Linear<Handle>) → Result:
    match random_bool():
        true  → consume(h)     // path 1: consumed
        false → Result.error() // path 2: NOT consumed
    // ERROR: Linear value not consumed on all paths

fn also_bad(h : Linear<Handle>) → Result:
    consume(h)
    consume(h)
    // ERROR: Linear value consumed twice on all paths
```

## 5. Arena-Based Compiler Phases

### 5.1 Arena Allocation

The compiler itself uses arena allocation for its data structures:

```
Each compiler phase has its own arena:
    Parser phase:           ParserArena
    Scope resolution phase: ScopeArena
    Type checking phase:    TypeArena
    Completeness phase:     CompleteArena
    Consistency phase:      ConsistentArena
    Reduction phase:        ReduceArena
    Dependency analysis:    DepArena
    Code generation:        CodeGenArena

Phase boundaries are clear.
Phase ends → entire arena is freed at once.
No individual malloc/free within a phase.
```

### 5.2 Arena Lifecycle

```
// Each phase:
arena = Arena_new(64 * 1024)    // 64KB initial, grows as needed

while parsing/scoping/checking:
    node = Arena_alloc(arena, sizeof(Node))
    // no free of individual nodes

Arena_destroy(arena)    // entire allocation freed at once
```

### 5.3 Why Arenas

```
1. No individual free: Allocation patterns within a compiler phase
   are complex and intertwined. Individual free is unnecessary overhead.

2. Phase boundaries: Each phase completes before the next begins.
   The entire phase's data is either consumed by the next phase
   or discarded.

3. No GC pauses: A single arena free is O(1). No GC tracing.

4. Predictable: Allocation is sequential bump-allocation within the arena.
   No fragmentation. No compaction.
```

### 5.4 Arena Implementation (C)

```c
typedef struct {
    char *start;
    char *current;
    char *end;
    size_t block_size;
    struct ArenaBlock *blocks;  // linked list of overflow blocks
} Arena;

void *arena_alloc(Arena *a, size_t size) {
    // Align to 8 bytes
    size = (size + 7) & ~7;
    if (a->current + size > a->end) {
        grow_arena(a, size);
    }
    void *ptr = a->current;
    a->current += size;
    return ptr;
}

void arena_destroy(Arena *a) {
    // Free all blocks at once
    ArenaBlock *block = a->blocks;
    while (block) {
        ArenaBlock *next = block->next;
        free(block);
        block = next;
    }
    free(a->start);
}
```

## 6. Lifetime Determination Algorithm

### 6.1 Pure Lifetime Analysis

For a pure proposition graph, lifetimes are determined by dataflow:

```
Algorithm: determine_lifetime(proposition P):
    if P is a root (top-level declaration, function argument, lambda capture):
        lifetime = scope_of(P)    // determined by lexical scope

    if P is a let-bound value:
        lifetime = from_let_to_last_use

    if P is a function return:
        lifetime = caller_determined

    if P is a match arm result:
        lifetime = lifetime of the match result
```

### 6.2 Linear Value Lifetime

```
Algorithm: determine_linear_lifetime(value V):
    1. Find the point where V is constructed (allocated)
    2. Find the unique point where V is consumed (deallocated)
    3. Lifetime: construct ↔ consume
    4. Verify: every path from construct to consume uses V exactly once
```

### 6.3 Lifetime Diagram

```
let handle : Linear<Handle> = open(...)     // ALLOCATE (proposition becomes true)
    // ... handle is alive here ...
    // ... handle may be passed around (moved, not copied) ...
let content = read_all(handle)                // CONSUME (proposition becomes false)
    // handle is DEAD here
    // content is alive (new proposition)
```

## 7. Copy vs Move

### 7.1 Persistent Types: Copy

```
Persistent<T> values are reference-counted at compile time.
Multiple references share the same memory.
The compiler proves that no reference mutates the value.
```

### 7.2 Linear and Affine Types: Move

```
Linear<T> and Affine<T> values are MOVED, not copied:

    let a : Linear<Handle> = open(...)
    let b = a    // a is MOVED to b. a is now logically consumed.

    // Using a after move:
    // read_all(a)   // COMPILE ERROR: a was moved to b
    read_all(b)      // OK: b owns the handle

Move is a logical operation: the proposition's truth has been transferred.
The original binding is logically false after the move.
```

### 7.3 Move Tracking

```
The compiler tracks the current binding of each linear value:

    open(...)         → handle is bound to `a`
    let b = a         → handle is bound to `b`, `a` is dead
    read_all(b)       → handle is consumed, `b` is dead

This is compile-time dataflow. No runtime reference counting.
```

## 8. Session Types (Communication Memory)

### 8.1 Channel as Linear Resource

```
channel : Channel<Request, Response>

// channel is a Linear value
// Sending consumes the Request (linear)
// Receiving produces a Response (linear)
// Using a channel is a complete logical transaction
```

### 8.2 Session Protocol

```
Channel<Req, Res> follows a session protocol:

    send(channel, req) : Linear<Channel<Req, Res>> → Linear<Channel<Next, Res>>
    recv(channel) : Linear<Channel<Req, Res>> → (Res, Linear<Channel<Req, Next>>)

    // The protocol is encoded in the type.
    // Deviation from the protocol is a type error (logical inconsistency).
```

### 8.3 Channel Lifetime

```
// Channel allocation:         when the connection is established
// Channel consumption:        when the connection is closed
// Messages (send/recv):       intermediate propositions that consume/produce

// Complete program:
    let chan : Linear<Channel<Request, Response>> = connect(addr)
    // chan is alive
    let _ = send(chan, request)         // chan consumed, next_chan produced
    let (resp, next_chan) = recv(chan)  // ERROR: chan was consumed by send
    // Correct:
    // let (resp, next_chan) = recv(next_chan)  // next_chan consumed
    // close(next_chan)                           // final consumption
```

## 9. Compiler Memory Pass

### 9.1 Memory Analysis Algorithm

```
function analyze_memory(program):

    // Phase 1: Determine modality of every value
    for each declaration:
        modality = classify_modality(decl.type)
        annotate(decl, modality)

    // Phase 2: Build consumption graph
    graph = build_consumption_graph(program)

    // Phase 3: Check linearity constraints
    for each Linear<T> value:
        verify_exactly_one_consumption(value, graph)

    for each Affine<T> value:
        verify_at_most_one_consumption(value, graph)

    // Phase 4: Determine lifetimes
    for each value:
        lifetime = determine_lifetime(value, graph)
        emit_allocation_site(value, lifetime.start)
        emit_deallocation_site(value, lifetime.end)

    // Phase 5: Verify no use-after-free
    for each use of value v at point p:
        assert(lifetime(v).start ≤ p ≤ lifetime(v).end)
```

### 9.2 Error Messages

```
Consumption errors:
    "Linear value 'handle' consumed twice: at accounts.l:42 and accounts.l:45"
    "Linear value 'handle' not consumed: discarded at accounts.l:50"
    "Affine value 'msg' consumed twice: at process.l:12 and process.l:13"

Lifetime errors:
    "Use of 'handle' after consumption: at accounts.l:46 (consumed at accounts.l:42)"
    "Use of 'config' outside its scope: at config.l:30"
```

## 10. Runtime Memory Management

### 10.1 The Runtime Memory Model

After the compiler determines lifetimes:

```
For Linear<T>:
    - Stack allocation if T is small (≤ register size)
    - Heap allocation if T is large
    - Deallocation is a compile-time constant offset from allocation
    - No runtime tracking needed

For Affine<T>:
    - Same as Linear, with optional discard path
    - Discard: deallocate without consuming the value

For Persistent<T>:
    - Heap allocation with compile-time reference counting
    - Last use → deallocation
    - Or arena-based for scope-limited persistent values

For function calls:
    - Parameters: caller allocates, callee consumes (stack)
    - Return values: callee allocates, caller consumes (register or stack)
```

### 10.2 No Runtime GC

```
No garbage collector means:
    No stop-the-world pauses
    No tracing
    No reference counting at runtime (compile-time determined)
    No finalizers
    No GC tuning
    No memory leaks from GC roots

Memory is managed by the structure of the logic itself.
```

### 10.3 Stack vs Heap

```
The compiler determines stack vs heap based on:
    1. Size of the type (small → stack, large → heap)
    2. Escape analysis (does the value escape the function?)
    3. Modality (Linear/Affine → move semantics, Persistent → reference)

LLVM's mem2reg pass further promotes stack allocations to registers when possible.
```

## 11. M₀ Subset

M₀ does NOT implement the linear type system. Memory management in the M₀ bootstrap compiler is:

```
M₀ memory:
    1. Arena allocation per compiler phase
    2. All values are treated as Persistent (no linearity tracking)
    3. No consumption analysis
    4. No move semantics — all values are copyable
    5. No session types
    6. Code generation uses stack allocation for locals
    7. LLVM handles register promotion
```

The M₀ bootstrap compiler's output conservatively allocates all values on the stack (or in LLVM registers). No heap allocation. No dynamic lifetimes. This is sufficient to compile the M₁ compiler (which then adds proper memory management).

## 12. Summary

```
Memory model derived from linear logic:
    Linear<T>    → exactly one use (unique ownership)
    Affine<T>    → at most one use (optional ownership)
    Persistent<T> → any number of uses (shared immutability)

Lifetime determined at compile time:
    Allocate when proposition becomes true
    Deallocate when proposition is consumed

Compiler uses arena allocation:
    Each phase has its own arena
    Phase boundaries are clear allocation/deallocation points
    No individual malloc/free within a phase

Runtime memory management:
    Stack allocation for small/short-lived values
    Heap allocation for large/long-lived values
    No garbage collector
    No reference counting at runtime
```

---

*For the type system that governs modalities, see `01-types.md`. For reduction semantics, see `03-reduction.md`.*
