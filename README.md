# M1

A self-hosting programming language with verified types.

## Install

Download the release for your platform. Add to PATH.

## Hello World

Create `hello.m1`:

```
module Hello {
    fn main() -> Int {
        println("Hello, World")
    }
}
```

Run:

```
m1 run hello.m1
```

## Functions

```
fn add(a : Int, b : Int) -> Int { a + b }
fn main() -> Int {
    println(int_to_string(add(3, 4)))
}
```

## Records

```
type Point = { x : Int, y : Int }
fn main() -> Int {
    let p : Point = { x = 3, y = 7 };
    println(int_to_string(p.x + p.y))
}
```

## Enums

```
type Option = | Some(Int) | None
```

## Pattern Matching

```
fn classify(n : Int) -> Int {
    match n {
        0 -> 1;
        _ -> n * 2;
    }
}
```

## Conditionals

```
fn abs(n : Int) -> Int {
    if n < 0 { 0 - n } else { n }
}
```

## Standard Library

| Function | Type |
|---|---|
| `print(s)` | `String -> Int` |
| `println(s)` | `String -> Int` |
| `string_len(s)` | `String -> Int` |
| `string_concat(a, b)` | `String -> String -> String` |
| `int_to_string(n)` | `Int -> String` |
| `read_file(path)` | `String -> String` |
| `write_file(path, content)` | `String -> String -> Int` |

All functions are auto-imported. No `external` declarations needed.

## Commands

```
m1 run <file.m1>     Compile and run
m1 build <file.m1>   Compile to executable
m1 check <file.m1>   Check syntax
m1 version           Print version
```

## What's Next

- Linear types
- Effect types
- Proposition verification
- `m1 verify`

## License

MIT
