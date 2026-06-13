# Revised Near-Term Priorities (Post-Discovery)

**Date:** 2026-06-14 (Week 1 exploration completed; Tier 1 port starting)

---

## The Discovery

The self-hosted compiler (`m1c.m0`) currently has almost no support for the temporal language constructs (`live`, `freeze`, `was`, `will`, `when/then`, `now`).

- Tokens exist in the lexer.
- Parser rules, AST nodes, and codegen for these constructs **do not exist** in `m1c.m0`.
- All real temporal behavior and Phase Graph usage lives only in the C bootstrap.

This changes the shape of the next 1–3 months of work.

---

## New Priority Order

### Tier 1 — Must Do Before Meaningful Temporal Work (Next 4–8 weeks)

1. **Port temporal frontend into m1c.m0**
   - Parser productions for `set live ...`, `freeze`, `was`, `will`, `when/then`, `now`.
   - Corresponding AST node kinds.
   - Basic structure / lowering so these constructs can be processed.

2. **Basic lowering that can reach the runtime + Phase Graph externals**
   - Emit calls that the existing `m0_runtime` + `phase_graph.c` can handle.
   - **Goal:** Make it possible for a program using temporal operators to be compiled by `m1c` and produce runnable output.

3. **Self-hosting stability improvements (in parallel)**
   - The compiler needs to handle larger inputs as we add more code.

### Tier 2 — Core v0.6 Deliverables (Once Tier 1 is in place)

- Real Phase Graph integration (calling the externals from the new lowering, constant folding for `was`, basic conflict detection).
- `now` re-check after mutation.
- Bare expression statements.
- Cross-platform build improvements.
- Regenerated evidence + updated documentation.

### Tier 3 — Polish & M2

- Full `will` + `now` conflict detection.
- Better error messages.
- More stdlib / examples.
- Advanced analysis, linear types, effects, etc.

---

## Why This Order

Trying to "integrate the Phase Graph" while the language constructs don't exist in the self-hosted compiler is backwards. The Phase Graph is a **consumer** of temporal events — we first need something that **produces** those events from source code.

---

## Updated Success Criteria for Next 30 Days

- [ ] The self-hosted compiler can parse and represent the five core temporal operators.
- [ ] At least a handful of the original temporal tests (or close equivalents) can be compiled by `m1c` instead of only the C bootstrap.
- [ ] Clear, public documentation of the discovery and the revised plan.
- [ ] Measurable progress on the frontend port (not just analysis).

---

## Communication

- Update `ROADMAP_v0.6.md` with a new section acknowledging the discovery.
- Use the Week 1 kickoff issue + filled template to keep the discovery and revised priorities visible.
- Consider a short public note (GitHub discussion) once the first 1–2 weeks of porting work are underway.

---

*This is the honest path. It is larger than the original 30-day scope, but it is the only path that leads to a credible v0.6.*
