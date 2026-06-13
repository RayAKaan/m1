#!/bin/bash
# Run this after pushing to GitHub to create the 5 gap issues via gh CLI
# Requires: gh auth login

gh issue create --title "[GAP] now invariants are only checked at declaration, not after mutation" \
  --label "gap,temporal,spec-vs-impl" \
  --body-file .github/ISSUE_TEMPLATE/gap-now-recheck.md

gh issue create --title "[GAP] will + now conflict detection is missing" \
  --label "gap,temporal,phase-graph" \
  --body-file .github/ISSUE_TEMPLATE/gap-will-now-conflict.md

gh issue create --title "[GAP] Bare expression statements require set _ wrapper" \
  --label "gap,syntax,parser" \
  --body-file .github/ISSUE_TEMPLATE/gap-bare-expr.md

gh issue create --title "[GAP] Error code scheme is only partially implemented" \
  --label "gap,diagnostics,usability" \
  --body-file .github/ISSUE_TEMPLATE/gap-error-codes.md

gh issue create --title "[GAP] m1c.exe cannot self-compile (stack overflow on m1c.m0)" \
  --label "gap,bootstrap,self-hosting" \
  --body-file .github/ISSUE_TEMPLATE/gap-self-compile.md

echo "All 5 gap issues created (if gh is authenticated)."
