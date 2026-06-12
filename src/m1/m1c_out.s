	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"m1c_out.c"
	.def	sprintf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,sprintf
	.globl	sprintf                         # -- Begin function sprintf
	.p2align	4
sprintf:                                # @sprintf
.seh_proc sprintf
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r9, 104(%rsp)
	movq	%r8, 96(%rsp)
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	leaq	96(%rsp), %rax
	movq	%rax, 40(%rsp)
	movq	40(%rsp), %r9
	movq	64(%rsp), %rdx
	movq	56(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %r8d
	callq	_vsprintf_l
	movl	%eax, 52(%rsp)
	movl	52(%rsp), %eax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	vsprintf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,vsprintf
	.globl	vsprintf                        # -- Begin function vsprintf
	.p2align	4
vsprintf:                               # @vsprintf
.seh_proc vsprintf
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r8, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	64(%rsp), %rax
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	movq	$-1, %rdx
	xorl	%r9d, %r9d
                                        # kill: def $r9 killed $r9d
	movq	%rax, 32(%rsp)
	callq	_vsnprintf_l
	nop
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	_snprintf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_snprintf
	.globl	_snprintf                       # -- Begin function _snprintf
	.p2align	4
_snprintf:                              # @_snprintf
.seh_proc _snprintf
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r9, 104(%rsp)
	movq	%r8, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	leaq	104(%rsp), %rax
	movq	%rax, 32(%rsp)
	movq	32(%rsp), %r9
	movq	64(%rsp), %r8
	movq	56(%rsp), %rdx
	movq	48(%rsp), %rcx
	callq	_vsnprintf
	movl	%eax, 44(%rsp)
	movl	44(%rsp), %eax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	_vsnprintf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_vsnprintf
	.globl	_vsnprintf                      # -- Begin function _vsnprintf
	.p2align	4
_vsnprintf:                             # @_vsnprintf
.seh_proc _vsnprintf
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r9, 64(%rsp)
	movq	%r8, 56(%rsp)
	movq	%rdx, 48(%rsp)
	movq	%rcx, 40(%rsp)
	movq	64(%rsp), %rax
	movq	56(%rsp), %r8
	movq	48(%rsp), %rdx
	movq	40(%rsp), %rcx
	xorl	%r9d, %r9d
                                        # kill: def $r9 killed $r9d
	movq	%rax, 32(%rsp)
	callq	_vsnprintf_l
	nop
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	ps_kind;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	ps_kind                         # -- Begin function ps_kind
	.p2align	4
ps_kind:                                # @ps_kind
.seh_proc ps_kind
# %bb.0:
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movq	%rcx, (%rsp)
	movq	(%rcx), %rax
	.seh_startepilogue
	popq	%rcx
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	ps_line;
	.scl	2;
	.type	32;
	.endef
	.globl	ps_line                         # -- Begin function ps_line
	.p2align	4
ps_line:                                # @ps_line
.seh_proc ps_line
# %bb.0:
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movq	%rcx, (%rsp)
	movq	8(%rcx), %rax
	.seh_startepilogue
	popq	%rcx
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	ps_col;
	.scl	2;
	.type	32;
	.endef
	.globl	ps_col                          # -- Begin function ps_col
	.p2align	4
ps_col:                                 # @ps_col
.seh_proc ps_col
# %bb.0:
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movq	%rcx, (%rsp)
	movq	16(%rcx), %rax
	.seh_startepilogue
	popq	%rcx
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	ps_str;
	.scl	2;
	.type	32;
	.endef
	.globl	ps_str                          # -- Begin function ps_str
	.p2align	4
ps_str:                                 # @ps_str
.seh_proc ps_str
# %bb.0:
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movq	%rcx, (%rsp)
	movq	32(%rcx), %rax
	.seh_startepilogue
	popq	%rcx
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	ps_int;
	.scl	2;
	.type	32;
	.endef
	.globl	ps_int                          # -- Begin function ps_int
	.p2align	4
ps_int:                                 # @ps_int
.seh_proc ps_int
# %bb.0:
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movq	%rcx, (%rsp)
	movq	24(%rcx), %rax
	.seh_startepilogue
	popq	%rcx
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	ps_adv;
	.scl	2;
	.type	32;
	.endef
	.globl	ps_adv                          # -- Begin function ps_adv
	.p2align	4
ps_adv:                                 # @ps_adv
.seh_proc ps_adv
# %bb.0:
	subq	$184, %rsp
	.seh_stackalloc 184
	.seh_endprologue
	movq	%rdx, 40(%rsp)                  # 8-byte Spill
	movq	%rcx, 48(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	%rcx, 176(%rsp)
	movq	%rdx, 168(%rsp)
	movq	40(%rdx), %rax
	movq	%rax, 64(%rsp)
	movq	48(%rdx), %rax
	movq	%rax, 72(%rsp)
	movq	56(%rdx), %rax
	movq	%rax, 80(%rsp)
	movq	64(%rdx), %rax
	movq	%rax, 88(%rsp)
	leaq	96(%rsp), %rcx
	leaq	64(%rsp), %rdx
	callq	m1_lexer_next
	movq	48(%rsp), %rcx                  # 8-byte Reload
	leaq	96(%rsp), %rdx
	movl	$40, %r8d
	callq	memcpy
	movq	40(%rsp), %rdx                  # 8-byte Reload
	movq	48(%rsp), %rcx                  # 8-byte Reload
	movq	56(%rsp), %rax                  # 8-byte Reload
	movq	136(%rsp), %r8
	movq	%r8, 40(%rcx)
	movq	144(%rsp), %r8
	movq	%r8, 48(%rcx)
	movq	152(%rsp), %r8
	movq	%r8, 56(%rcx)
	movq	160(%rsp), %r8
	movq	%r8, 64(%rcx)
	movq	72(%rdx), %rdx
	movq	%rdx, 72(%rcx)
	.seh_startepilogue
	addq	$184, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	ps_err;
	.scl	2;
	.type	32;
	.endef
	.globl	ps_err                          # -- Begin function ps_err
	.p2align	4
ps_err:                                 # @ps_err
.seh_proc ps_err
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%rdx, 32(%rsp)                  # 8-byte Spill
	movq	%rcx, 40(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	movq	%rcx, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movl	$40, %r8d
	callq	memcpy
	movq	32(%rsp), %rdx                  # 8-byte Reload
	movq	40(%rsp), %rcx                  # 8-byte Reload
	movq	48(%rsp), %rax                  # 8-byte Reload
	movq	40(%rdx), %r8
	movq	%r8, 40(%rcx)
	movq	48(%rdx), %r8
	movq	%r8, 48(%rcx)
	movq	56(%rdx), %r8
	movq	%r8, 56(%rcx)
	movq	64(%rdx), %r8
	movq	%r8, 64(%rcx)
	movq	72(%rdx), %rdx
	addq	$1, %rdx
	movq	%rdx, 72(%rcx)
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	mk_pr;
	.scl	2;
	.type	32;
	.endef
	.globl	mk_pr                           # -- Begin function mk_pr
	.p2align	4
mk_pr:                                  # @mk_pr
.seh_proc mk_pr
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r8, 32(%rsp)                   # 8-byte Spill
	movq	%rdx, %rax
	movq	32(%rsp), %rdx                  # 8-byte Reload
	movq	%rcx, %r8
	movq	%r8, 40(%rsp)                   # 8-byte Spill
	movq	%rcx, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movq	%rax, 48(%rsp)
	movq	48(%rsp), %rax
	movq	%rax, (%rcx)
	addq	$8, %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	40(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	nk;
	.scl	2;
	.type	32;
	.endef
	.globl	nk                              # -- Begin function nk
	.p2align	4
nk:                                     # @nk
.seh_proc nk
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	%r9, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	96(%rsp), %rcx
	callq	m0_alloc
	movq	%rax, 64(%rsp)
	movq	72(%rsp), %r8
	movq	64(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_set
	movq	%rax, 56(%rsp)
	movq	80(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$1, %edx
	callq	m0_set
	movq	%rax, 48(%rsp)
	movq	88(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$2, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_int;
	.scl	2;
	.type	32;
	.endef
	.globl	n_int                           # -- Begin function n_int
	.p2align	4
n_int:                                  # @n_int
.seh_proc n_int
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r8, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	64(%rsp), %r8
	movq	56(%rsp), %rdx
	movq	N_INT(%rip), %rcx
	movl	$4, %r9d
	callq	nk
	movq	%rax, 40(%rsp)
	movq	48(%rsp), %r8
	movq	40(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	40(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_str;
	.scl	2;
	.type	32;
	.endef
	.globl	n_str                           # -- Begin function n_str
	.p2align	4
n_str:                                  # @n_str
.seh_proc n_str
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r8, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	64(%rsp), %r8
	movq	56(%rsp), %rdx
	movq	N_STRING(%rip), %rcx
	movl	$4, %r9d
	callq	nk
	movq	%rax, 40(%rsp)
	movq	48(%rsp), %r8
	movq	40(%rsp), %rcx
	movl	$3, %edx
	callq	m0_store_string
	movq	%rax, 32(%rsp)
	movq	40(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_bool;
	.scl	2;
	.type	32;
	.endef
	.globl	n_bool                          # -- Begin function n_bool
	.p2align	4
n_bool:                                 # @n_bool
.seh_proc n_bool
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r8, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	64(%rsp), %r8
	movq	56(%rsp), %rdx
	movq	N_BOOL(%rip), %rcx
	movl	$4, %r9d
	callq	nk
	movq	%rax, 40(%rsp)
	movq	48(%rsp), %r8
	movq	40(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	40(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_unit;
	.scl	2;
	.type	32;
	.endef
	.globl	n_unit                          # -- Begin function n_unit
	.p2align	4
n_unit:                                 # @n_unit
.seh_proc n_unit
# %bb.0:
	subq	$56, %rsp
	.seh_stackalloc 56
	.seh_endprologue
	movq	%rdx, 48(%rsp)
	movq	%rcx, 40(%rsp)
	movq	48(%rsp), %r8
	movq	40(%rsp), %rdx
	movq	N_UNIT(%rip), %rcx
	movl	$3, %r9d
	callq	nk
	nop
	.seh_startepilogue
	addq	$56, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_name;
	.scl	2;
	.type	32;
	.endef
	.globl	n_name                          # -- Begin function n_name
	.p2align	4
n_name:                                 # @n_name
.seh_proc n_name
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r8, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	64(%rsp), %r8
	movq	56(%rsp), %rdx
	movq	N_NAME(%rip), %rcx
	movl	$4, %r9d
	callq	nk
	movq	%rax, 40(%rsp)
	movq	48(%rsp), %r8
	movq	40(%rsp), %rcx
	movl	$3, %edx
	callq	m0_store_string
	movq	%rax, 32(%rsp)
	movq	40(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_bin;
	.scl	2;
	.type	32;
	.endef
	.globl	n_bin                           # -- Begin function n_bin
	.p2align	4
n_bin:                                  # @n_bin
.seh_proc n_bin
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	144(%rsp), %rax
	movq	%r9, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	144(%rsp), %r8
	movq	96(%rsp), %rdx
	movq	N_BINARY(%rip), %rcx
	movl	$6, %r9d
	callq	nk
	movq	%rax, 64(%rsp)
	movq	72(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 56(%rsp)
	movq	80(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 48(%rsp)
	movq	88(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$5, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_not;
	.scl	2;
	.type	32;
	.endef
	.globl	n_not                           # -- Begin function n_not
	.p2align	4
n_not:                                  # @n_not
.seh_proc n_not
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r8, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	64(%rsp), %r8
	movq	56(%rsp), %rdx
	movq	N_NOT(%rip), %rcx
	movl	$4, %r9d
	callq	nk
	movq	%rax, 40(%rsp)
	movq	48(%rsp), %r8
	movq	40(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	40(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_field;
	.scl	2;
	.type	32;
	.endef
	.globl	n_field                         # -- Begin function n_field
	.p2align	4
n_field:                                # @n_field
.seh_proc n_field
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%r9, 80(%rsp)
	movq	%r8, 72(%rsp)
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movq	80(%rsp), %r8
	movq	72(%rsp), %rdx
	movq	N_FIELD(%rip), %rcx
	movl	$5, %r9d
	callq	nk
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$4, %edx
	callq	m0_store_string
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_call;
	.scl	2;
	.type	32;
	.endef
	.globl	n_call                          # -- Begin function n_call
	.p2align	4
n_call:                                 # @n_call
.seh_proc n_call
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	144(%rsp), %rax
	movq	%r9, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	144(%rsp), %r8
	movq	96(%rsp), %rdx
	movq	N_CALL(%rip), %rcx
	movl	$6, %r9d
	callq	nk
	movq	%rax, 64(%rsp)
	movq	72(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 56(%rsp)
	movq	80(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 48(%rsp)
	movq	88(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$5, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_let;
	.scl	2;
	.type	32;
	.endef
	.globl	n_let                           # -- Begin function n_let
	.p2align	4
n_let:                                  # @n_let
.seh_proc n_let
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	152(%rsp), %rax
	movq	144(%rsp), %rax
	movq	%r9, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	152(%rsp), %r8
	movq	144(%rsp), %rdx
	movq	N_LET(%rip), %rcx
	movl	$7, %r9d
	callq	nk
	movq	%rax, 64(%rsp)
	movq	72(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$3, %edx
	callq	m0_store_string
	movq	%rax, 56(%rsp)
	movq	80(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 48(%rsp)
	movq	88(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$5, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	96(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$6, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_match;
	.scl	2;
	.type	32;
	.endef
	.globl	n_match                         # -- Begin function n_match
	.p2align	4
n_match:                                # @n_match
.seh_proc n_match
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	144(%rsp), %rax
	movq	%r9, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	144(%rsp), %r8
	movq	96(%rsp), %rdx
	movq	N_MATCH(%rip), %rcx
	movl	$6, %r9d
	callq	nk
	movq	%rax, 64(%rsp)
	movq	72(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 56(%rsp)
	movq	80(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 48(%rsp)
	movq	88(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$5, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_if;
	.scl	2;
	.type	32;
	.endef
	.globl	n_if                            # -- Begin function n_if
	.p2align	4
n_if:                                   # @n_if
.seh_proc n_if
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	144(%rsp), %rax
	movq	%r9, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	144(%rsp), %r8
	movq	96(%rsp), %rdx
	movq	N_IF(%rip), %rcx
	movl	$6, %r9d
	callq	nk
	movq	%rax, 64(%rsp)
	movq	72(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 56(%rsp)
	movq	80(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 48(%rsp)
	movq	88(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$5, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_record;
	.scl	2;
	.type	32;
	.endef
	.globl	n_record                        # -- Begin function n_record
	.p2align	4
n_record:                               # @n_record
.seh_proc n_record
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%r9, 80(%rsp)
	movq	%r8, 72(%rsp)
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movq	80(%rsp), %r8
	movq	72(%rsp), %rdx
	movq	N_RECORD(%rip), %rcx
	movl	$5, %r9d
	callq	nk
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	t_name;
	.scl	2;
	.type	32;
	.endef
	.globl	t_name                          # -- Begin function t_name
	.p2align	4
t_name:                                 # @t_name
.seh_proc t_name
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r8, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	64(%rsp), %r8
	movq	56(%rsp), %rdx
	movq	T_NAMED(%rip), %rcx
	movl	$4, %r9d
	callq	nk
	movq	%rax, 40(%rsp)
	movq	48(%rsp), %r8
	movq	40(%rsp), %rcx
	movl	$3, %edx
	callq	m0_store_string
	movq	%rax, 32(%rsp)
	movq	40(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	t_fn;
	.scl	2;
	.type	32;
	.endef
	.globl	t_fn                            # -- Begin function t_fn
	.p2align	4
t_fn:                                   # @t_fn
.seh_proc t_fn
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	144(%rsp), %rax
	movq	%r9, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	144(%rsp), %r8
	movq	96(%rsp), %rdx
	movq	T_FN(%rip), %rcx
	movl	$6, %r9d
	callq	nk
	movq	%rax, 64(%rsp)
	movq	72(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 56(%rsp)
	movq	80(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 48(%rsp)
	movq	88(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$5, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	t_record;
	.scl	2;
	.type	32;
	.endef
	.globl	t_record                        # -- Begin function t_record
	.p2align	4
t_record:                               # @t_record
.seh_proc t_record
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%r9, 80(%rsp)
	movq	%r8, 72(%rsp)
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movq	80(%rsp), %r8
	movq	72(%rsp), %rdx
	movq	T_RECORD(%rip), %rcx
	movl	$5, %r9d
	callq	nk
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	t_sum;
	.scl	2;
	.type	32;
	.endef
	.globl	t_sum                           # -- Begin function t_sum
	.p2align	4
t_sum:                                  # @t_sum
.seh_proc t_sum
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%r9, 80(%rsp)
	movq	%r8, 72(%rsp)
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movq	80(%rsp), %r8
	movq	72(%rsp), %rdx
	movq	T_SUM(%rip), %rcx
	movl	$5, %r9d
	callq	nk
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	t_app;
	.scl	2;
	.type	32;
	.endef
	.globl	t_app                           # -- Begin function t_app
	.p2align	4
t_app:                                  # @t_app
.seh_proc t_app
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	144(%rsp), %rax
	movq	%r9, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	144(%rsp), %r8
	movq	96(%rsp), %rdx
	movq	T_APP(%rip), %rcx
	movl	$6, %r9d
	callq	nk
	movq	%rax, 64(%rsp)
	movq	72(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 56(%rsp)
	movq	80(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 48(%rsp)
	movq	88(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$5, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	mk_param;
	.scl	2;
	.type	32;
	.endef
	.globl	mk_param                        # -- Begin function mk_param
	.p2align	4
mk_param:                               # @mk_param
.seh_proc mk_param
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movl	$2, %ecx
	callq	m0_alloc
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_store_string
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$1, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	mk_fi;
	.scl	2;
	.type	32;
	.endef
	.globl	mk_fi                           # -- Begin function mk_fi
	.p2align	4
mk_fi:                                  # @mk_fi
.seh_proc mk_fi
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movl	$2, %ecx
	callq	m0_alloc
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_store_string
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$1, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	mk_arm;
	.scl	2;
	.type	32;
	.endef
	.globl	mk_arm                          # -- Begin function mk_arm
	.p2align	4
mk_arm:                                 # @mk_arm
.seh_proc mk_arm
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movl	$2, %ecx
	callq	m0_alloc
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$1, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	mk_ctor;
	.scl	2;
	.type	32;
	.endef
	.globl	mk_ctor                         # -- Begin function mk_ctor
	.p2align	4
mk_ctor:                                # @mk_ctor
.seh_proc mk_ctor
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movl	$2, %ecx
	callq	m0_alloc
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_store_string
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$1, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	p_wild;
	.scl	2;
	.type	32;
	.endef
	.globl	p_wild                          # -- Begin function p_wild
	.p2align	4
p_wild:                                 # @p_wild
.seh_proc p_wild
# %bb.0:
	subq	$56, %rsp
	.seh_stackalloc 56
	.seh_endprologue
	movq	%rdx, 48(%rsp)
	movq	%rcx, 40(%rsp)
	movq	48(%rsp), %r8
	movq	40(%rsp), %rdx
	movq	P_WILD(%rip), %rcx
	movl	$3, %r9d
	callq	nk
	nop
	.seh_startepilogue
	addq	$56, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	p_lit;
	.scl	2;
	.type	32;
	.endef
	.globl	p_lit                           # -- Begin function p_lit
	.p2align	4
p_lit:                                  # @p_lit
.seh_proc p_lit
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r8, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	64(%rsp), %r8
	movq	56(%rsp), %rdx
	movq	P_LIT(%rip), %rcx
	movl	$4, %r9d
	callq	nk
	movq	%rax, 40(%rsp)
	movq	48(%rsp), %r8
	movq	40(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	40(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	p_ctor;
	.scl	2;
	.type	32;
	.endef
	.globl	p_ctor                          # -- Begin function p_ctor
	.p2align	4
p_ctor:                                 # @p_ctor
.seh_proc p_ctor
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%r9, 80(%rsp)
	movq	%r8, 72(%rsp)
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movq	80(%rsp), %r8
	movq	72(%rsp), %rdx
	movq	P_CTOR(%rip), %rcx
	movl	$5, %r9d
	callq	nk
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$3, %edx
	callq	m0_store_string
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	p_name;
	.scl	2;
	.type	32;
	.endef
	.globl	p_name                          # -- Begin function p_name
	.p2align	4
p_name:                                 # @p_name
.seh_proc p_name
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r8, 64(%rsp)
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	64(%rsp), %r8
	movq	56(%rsp), %rdx
	movq	P_NAME(%rip), %rcx
	movl	$4, %r9d
	callq	nk
	movq	%rax, 40(%rsp)
	movq	48(%rsp), %r8
	movq	40(%rsp), %rcx
	movl	$3, %edx
	callq	m0_store_string
	movq	%rax, 32(%rsp)
	movq	40(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_type_decl;
	.scl	2;
	.type	32;
	.endef
	.globl	n_type_decl                     # -- Begin function n_type_decl
	.p2align	4
n_type_decl:                            # @n_type_decl
.seh_proc n_type_decl
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%r9, 80(%rsp)
	movq	%r8, 72(%rsp)
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movq	80(%rsp), %r8
	movq	72(%rsp), %rdx
	movq	N_TYPE_DECL(%rip), %rcx
	movl	$5, %r9d
	callq	nk
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$3, %edx
	callq	m0_store_string
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_fn_decl;
	.scl	2;
	.type	32;
	.endef
	.globl	n_fn_decl                       # -- Begin function n_fn_decl
	.p2align	4
n_fn_decl:                              # @n_fn_decl
.seh_proc n_fn_decl
# %bb.0:
	subq	$120, %rsp
	.seh_stackalloc 120
	.seh_endprologue
	movq	176(%rsp), %rax
	movq	168(%rsp), %rax
	movq	160(%rsp), %rax
	movq	%r9, 112(%rsp)
	movq	%r8, 104(%rsp)
	movq	%rdx, 96(%rsp)
	movq	%rcx, 88(%rsp)
	movq	176(%rsp), %r8
	movq	168(%rsp), %rdx
	movq	N_FN_DECL(%rip), %rcx
	movl	$8, %r9d
	callq	nk
	movq	%rax, 80(%rsp)
	movq	88(%rsp), %r8
	movq	80(%rsp), %rcx
	movl	$3, %edx
	callq	m0_store_string
	movq	%rax, 72(%rsp)
	movq	96(%rsp), %r8
	movq	80(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 64(%rsp)
	movq	104(%rsp), %r8
	movq	80(%rsp), %rcx
	movl	$5, %edx
	callq	m0_set
	movq	%rax, 56(%rsp)
	movq	112(%rsp), %r8
	movq	80(%rsp), %rcx
	movl	$6, %edx
	callq	m0_set
	movq	%rax, 48(%rsp)
	movq	160(%rsp), %r8
	movq	80(%rsp), %rcx
	movl	$7, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	80(%rsp), %rax
	.seh_startepilogue
	addq	$120, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_extern;
	.scl	2;
	.type	32;
	.endef
	.globl	n_extern                        # -- Begin function n_extern
	.p2align	4
n_extern:                               # @n_extern
.seh_proc n_extern
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%r9, 80(%rsp)
	movq	%r8, 72(%rsp)
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movq	80(%rsp), %r8
	movq	72(%rsp), %rdx
	movq	N_EXTERN(%rip), %rcx
	movl	$5, %r9d
	callq	nk
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$3, %edx
	callq	m0_store_string
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_mod;
	.scl	2;
	.type	32;
	.endef
	.globl	n_mod                           # -- Begin function n_mod
	.p2align	4
n_mod:                                  # @n_mod
.seh_proc n_mod
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	144(%rsp), %rax
	movq	%r9, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	144(%rsp), %r8
	movq	96(%rsp), %rdx
	movq	N_MOD(%rip), %rcx
	movl	$6, %r9d
	callq	nk
	movq	%rax, 64(%rsp)
	movq	72(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$3, %edx
	callq	m0_store_string
	movq	%rax, 56(%rsp)
	movq	80(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 48(%rsp)
	movq	88(%rsp), %r8
	movq	64(%rsp), %rcx
	movl	$5, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	n_prog;
	.scl	2;
	.type	32;
	.endef
	.globl	n_prog                          # -- Begin function n_prog
	.p2align	4
n_prog:                                 # @n_prog
.seh_proc n_prog
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%r9, 80(%rsp)
	movq	%r8, 72(%rsp)
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movq	80(%rsp), %r8
	movq	72(%rsp), %rdx
	movq	N_PROG(%rip), %rcx
	movl	$5, %r9d
	callq	nk
	movq	%rax, 48(%rsp)
	movq	56(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$3, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %r8
	movq	48(%rsp), %rcx
	movl	$4, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	list_rev;
	.scl	2;
	.type	32;
	.endef
	.globl	list_rev                        # -- Begin function list_rev
	.p2align	4
list_rev:                               # @list_rev
.seh_proc list_rev
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	48(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB44_2
# %bb.1:
	movq	56(%rsp), %rax
	movq	%rax, 64(%rsp)
	jmp	.LBB44_3
.LBB44_2:
	movq	56(%rsp), %rax
	movq	%rax, 32(%rsp)                  # 8-byte Spill
	movq	48(%rsp), %rcx
	callq	m0_head
	movq	32(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, %rcx
	callq	m0_cons
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	movq	48(%rsp), %rcx
	callq	m0_tail
	movq	40(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, %rcx
	callq	list_rev
	movq	%rax, 64(%rsp)
.LBB44_3:
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	rev;
	.scl	2;
	.type	32;
	.endef
	.globl	rev                             # -- Begin function rev
	.p2align	4
rev:                                    # @rev
.seh_proc rev
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movq	%rcx, 32(%rsp)
	movq	m0_nil(%rip), %rdx
	movq	32(%rsp), %rcx
	callq	list_rev
	nop
	.seh_startepilogue
	addq	$40, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	list_len;
	.scl	2;
	.type	32;
	.endef
	.globl	list_len                        # -- Begin function list_len
	.p2align	4
list_len:                               # @list_len
.seh_proc list_len
# %bb.0:
	subq	$56, %rsp
	.seh_stackalloc 56
	.seh_endprologue
	movq	%rcx, 40(%rsp)
	movq	40(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB46_2
# %bb.1:
	movq	$0, 48(%rsp)
	jmp	.LBB46_3
.LBB46_2:
	movq	40(%rsp), %rcx
	callq	m0_tail
	movq	%rax, %rcx
	callq	list_len
	addq	$1, %rax
	movq	%rax, 48(%rsp)
.LBB46_3:
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$56, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	gather_type_fields;
	.scl	2;
	.type	32;
	.endef
	.globl	gather_type_fields              # -- Begin function gather_type_fields
	.p2align	4
gather_type_fields:                     # @gather_type_fields
.seh_proc gather_type_fields
# %bb.0:
	subq	$1288, %rsp                     # imm = 0x508
	.seh_stackalloc 1288
	.seh_endprologue
	movq	%rdx, 88(%rsp)                  # 8-byte Spill
	movq	%rcx, 96(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 104(%rsp)                 # 8-byte Spill
	movq	1328(%rsp), %rax
	movq	%rcx, 1280(%rsp)
	movq	%r9, 1272(%rsp)
	movq	%r8, 1264(%rsp)
	movq	%rdx, 1256(%rsp)
	leaq	1176(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1176(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_RBRACE(%rip), %rax
	jne	.LBB47_2
# %bb.1:
	movq	88(%rsp), %rdx                  # 8-byte Reload
	leaq	1016(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1096(%rsp), %rcx
	leaq	1016(%rsp), %rdx
	callq	ps_adv
	movq	1328(%rsp), %rax
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	movq	1272(%rsp), %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	movq	1264(%rsp), %rcx
	callq	list_len
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	1264(%rsp), %rcx
	callq	rev
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movq	72(%rsp), %r8                   # 8-byte Reload
	movq	80(%rsp), %r9                   # 8-byte Reload
	movq	%rax, %rcx
	callq	t_record
	movq	96(%rsp), %rcx                  # 8-byte Reload
	movq	%rax, %rdx
	leaq	1096(%rsp), %r8
	callq	mk_pr
	jmp	.LBB47_6
.LBB47_2:
	movq	88(%rsp), %rdx                  # 8-byte Reload
	leaq	928(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	928(%rsp), %rcx
	callq	ps_str
	movq	88(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 1008(%rsp)
	leaq	688(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	768(%rsp), %rcx
	leaq	688(%rsp), %rdx
	callq	ps_adv
	leaq	848(%rsp), %rcx
	leaq	768(%rsp), %rdx
	callq	ps_adv
	leaq	520(%rsp), %rcx
	leaq	848(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	600(%rsp), %rcx
	leaq	520(%rsp), %rdx
	callq	parse_type_expr
	movq	600(%rsp), %rdx
	movq	1008(%rsp), %rcx
	callq	mk_fi
	movq	%rax, 512(%rsp)
	leaq	600(%rsp), %rdx
	addq	$8, %rdx
	leaq	352(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	352(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_COMMA(%rip), %rax
	jne	.LBB47_4
# %bb.3:
	leaq	600(%rsp), %rdx
	addq	$8, %rdx
	leaq	192(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	272(%rsp), %rcx
	leaq	192(%rsp), %rdx
	callq	ps_adv
	leaq	432(%rsp), %rcx
	leaq	272(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	jmp	.LBB47_5
.LBB47_4:
	leaq	600(%rsp), %rdx
	addq	$8, %rdx
	leaq	432(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
.LBB47_5:
	movq	1328(%rsp), %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	1272(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	movq	1264(%rsp), %rdx
	movq	512(%rsp), %rcx
	callq	m0_cons
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	leaq	112(%rsp), %rcx
	leaq	432(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	96(%rsp), %rcx                  # 8-byte Reload
	movq	40(%rsp), %r8                   # 8-byte Reload
	movq	48(%rsp), %r9                   # 8-byte Reload
	movq	56(%rsp), %rax                  # 8-byte Reload
	leaq	112(%rsp), %rdx
	movq	%rax, 32(%rsp)
	callq	gather_type_fields
.LBB47_6:
	movq	104(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$1288, %rsp                     # imm = 0x508
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_type_expr;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_type_expr                 # -- Begin function parse_type_expr
	.p2align	4
parse_type_expr:                        # @parse_type_expr
.seh_proc parse_type_expr
# %bb.0:
	subq	$152, %rsp
	.seh_stackalloc 152
	.seh_endprologue
	movq	%rcx, 40(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	movq	%rcx, 144(%rsp)
	movq	%rdx, 136(%rsp)
	leaq	56(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	40(%rsp), %rcx                  # 8-byte Reload
	leaq	56(%rsp), %rdx
	callq	parse_type_arrow
	movq	48(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$152, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	gather_ctors;
	.scl	2;
	.type	32;
	.endef
	.globl	gather_ctors                    # -- Begin function gather_ctors
	.p2align	4
gather_ctors:                           # @gather_ctors
.seh_proc gather_ctors
# %bb.0:
	subq	$1576, %rsp                     # imm = 0x628
	.seh_stackalloc 1576
	.seh_endprologue
	movq	%rdx, 120(%rsp)                 # 8-byte Spill
	movq	%rcx, 104(%rsp)                 # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 112(%rsp)                 # 8-byte Spill
	movq	1616(%rsp), %rax
	movq	%rcx, 1568(%rsp)
	movq	%r9, 1560(%rsp)
	movq	%r8, 1552(%rsp)
	movq	%rdx, 1544(%rsp)
	leaq	1456(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1456(%rsp), %rcx
	callq	ps_str
	movq	120(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 1536(%rsp)
	leaq	1296(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1376(%rsp), %rcx
	leaq	1296(%rsp), %rdx
	callq	ps_adv
	leaq	1128(%rsp), %rcx
	leaq	1376(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	1128(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_LPAREN(%rip), %rax
	jne	.LBB49_2
# %bb.1:
	leaq	880(%rsp), %rcx
	leaq	1376(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	960(%rsp), %rcx
	leaq	880(%rsp), %rdx
	callq	ps_adv
	leaq	1040(%rsp), %rcx
	leaq	960(%rsp), %rdx
	callq	parse_type_expr
	leaq	1040(%rsp), %rdx
	addq	$8, %rdx
	leaq	632(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	712(%rsp), %rcx
	leaq	632(%rsp), %rdx
	callq	ps_adv
	movq	1040(%rsp), %rdx
	leaq	792(%rsp), %rcx
	leaq	712(%rsp), %r8
	callq	mk_pr
	leaq	1208(%rsp), %rcx
	leaq	792(%rsp), %rdx
	movl	$88, %r8d
	callq	memcpy
	jmp	.LBB49_3
.LBB49_2:
	leaq	464(%rsp), %rcx
	leaq	1376(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	544(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	leaq	464(%rsp), %r8
	callq	mk_pr
	leaq	1208(%rsp), %rcx
	leaq	544(%rsp), %rdx
	movl	$88, %r8d
	callq	memcpy
.LBB49_3:
	movq	1208(%rsp), %rdx
	movq	1536(%rsp), %rcx
	callq	mk_ctor
	movq	%rax, 456(%rsp)
	movq	1552(%rsp), %rdx
	movq	456(%rsp), %rcx
	callq	m0_cons
	movq	%rax, 448(%rsp)
	leaq	1208(%rsp), %rdx
	addq	$8, %rdx
	leaq	368(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	368(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_PIPE(%rip), %rax
	jne	.LBB49_5
# %bb.4:
	movq	1616(%rsp), %rax
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	movq	1560(%rsp), %rax
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	movq	448(%rsp), %rax
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	leaq	1208(%rsp), %rdx
	addq	$8, %rdx
	leaq	208(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	288(%rsp), %rcx
	leaq	208(%rsp), %rdx
	callq	ps_adv
	movq	104(%rsp), %rcx                 # 8-byte Reload
	movq	80(%rsp), %r8                   # 8-byte Reload
	movq	88(%rsp), %r9                   # 8-byte Reload
	movq	96(%rsp), %rax                  # 8-byte Reload
	leaq	288(%rsp), %rdx
	movq	%rax, 32(%rsp)
	callq	gather_ctors
	jmp	.LBB49_6
.LBB49_5:
	leaq	1208(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	1616(%rsp), %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	1560(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	movq	448(%rsp), %rcx
	callq	list_len
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	movq	448(%rsp), %rcx
	callq	rev
	movq	40(%rsp), %rdx                  # 8-byte Reload
	movq	48(%rsp), %r8                   # 8-byte Reload
	movq	56(%rsp), %r9                   # 8-byte Reload
	movq	%rax, %rcx
	callq	t_sum
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	leaq	128(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	104(%rsp), %rcx                 # 8-byte Reload
	movq	72(%rsp), %rdx                  # 8-byte Reload
	leaq	128(%rsp), %r8
	callq	mk_pr
.LBB49_6:
	movq	112(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$1576, %rsp                     # imm = 0x628
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_type_atom;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_type_atom                 # -- Begin function parse_type_atom
	.p2align	4
parse_type_atom:                        # @parse_type_atom
.seh_proc parse_type_atom
# %bb.0:
	subq	$1800, %rsp                     # imm = 0x708
	.seh_stackalloc 1800
	.seh_endprologue
	movq	%rdx, 144(%rsp)                 # 8-byte Spill
	movq	%rcx, 128(%rsp)                 # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 136(%rsp)                 # 8-byte Spill
	movq	%rcx, 1792(%rsp)
	movq	%rdx, 1784(%rsp)
	leaq	1696(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1696(%rsp), %rcx
	callq	ps_kind
	movq	144(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 1776(%rsp)
	leaq	1608(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1608(%rsp), %rcx
	callq	ps_line
	movq	144(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 1688(%rsp)
	leaq	1520(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1520(%rsp), %rcx
	callq	ps_col
	movq	%rax, 1600(%rsp)
	movq	1776(%rsp), %rax
	cmpq	TK_IDENT(%rip), %rax
	jne	.LBB50_2
# %bb.1:
	movq	144(%rsp), %rdx                 # 8-byte Reload
	leaq	1360(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1440(%rsp), %rcx
	leaq	1360(%rsp), %rdx
	callq	ps_adv
	movq	144(%rsp), %rdx                 # 8-byte Reload
	movq	1600(%rsp), %rax
	movq	%rax, 120(%rsp)                 # 8-byte Spill
	movq	1688(%rsp), %rax
	movq	%rax, 112(%rsp)                 # 8-byte Spill
	leaq	1280(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1280(%rsp), %rcx
	callq	ps_str
	movq	112(%rsp), %rdx                 # 8-byte Reload
	movq	120(%rsp), %r8                  # 8-byte Reload
	movq	%rax, %rcx
	callq	t_name
	movq	128(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	1440(%rsp), %r8
	callq	mk_pr
	jmp	.LBB50_11
.LBB50_2:
	movq	1776(%rsp), %rax
	cmpq	TK_INT(%rip), %rax
	jne	.LBB50_4
# %bb.3:
	movq	144(%rsp), %rdx                 # 8-byte Reload
	leaq	1120(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1200(%rsp), %rcx
	leaq	1120(%rsp), %rdx
	callq	ps_adv
	movq	144(%rsp), %rdx                 # 8-byte Reload
	movq	1600(%rsp), %rax
	movq	%rax, 104(%rsp)                 # 8-byte Spill
	movq	1688(%rsp), %rax
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	leaq	1040(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1040(%rsp), %rcx
	callq	ps_str
	movq	96(%rsp), %rdx                  # 8-byte Reload
	movq	104(%rsp), %r8                  # 8-byte Reload
	movq	%rax, %rcx
	callq	t_name
	movq	128(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	1200(%rsp), %r8
	callq	mk_pr
	jmp	.LBB50_11
.LBB50_4:
	movq	1776(%rsp), %rax
	cmpq	TK_LBRACE(%rip), %rax
	jne	.LBB50_6
# %bb.5:
	movq	144(%rsp), %rdx                 # 8-byte Reload
	movq	1600(%rsp), %rax
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	movq	1688(%rsp), %rax
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	movq	m0_nil(%rip), %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	leaq	880(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	960(%rsp), %rcx
	leaq	880(%rsp), %rdx
	callq	ps_adv
	movq	128(%rsp), %rcx                 # 8-byte Reload
	movq	72(%rsp), %r8                   # 8-byte Reload
	movq	80(%rsp), %r9                   # 8-byte Reload
	movq	88(%rsp), %rax                  # 8-byte Reload
	leaq	960(%rsp), %rdx
	movq	%rax, 32(%rsp)
	callq	gather_type_fields
	jmp	.LBB50_11
.LBB50_6:
	movq	1776(%rsp), %rax
	cmpq	TK_PIPE(%rip), %rax
	jne	.LBB50_8
# %bb.7:
	movq	144(%rsp), %rdx                 # 8-byte Reload
	movq	1600(%rsp), %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	1688(%rsp), %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	m0_nil(%rip), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	720(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	800(%rsp), %rcx
	leaq	720(%rsp), %rdx
	callq	ps_adv
	movq	128(%rsp), %rcx                 # 8-byte Reload
	movq	48(%rsp), %r8                   # 8-byte Reload
	movq	56(%rsp), %r9                   # 8-byte Reload
	movq	64(%rsp), %rax                  # 8-byte Reload
	leaq	800(%rsp), %rdx
	movq	%rax, 32(%rsp)
	callq	gather_ctors
	jmp	.LBB50_11
.LBB50_8:
	movq	1776(%rsp), %rax
	cmpq	TK_LPAREN(%rip), %rax
	jne	.LBB50_10
# %bb.9:
	movq	144(%rsp), %rdx                 # 8-byte Reload
	leaq	472(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	552(%rsp), %rcx
	leaq	472(%rsp), %rdx
	callq	ps_adv
	leaq	632(%rsp), %rcx
	leaq	552(%rsp), %rdx
	callq	parse_type_expr
	leaq	632(%rsp), %rdx
	addq	$8, %rdx
	leaq	312(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	392(%rsp), %rcx
	leaq	312(%rsp), %rdx
	callq	ps_adv
	movq	128(%rsp), %rcx                 # 8-byte Reload
	movq	632(%rsp), %rdx
	leaq	392(%rsp), %r8
	callq	mk_pr
	jmp	.LBB50_11
.LBB50_10:
	movq	144(%rsp), %rdx                 # 8-byte Reload
	leaq	152(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	232(%rsp), %rcx
	leaq	152(%rsp), %rdx
	callq	ps_err
	movq	1600(%rsp), %rdx
	movq	1688(%rsp), %rcx
	callq	n_unit
	movq	128(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	232(%rsp), %r8
	callq	mk_pr
.LBB50_11:
	movq	136(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$1800, %rsp                     # imm = 0x708
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_type_app_ga;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_type_app_ga               # -- Begin function parse_type_app_ga
	.p2align	4
parse_type_app_ga:                      # @parse_type_app_ga
.seh_proc parse_type_app_ga
# %bb.0:
	subq	$968, %rsp                      # imm = 0x3C8
	.seh_stackalloc 968
	.seh_endprologue
	movq	%r8, 104(%rsp)                  # 8-byte Spill
	movq	%rdx, %rax
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	%rcx, 112(%rsp)                 # 8-byte Spill
	movq	%rcx, %r8
	movq	%r8, 120(%rsp)                  # 8-byte Spill
	movq	1016(%rsp), %r8
	movq	1008(%rsp), %r8
	movq	%rcx, 960(%rsp)
	movq	%r9, 952(%rsp)
	movq	%rdx, 944(%rsp)
	movq	%rax, 936(%rsp)
	leaq	856(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	856(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_RPAREN(%rip), %rax
	jne	.LBB51_2
# %bb.1:
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	696(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	776(%rsp), %rcx
	leaq	696(%rsp), %rdx
	callq	ps_adv
	movq	1016(%rsp), %rax
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	movq	1008(%rsp), %rax
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	movq	952(%rsp), %rcx
	callq	list_len
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	movq	952(%rsp), %rcx
	callq	rev
	movq	80(%rsp), %r8                   # 8-byte Reload
	movq	88(%rsp), %r9                   # 8-byte Reload
	movq	%rax, %rdx
	movq	96(%rsp), %rax                  # 8-byte Reload
	movq	936(%rsp), %rcx
	movq	%rax, 32(%rsp)
	callq	t_app
	movq	112(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	776(%rsp), %r8
	callq	mk_pr
	jmp	.LBB51_6
.LBB51_2:
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	528(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	608(%rsp), %rcx
	leaq	528(%rsp), %rdx
	callq	parse_type_expr
	leaq	608(%rsp), %rdx
	addq	$8, %rdx
	leaq	368(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	368(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_COMMA(%rip), %rax
	jne	.LBB51_4
# %bb.3:
	leaq	608(%rsp), %rdx
	addq	$8, %rdx
	leaq	208(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	288(%rsp), %rcx
	leaq	208(%rsp), %rdx
	callq	ps_adv
	leaq	448(%rsp), %rcx
	leaq	288(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	jmp	.LBB51_5
.LBB51_4:
	leaq	608(%rsp), %rdx
	addq	$8, %rdx
	leaq	448(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
.LBB51_5:
	movq	1016(%rsp), %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	movq	1008(%rsp), %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	952(%rsp), %rdx
	movq	608(%rsp), %rcx
	callq	m0_cons
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	936(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	128(%rsp), %rcx
	leaq	448(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	112(%rsp), %rcx                 # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	movq	56(%rsp), %r9                   # 8-byte Reload
	movq	64(%rsp), %r10                  # 8-byte Reload
	movq	72(%rsp), %rax                  # 8-byte Reload
	leaq	128(%rsp), %r8
	movq	%r10, 32(%rsp)
	movq	%rax, 40(%rsp)
	callq	parse_type_app_ga
.LBB51_6:
	movq	120(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$968, %rsp                      # imm = 0x3C8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_type_app;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_type_app                  # -- Begin function parse_type_app
	.p2align	4
parse_type_app:                         # @parse_type_app
.seh_proc parse_type_app
# %bb.0:
	subq	$696, %rsp                      # imm = 0x2B8
	.seh_stackalloc 696
	.seh_endprologue
	movq	%rcx, 80(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	movq	%rcx, 688(%rsp)
	movq	%rdx, 680(%rsp)
	leaq	512(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	592(%rsp), %rcx
	leaq	512(%rsp), %rdx
	callq	parse_type_atom
	leaq	592(%rsp), %rdx
	addq	$8, %rdx
	leaq	432(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	432(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_LPAREN(%rip), %rax
	jne	.LBB52_2
# %bb.1:
	leaq	592(%rsp), %rdx
	addq	$8, %rdx
	leaq	344(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	344(%rsp), %rcx
	callq	ps_line
	movq	%rax, 424(%rsp)
	leaq	592(%rsp), %rdx
	addq	$8, %rdx
	leaq	256(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	256(%rsp), %rcx
	callq	ps_col
	movq	%rax, 336(%rsp)
	movq	336(%rsp), %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	movq	424(%rsp), %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	m0_nil(%rip), %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	592(%rsp), %rdx
	addq	$8, %rdx
	leaq	96(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	176(%rsp), %rcx
	leaq	96(%rsp), %rdx
	callq	ps_adv
	movq	80(%rsp), %rcx                  # 8-byte Reload
	movq	56(%rsp), %r9                   # 8-byte Reload
	movq	64(%rsp), %r10                  # 8-byte Reload
	movq	72(%rsp), %rax                  # 8-byte Reload
	movq	592(%rsp), %rdx
	leaq	176(%rsp), %r8
	movq	%r10, 32(%rsp)
	movq	%rax, 40(%rsp)
	callq	parse_type_app_ga
	jmp	.LBB52_3
.LBB52_2:
	movq	80(%rsp), %rcx                  # 8-byte Reload
	leaq	592(%rsp), %rdx
	movl	$88, %r8d
	callq	memcpy
.LBB52_3:
	movq	88(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$696, %rsp                      # imm = 0x2B8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_type_arrow;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_type_arrow                # -- Begin function parse_type_arrow
	.p2align	4
parse_type_arrow:                       # @parse_type_arrow
.seh_proc parse_type_arrow
# %bb.0:
	subq	$856, %rsp                      # imm = 0x358
	.seh_stackalloc 856
	.seh_endprologue
	movq	%rcx, 88(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	movq	%rcx, 848(%rsp)
	movq	%rdx, 840(%rsp)
	leaq	672(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	752(%rsp), %rcx
	leaq	672(%rsp), %rdx
	callq	parse_type_app
	leaq	752(%rsp), %rdx
	addq	$8, %rdx
	leaq	592(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	592(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_ARROW(%rip), %rax
	jne	.LBB53_2
# %bb.1:
	leaq	752(%rsp), %rdx
	addq	$8, %rdx
	leaq	344(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	424(%rsp), %rcx
	leaq	344(%rsp), %rdx
	callq	ps_adv
	leaq	504(%rsp), %rcx
	leaq	424(%rsp), %rdx
	callq	parse_type_arrow
	leaq	504(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	leaq	752(%rsp), %rdx
	addq	$8, %rdx
	leaq	264(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	264(%rsp), %rcx
	callq	ps_col
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	leaq	752(%rsp), %rdx
	addq	$8, %rdx
	leaq	184(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	184(%rsp), %rcx
	callq	ps_line
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	504(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	movq	m0_nil(%rip), %rdx
	movq	752(%rsp), %rcx
	callq	m0_cons
	movq	48(%rsp), %r8                   # 8-byte Reload
	movq	56(%rsp), %r9                   # 8-byte Reload
	movq	%rax, %rcx
	movq	64(%rsp), %rax                  # 8-byte Reload
	movl	$1, %edx
	movq	%rax, 32(%rsp)
	callq	t_fn
	movq	72(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	leaq	104(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	88(%rsp), %rcx                  # 8-byte Reload
	movq	80(%rsp), %rdx                  # 8-byte Reload
	leaq	104(%rsp), %r8
	callq	mk_pr
	jmp	.LBB53_3
.LBB53_2:
	movq	88(%rsp), %rcx                  # 8-byte Reload
	leaq	752(%rsp), %rdx
	movl	$88, %r8d
	callq	memcpy
.LBB53_3:
	movq	96(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$856, %rsp                      # imm = 0x358
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	gather_params;
	.scl	2;
	.type	32;
	.endef
	.globl	gather_params                   # -- Begin function gather_params
	.p2align	4
gather_params:                          # @gather_params
.seh_proc gather_params
# %bb.0:
	subq	$1240, %rsp                     # imm = 0x4D8
	.seh_stackalloc 1240
	.seh_endprologue
	movq	%rdx, 48(%rsp)                  # 8-byte Spill
	movq	%rcx, 56(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	%rcx, 1232(%rsp)
	movq	%r8, 1224(%rsp)
	movq	%rdx, 1216(%rsp)
	leaq	1136(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1136(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_RPAREN(%rip), %rax
	jne	.LBB54_2
# %bb.1:
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	976(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1056(%rsp), %rcx
	leaq	976(%rsp), %rdx
	callq	ps_adv
	movq	1224(%rsp), %rcx
	callq	rev
	movq	56(%rsp), %rcx                  # 8-byte Reload
	movq	%rax, %rdx
	leaq	1056(%rsp), %r8
	callq	mk_pr
	jmp	.LBB54_6
.LBB54_2:
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	888(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	888(%rsp), %rcx
	callq	ps_str
	movq	48(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 968(%rsp)
	leaq	648(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	728(%rsp), %rcx
	leaq	648(%rsp), %rdx
	callq	ps_adv
	leaq	808(%rsp), %rcx
	leaq	728(%rsp), %rdx
	callq	ps_adv
	leaq	480(%rsp), %rcx
	leaq	808(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	560(%rsp), %rcx
	leaq	480(%rsp), %rdx
	callq	parse_type_expr
	movq	560(%rsp), %rdx
	movq	968(%rsp), %rcx
	callq	mk_param
	movq	%rax, 472(%rsp)
	leaq	560(%rsp), %rdx
	addq	$8, %rdx
	leaq	312(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	312(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_COMMA(%rip), %rax
	jne	.LBB54_4
# %bb.3:
	leaq	560(%rsp), %rdx
	addq	$8, %rdx
	leaq	152(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	232(%rsp), %rcx
	leaq	152(%rsp), %rdx
	callq	ps_adv
	leaq	392(%rsp), %rcx
	leaq	232(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	jmp	.LBB54_5
.LBB54_4:
	leaq	560(%rsp), %rdx
	addq	$8, %rdx
	leaq	392(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
.LBB54_5:
	movq	1224(%rsp), %rdx
	movq	472(%rsp), %rcx
	callq	m0_cons
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	leaq	72(%rsp), %rcx
	leaq	392(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	56(%rsp), %rcx                  # 8-byte Reload
	movq	40(%rsp), %r8                   # 8-byte Reload
	leaq	72(%rsp), %rdx
	callq	gather_params
.LBB54_6:
	movq	64(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$1240, %rsp                     # imm = 0x4D8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_pat_atom;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_pat_atom                  # -- Begin function parse_pat_atom
	.p2align	4
parse_pat_atom:                         # @parse_pat_atom
.seh_proc parse_pat_atom
# %bb.0:
	subq	$2040, %rsp                     # imm = 0x7F8
	.seh_stackalloc 2040
	.seh_endprologue
	movq	%rdx, 136(%rsp)                 # 8-byte Spill
	movq	%rcx, 120(%rsp)                 # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 128(%rsp)                 # 8-byte Spill
	movq	%rcx, 2032(%rsp)
	movq	%rdx, 2024(%rsp)
	leaq	1936(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1936(%rsp), %rcx
	callq	ps_kind
	movq	136(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 2016(%rsp)
	leaq	1848(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1848(%rsp), %rcx
	callq	ps_line
	movq	136(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 1928(%rsp)
	leaq	1760(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1760(%rsp), %rcx
	callq	ps_col
	movq	%rax, 1840(%rsp)
	movq	2016(%rsp), %rax
	cmpq	TK_INT(%rip), %rax
	jne	.LBB55_2
# %bb.1:
	movq	136(%rsp), %rdx                 # 8-byte Reload
	leaq	1600(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1680(%rsp), %rcx
	leaq	1600(%rsp), %rdx
	callq	ps_adv
	movq	136(%rsp), %rdx                 # 8-byte Reload
	movq	1840(%rsp), %rax
	movq	%rax, 112(%rsp)                 # 8-byte Spill
	movq	1928(%rsp), %rax
	movq	%rax, 104(%rsp)                 # 8-byte Spill
	movq	1840(%rsp), %rax
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	movq	1928(%rsp), %rax
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	leaq	1520(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1520(%rsp), %rcx
	callq	ps_int
	movq	88(%rsp), %rdx                  # 8-byte Reload
	movq	96(%rsp), %r8                   # 8-byte Reload
	movq	%rax, %rcx
	callq	n_int
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	112(%rsp), %r8                  # 8-byte Reload
	movq	%rax, %rcx
	callq	p_lit
	movq	120(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	1680(%rsp), %r8
	callq	mk_pr
	jmp	.LBB55_13
.LBB55_2:
	movq	2016(%rsp), %rax
	cmpq	TK_TRUE(%rip), %rax
	jne	.LBB55_4
# %bb.3:
	movq	136(%rsp), %rdx                 # 8-byte Reload
	leaq	1360(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1440(%rsp), %rcx
	leaq	1360(%rsp), %rdx
	callq	ps_adv
	movq	1840(%rsp), %rax
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	movq	1928(%rsp), %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	movq	1840(%rsp), %r8
	movq	1928(%rsp), %rdx
	movl	$1, %ecx
	callq	n_bool
	movq	72(%rsp), %rdx                  # 8-byte Reload
	movq	80(%rsp), %r8                   # 8-byte Reload
	movq	%rax, %rcx
	callq	p_lit
	movq	120(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	1440(%rsp), %r8
	callq	mk_pr
	jmp	.LBB55_13
.LBB55_4:
	movq	2016(%rsp), %rax
	cmpq	TK_FALSE(%rip), %rax
	jne	.LBB55_6
# %bb.5:
	movq	136(%rsp), %rdx                 # 8-byte Reload
	leaq	1200(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1280(%rsp), %rcx
	leaq	1200(%rsp), %rdx
	callq	ps_adv
	movq	1840(%rsp), %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	1928(%rsp), %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	1840(%rsp), %r8
	movq	1928(%rsp), %rdx
	xorl	%eax, %eax
	movl	%eax, %ecx
	callq	n_bool
	movq	56(%rsp), %rdx                  # 8-byte Reload
	movq	64(%rsp), %r8                   # 8-byte Reload
	movq	%rax, %rcx
	callq	p_lit
	movq	120(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	1280(%rsp), %r8
	callq	mk_pr
	jmp	.LBB55_13
.LBB55_6:
	movq	2016(%rsp), %rax
	cmpq	TK_IDENT(%rip), %rax
	jne	.LBB55_12
# %bb.7:
	movq	136(%rsp), %rdx                 # 8-byte Reload
	leaq	1112(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1112(%rsp), %rcx
	callq	ps_str
	movq	136(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 1192(%rsp)
	leaq	952(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1032(%rsp), %rcx
	leaq	952(%rsp), %rdx
	callq	ps_adv
	movq	1192(%rsp), %rcx
	leaq	"??_C@_01IDAFKMJL@_?$AA@"(%rip), %rdx
	callq	m0_string_eq
	cmpq	$1, %rax
	jne	.LBB55_9
# %bb.8:
	movq	1840(%rsp), %rdx
	movq	1928(%rsp), %rcx
	callq	p_wild
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	872(%rsp), %rcx
	leaq	1032(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	120(%rsp), %rcx                 # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	872(%rsp), %r8
	callq	mk_pr
	jmp	.LBB55_13
.LBB55_9:
	leaq	792(%rsp), %rcx
	leaq	1032(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	792(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_LPAREN(%rip), %rax
	jne	.LBB55_11
# %bb.10:
	leaq	544(%rsp), %rcx
	leaq	1032(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	624(%rsp), %rcx
	leaq	544(%rsp), %rdx
	callq	ps_adv
	leaq	704(%rsp), %rcx
	leaq	624(%rsp), %rdx
	callq	parse_pat_atom
	leaq	704(%rsp), %rdx
	addq	$8, %rdx
	leaq	384(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	464(%rsp), %rcx
	leaq	384(%rsp), %rdx
	callq	ps_adv
	movq	1840(%rsp), %r9
	movq	1928(%rsp), %r8
	movq	704(%rsp), %rdx
	movq	1192(%rsp), %rcx
	callq	p_ctor
	movq	120(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	464(%rsp), %r8
	callq	mk_pr
	jmp	.LBB55_13
.LBB55_11:
	movq	1840(%rsp), %r8
	movq	1928(%rsp), %rdx
	movq	1192(%rsp), %rcx
	callq	p_name
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	leaq	304(%rsp), %rcx
	leaq	1032(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	120(%rsp), %rcx                 # 8-byte Reload
	movq	40(%rsp), %rdx                  # 8-byte Reload
	leaq	304(%rsp), %r8
	callq	mk_pr
	jmp	.LBB55_13
.LBB55_12:
	movq	136(%rsp), %rdx                 # 8-byte Reload
	leaq	144(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	224(%rsp), %rcx
	leaq	144(%rsp), %rdx
	callq	ps_err
	movq	1840(%rsp), %rdx
	movq	1928(%rsp), %rcx
	callq	p_wild
	movq	120(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	224(%rsp), %r8
	callq	mk_pr
.LBB55_13:
	movq	128(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$2040, %rsp                     # imm = 0x7F8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	gather_args;
	.scl	2;
	.type	32;
	.endef
	.globl	gather_args                     # -- Begin function gather_args
	.p2align	4
gather_args:                            # @gather_args
.seh_proc gather_args
# %bb.0:
	subq	$904, %rsp                      # imm = 0x388
	.seh_stackalloc 904
	.seh_endprologue
	movq	%rdx, 48(%rsp)                  # 8-byte Spill
	movq	%rcx, 56(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	%rcx, 896(%rsp)
	movq	%r8, 888(%rsp)
	movq	%rdx, 880(%rsp)
	leaq	800(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	800(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_RPAREN(%rip), %rax
	jne	.LBB56_2
# %bb.1:
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	640(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	720(%rsp), %rcx
	leaq	640(%rsp), %rdx
	callq	ps_adv
	movq	888(%rsp), %rcx
	callq	rev
	movq	56(%rsp), %rcx                  # 8-byte Reload
	movq	%rax, %rdx
	leaq	720(%rsp), %r8
	callq	mk_pr
	jmp	.LBB56_6
.LBB56_2:
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	472(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	552(%rsp), %rcx
	leaq	472(%rsp), %rdx
	callq	parse_impl
	leaq	552(%rsp), %rdx
	addq	$8, %rdx
	leaq	312(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	312(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_COMMA(%rip), %rax
	jne	.LBB56_4
# %bb.3:
	leaq	552(%rsp), %rdx
	addq	$8, %rdx
	leaq	152(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	232(%rsp), %rcx
	leaq	152(%rsp), %rdx
	callq	ps_adv
	leaq	392(%rsp), %rcx
	leaq	232(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	jmp	.LBB56_5
.LBB56_4:
	leaq	552(%rsp), %rdx
	addq	$8, %rdx
	leaq	392(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
.LBB56_5:
	movq	888(%rsp), %rdx
	movq	552(%rsp), %rcx
	callq	m0_cons
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	leaq	72(%rsp), %rcx
	leaq	392(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	56(%rsp), %rcx                  # 8-byte Reload
	movq	40(%rsp), %r8                   # 8-byte Reload
	leaq	72(%rsp), %rdx
	callq	gather_args
.LBB56_6:
	movq	64(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$904, %rsp                      # imm = 0x388
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_impl;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_impl                      # -- Begin function parse_impl
	.p2align	4
parse_impl:                             # @parse_impl
.seh_proc parse_impl
# %bb.0:
	subq	$840, %rsp                      # imm = 0x348
	.seh_stackalloc 840
	.seh_endprologue
	movq	%rcx, 72(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	movq	%rcx, 832(%rsp)
	movq	%rdx, 824(%rsp)
	leaq	656(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	736(%rsp), %rcx
	leaq	656(%rsp), %rdx
	callq	parse_or
	leaq	736(%rsp), %rdx
	addq	$8, %rdx
	leaq	576(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	576(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_ARROW(%rip), %rax
	jne	.LBB57_2
# %bb.1:
	leaq	736(%rsp), %rdx
	addq	$8, %rdx
	leaq	328(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	408(%rsp), %rcx
	leaq	328(%rsp), %rdx
	callq	ps_adv
	leaq	488(%rsp), %rcx
	leaq	408(%rsp), %rdx
	callq	parse_impl
	leaq	488(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	736(%rsp), %rdx
	addq	$8, %rdx
	leaq	248(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	248(%rsp), %rcx
	callq	ps_col
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	736(%rsp), %rdx
	addq	$8, %rdx
	leaq	168(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	168(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	48(%rsp), %rax                  # 8-byte Reload
	movq	488(%rsp), %r8
	movq	736(%rsp), %rdx
	movq	OP_IMPL(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	56(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	leaq	88(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	72(%rsp), %rcx                  # 8-byte Reload
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	88(%rsp), %r8
	callq	mk_pr
	jmp	.LBB57_3
.LBB57_2:
	movq	72(%rsp), %rcx                  # 8-byte Reload
	leaq	736(%rsp), %rdx
	movl	$88, %r8d
	callq	memcpy
.LBB57_3:
	movq	80(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$840, %rsp                      # imm = 0x348
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_postfix_loop;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_postfix_loop              # -- Begin function parse_postfix_loop
	.p2align	4
parse_postfix_loop:                     # @parse_postfix_loop
.seh_proc parse_postfix_loop
# %bb.0:
	subq	$1448, %rsp                     # imm = 0x5A8
	.seh_stackalloc 1448
	.seh_endprologue
	movq	%r8, 104(%rsp)                  # 8-byte Spill
	movq	%rdx, %rax
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	%rcx, 112(%rsp)                 # 8-byte Spill
	movq	%rcx, %r8
	movq	%r8, 120(%rsp)                  # 8-byte Spill
	movq	%rcx, 1440(%rsp)
	movq	%rdx, 1432(%rsp)
	movq	%rax, 1424(%rsp)
	leaq	1344(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1344(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_DOT(%rip), %rax
	jne	.LBB58_2
# %bb.1:
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	1176(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1256(%rsp), %rcx
	leaq	1176(%rsp), %rdx
	callq	ps_adv
	leaq	1256(%rsp), %rcx
	callq	ps_str
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 1336(%rsp)
	leaq	936(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1016(%rsp), %rcx
	leaq	936(%rsp), %rdx
	callq	ps_adv
	leaq	1096(%rsp), %rcx
	leaq	1016(%rsp), %rdx
	callq	ps_adv
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	856(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	856(%rsp), %rcx
	callq	ps_col
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	leaq	776(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	776(%rsp), %rcx
	callq	ps_line
	movq	96(%rsp), %r9                   # 8-byte Reload
	movq	%rax, %r8
	movq	1336(%rsp), %rdx
	movq	1424(%rsp), %rcx
	callq	n_field
	movq	112(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	1096(%rsp), %r8
	callq	parse_postfix_loop
	jmp	.LBB58_5
.LBB58_2:
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	696(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	696(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_LPAREN(%rip), %rax
	jne	.LBB58_4
# %bb.3:
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	m0_nil(%rip), %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	448(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	528(%rsp), %rcx
	leaq	448(%rsp), %rdx
	callq	ps_adv
	movq	56(%rsp), %r8                   # 8-byte Reload
	leaq	608(%rsp), %rcx
	leaq	528(%rsp), %rdx
	callq	gather_args
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	608(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	leaq	368(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	368(%rsp), %rcx
	callq	ps_col
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	leaq	288(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	288(%rsp), %rcx
	callq	ps_line
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	608(%rsp), %rcx
	callq	list_len
	movq	64(%rsp), %r9                   # 8-byte Reload
	movq	%rax, %r8
	movq	72(%rsp), %rax                  # 8-byte Reload
	movq	608(%rsp), %rdx
	movq	1424(%rsp), %rcx
	movq	%rax, 32(%rsp)
	callq	n_call
	movq	80(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	leaq	208(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	112(%rsp), %rcx                 # 8-byte Reload
	movq	88(%rsp), %rdx                  # 8-byte Reload
	leaq	208(%rsp), %r8
	callq	parse_postfix_loop
	jmp	.LBB58_5
.LBB58_4:
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	1424(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	128(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	112(%rsp), %rcx                 # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	128(%rsp), %r8
	callq	mk_pr
.LBB58_5:
	movq	120(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$1448, %rsp                     # imm = 0x5A8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_postfix;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_postfix                   # -- Begin function parse_postfix
	.p2align	4
parse_postfix:                          # @parse_postfix
.seh_proc parse_postfix
# %bb.0:
	subq	$328, %rsp                      # imm = 0x148
	.seh_stackalloc 328
	.seh_endprologue
	movq	%rcx, 40(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	%rcx, 320(%rsp)
	movq	%rdx, 312(%rsp)
	leaq	144(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	224(%rsp), %rcx
	leaq	144(%rsp), %rdx
	callq	parse_atom
	leaq	224(%rsp), %rdx
	addq	$8, %rdx
	movq	224(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	64(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	40(%rsp), %rcx                  # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	64(%rsp), %r8
	callq	parse_postfix_loop
	movq	56(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$328, %rsp                      # imm = 0x148
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_atom;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_atom                      # -- Begin function parse_atom
	.p2align	4
parse_atom:                             # @parse_atom
.seh_proc parse_atom
# %bb.0:
	movl	$6616, %eax                     # imm = 0x19D8
	callq	__chkstk
	subq	%rax, %rsp
	.seh_stackalloc 6616
	.seh_endprologue
	movq	%rdx, 216(%rsp)                 # 8-byte Spill
	movq	%rcx, 200(%rsp)                 # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 208(%rsp)                 # 8-byte Spill
	movq	%rcx, 6608(%rsp)
	movq	%rdx, 6600(%rsp)
	leaq	6512(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	6512(%rsp), %rcx
	callq	ps_kind
	movq	216(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 6592(%rsp)
	leaq	6424(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	6424(%rsp), %rcx
	callq	ps_line
	movq	216(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 6504(%rsp)
	leaq	6336(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	6336(%rsp), %rcx
	callq	ps_col
	movq	%rax, 6416(%rsp)
	movq	6592(%rsp), %rax
	cmpq	TK_INT(%rip), %rax
	jne	.LBB60_2
# %bb.1:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	leaq	6176(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	6256(%rsp), %rcx
	leaq	6176(%rsp), %rdx
	callq	ps_adv
	movq	216(%rsp), %rdx                 # 8-byte Reload
	movq	6416(%rsp), %rax
	movq	%rax, 192(%rsp)                 # 8-byte Spill
	movq	6504(%rsp), %rax
	movq	%rax, 184(%rsp)                 # 8-byte Spill
	leaq	6096(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	6096(%rsp), %rcx
	callq	ps_int
	movq	184(%rsp), %rdx                 # 8-byte Reload
	movq	192(%rsp), %r8                  # 8-byte Reload
	movq	%rax, %rcx
	callq	n_int
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	6256(%rsp), %r8
	callq	mk_pr
	jmp	.LBB60_31
.LBB60_2:
	movq	6592(%rsp), %rax
	cmpq	TK_STRING(%rip), %rax
	jne	.LBB60_4
# %bb.3:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	leaq	5936(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	6016(%rsp), %rcx
	leaq	5936(%rsp), %rdx
	callq	ps_adv
	movq	216(%rsp), %rdx                 # 8-byte Reload
	movq	6416(%rsp), %rax
	movq	%rax, 176(%rsp)                 # 8-byte Spill
	movq	6504(%rsp), %rax
	movq	%rax, 168(%rsp)                 # 8-byte Spill
	leaq	5856(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	5856(%rsp), %rcx
	callq	ps_str
	movq	168(%rsp), %rdx                 # 8-byte Reload
	movq	176(%rsp), %r8                  # 8-byte Reload
	movq	%rax, %rcx
	callq	n_str
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	6016(%rsp), %r8
	callq	mk_pr
	jmp	.LBB60_31
.LBB60_4:
	movq	6592(%rsp), %rax
	cmpq	TK_TRUE(%rip), %rax
	jne	.LBB60_6
# %bb.5:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	leaq	5696(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	5776(%rsp), %rcx
	leaq	5696(%rsp), %rdx
	callq	ps_adv
	movq	6416(%rsp), %r8
	movq	6504(%rsp), %rdx
	movl	$1, %ecx
	callq	n_bool
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	5776(%rsp), %r8
	callq	mk_pr
	jmp	.LBB60_31
.LBB60_6:
	movq	6592(%rsp), %rax
	cmpq	TK_FALSE(%rip), %rax
	jne	.LBB60_8
# %bb.7:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	leaq	5536(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	5616(%rsp), %rcx
	leaq	5536(%rsp), %rdx
	callq	ps_adv
	movq	6416(%rsp), %r8
	movq	6504(%rsp), %rdx
	xorl	%eax, %eax
	movl	%eax, %ecx
	callq	n_bool
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	5616(%rsp), %r8
	callq	mk_pr
	jmp	.LBB60_31
.LBB60_8:
	movq	6592(%rsp), %rax
	cmpq	TK_UNIT(%rip), %rax
	jne	.LBB60_10
# %bb.9:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	leaq	5376(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	5456(%rsp), %rcx
	leaq	5376(%rsp), %rdx
	callq	ps_adv
	movq	6416(%rsp), %rdx
	movq	6504(%rsp), %rcx
	callq	n_unit
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	5456(%rsp), %r8
	callq	mk_pr
	jmp	.LBB60_31
.LBB60_10:
	movq	6592(%rsp), %rax
	cmpq	TK_IDENT(%rip), %rax
	jne	.LBB60_12
# %bb.11:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	leaq	5216(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	5296(%rsp), %rcx
	leaq	5216(%rsp), %rdx
	callq	ps_adv
	movq	216(%rsp), %rdx                 # 8-byte Reload
	movq	6416(%rsp), %rax
	movq	%rax, 160(%rsp)                 # 8-byte Spill
	movq	6504(%rsp), %rax
	movq	%rax, 152(%rsp)                 # 8-byte Spill
	leaq	5136(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	5136(%rsp), %rcx
	callq	ps_str
	movq	152(%rsp), %rdx                 # 8-byte Reload
	movq	160(%rsp), %r8                  # 8-byte Reload
	movq	%rax, %rcx
	callq	n_name
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	5296(%rsp), %r8
	callq	mk_pr
	jmp	.LBB60_31
.LBB60_12:
	movq	6592(%rsp), %rax
	cmpq	TK_LET(%rip), %rax
	jne	.LBB60_14
# %bb.13:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	leaq	4968(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	5048(%rsp), %rcx
	leaq	4968(%rsp), %rdx
	callq	ps_adv
	leaq	5048(%rsp), %rcx
	callq	ps_str
	movq	216(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 5128(%rsp)
	leaq	4648(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	4728(%rsp), %rcx
	leaq	4648(%rsp), %rdx
	callq	ps_adv
	leaq	4808(%rsp), %rcx
	leaq	4728(%rsp), %rdx
	callq	ps_adv
	leaq	4888(%rsp), %rcx
	leaq	4808(%rsp), %rdx
	callq	ps_adv
	leaq	4480(%rsp), %rcx
	leaq	4888(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	4560(%rsp), %rcx
	leaq	4480(%rsp), %rdx
	callq	parse_type_expr
	leaq	4560(%rsp), %rdx
	addq	$8, %rdx
	leaq	4320(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	4400(%rsp), %rcx
	leaq	4320(%rsp), %rdx
	callq	ps_adv
	leaq	4152(%rsp), %rcx
	leaq	4400(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	4232(%rsp), %rcx
	leaq	4152(%rsp), %rdx
	callq	parse_expr
	leaq	4232(%rsp), %rdx
	addq	$8, %rdx
	leaq	3992(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	4072(%rsp), %rcx
	leaq	3992(%rsp), %rdx
	callq	ps_adv
	leaq	3824(%rsp), %rcx
	leaq	4072(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	3904(%rsp), %rcx
	leaq	3824(%rsp), %rdx
	callq	parse_expr
	leaq	3904(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 136(%rsp)                 # 8-byte Spill
	movq	6416(%rsp), %rax
	movq	6504(%rsp), %r10
	movq	3904(%rsp), %r9
	movq	4232(%rsp), %r8
	movq	4560(%rsp), %rdx
	movq	5128(%rsp), %rcx
	movq	%r10, 32(%rsp)
	movq	%rax, 40(%rsp)
	callq	n_let
	movq	136(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 144(%rsp)                 # 8-byte Spill
	leaq	3744(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	144(%rsp), %rdx                 # 8-byte Reload
	leaq	3744(%rsp), %r8
	callq	mk_pr
	jmp	.LBB60_31
.LBB60_14:
	movq	6592(%rsp), %rax
	cmpq	TK_MATCH(%rip), %rax
	jne	.LBB60_16
# %bb.15:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	leaq	3496(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	3576(%rsp), %rcx
	leaq	3496(%rsp), %rdx
	callq	ps_adv
	leaq	3656(%rsp), %rcx
	leaq	3576(%rsp), %rdx
	callq	parse_expr
	movq	m0_nil(%rip), %rax
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	leaq	3656(%rsp), %rdx
	addq	$8, %rdx
	leaq	3248(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	3328(%rsp), %rcx
	leaq	3248(%rsp), %rdx
	callq	ps_adv
	movq	96(%rsp), %r8                   # 8-byte Reload
	leaq	3408(%rsp), %rcx
	leaq	3328(%rsp), %rdx
	callq	gather_arms
	leaq	3408(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 120(%rsp)                 # 8-byte Spill
	movq	6416(%rsp), %rax
	movq	%rax, 112(%rsp)                 # 8-byte Spill
	movq	6504(%rsp), %rax
	movq	%rax, 104(%rsp)                 # 8-byte Spill
	movq	3408(%rsp), %rcx
	callq	list_len
	movq	104(%rsp), %r9                  # 8-byte Reload
	movq	%rax, %r8
	movq	112(%rsp), %rax                 # 8-byte Reload
	movq	3408(%rsp), %rdx
	movq	3656(%rsp), %rcx
	movq	%rax, 32(%rsp)
	callq	n_match
	movq	120(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 128(%rsp)                 # 8-byte Spill
	leaq	3168(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	128(%rsp), %rdx                 # 8-byte Reload
	leaq	3168(%rsp), %r8
	callq	mk_pr
	jmp	.LBB60_31
.LBB60_16:
	movq	6592(%rsp), %rax
	cmpq	TK_IF(%rip), %rax
	jne	.LBB60_24
# %bb.17:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	leaq	2920(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	3000(%rsp), %rcx
	leaq	2920(%rsp), %rdx
	callq	ps_adv
	leaq	3080(%rsp), %rcx
	leaq	3000(%rsp), %rdx
	callq	parse_expr
	leaq	3080(%rsp), %rdx
	addq	$8, %rdx
	leaq	2760(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	2840(%rsp), %rcx
	leaq	2760(%rsp), %rdx
	callq	ps_adv
	leaq	2592(%rsp), %rcx
	leaq	2840(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	2672(%rsp), %rcx
	leaq	2592(%rsp), %rdx
	callq	parse_expr
	leaq	2672(%rsp), %rdx
	addq	$8, %rdx
	leaq	2432(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	2512(%rsp), %rcx
	leaq	2432(%rsp), %rdx
	callq	ps_adv
	leaq	2264(%rsp), %rcx
	leaq	2512(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	2264(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_ELSE(%rip), %rax
	jne	.LBB60_22
# %bb.18:
	leaq	2104(%rsp), %rcx
	leaq	2512(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	2184(%rsp), %rcx
	leaq	2104(%rsp), %rdx
	callq	ps_adv
	leaq	2184(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_LBRACE(%rip), %rax
	jne	.LBB60_20
# %bb.19:
	leaq	1856(%rsp), %rcx
	leaq	2512(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	1936(%rsp), %rcx
	leaq	1856(%rsp), %rdx
	callq	ps_adv
	leaq	2016(%rsp), %rcx
	leaq	1936(%rsp), %rdx
	callq	parse_expr
	leaq	2016(%rsp), %rdx
	addq	$8, %rdx
	leaq	1608(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1688(%rsp), %rcx
	leaq	1608(%rsp), %rdx
	callq	ps_adv
	movq	2016(%rsp), %rdx
	leaq	1768(%rsp), %rcx
	leaq	1688(%rsp), %r8
	callq	mk_pr
	leaq	2344(%rsp), %rcx
	leaq	1768(%rsp), %rdx
	movl	$88, %r8d
	callq	memcpy
	jmp	.LBB60_21
.LBB60_20:
	leaq	1360(%rsp), %rcx
	leaq	2512(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	1440(%rsp), %rcx
	leaq	1360(%rsp), %rdx
	callq	ps_adv
	leaq	1520(%rsp), %rcx
	leaq	1440(%rsp), %rdx
	callq	parse_expr
	leaq	2344(%rsp), %rcx
	leaq	1520(%rsp), %rdx
	movl	$88, %r8d
	callq	memcpy
.LBB60_21:
	jmp	.LBB60_23
.LBB60_22:
	movq	6416(%rsp), %rdx
	movq	6504(%rsp), %rcx
	callq	n_unit
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	leaq	1192(%rsp), %rcx
	leaq	2512(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	88(%rsp), %rdx                  # 8-byte Reload
	leaq	1272(%rsp), %rcx
	leaq	1192(%rsp), %r8
	callq	mk_pr
	leaq	2344(%rsp), %rcx
	leaq	1272(%rsp), %rdx
	movl	$88, %r8d
	callq	memcpy
.LBB60_23:
	leaq	2344(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	movq	6416(%rsp), %rax
	movq	6504(%rsp), %r9
	movq	2344(%rsp), %r8
	movq	2672(%rsp), %rdx
	movq	3080(%rsp), %rcx
	movq	%rax, 32(%rsp)
	callq	n_if
	movq	72(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	leaq	1112(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	80(%rsp), %rdx                  # 8-byte Reload
	leaq	1112(%rsp), %r8
	callq	mk_pr
	jmp	.LBB60_31
.LBB60_24:
	movq	6592(%rsp), %rax
	cmpq	TK_LBRACE(%rip), %rax
	jne	.LBB60_26
# %bb.25:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	movq	m0_nil(%rip), %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	leaq	952(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1032(%rsp), %rcx
	leaq	952(%rsp), %rdx
	callq	ps_adv
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	64(%rsp), %r8                   # 8-byte Reload
	leaq	1032(%rsp), %rdx
	callq	gather_field_inits
	jmp	.LBB60_31
.LBB60_26:
	movq	6592(%rsp), %rax
	cmpq	TK_LBRACK(%rip), %rax
	jne	.LBB60_28
# %bb.27:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	movq	m0_nil(%rip), %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	792(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	872(%rsp), %rcx
	leaq	792(%rsp), %rdx
	callq	ps_adv
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	56(%rsp), %r8                   # 8-byte Reload
	leaq	872(%rsp), %rdx
	callq	gather_list_elems
	jmp	.LBB60_31
.LBB60_28:
	movq	6592(%rsp), %rax
	cmpq	TK_LPAREN(%rip), %rax
	jne	.LBB60_30
# %bb.29:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	leaq	544(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	624(%rsp), %rcx
	leaq	544(%rsp), %rdx
	callq	ps_adv
	leaq	704(%rsp), %rcx
	leaq	624(%rsp), %rdx
	callq	parse_expr
	leaq	704(%rsp), %rdx
	addq	$8, %rdx
	leaq	384(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	464(%rsp), %rcx
	leaq	384(%rsp), %rdx
	callq	ps_adv
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	704(%rsp), %rdx
	leaq	464(%rsp), %r8
	callq	mk_pr
	jmp	.LBB60_31
.LBB60_30:
	movq	216(%rsp), %rdx                 # 8-byte Reload
	leaq	224(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	304(%rsp), %rcx
	leaq	224(%rsp), %rdx
	callq	ps_err
	movq	6416(%rsp), %rdx
	movq	6504(%rsp), %rcx
	callq	n_unit
	movq	200(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	304(%rsp), %r8
	callq	mk_pr
.LBB60_31:
	movq	208(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$6616, %rsp                     # imm = 0x19D8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_unary;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_unary                     # -- Begin function parse_unary
	.p2align	4
parse_unary:                            # @parse_unary
.seh_proc parse_unary
# %bb.0:
	subq	$1528, %rsp                     # imm = 0x5F8
	.seh_stackalloc 1528
	.seh_endprologue
	movq	%rdx, 112(%rsp)                 # 8-byte Spill
	movq	%rcx, 120(%rsp)                 # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 128(%rsp)                 # 8-byte Spill
	movq	%rcx, 1520(%rsp)
	movq	%rdx, 1512(%rsp)
	leaq	1432(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1432(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_NOT(%rip), %rax
	jne	.LBB61_2
# %bb.1:
	movq	112(%rsp), %rdx                 # 8-byte Reload
	leaq	1184(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1264(%rsp), %rcx
	leaq	1184(%rsp), %rdx
	callq	ps_adv
	leaq	1344(%rsp), %rcx
	leaq	1264(%rsp), %rdx
	callq	parse_unary
	movq	112(%rsp), %rdx                 # 8-byte Reload
	leaq	1344(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	leaq	1104(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1104(%rsp), %rcx
	callq	ps_col
	movq	112(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	leaq	1024(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1024(%rsp), %rcx
	callq	ps_line
	movq	88(%rsp), %r8                   # 8-byte Reload
	movq	%rax, %rdx
	movq	1344(%rsp), %rcx
	callq	n_not
	movq	96(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 104(%rsp)                 # 8-byte Spill
	leaq	944(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	120(%rsp), %rcx                 # 8-byte Reload
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	944(%rsp), %r8
	callq	mk_pr
	jmp	.LBB61_5
.LBB61_2:
	movq	112(%rsp), %rdx                 # 8-byte Reload
	leaq	864(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	864(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_MINUS(%rip), %rax
	jne	.LBB61_4
# %bb.3:
	movq	112(%rsp), %rdx                 # 8-byte Reload
	leaq	616(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	696(%rsp), %rcx
	leaq	616(%rsp), %rdx
	callq	ps_adv
	leaq	776(%rsp), %rcx
	leaq	696(%rsp), %rdx
	callq	parse_unary
	movq	112(%rsp), %rdx                 # 8-byte Reload
	leaq	776(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	leaq	536(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	536(%rsp), %rcx
	callq	ps_col
	movq	112(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	leaq	456(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	456(%rsp), %rcx
	callq	ps_line
	movq	112(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	776(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	376(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	376(%rsp), %rcx
	callq	ps_col
	movq	112(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	leaq	296(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	296(%rsp), %rcx
	callq	ps_line
	movq	40(%rsp), %r8                   # 8-byte Reload
	movq	%rax, %rdx
	xorl	%eax, %eax
	movl	%eax, %ecx
	callq	n_int
	movq	48(%rsp), %r8                   # 8-byte Reload
	movq	56(%rsp), %r9                   # 8-byte Reload
	movq	%rax, %rdx
	movq	64(%rsp), %rax                  # 8-byte Reload
	movq	OP_SUB(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	72(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	leaq	216(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	120(%rsp), %rcx                 # 8-byte Reload
	movq	80(%rsp), %rdx                  # 8-byte Reload
	leaq	216(%rsp), %r8
	callq	mk_pr
	jmp	.LBB61_5
.LBB61_4:
	movq	112(%rsp), %rdx                 # 8-byte Reload
	leaq	136(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	120(%rsp), %rcx                 # 8-byte Reload
	leaq	136(%rsp), %rdx
	callq	parse_postfix
.LBB61_5:
	movq	128(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$1528, %rsp                     # imm = 0x5F8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_mul_loop;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_mul_loop                  # -- Begin function parse_mul_loop
	.p2align	4
parse_mul_loop:                         # @parse_mul_loop
.seh_proc parse_mul_loop
# %bb.0:
	subq	$1960, %rsp                     # imm = 0x7A8
	.seh_stackalloc 1960
	.seh_endprologue
	movq	%r8, 128(%rsp)                  # 8-byte Spill
	movq	%rdx, %rax
	movq	128(%rsp), %rdx                 # 8-byte Reload
	movq	%rcx, 136(%rsp)                 # 8-byte Spill
	movq	%rcx, %r8
	movq	%r8, 144(%rsp)                  # 8-byte Spill
	movq	%rcx, 1952(%rsp)
	movq	%rdx, 1944(%rsp)
	movq	%rax, 1936(%rsp)
	leaq	1856(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1856(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_STAR(%rip), %rax
	jne	.LBB62_2
# %bb.1:
	movq	128(%rsp), %rdx                 # 8-byte Reload
	leaq	1608(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1688(%rsp), %rcx
	leaq	1608(%rsp), %rdx
	callq	ps_adv
	leaq	1768(%rsp), %rcx
	leaq	1688(%rsp), %rdx
	callq	parse_unary
	movq	128(%rsp), %rdx                 # 8-byte Reload
	leaq	1768(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 112(%rsp)                 # 8-byte Spill
	leaq	1528(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1528(%rsp), %rcx
	callq	ps_col
	movq	128(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 104(%rsp)                 # 8-byte Spill
	leaq	1448(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1448(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	104(%rsp), %rax                 # 8-byte Reload
	movq	1768(%rsp), %r8
	movq	1936(%rsp), %rdx
	movq	OP_MUL(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	112(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 120(%rsp)                 # 8-byte Spill
	leaq	1368(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	136(%rsp), %rcx                 # 8-byte Reload
	movq	120(%rsp), %rdx                 # 8-byte Reload
	leaq	1368(%rsp), %r8
	callq	parse_mul_loop
	jmp	.LBB62_7
.LBB62_2:
	movq	128(%rsp), %rdx                 # 8-byte Reload
	leaq	1288(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1288(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_SLASH(%rip), %rax
	jne	.LBB62_4
# %bb.3:
	movq	128(%rsp), %rdx                 # 8-byte Reload
	leaq	1040(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1120(%rsp), %rcx
	leaq	1040(%rsp), %rdx
	callq	ps_adv
	leaq	1200(%rsp), %rcx
	leaq	1120(%rsp), %rdx
	callq	parse_unary
	movq	128(%rsp), %rdx                 # 8-byte Reload
	leaq	1200(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	leaq	960(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	960(%rsp), %rcx
	callq	ps_col
	movq	128(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	leaq	880(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	880(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	80(%rsp), %rax                  # 8-byte Reload
	movq	1200(%rsp), %r8
	movq	1936(%rsp), %rdx
	movq	OP_DIV(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	88(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	leaq	800(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	136(%rsp), %rcx                 # 8-byte Reload
	movq	96(%rsp), %rdx                  # 8-byte Reload
	leaq	800(%rsp), %r8
	callq	parse_mul_loop
	jmp	.LBB62_7
.LBB62_4:
	movq	128(%rsp), %rdx                 # 8-byte Reload
	leaq	720(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	720(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_PERCENT(%rip), %rax
	jne	.LBB62_6
# %bb.5:
	movq	128(%rsp), %rdx                 # 8-byte Reload
	leaq	472(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	552(%rsp), %rcx
	leaq	472(%rsp), %rdx
	callq	ps_adv
	leaq	632(%rsp), %rcx
	leaq	552(%rsp), %rdx
	callq	parse_unary
	movq	128(%rsp), %rdx                 # 8-byte Reload
	leaq	632(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	leaq	392(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	392(%rsp), %rcx
	callq	ps_col
	movq	128(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	312(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	312(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	56(%rsp), %rax                  # 8-byte Reload
	movq	632(%rsp), %r8
	movq	1936(%rsp), %rdx
	movq	OP_MOD(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	leaq	232(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	136(%rsp), %rcx                 # 8-byte Reload
	movq	72(%rsp), %rdx                  # 8-byte Reload
	leaq	232(%rsp), %r8
	callq	parse_mul_loop
	jmp	.LBB62_7
.LBB62_6:
	movq	128(%rsp), %rdx                 # 8-byte Reload
	movq	1936(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	152(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	136(%rsp), %rcx                 # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	152(%rsp), %r8
	callq	mk_pr
.LBB62_7:
	movq	144(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$1960, %rsp                     # imm = 0x7A8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_mul;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_mul                       # -- Begin function parse_mul
	.p2align	4
parse_mul:                              # @parse_mul
.seh_proc parse_mul
# %bb.0:
	subq	$328, %rsp                      # imm = 0x148
	.seh_stackalloc 328
	.seh_endprologue
	movq	%rcx, 40(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	%rcx, 320(%rsp)
	movq	%rdx, 312(%rsp)
	leaq	144(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	224(%rsp), %rcx
	leaq	144(%rsp), %rdx
	callq	parse_unary
	leaq	224(%rsp), %rdx
	addq	$8, %rdx
	movq	224(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	64(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	40(%rsp), %rcx                  # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	64(%rsp), %r8
	callq	parse_mul_loop
	movq	56(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$328, %rsp                      # imm = 0x148
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_add_loop;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_add_loop                  # -- Begin function parse_add_loop
	.p2align	4
parse_add_loop:                         # @parse_add_loop
.seh_proc parse_add_loop
# %bb.0:
	subq	$1368, %rsp                     # imm = 0x558
	.seh_stackalloc 1368
	.seh_endprologue
	movq	%r8, 104(%rsp)                  # 8-byte Spill
	movq	%rdx, %rax
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	%rcx, 112(%rsp)                 # 8-byte Spill
	movq	%rcx, %r8
	movq	%r8, 120(%rsp)                  # 8-byte Spill
	movq	%rcx, 1360(%rsp)
	movq	%rdx, 1352(%rsp)
	movq	%rax, 1344(%rsp)
	leaq	1264(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1264(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_PLUS(%rip), %rax
	jne	.LBB64_2
# %bb.1:
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	1016(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1096(%rsp), %rcx
	leaq	1016(%rsp), %rdx
	callq	ps_adv
	leaq	1176(%rsp), %rcx
	leaq	1096(%rsp), %rdx
	callq	parse_mul
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	1176(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	leaq	936(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	936(%rsp), %rcx
	callq	ps_col
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	leaq	856(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	856(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	80(%rsp), %rax                  # 8-byte Reload
	movq	1176(%rsp), %r8
	movq	1344(%rsp), %rdx
	movq	OP_ADD(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	88(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	leaq	776(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	112(%rsp), %rcx                 # 8-byte Reload
	movq	96(%rsp), %rdx                  # 8-byte Reload
	leaq	776(%rsp), %r8
	callq	parse_add_loop
	jmp	.LBB64_5
.LBB64_2:
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	696(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	696(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_MINUS(%rip), %rax
	jne	.LBB64_4
# %bb.3:
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	448(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	528(%rsp), %rcx
	leaq	448(%rsp), %rdx
	callq	ps_adv
	leaq	608(%rsp), %rcx
	leaq	528(%rsp), %rdx
	callq	parse_mul
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	608(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	leaq	368(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	368(%rsp), %rcx
	callq	ps_col
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	288(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	288(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	56(%rsp), %rax                  # 8-byte Reload
	movq	608(%rsp), %r8
	movq	1344(%rsp), %rdx
	movq	OP_SUB(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	leaq	208(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	112(%rsp), %rcx                 # 8-byte Reload
	movq	72(%rsp), %rdx                  # 8-byte Reload
	leaq	208(%rsp), %r8
	callq	parse_add_loop
	jmp	.LBB64_5
.LBB64_4:
	movq	104(%rsp), %rdx                 # 8-byte Reload
	movq	1344(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	128(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	112(%rsp), %rcx                 # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	128(%rsp), %r8
	callq	mk_pr
.LBB64_5:
	movq	120(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$1368, %rsp                     # imm = 0x558
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_add;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_add                       # -- Begin function parse_add
	.p2align	4
parse_add:                              # @parse_add
.seh_proc parse_add
# %bb.0:
	subq	$328, %rsp                      # imm = 0x148
	.seh_stackalloc 328
	.seh_endprologue
	movq	%rcx, 40(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	%rcx, 320(%rsp)
	movq	%rdx, 312(%rsp)
	leaq	144(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	224(%rsp), %rcx
	leaq	144(%rsp), %rdx
	callq	parse_mul
	leaq	224(%rsp), %rdx
	addq	$8, %rdx
	movq	224(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	64(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	40(%rsp), %rcx                  # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	64(%rsp), %r8
	callq	parse_add_loop
	movq	56(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$328, %rsp                      # imm = 0x148
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_cmp;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_cmp                       # -- Begin function parse_cmp
	.p2align	4
parse_cmp:                              # @parse_cmp
.seh_proc parse_cmp
# %bb.0:
	subq	$3400, %rsp                     # imm = 0xD48
	.seh_stackalloc 3400
	.seh_endprologue
	movq	%rcx, 184(%rsp)                 # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 192(%rsp)                 # 8-byte Spill
	movq	%rcx, 3392(%rsp)
	movq	%rdx, 3384(%rsp)
	leaq	3216(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	3296(%rsp), %rcx
	leaq	3216(%rsp), %rdx
	callq	parse_add
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	3128(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	3128(%rsp), %rcx
	callq	ps_kind
	movq	%rax, 3208(%rsp)
	movq	3208(%rsp), %rax
	cmpq	TK_EQEQ(%rip), %rax
	jne	.LBB66_2
# %bb.1:
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	2880(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	2960(%rsp), %rcx
	leaq	2880(%rsp), %rdx
	callq	ps_adv
	leaq	3040(%rsp), %rcx
	leaq	2960(%rsp), %rdx
	callq	parse_add
	leaq	3040(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 168(%rsp)                 # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	2800(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	2800(%rsp), %rcx
	callq	ps_col
	movq	%rax, 160(%rsp)                 # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	2720(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	2720(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	160(%rsp), %rax                 # 8-byte Reload
	movq	3040(%rsp), %r8
	movq	3296(%rsp), %rdx
	movq	OP_EQ(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	168(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 176(%rsp)                 # 8-byte Spill
	leaq	2640(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	184(%rsp), %rcx                 # 8-byte Reload
	movq	176(%rsp), %rdx                 # 8-byte Reload
	leaq	2640(%rsp), %r8
	callq	mk_pr
	jmp	.LBB66_13
.LBB66_2:
	movq	3208(%rsp), %rax
	cmpq	TK_NEQ(%rip), %rax
	jne	.LBB66_4
# %bb.3:
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	2392(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	2472(%rsp), %rcx
	leaq	2392(%rsp), %rdx
	callq	ps_adv
	leaq	2552(%rsp), %rcx
	leaq	2472(%rsp), %rdx
	callq	parse_add
	leaq	2552(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 144(%rsp)                 # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	2312(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	2312(%rsp), %rcx
	callq	ps_col
	movq	%rax, 136(%rsp)                 # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	2232(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	2232(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	136(%rsp), %rax                 # 8-byte Reload
	movq	2552(%rsp), %r8
	movq	3296(%rsp), %rdx
	movq	OP_NEQ(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	144(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 152(%rsp)                 # 8-byte Spill
	leaq	2152(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	184(%rsp), %rcx                 # 8-byte Reload
	movq	152(%rsp), %rdx                 # 8-byte Reload
	leaq	2152(%rsp), %r8
	callq	mk_pr
	jmp	.LBB66_13
.LBB66_4:
	movq	3208(%rsp), %rax
	cmpq	TK_LT(%rip), %rax
	jne	.LBB66_6
# %bb.5:
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	1904(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1984(%rsp), %rcx
	leaq	1904(%rsp), %rdx
	callq	ps_adv
	leaq	2064(%rsp), %rcx
	leaq	1984(%rsp), %rdx
	callq	parse_add
	leaq	2064(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 120(%rsp)                 # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	1824(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1824(%rsp), %rcx
	callq	ps_col
	movq	%rax, 112(%rsp)                 # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	1744(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1744(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	112(%rsp), %rax                 # 8-byte Reload
	movq	2064(%rsp), %r8
	movq	3296(%rsp), %rdx
	movq	OP_LT(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	120(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 128(%rsp)                 # 8-byte Spill
	leaq	1664(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	184(%rsp), %rcx                 # 8-byte Reload
	movq	128(%rsp), %rdx                 # 8-byte Reload
	leaq	1664(%rsp), %r8
	callq	mk_pr
	jmp	.LBB66_13
.LBB66_6:
	movq	3208(%rsp), %rax
	cmpq	TK_GT(%rip), %rax
	jne	.LBB66_8
# %bb.7:
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	1416(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1496(%rsp), %rcx
	leaq	1416(%rsp), %rdx
	callq	ps_adv
	leaq	1576(%rsp), %rcx
	leaq	1496(%rsp), %rdx
	callq	parse_add
	leaq	1576(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	1336(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1336(%rsp), %rcx
	callq	ps_col
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	1256(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1256(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	88(%rsp), %rax                  # 8-byte Reload
	movq	1576(%rsp), %r8
	movq	3296(%rsp), %rdx
	movq	OP_GT(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	96(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 104(%rsp)                 # 8-byte Spill
	leaq	1176(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	184(%rsp), %rcx                 # 8-byte Reload
	movq	104(%rsp), %rdx                 # 8-byte Reload
	leaq	1176(%rsp), %r8
	callq	mk_pr
	jmp	.LBB66_13
.LBB66_8:
	movq	3208(%rsp), %rax
	cmpq	TK_LE(%rip), %rax
	jne	.LBB66_10
# %bb.9:
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	928(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1008(%rsp), %rcx
	leaq	928(%rsp), %rdx
	callq	ps_adv
	leaq	1088(%rsp), %rcx
	leaq	1008(%rsp), %rdx
	callq	parse_add
	leaq	1088(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	848(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	848(%rsp), %rcx
	callq	ps_col
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	768(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	768(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	64(%rsp), %rax                  # 8-byte Reload
	movq	1088(%rsp), %r8
	movq	3296(%rsp), %rdx
	movq	OP_LE(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	72(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	leaq	688(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	184(%rsp), %rcx                 # 8-byte Reload
	movq	80(%rsp), %rdx                  # 8-byte Reload
	leaq	688(%rsp), %r8
	callq	mk_pr
	jmp	.LBB66_13
.LBB66_10:
	movq	3208(%rsp), %rax
	cmpq	TK_GE(%rip), %rax
	jne	.LBB66_12
# %bb.11:
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	440(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	520(%rsp), %rcx
	leaq	440(%rsp), %rdx
	callq	ps_adv
	leaq	600(%rsp), %rcx
	leaq	520(%rsp), %rdx
	callq	parse_add
	leaq	600(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	360(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	360(%rsp), %rcx
	callq	ps_col
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	leaq	3296(%rsp), %rdx
	addq	$8, %rdx
	leaq	280(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	280(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	40(%rsp), %rax                  # 8-byte Reload
	movq	600(%rsp), %r8
	movq	3296(%rsp), %rdx
	movq	OP_GE(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	48(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	200(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	184(%rsp), %rcx                 # 8-byte Reload
	movq	56(%rsp), %rdx                  # 8-byte Reload
	leaq	200(%rsp), %r8
	callq	mk_pr
	jmp	.LBB66_13
.LBB66_12:
	movq	184(%rsp), %rcx                 # 8-byte Reload
	leaq	3296(%rsp), %rdx
	movl	$88, %r8d
	callq	memcpy
.LBB66_13:
	movq	192(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$3400, %rsp                     # imm = 0xD48
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_and_loop;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_and_loop                  # -- Begin function parse_and_loop
	.p2align	4
parse_and_loop:                         # @parse_and_loop
.seh_proc parse_and_loop
# %bb.0:
	subq	$776, %rsp                      # imm = 0x308
	.seh_stackalloc 776
	.seh_endprologue
	movq	%r8, 80(%rsp)                   # 8-byte Spill
	movq	%rdx, %rax
	movq	80(%rsp), %rdx                  # 8-byte Reload
	movq	%rcx, 88(%rsp)                  # 8-byte Spill
	movq	%rcx, %r8
	movq	%r8, 96(%rsp)                   # 8-byte Spill
	movq	%rcx, 768(%rsp)
	movq	%rdx, 760(%rsp)
	movq	%rax, 752(%rsp)
	leaq	672(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	672(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_AND(%rip), %rax
	jne	.LBB67_2
# %bb.1:
	movq	80(%rsp), %rdx                  # 8-byte Reload
	leaq	424(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	504(%rsp), %rcx
	leaq	424(%rsp), %rdx
	callq	ps_adv
	leaq	584(%rsp), %rcx
	leaq	504(%rsp), %rdx
	callq	parse_cmp
	movq	80(%rsp), %rdx                  # 8-byte Reload
	leaq	584(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	leaq	344(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	344(%rsp), %rcx
	callq	ps_col
	movq	80(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	264(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	264(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	56(%rsp), %rax                  # 8-byte Reload
	movq	584(%rsp), %r8
	movq	752(%rsp), %rdx
	movq	OP_AND(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	leaq	184(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	88(%rsp), %rcx                  # 8-byte Reload
	movq	72(%rsp), %rdx                  # 8-byte Reload
	leaq	184(%rsp), %r8
	callq	parse_and_loop
	jmp	.LBB67_3
.LBB67_2:
	movq	80(%rsp), %rdx                  # 8-byte Reload
	movq	752(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	104(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	88(%rsp), %rcx                  # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	104(%rsp), %r8
	callq	mk_pr
.LBB67_3:
	movq	96(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$776, %rsp                      # imm = 0x308
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_and;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_and                       # -- Begin function parse_and
	.p2align	4
parse_and:                              # @parse_and
.seh_proc parse_and
# %bb.0:
	subq	$328, %rsp                      # imm = 0x148
	.seh_stackalloc 328
	.seh_endprologue
	movq	%rcx, 40(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	%rcx, 320(%rsp)
	movq	%rdx, 312(%rsp)
	leaq	144(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	224(%rsp), %rcx
	leaq	144(%rsp), %rdx
	callq	parse_cmp
	leaq	224(%rsp), %rdx
	addq	$8, %rdx
	movq	224(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	64(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	40(%rsp), %rcx                  # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	64(%rsp), %r8
	callq	parse_and_loop
	movq	56(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$328, %rsp                      # imm = 0x148
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_or_loop;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_or_loop                   # -- Begin function parse_or_loop
	.p2align	4
parse_or_loop:                          # @parse_or_loop
.seh_proc parse_or_loop
# %bb.0:
	subq	$776, %rsp                      # imm = 0x308
	.seh_stackalloc 776
	.seh_endprologue
	movq	%r8, 80(%rsp)                   # 8-byte Spill
	movq	%rdx, %rax
	movq	80(%rsp), %rdx                  # 8-byte Reload
	movq	%rcx, 88(%rsp)                  # 8-byte Spill
	movq	%rcx, %r8
	movq	%r8, 96(%rsp)                   # 8-byte Spill
	movq	%rcx, 768(%rsp)
	movq	%rdx, 760(%rsp)
	movq	%rax, 752(%rsp)
	leaq	672(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	672(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_OR(%rip), %rax
	jne	.LBB69_2
# %bb.1:
	movq	80(%rsp), %rdx                  # 8-byte Reload
	leaq	424(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	504(%rsp), %rcx
	leaq	424(%rsp), %rdx
	callq	ps_adv
	leaq	584(%rsp), %rcx
	leaq	504(%rsp), %rdx
	callq	parse_and
	movq	80(%rsp), %rdx                  # 8-byte Reload
	leaq	584(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	leaq	344(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	344(%rsp), %rcx
	callq	ps_col
	movq	80(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	264(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	264(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	56(%rsp), %rax                  # 8-byte Reload
	movq	584(%rsp), %r8
	movq	752(%rsp), %rdx
	movq	OP_OR(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	leaq	184(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	88(%rsp), %rcx                  # 8-byte Reload
	movq	72(%rsp), %rdx                  # 8-byte Reload
	leaq	184(%rsp), %r8
	callq	parse_or_loop
	jmp	.LBB69_3
.LBB69_2:
	movq	80(%rsp), %rdx                  # 8-byte Reload
	movq	752(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	104(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	88(%rsp), %rcx                  # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	104(%rsp), %r8
	callq	mk_pr
.LBB69_3:
	movq	96(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$776, %rsp                      # imm = 0x308
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_or;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_or                        # -- Begin function parse_or
	.p2align	4
parse_or:                               # @parse_or
.seh_proc parse_or
# %bb.0:
	subq	$328, %rsp                      # imm = 0x148
	.seh_stackalloc 328
	.seh_endprologue
	movq	%rcx, 40(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	%rcx, 320(%rsp)
	movq	%rdx, 312(%rsp)
	leaq	144(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	224(%rsp), %rcx
	leaq	144(%rsp), %rdx
	callq	parse_and
	leaq	224(%rsp), %rdx
	addq	$8, %rdx
	movq	224(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	64(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	40(%rsp), %rcx                  # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	64(%rsp), %r8
	callq	parse_or_loop
	movq	56(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$328, %rsp                      # imm = 0x148
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_expr;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_expr                      # -- Begin function parse_expr
	.p2align	4
parse_expr:                             # @parse_expr
.seh_proc parse_expr
# %bb.0:
	subq	$1240, %rsp                     # imm = 0x4D8
	.seh_stackalloc 1240
	.seh_endprologue
	movq	%rdx, 64(%rsp)                  # 8-byte Spill
	movq	%rcx, 72(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	movq	%rcx, 1232(%rsp)
	movq	%rdx, 1224(%rsp)
	leaq	1144(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1144(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_BIDI(%rip), %rax
	jne	.LBB71_4
# %bb.1:
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	896(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	976(%rsp), %rcx
	leaq	896(%rsp), %rdx
	callq	ps_adv
	leaq	1056(%rsp), %rcx
	leaq	976(%rsp), %rdx
	callq	parse_impl
	leaq	1056(%rsp), %rdx
	addq	$8, %rdx
	leaq	816(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	816(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_BIDI(%rip), %rax
	jne	.LBB71_3
# %bb.2:
	leaq	1056(%rsp), %rdx
	addq	$8, %rdx
	leaq	568(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	648(%rsp), %rcx
	leaq	568(%rsp), %rdx
	callq	ps_adv
	leaq	728(%rsp), %rcx
	leaq	648(%rsp), %rdx
	callq	parse_impl
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	728(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	488(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	488(%rsp), %rcx
	callq	ps_col
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	leaq	408(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	408(%rsp), %rcx
	callq	ps_line
	movq	%rax, %r9
	movq	40(%rsp), %rax                  # 8-byte Reload
	movq	728(%rsp), %r8
	movq	1056(%rsp), %rdx
	movq	OP_IFF(%rip), %rcx
	movq	%rax, 32(%rsp)
	callq	n_bin
	movq	48(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	328(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	72(%rsp), %rcx                  # 8-byte Reload
	movq	56(%rsp), %rdx                  # 8-byte Reload
	leaq	328(%rsp), %r8
	callq	mk_pr
	jmp	.LBB71_5
.LBB71_3:
	leaq	1056(%rsp), %rdx
	addq	$8, %rdx
	leaq	168(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	248(%rsp), %rcx
	leaq	168(%rsp), %rdx
	callq	ps_err
	movq	72(%rsp), %rcx                  # 8-byte Reload
	movq	1056(%rsp), %rdx
	leaq	248(%rsp), %r8
	callq	mk_pr
	jmp	.LBB71_5
.LBB71_4:
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	88(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	72(%rsp), %rcx                  # 8-byte Reload
	leaq	88(%rsp), %rdx
	callq	parse_impl
.LBB71_5:
	movq	80(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$1240, %rsp                     # imm = 0x4D8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	gather_arms;
	.scl	2;
	.type	32;
	.endef
	.globl	gather_arms                     # -- Begin function gather_arms
	.p2align	4
gather_arms:                            # @gather_arms
.seh_proc gather_arms
# %bb.0:
	subq	$1080, %rsp                     # imm = 0x438
	.seh_stackalloc 1080
	.seh_endprologue
	movq	%rdx, 56(%rsp)                  # 8-byte Spill
	movq	%rcx, 64(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	movq	%rcx, 1072(%rsp)
	movq	%r8, 1064(%rsp)
	movq	%rdx, 1056(%rsp)
	leaq	976(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	976(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_RBRACE(%rip), %rax
	jne	.LBB72_2
# %bb.1:
	movq	56(%rsp), %rdx                  # 8-byte Reload
	leaq	816(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	896(%rsp), %rcx
	leaq	816(%rsp), %rdx
	callq	ps_adv
	movq	1064(%rsp), %rcx
	callq	rev
	movq	64(%rsp), %rcx                  # 8-byte Reload
	movq	%rax, %rdx
	leaq	896(%rsp), %r8
	callq	mk_pr
	jmp	.LBB72_3
.LBB72_2:
	movq	56(%rsp), %rdx                  # 8-byte Reload
	leaq	648(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	728(%rsp), %rcx
	leaq	648(%rsp), %rdx
	callq	parse_pat_atom
	leaq	728(%rsp), %rdx
	addq	$8, %rdx
	leaq	488(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	568(%rsp), %rcx
	leaq	488(%rsp), %rdx
	callq	ps_adv
	leaq	320(%rsp), %rcx
	leaq	568(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	400(%rsp), %rcx
	leaq	320(%rsp), %rdx
	callq	parse_expr
	leaq	400(%rsp), %rdx
	addq	$8, %rdx
	leaq	160(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	240(%rsp), %rcx
	leaq	160(%rsp), %rdx
	callq	ps_adv
	movq	1064(%rsp), %rax
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	movq	400(%rsp), %rdx
	movq	728(%rsp), %rcx
	callq	mk_arm
	movq	40(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, %rcx
	callq	m0_cons
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	80(%rsp), %rcx
	leaq	240(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	64(%rsp), %rcx                  # 8-byte Reload
	movq	48(%rsp), %r8                   # 8-byte Reload
	leaq	80(%rsp), %rdx
	callq	gather_arms
.LBB72_3:
	movq	72(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$1080, %rsp                     # imm = 0x438
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	gather_field_inits;
	.scl	2;
	.type	32;
	.endef
	.globl	gather_field_inits              # -- Begin function gather_field_inits
	.p2align	4
gather_field_inits:                     # @gather_field_inits
.seh_proc gather_field_inits
# %bb.0:
	subq	$1240, %rsp                     # imm = 0x4D8
	.seh_stackalloc 1240
	.seh_endprologue
	movq	%rdx, 56(%rsp)                  # 8-byte Spill
	movq	%rcx, 64(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	movq	%rcx, 1232(%rsp)
	movq	%r8, 1224(%rsp)
	movq	%rdx, 1216(%rsp)
	leaq	1136(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1136(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_RBRACE(%rip), %rax
	jne	.LBB73_2
# %bb.1:
	movq	56(%rsp), %rdx                  # 8-byte Reload
	leaq	976(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1056(%rsp), %rcx
	leaq	976(%rsp), %rdx
	callq	ps_adv
	movq	1224(%rsp), %rcx
	callq	rev
	movq	64(%rsp), %rcx                  # 8-byte Reload
	movq	%rax, %rdx
	leaq	1056(%rsp), %r8
	callq	mk_pr
	jmp	.LBB73_6
.LBB73_2:
	movq	56(%rsp), %rdx                  # 8-byte Reload
	leaq	888(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	888(%rsp), %rcx
	callq	ps_str
	movq	56(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 968(%rsp)
	leaq	648(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	728(%rsp), %rcx
	leaq	648(%rsp), %rdx
	callq	ps_adv
	leaq	808(%rsp), %rcx
	leaq	728(%rsp), %rdx
	callq	ps_adv
	leaq	480(%rsp), %rcx
	leaq	808(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	560(%rsp), %rcx
	leaq	480(%rsp), %rdx
	callq	parse_impl
	leaq	560(%rsp), %rdx
	addq	$8, %rdx
	leaq	320(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	320(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_COMMA(%rip), %rax
	jne	.LBB73_4
# %bb.3:
	leaq	560(%rsp), %rdx
	addq	$8, %rdx
	leaq	160(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	240(%rsp), %rcx
	leaq	160(%rsp), %rdx
	callq	ps_adv
	leaq	400(%rsp), %rcx
	leaq	240(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	jmp	.LBB73_5
.LBB73_4:
	leaq	560(%rsp), %rdx
	addq	$8, %rdx
	leaq	400(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
.LBB73_5:
	movq	1224(%rsp), %rax
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	movq	560(%rsp), %rdx
	movq	968(%rsp), %rcx
	callq	mk_fi
	movq	40(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, %rcx
	callq	m0_cons
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	80(%rsp), %rcx
	leaq	400(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	64(%rsp), %rcx                  # 8-byte Reload
	movq	48(%rsp), %r8                   # 8-byte Reload
	leaq	80(%rsp), %rdx
	callq	gather_field_inits
.LBB73_6:
	movq	72(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$1240, %rsp                     # imm = 0x4D8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	gather_list_elems;
	.scl	2;
	.type	32;
	.endef
	.globl	gather_list_elems               # -- Begin function gather_list_elems
	.p2align	4
gather_list_elems:                      # @gather_list_elems
.seh_proc gather_list_elems
# %bb.0:
	subq	$904, %rsp                      # imm = 0x388
	.seh_stackalloc 904
	.seh_endprologue
	movq	%rdx, 48(%rsp)                  # 8-byte Spill
	movq	%rcx, 56(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	%rcx, 896(%rsp)
	movq	%r8, 888(%rsp)
	movq	%rdx, 880(%rsp)
	leaq	800(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	800(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_RBRACK(%rip), %rax
	jne	.LBB74_2
# %bb.1:
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	640(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	720(%rsp), %rcx
	leaq	640(%rsp), %rdx
	callq	ps_adv
	movq	888(%rsp), %rcx
	callq	rev
	movq	56(%rsp), %rcx                  # 8-byte Reload
	movq	%rax, %rdx
	leaq	720(%rsp), %r8
	callq	mk_pr
	jmp	.LBB74_6
.LBB74_2:
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	472(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	552(%rsp), %rcx
	leaq	472(%rsp), %rdx
	callq	parse_impl
	leaq	552(%rsp), %rdx
	addq	$8, %rdx
	leaq	312(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	312(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_COMMA(%rip), %rax
	jne	.LBB74_4
# %bb.3:
	leaq	552(%rsp), %rdx
	addq	$8, %rdx
	leaq	152(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	232(%rsp), %rcx
	leaq	152(%rsp), %rdx
	callq	ps_adv
	leaq	392(%rsp), %rcx
	leaq	232(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	jmp	.LBB74_5
.LBB74_4:
	leaq	552(%rsp), %rdx
	addq	$8, %rdx
	leaq	392(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
.LBB74_5:
	movq	888(%rsp), %rdx
	movq	552(%rsp), %rcx
	callq	m0_cons
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	leaq	72(%rsp), %rcx
	leaq	392(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	56(%rsp), %rcx                  # 8-byte Reload
	movq	40(%rsp), %r8                   # 8-byte Reload
	leaq	72(%rsp), %rdx
	callq	gather_list_elems
.LBB74_6:
	movq	64(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$904, %rsp                      # imm = 0x388
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_decl;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_decl                      # -- Begin function parse_decl
	.p2align	4
parse_decl:                             # @parse_decl
.seh_proc parse_decl
# %bb.0:
	subq	$3800, %rsp                     # imm = 0xED8
	.seh_stackalloc 3800
	.seh_endprologue
	movq	%rdx, 152(%rsp)                 # 8-byte Spill
	movq	%rcx, 160(%rsp)                 # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 168(%rsp)                 # 8-byte Spill
	movq	%rcx, 3792(%rsp)
	movq	%rdx, 3784(%rsp)
	movl	pd_cnt(%rip), %eax
	addl	$1, %eax
	movl	%eax, pd_cnt(%rip)
	cmpl	$20, pd_cnt(%rip)
	jle	.LBB75_2
# %bb.1:
	movq	152(%rsp), %rdx                 # 8-byte Reload
	leaq	3704(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	3704(%rsp), %rcx
	callq	ps_kind
	movq	%rax, 144(%rsp)                 # 8-byte Spill
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	144(%rsp), %r8                  # 8-byte Reload
	movq	%rax, %rcx
	leaq	"??_C@_0P@LLIJJCME@pd?5INF?5k?$DN?$CFlld?6?$AA@"(%rip), %rdx
	callq	fprintf
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	callq	fflush
	movq	152(%rsp), %rdx                 # 8-byte Reload
	leaq	3544(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	3624(%rsp), %rcx
	leaq	3544(%rsp), %rdx
	callq	ps_err
	movq	160(%rsp), %rcx                 # 8-byte Reload
	xorl	%eax, %eax
	movl	%eax, %edx
	leaq	3624(%rsp), %r8
	callq	mk_pr
	jmp	.LBB75_9
.LBB75_2:
	movq	152(%rsp), %rdx                 # 8-byte Reload
	leaq	3456(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	3456(%rsp), %rcx
	callq	ps_kind
	movq	152(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 3536(%rsp)
	leaq	3368(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	3368(%rsp), %rcx
	callq	ps_line
	movq	152(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 3448(%rsp)
	leaq	3280(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	3280(%rsp), %rcx
	callq	ps_col
	movq	%rax, 3360(%rsp)
	movq	3536(%rsp), %rax
	cmpq	TK_TYPE(%rip), %rax
	jne	.LBB75_4
# %bb.3:
	movq	152(%rsp), %rdx                 # 8-byte Reload
	leaq	3112(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	3192(%rsp), %rcx
	leaq	3112(%rsp), %rdx
	callq	ps_adv
	leaq	3192(%rsp), %rcx
	callq	ps_str
	movq	152(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 3272(%rsp)
	leaq	2792(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	2872(%rsp), %rcx
	leaq	2792(%rsp), %rdx
	callq	ps_adv
	leaq	2952(%rsp), %rcx
	leaq	2872(%rsp), %rdx
	callq	ps_adv
	leaq	3032(%rsp), %rcx
	leaq	2952(%rsp), %rdx
	callq	ps_adv
	leaq	2624(%rsp), %rcx
	leaq	3032(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	2704(%rsp), %rcx
	leaq	2624(%rsp), %rdx
	callq	parse_type_expr
	leaq	2704(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 128(%rsp)                 # 8-byte Spill
	movq	3360(%rsp), %r9
	movq	3448(%rsp), %r8
	movq	2704(%rsp), %rdx
	movq	3272(%rsp), %rcx
	callq	n_type_decl
	movq	128(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 136(%rsp)                 # 8-byte Spill
	leaq	2544(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	160(%rsp), %rcx                 # 8-byte Reload
	movq	136(%rsp), %rdx                 # 8-byte Reload
	leaq	2544(%rsp), %r8
	callq	mk_pr
	jmp	.LBB75_9
.LBB75_4:
	movq	3536(%rsp), %rax
	cmpq	TK_FN(%rip), %rax
	jne	.LBB75_6
# %bb.5:
	movq	152(%rsp), %rdx                 # 8-byte Reload
	leaq	2376(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	2456(%rsp), %rcx
	leaq	2376(%rsp), %rdx
	callq	ps_adv
	leaq	2456(%rsp), %rcx
	callq	ps_str
	movq	152(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 2536(%rsp)
	movq	m0_nil(%rip), %rax
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	leaq	1968(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	2048(%rsp), %rcx
	leaq	1968(%rsp), %rdx
	callq	ps_adv
	leaq	2128(%rsp), %rcx
	leaq	2048(%rsp), %rdx
	callq	ps_adv
	leaq	2208(%rsp), %rcx
	leaq	2128(%rsp), %rdx
	callq	ps_adv
	movq	80(%rsp), %r8                   # 8-byte Reload
	leaq	2288(%rsp), %rcx
	leaq	2208(%rsp), %rdx
	callq	gather_params
	leaq	2288(%rsp), %rdx
	addq	$8, %rdx
	leaq	1808(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1888(%rsp), %rcx
	leaq	1808(%rsp), %rdx
	callq	ps_adv
	leaq	1640(%rsp), %rcx
	leaq	1888(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	1720(%rsp), %rcx
	leaq	1640(%rsp), %rdx
	callq	parse_type_expr
	leaq	1720(%rsp), %rdx
	addq	$8, %rdx
	leaq	1480(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1560(%rsp), %rcx
	leaq	1480(%rsp), %rdx
	callq	ps_adv
	leaq	1312(%rsp), %rcx
	leaq	1560(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	1392(%rsp), %rcx
	leaq	1312(%rsp), %rdx
	callq	parse_expr
	leaq	1392(%rsp), %rdx
	addq	$8, %rdx
	leaq	1152(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1232(%rsp), %rcx
	leaq	1152(%rsp), %rdx
	callq	ps_adv
	movq	3360(%rsp), %rax
	movq	%rax, 112(%rsp)                 # 8-byte Spill
	movq	3448(%rsp), %rax
	movq	%rax, 104(%rsp)                 # 8-byte Spill
	movq	1392(%rsp), %rax
	movq	%rax, 96(%rsp)                  # 8-byte Spill
	movq	1720(%rsp), %rax
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	movq	2288(%rsp), %rcx
	callq	list_len
	movq	88(%rsp), %r9                   # 8-byte Reload
	movq	96(%rsp), %r11                  # 8-byte Reload
	movq	104(%rsp), %r10                 # 8-byte Reload
	movq	%rax, %r8
	movq	112(%rsp), %rax                 # 8-byte Reload
	movq	2288(%rsp), %rdx
	movq	2536(%rsp), %rcx
	movq	%r11, 32(%rsp)
	movq	%r10, 40(%rsp)
	movq	%rax, 48(%rsp)
	callq	n_fn_decl
	movq	%rax, 120(%rsp)                 # 8-byte Spill
	leaq	1072(%rsp), %rcx
	leaq	1232(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	160(%rsp), %rcx                 # 8-byte Reload
	movq	120(%rsp), %rdx                 # 8-byte Reload
	leaq	1072(%rsp), %r8
	callq	mk_pr
	jmp	.LBB75_9
.LBB75_6:
	movq	3536(%rsp), %rax
	cmpq	TK_EXTERNAL(%rip), %rax
	jne	.LBB75_8
# %bb.7:
	movq	152(%rsp), %rdx                 # 8-byte Reload
	leaq	904(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	984(%rsp), %rcx
	leaq	904(%rsp), %rdx
	callq	ps_adv
	leaq	984(%rsp), %rcx
	callq	ps_str
	movq	152(%rsp), %rdx                 # 8-byte Reload
	movq	%rax, 1064(%rsp)
	leaq	584(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	664(%rsp), %rcx
	leaq	584(%rsp), %rdx
	callq	ps_adv
	leaq	744(%rsp), %rcx
	leaq	664(%rsp), %rdx
	callq	ps_adv
	leaq	824(%rsp), %rcx
	leaq	744(%rsp), %rdx
	callq	ps_adv
	leaq	416(%rsp), %rcx
	leaq	824(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	496(%rsp), %rcx
	leaq	416(%rsp), %rdx
	callq	parse_type_expr
	leaq	496(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	3360(%rsp), %r9
	movq	3448(%rsp), %r8
	movq	496(%rsp), %rdx
	movq	1064(%rsp), %rcx
	callq	n_extern
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	leaq	336(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	160(%rsp), %rcx                 # 8-byte Reload
	movq	72(%rsp), %rdx                  # 8-byte Reload
	leaq	336(%rsp), %r8
	callq	mk_pr
	jmp	.LBB75_9
.LBB75_8:
	movq	152(%rsp), %rdx                 # 8-byte Reload
	leaq	176(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	256(%rsp), %rcx
	leaq	176(%rsp), %rdx
	callq	ps_err
	movq	3360(%rsp), %rdx
	movq	3448(%rsp), %rcx
	callq	n_unit
	movq	160(%rsp), %rcx                 # 8-byte Reload
	movq	%rax, %rdx
	leaq	256(%rsp), %r8
	callq	mk_pr
.LBB75_9:
	movq	168(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$3800, %rsp                     # imm = 0xED8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	fprintf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,fprintf
	.globl	fprintf                         # -- Begin function fprintf
	.p2align	4
fprintf:                                # @fprintf
.seh_proc fprintf
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r9, 104(%rsp)
	movq	%r8, 96(%rsp)
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	leaq	96(%rsp), %rax
	movq	%rax, 40(%rsp)
	movq	40(%rsp), %r9
	movq	64(%rsp), %rdx
	movq	56(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %r8d
	callq	_vfprintf_l
	movl	%eax, 52(%rsp)
	movl	52(%rsp), %eax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	gather_decls;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	gather_decls                    # -- Begin function gather_decls
	.p2align	4
gather_decls:                           # @gather_decls
.seh_proc gather_decls
# %bb.0:
	subq	$680, %rsp                      # imm = 0x2A8
	.seh_stackalloc 680
	.seh_endprologue
	movq	%rdx, 64(%rsp)                  # 8-byte Spill
	movq	%rcx, 72(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	movq	%rcx, 672(%rsp)
	movq	%r8, 664(%rsp)
	movq	%rdx, 656(%rsp)
	movl	gd_cnt(%rip), %eax
	addl	$1, %eax
	movl	%eax, gd_cnt(%rip)
	cmpl	$100, gd_cnt(%rip)
	jle	.LBB77_2
# %bb.1:
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movq	72(%rdx), %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	576(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	576(%rsp), %rcx
	callq	ps_kind
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	48(%rsp), %r8                   # 8-byte Reload
	movq	56(%rsp), %r9                   # 8-byte Reload
	movq	%rax, %rcx
	leaq	"??_C@_0BG@FLFFMMNN@gd?5INF?5k?$DN?$CFlld?5e?$DN?$CFlld?6?$AA@"(%rip), %rdx
	callq	fprintf
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	callq	fflush
	movl	$1, %ecx
	callq	exit
.LBB77_2:
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	496(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	496(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_RBRACE(%rip), %rax
	jne	.LBB77_4
# %bb.3:
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movl	$0, gd_cnt(%rip)
	leaq	336(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	416(%rsp), %rcx
	leaq	336(%rsp), %rdx
	callq	ps_adv
	movq	664(%rsp), %rcx
	callq	rev
	movq	72(%rsp), %rcx                  # 8-byte Reload
	movq	%rax, %rdx
	leaq	416(%rsp), %r8
	callq	mk_pr
	jmp	.LBB77_5
.LBB77_4:
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	168(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	248(%rsp), %rcx
	leaq	168(%rsp), %rdx
	callq	parse_decl
	movq	664(%rsp), %rdx
	movq	248(%rsp), %rcx
	callq	m0_cons
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	leaq	248(%rsp), %rdx
	addq	$8, %rdx
	leaq	88(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	72(%rsp), %rcx                  # 8-byte Reload
	movq	40(%rsp), %r8                   # 8-byte Reload
	leaq	88(%rsp), %rdx
	callq	gather_decls
.LBB77_5:
	movq	80(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$680, %rsp                      # imm = 0x2A8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_module;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_module                    # -- Begin function parse_module
	.p2align	4
parse_module:                           # @parse_module
.seh_proc parse_module
# %bb.0:
	subq	$1288, %rsp                     # imm = 0x508
	.seh_stackalloc 1288
	.seh_endprologue
	movq	%rdx, 96(%rsp)                  # 8-byte Spill
	movq	%rcx, 104(%rsp)                 # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 112(%rsp)                 # 8-byte Spill
	movq	%rcx, 1280(%rsp)
	movq	%rdx, 1272(%rsp)
	movl	pm_cnt(%rip), %eax
	addl	$1, %eax
	movl	%eax, pm_cnt(%rip)
	cmpl	$10, pm_cnt(%rip)
	jle	.LBB78_2
# %bb.1:
	movq	96(%rsp), %rdx                  # 8-byte Reload
	leaq	1192(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1192(%rsp), %rcx
	callq	ps_kind
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	88(%rsp), %r8                   # 8-byte Reload
	movq	%rax, %rcx
	leaq	"??_C@_0P@BFNPGNIE@pm?5INF?5k?$DN?$CFlld?6?$AA@"(%rip), %rdx
	callq	fprintf
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	callq	fflush
	movq	96(%rsp), %rdx                  # 8-byte Reload
	leaq	1032(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	1112(%rsp), %rcx
	leaq	1032(%rsp), %rdx
	callq	ps_err
	movq	104(%rsp), %rcx                 # 8-byte Reload
	xorl	%eax, %eax
	movl	%eax, %edx
	leaq	1112(%rsp), %r8
	callq	mk_pr
	jmp	.LBB78_3
.LBB78_2:
	movq	96(%rsp), %rdx                  # 8-byte Reload
	leaq	944(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	944(%rsp), %rcx
	callq	ps_line
	movq	96(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 1024(%rsp)
	leaq	856(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	856(%rsp), %rcx
	callq	ps_col
	movq	96(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 936(%rsp)
	leaq	688(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	768(%rsp), %rcx
	leaq	688(%rsp), %rdx
	callq	ps_adv
	leaq	768(%rsp), %rcx
	callq	ps_str
	movq	96(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 848(%rsp)
	leaq	368(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	448(%rsp), %rcx
	leaq	368(%rsp), %rdx
	callq	ps_adv
	leaq	528(%rsp), %rcx
	leaq	448(%rsp), %rdx
	callq	ps_adv
	leaq	608(%rsp), %rcx
	leaq	528(%rsp), %rdx
	callq	ps_adv
	movq	m0_nil(%rip), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	200(%rsp), %rcx
	leaq	608(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	movq	48(%rsp), %r8                   # 8-byte Reload
	leaq	280(%rsp), %rcx
	leaq	200(%rsp), %rdx
	callq	gather_decls
	leaq	280(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	movq	936(%rsp), %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	1024(%rsp), %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	280(%rsp), %rcx
	callq	list_len
	movq	56(%rsp), %r9                   # 8-byte Reload
	movq	%rax, %r8
	movq	64(%rsp), %rax                  # 8-byte Reload
	movq	280(%rsp), %rdx
	movq	848(%rsp), %rcx
	movq	%rax, 32(%rsp)
	callq	n_mod
	movq	72(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	leaq	120(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	104(%rsp), %rcx                 # 8-byte Reload
	movq	80(%rsp), %rdx                  # 8-byte Reload
	leaq	120(%rsp), %r8
	callq	mk_pr
.LBB78_3:
	movq	112(%rsp), %rax                 # 8-byte Reload
	.seh_startepilogue
	addq	$1288, %rsp                     # imm = 0x508
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	gather_modules;
	.scl	2;
	.type	32;
	.endef
	.globl	gather_modules                  # -- Begin function gather_modules
	.p2align	4
gather_modules:                         # @gather_modules
.seh_proc gather_modules
# %bb.0:
	subq	$1000, %rsp                     # imm = 0x3E8
	.seh_stackalloc 1000
	.seh_endprologue
	movq	%rdx, 64(%rsp)                  # 8-byte Spill
	movq	%rcx, 72(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	movq	%rcx, 992(%rsp)
	movq	%r8, 984(%rsp)
	movq	%rdx, 976(%rsp)
	movl	gm_cnt(%rip), %eax
	addl	$1, %eax
	movl	%eax, gm_cnt(%rip)
	cmpl	$100, gm_cnt(%rip)
	jle	.LBB79_2
# %bb.1:
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	896(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	896(%rsp), %rcx
	callq	ps_kind
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	56(%rsp), %r8                   # 8-byte Reload
	movq	%rax, %rcx
	leaq	"??_C@_0P@MKLMPNNB@gm?5INF?5k?$DN?$CFlld?6?$AA@"(%rip), %rdx
	callq	fprintf
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	callq	fflush
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	736(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	816(%rsp), %rcx
	leaq	736(%rsp), %rdx
	callq	ps_err
	movq	72(%rsp), %rcx                  # 8-byte Reload
	xorl	%eax, %eax
	movl	%eax, %edx
	leaq	816(%rsp), %r8
	callq	mk_pr
	jmp	.LBB79_7
.LBB79_2:
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	656(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	656(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_EOF(%rip), %rax
	jne	.LBB79_4
# %bb.3:
	movl	$0, gm_cnt(%rip)
	movq	984(%rsp), %rcx
	callq	rev
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	leaq	576(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	72(%rsp), %rcx                  # 8-byte Reload
	movq	48(%rsp), %rdx                  # 8-byte Reload
	leaq	576(%rsp), %r8
	callq	mk_pr
	jmp	.LBB79_7
.LBB79_4:
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	496(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	496(%rsp), %rcx
	callq	ps_kind
	cmpq	TK_MODULE(%rip), %rax
	jne	.LBB79_6
# %bb.5:
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	328(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	408(%rsp), %rcx
	leaq	328(%rsp), %rdx
	callq	parse_module
	movq	984(%rsp), %rdx
	movq	408(%rsp), %rcx
	callq	m0_cons
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	leaq	408(%rsp), %rdx
	addq	$8, %rdx
	leaq	248(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	72(%rsp), %rcx                  # 8-byte Reload
	movq	40(%rsp), %r8                   # 8-byte Reload
	leaq	248(%rsp), %rdx
	callq	gather_modules
	jmp	.LBB79_7
.LBB79_6:
	movq	64(%rsp), %rdx                  # 8-byte Reload
	leaq	88(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	168(%rsp), %rcx
	leaq	88(%rsp), %rdx
	callq	ps_err
	movq	984(%rsp), %rcx
	callq	rev
	movq	72(%rsp), %rcx                  # 8-byte Reload
	movq	%rax, %rdx
	leaq	168(%rsp), %r8
	callq	mk_pr
.LBB79_7:
	movq	80(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$1000, %rsp                     # imm = 0x3E8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_program;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_program                   # -- Begin function parse_program
	.p2align	4
parse_program:                          # @parse_program
.seh_proc parse_program
# %bb.0:
	subq	$520, %rsp                      # imm = 0x208
	.seh_stackalloc 520
	.seh_endprologue
	movq	%rdx, 40(%rsp)                  # 8-byte Spill
	movq	%rcx, 72(%rsp)                  # 8-byte Spill
	movq	%rcx, %rax
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	movq	%rcx, 512(%rsp)
	movq	%rdx, 504(%rsp)
	movq	m0_nil(%rip), %rax
	movq	%rax, 32(%rsp)                  # 8-byte Spill
	leaq	336(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	32(%rsp), %r8                   # 8-byte Reload
	leaq	416(%rsp), %rcx
	leaq	336(%rsp), %rdx
	callq	gather_modules
	movq	40(%rsp), %rdx                  # 8-byte Reload
	leaq	416(%rsp), %rax
	addq	$8, %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	leaq	256(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	256(%rsp), %rcx
	callq	ps_col
	movq	40(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	leaq	176(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	leaq	176(%rsp), %rcx
	callq	ps_line
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	movq	416(%rsp), %rcx
	callq	list_len
	movq	48(%rsp), %r8                   # 8-byte Reload
	movq	56(%rsp), %r9                   # 8-byte Reload
	movq	%rax, %rdx
	movq	416(%rsp), %rcx
	callq	n_prog
	movq	64(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	leaq	96(%rsp), %rcx
	movl	$80, %r8d
	callq	memcpy
	movq	72(%rsp), %rcx                  # 8-byte Reload
	movq	80(%rsp), %rdx                  # 8-byte Reload
	leaq	96(%rsp), %r8
	callq	mk_pr
	movq	88(%rsp), %rax                  # 8-byte Reload
	.seh_startepilogue
	addq	$520, %rsp                      # imm = 0x208
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	reg_entry;
	.scl	2;
	.type	32;
	.endef
	.globl	reg_entry                       # -- Begin function reg_entry
	.p2align	4
reg_entry:                              # @reg_entry
.seh_proc reg_entry
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%r8, 80(%rsp)
	movq	%rdx, 72(%rsp)
	movq	%rcx, 64(%rsp)
	movl	$3, %ecx
	callq	m0_alloc
	movq	%rax, 56(%rsp)
	movq	64(%rsp), %r8
	movq	56(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_store_string
	movq	%rax, 48(%rsp)
	movq	72(%rsp), %r8
	movq	56(%rsp), %rcx
	movl	$1, %edx
	callq	m0_set
	movq	%rax, 40(%rsp)
	movq	80(%rsp), %r8
	movq	56(%rsp), %rcx
	movl	$2, %edx
	callq	m0_set
	movq	%rax, 32(%rsp)
	movq	56(%rsp), %rax
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	reg_name;
	.scl	2;
	.type	32;
	.endef
	.globl	reg_name                        # -- Begin function reg_name
	.p2align	4
reg_name:                               # @reg_name
.seh_proc reg_name
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movq	%rcx, 32(%rsp)
	movq	32(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_load_string
	nop
	.seh_startepilogue
	addq	$40, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	reg_type;
	.scl	2;
	.type	32;
	.endef
	.globl	reg_type                        # -- Begin function reg_type
	.p2align	4
reg_type:                               # @reg_type
.seh_proc reg_type
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movq	%rcx, 32(%rsp)
	movq	32(%rsp), %rcx
	movl	$1, %edx
	callq	m0_get
	nop
	.seh_startepilogue
	addq	$40, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	reg_fields;
	.scl	2;
	.type	32;
	.endef
	.globl	reg_fields                      # -- Begin function reg_fields
	.p2align	4
reg_fields:                             # @reg_fields
.seh_proc reg_fields
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movq	%rcx, 32(%rsp)
	movq	32(%rsp), %rcx
	movl	$2, %edx
	callq	m0_get
	nop
	.seh_startepilogue
	addq	$40, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	lookup_reg;
	.scl	2;
	.type	32;
	.endef
	.globl	lookup_reg                      # -- Begin function lookup_reg
	.p2align	4
lookup_reg:                             # @lookup_reg
.seh_proc lookup_reg
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	48(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB85_2
# %bb.1:
	movq	$0, 64(%rsp)
	jmp	.LBB85_5
.LBB85_2:
	movq	56(%rsp), %rax
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	movq	48(%rsp), %rcx
	callq	m0_head
	movq	%rax, %rcx
	callq	reg_name
	movq	40(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, %rcx
	callq	m0_string_eq
	cmpq	$1, %rax
	jne	.LBB85_4
# %bb.3:
	movq	48(%rsp), %rcx
	callq	m0_head
	movq	%rax, 64(%rsp)
	jmp	.LBB85_5
.LBB85_4:
	movq	56(%rsp), %rax
	movq	%rax, 32(%rsp)                  # 8-byte Spill
	movq	48(%rsp), %rcx
	callq	m0_tail
	movq	32(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, %rcx
	callq	lookup_reg
	movq	%rax, 64(%rsp)
.LBB85_5:
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	build_reg;
	.scl	2;
	.type	32;
	.endef
	.globl	build_reg                       # -- Begin function build_reg
	.p2align	4
build_reg:                              # @build_reg
.seh_proc build_reg
# %bb.0:
	subq	$120, %rsp
	.seh_stackalloc 120
	.seh_endprologue
	movq	%rdx, 104(%rsp)
	movq	%rcx, 96(%rsp)
	movq	96(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB86_2
# %bb.1:
	movq	104(%rsp), %rax
	movq	%rax, 112(%rsp)
	jmp	.LBB86_8
.LBB86_2:
	movq	96(%rsp), %rcx
	callq	m0_head
	movq	%rax, 88(%rsp)
	movq	88(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_get
	cmpq	N_TYPE_DECL(%rip), %rax
	jne	.LBB86_7
# %bb.3:
	movq	88(%rsp), %rcx
	movl	$3, %edx
	callq	m0_load_string
	movq	%rax, 80(%rsp)
	movq	88(%rsp), %rcx
	movl	$4, %edx
	callq	m0_get
	movq	%rax, 72(%rsp)
	movq	72(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_get
	cmpq	T_RECORD(%rip), %rax
	jne	.LBB86_5
# %bb.4:
	movq	72(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, 64(%rsp)
	jmp	.LBB86_6
.LBB86_5:
	movq	m0_nil(%rip), %rax
	movq	%rax, 64(%rsp)
.LBB86_6:
	movq	104(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	movq	64(%rsp), %r8
	movq	72(%rsp), %rdx
	movq	80(%rsp), %rcx
	callq	reg_entry
	movq	48(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, %rcx
	callq	m0_cons
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	96(%rsp), %rcx
	callq	m0_tail
	movq	56(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, %rcx
	callq	build_reg
	movq	%rax, 112(%rsp)
	jmp	.LBB86_8
.LBB86_7:
	movq	104(%rsp), %rax
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	movq	96(%rsp), %rcx
	callq	m0_tail
	movq	40(%rsp), %rdx                  # 8-byte Reload
	movq	%rax, %rcx
	callq	build_reg
	movq	%rax, 112(%rsp)
.LBB86_8:
	movq	112(%rsp), %rax
	.seh_startepilogue
	addq	$120, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_c_type;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_c_type                     # -- Begin function emit_c_type
	.p2align	4
emit_c_type:                            # @emit_c_type
.seh_proc emit_c_type
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	56(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_get
	movq	%rax, 40(%rsp)
	movq	40(%rsp), %rax
	cmpq	T_NAMED(%rip), %rax
	jne	.LBB87_14
# %bb.1:
	movq	56(%rsp), %rcx
	movl	$3, %edx
	callq	m0_load_string
	movq	%rax, 32(%rsp)
	movq	32(%rsp), %rcx
	leaq	"??_C@_03DBLNGNIM@Int?$AA@"(%rip), %rdx
	callq	m0_string_eq
	cmpq	$1, %rax
	jne	.LBB87_3
# %bb.2:
	leaq	"??_C@_07GDNIBEMG@int64_t?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
	jmp	.LBB87_17
.LBB87_3:
	movq	32(%rsp), %rcx
	leaq	"??_C@_05KKPNNHNB@Float?$AA@"(%rip), %rdx
	callq	m0_string_eq
	cmpq	$1, %rax
	jne	.LBB87_5
# %bb.4:
	leaq	"??_C@_06BNJCAIGJ@double?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
	jmp	.LBB87_17
.LBB87_5:
	movq	32(%rsp), %rcx
	leaq	"??_C@_06ENNEIMBA@String?$AA@"(%rip), %rdx
	callq	m0_string_eq
	cmpq	$1, %rax
	jne	.LBB87_7
# %bb.6:
	leaq	"??_C@_05NCJLPPFE@char?$CK?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
	jmp	.LBB87_17
.LBB87_7:
	movq	32(%rsp), %rcx
	leaq	"??_C@_04PCGIEMCI@Bool?$AA@"(%rip), %rdx
	callq	m0_string_eq
	cmpq	$1, %rax
	jne	.LBB87_9
# %bb.8:
	leaq	"??_C@_03JBIPMCLC@int?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
	jmp	.LBB87_17
.LBB87_9:
	movq	32(%rsp), %rcx
	leaq	"??_C@_04IMAAEPPE@Char?$AA@"(%rip), %rdx
	callq	m0_string_eq
	cmpq	$1, %rax
	jne	.LBB87_11
# %bb.10:
	leaq	"??_C@_04ENMBGAPA@char?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
	jmp	.LBB87_17
.LBB87_11:
	movq	32(%rsp), %rcx
	leaq	"??_C@_04BOICIEDE@Unit?$AA@"(%rip), %rdx
	callq	m0_string_eq
	cmpq	$1, %rax
	jne	.LBB87_13
# %bb.12:
	leaq	"??_C@_04GKJNKENE@void?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
	jmp	.LBB87_17
.LBB87_13:
	movq	32(%rsp), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
	jmp	.LBB87_17
.LBB87_14:
	movq	40(%rsp), %rax
	cmpq	T_FN(%rip), %rax
	jne	.LBB87_16
# %bb.15:
	movq	56(%rsp), %rcx
	movl	$5, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	48(%rsp), %rcx
	callq	emit_c_type
	movq	%rax, 64(%rsp)
	jmp	.LBB87_17
.LBB87_16:
	leaq	"??_C@_07GDNIBEMG@int64_t?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
.LBB87_17:
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_typedef_ef;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_typedef_ef                 # -- Begin function emit_typedef_ef
	.p2align	4
emit_typedef_ef:                        # @emit_typedef_ef
.seh_proc emit_typedef_ef
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%rdx, 72(%rsp)
	movq	%rcx, 64(%rsp)
	movq	72(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB88_2
# %bb.1:
	movq	$0, 80(%rsp)
	jmp	.LBB88_3
.LBB88_2:
	movq	72(%rsp), %rcx
	callq	m0_head
	movq	%rax, %rcx
	movl	$1, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	64(%rsp), %rcx
	callq	emit_c_type
	movq	%rax, 56(%rsp)
	leaq	"??_C@_01CLKCMJKC@?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	movq	72(%rsp), %rcx
	callq	m0_head
	movq	%rax, %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_load_string
	movq	%rax, %rcx
	callq	m0_print
	movq	%rax, 40(%rsp)
	leaq	"??_C@_02LNAEAIDO@?$DL?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 32(%rsp)
	movq	72(%rsp), %rcx
	callq	m0_tail
	movq	%rax, %rdx
	movq	64(%rsp), %rcx
	callq	emit_typedef_ef
	movq	%rax, 80(%rsp)
.LBB88_3:
	movq	80(%rsp), %rax
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_typedef_ec;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_typedef_ec                 # -- Begin function emit_typedef_ec
	.p2align	4
emit_typedef_ec:                        # @emit_typedef_ec
.seh_proc emit_typedef_ec
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	%rdx, 88(%rsp)
	movq	%rcx, 80(%rsp)
	movq	88(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB89_2
# %bb.1:
	movq	$0, 96(%rsp)
	jmp	.LBB89_5
.LBB89_2:
	movq	88(%rsp), %rcx
	callq	m0_head
	movq	%rax, %rcx
	movl	$1, %edx
	callq	m0_get
	movq	%rax, 72(%rsp)
	cmpq	$0, 72(%rsp)
	je	.LBB89_4
# %bb.3:
	movq	72(%rsp), %rdx
	movq	80(%rsp), %rcx
	callq	emit_c_type
	movq	%rax, 64(%rsp)
	leaq	"??_C@_01CLKCMJKC@?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 56(%rsp)
	movq	88(%rsp), %rcx
	callq	m0_head
	movq	%rax, %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_load_string
	movq	%rax, %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	leaq	"??_C@_04HAHAIBGL@_v?$DL?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 40(%rsp)
	movq	40(%rsp), %rax
	movq	%rax, 96(%rsp)
	jmp	.LBB89_5
.LBB89_4:
	movq	$0, 96(%rsp)
.LBB89_5:
	movq	96(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_typedef;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_typedef                    # -- Begin function emit_typedef
	.p2align	4
emit_typedef:                           # @emit_typedef
.seh_proc emit_typedef
# %bb.0:
	subq	$136, %rsp
	.seh_stackalloc 136
	.seh_endprologue
	movq	%r8, 120(%rsp)
	movq	%rdx, 112(%rsp)
	movq	%rcx, 104(%rsp)
	movq	112(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_get
	movq	%rax, 96(%rsp)
	movq	96(%rsp), %rax
	cmpq	T_RECORD(%rip), %rax
	jne	.LBB90_2
# %bb.1:
	leaq	"??_C@_0BC@DJJDKMJG@typedef?5struct?5?$HL?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 88(%rsp)
	movq	112(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	104(%rsp), %rcx
	callq	emit_typedef_ef
	movq	%rax, 80(%rsp)
	leaq	"??_C@_02MJBDPJEM@?$HN?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 72(%rsp)
	movq	120(%rsp), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
	leaq	"??_C@_02NCGPMEBG@?$DL?6?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 128(%rsp)
	jmp	.LBB90_5
.LBB90_2:
	movq	96(%rsp), %rax
	cmpq	T_SUM(%rip), %rax
	jne	.LBB90_4
# %bb.3:
	leaq	"??_C@_0CD@LNDJJAKB@typedef?5struct?5?$HL?5int?5tag?$DL?5union?5@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 56(%rsp)
	movq	112(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	104(%rsp), %rcx
	callq	emit_typedef_ec
	movq	%rax, 48(%rsp)
	leaq	"??_C@_0L@JHLMPDHF@?$HN?5data?$DL?5?$HN?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 40(%rsp)
	movq	120(%rsp), %rcx
	callq	m0_print
	movq	%rax, 32(%rsp)
	leaq	"??_C@_02NCGPMEBG@?$DL?6?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 128(%rsp)
	jmp	.LBB90_5
.LBB90_4:
	movq	$0, 128(%rsp)
.LBB90_5:
	movq	128(%rsp), %rax
	.seh_startepilogue
	addq	$136, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_c_expr_ea;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_c_expr_ea                  # -- Begin function emit_c_expr_ea
	.p2align	4
emit_c_expr_ea:                         # @emit_c_expr_ea
.seh_proc emit_c_expr_ea
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%r8, 72(%rsp)
	movq	%rdx, 64(%rsp)
	movq	%rcx, 56(%rsp)
	movq	64(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB91_2
# %bb.1:
	movq	$0, 80(%rsp)
	jmp	.LBB91_5
.LBB91_2:
	cmpq	$0, 72(%rsp)
	jne	.LBB91_4
# %bb.3:
	leaq	"??_C@_02KEGNLNML@?0?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	movq	48(%rsp), %rax
	movq	%rax, 80(%rsp)
	jmp	.LBB91_5
.LBB91_4:
	movq	$0, 80(%rsp)
.LBB91_5:
	movq	80(%rsp), %rax
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_c_expr_arms_ea;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_c_expr_arms_ea             # -- Begin function emit_c_expr_arms_ea
	.p2align	4
emit_c_expr_arms_ea:                    # @emit_c_expr_arms_ea
.seh_proc emit_c_expr_arms_ea
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	80(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB92_2
# %bb.1:
	movq	$0, 96(%rsp)
	jmp	.LBB92_5
.LBB92_2:
	movq	80(%rsp), %rcx
	callq	m0_head
	movq	%rax, %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_get
	movq	%rax, 64(%rsp)
	movq	80(%rsp), %rcx
	callq	m0_head
	movq	%rax, %rcx
	movl	$1, %edx
	callq	m0_get
	movq	%rax, 56(%rsp)
	movq	64(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_get
	movq	%rax, 48(%rsp)
	cmpq	$0, 88(%rsp)
	jne	.LBB92_4
# %bb.3:
	leaq	"??_C@_06LMHDPKD@?5else?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 40(%rsp)
	movq	40(%rsp), %rax
	movq	%rax, 96(%rsp)
	jmp	.LBB92_5
.LBB92_4:
	movq	$0, 96(%rsp)
.LBB92_5:
	movq	96(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_c_expr_ef;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_c_expr_ef                  # -- Begin function emit_c_expr_ef
	.p2align	4
emit_c_expr_ef:                         # @emit_c_expr_ef
.seh_proc emit_c_expr_ef
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	80(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB93_2
# %bb.1:
	movq	$0, 96(%rsp)
	jmp	.LBB93_5
.LBB93_2:
	cmpq	$0, 88(%rsp)
	jne	.LBB93_4
# %bb.3:
	leaq	"??_C@_02KEGNLNML@?0?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
	movq	64(%rsp), %rax
	movq	%rax, 96(%rsp)
	jmp	.LBB93_5
.LBB93_4:
	movq	$0, 96(%rsp)
.LBB93_5:
	movq	96(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_fn_ep;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_fn_ep                      # -- Begin function emit_fn_ep
	.p2align	4
emit_fn_ep:                             # @emit_fn_ep
.seh_proc emit_fn_ep
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	80(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB94_2
# %bb.1:
	movq	$0, 96(%rsp)
	jmp	.LBB94_5
.LBB94_2:
	cmpq	$0, 88(%rsp)
	jne	.LBB94_4
# %bb.3:
	leaq	"??_C@_02KEGNLNML@?0?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
	movq	64(%rsp), %rax
	movq	%rax, 96(%rsp)
	jmp	.LBB94_5
.LBB94_4:
	movq	$0, 96(%rsp)
.LBB94_5:
	movq	96(%rsp), %rax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_c_op;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_c_op                       # -- Begin function emit_c_op
	.p2align	4
emit_c_op:                              # @emit_c_op
.seh_proc emit_c_op
# %bb.0:
	subq	$56, %rsp
	.seh_stackalloc 56
	.seh_endprologue
	movq	%rcx, 40(%rsp)
	movq	40(%rsp), %rax
	cmpq	OP_ADD(%rip), %rax
	jne	.LBB95_2
# %bb.1:
	leaq	"??_C@_01MIFGBAGJ@?$CL?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_2:
	movq	40(%rsp), %rax
	cmpq	OP_SUB(%rip), %rax
	jne	.LBB95_4
# %bb.3:
	leaq	"??_C@_01JOAMLHOP@?9?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_4:
	movq	40(%rsp), %rax
	cmpq	OP_MUL(%rip), %rax
	jne	.LBB95_6
# %bb.5:
	leaq	"??_C@_01NBENCBCI@?$CK?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_6:
	movq	40(%rsp), %rax
	cmpq	OP_DIV(%rip), %rax
	jne	.LBB95_8
# %bb.7:
	leaq	"??_C@_01KMDKNFGN@?1?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_8:
	movq	40(%rsp), %rax
	cmpq	OP_MOD(%rip), %rax
	jne	.LBB95_10
# %bb.9:
	leaq	"??_C@_01FGNFDNOH@?$CF?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_10:
	movq	40(%rsp), %rax
	cmpq	OP_EQ(%rip), %rax
	jne	.LBB95_12
# %bb.11:
	leaq	"??_C@_02EGOFBIJA@?$DN?$DN?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_12:
	movq	40(%rsp), %rax
	cmpq	OP_NEQ(%rip), %rax
	jne	.LBB95_14
# %bb.13:
	leaq	"??_C@_02FDNJECIE@?$CB?$DN?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_14:
	movq	40(%rsp), %rax
	cmpq	OP_LT(%rip), %rax
	jne	.LBB95_16
# %bb.15:
	leaq	"??_C@_01MNNFJEPP@?$DM?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_16:
	movq	40(%rsp), %rax
	cmpq	OP_GT(%rip), %rax
	jne	.LBB95_18
# %bb.17:
	leaq	"??_C@_01PPODPGHN@?$DO?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_18:
	movq	40(%rsp), %rax
	cmpq	OP_LE(%rip), %rax
	jne	.LBB95_20
# %bb.19:
	leaq	"??_C@_02EHCHHCKH@?$DM?$DN?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_20:
	movq	40(%rsp), %rax
	cmpq	OP_GE(%rip), %rax
	jne	.LBB95_22
# %bb.21:
	leaq	"??_C@_02EEKDKGMJ@?$DO?$DN?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_22:
	movq	40(%rsp), %rax
	cmpq	OP_AND(%rip), %rax
	jne	.LBB95_24
# %bb.23:
	leaq	"??_C@_02PPKAJPJL@?$CG?$CG?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_24:
	movq	40(%rsp), %rax
	cmpq	OP_OR(%rip), %rax
	jne	.LBB95_26
# %bb.25:
	leaq	"??_C@_02NONPIBCD@?$HM?$HM?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	jmp	.LBB95_27
.LBB95_26:
	leaq	"??_C@_01OGPIMHDM@?$DP?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
.LBB95_27:
	movq	48(%rsp), %rax
	.seh_startepilogue
	addq	$56, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_c_expr;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_c_expr                     # -- Begin function emit_c_expr
	.p2align	4
emit_c_expr:                            # @emit_c_expr
.seh_proc emit_c_expr
# %bb.0:
	subq	$392, %rsp                      # imm = 0x188
	.seh_stackalloc 392
	.seh_endprologue
	movq	%rdx, 376(%rsp)
	movq	%rcx, 368(%rsp)
	movq	376(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_get
	movq	%rax, 360(%rsp)
	movq	360(%rsp), %rax
	cmpq	N_INT(%rip), %rax
	jne	.LBB96_2
# %bb.1:
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, %rcx
	callq	m0_print_int
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_2:
	movq	360(%rsp), %rax
	cmpq	N_STRING(%rip), %rax
	jne	.LBB96_4
# %bb.3:
	leaq	"??_C@_01BJJEKLCA@?$CC?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 352(%rsp)
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_load_string
	movq	%rax, %rcx
	callq	m0_print
	movq	%rax, 344(%rsp)
	leaq	"??_C@_01BJJEKLCA@?$CC?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_4:
	movq	360(%rsp), %rax
	cmpq	N_BOOL(%rip), %rax
	jne	.LBB96_8
# %bb.5:
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	cmpq	$1, %rax
	jne	.LBB96_7
# %bb.6:
	leaq	"??_C@_01HIHLOKLC@1?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_7:
	leaq	"??_C@_01GBGANLPD@0?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_8:
	movq	360(%rsp), %rax
	cmpq	N_UNIT(%rip), %rax
	jne	.LBB96_10
# %bb.9:
	leaq	"??_C@_01GBGANLPD@0?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_10:
	movq	360(%rsp), %rax
	cmpq	N_NAME(%rip), %rax
	jne	.LBB96_12
# %bb.11:
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_load_string
	movq	%rax, %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_12:
	movq	360(%rsp), %rax
	cmpq	N_BINARY(%rip), %rax
	jne	.LBB96_14
# %bb.13:
	leaq	"??_C@_01ODHLEDKK@?$CI?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 336(%rsp)
	movq	376(%rsp), %rcx
	movl	$4, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_expr
	movq	%rax, 328(%rsp)
	leaq	"??_C@_01CLKCMJKC@?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 320(%rsp)
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, %rcx
	callq	emit_c_op
	movq	%rax, 312(%rsp)
	leaq	"??_C@_01CLKCMJKC@?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 304(%rsp)
	movq	376(%rsp), %rcx
	movl	$5, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_expr
	movq	%rax, 296(%rsp)
	leaq	"??_C@_01PKGAHCOL@?$CJ?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_14:
	movq	360(%rsp), %rax
	cmpq	N_NOT(%rip), %rax
	jne	.LBB96_16
# %bb.15:
	leaq	"??_C@_02LKHPCEFG@?$CI?$CB?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 288(%rsp)
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_expr
	movq	%rax, 280(%rsp)
	leaq	"??_C@_01PKGAHCOL@?$CJ?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_16:
	movq	360(%rsp), %rax
	cmpq	N_FIELD(%rip), %rax
	jne	.LBB96_18
# %bb.17:
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_expr
	movq	%rax, 272(%rsp)
	leaq	"??_C@_01LFCBOECM@?4?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 264(%rsp)
	movq	376(%rsp), %rcx
	movl	$4, %edx
	callq	m0_load_string
	movq	%rax, %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_18:
	movq	360(%rsp), %rax
	cmpq	N_CALL(%rip), %rax
	jne	.LBB96_20
# %bb.19:
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_expr
	movq	%rax, 256(%rsp)
	leaq	"??_C@_01ODHLEDKK@?$CI?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 248(%rsp)
	movq	376(%rsp), %rcx
	movl	$4, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	movl	$1, %r8d
	callq	emit_c_expr_ea
	movq	%rax, 240(%rsp)
	leaq	"??_C@_01PKGAHCOL@?$CJ?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_20:
	movq	360(%rsp), %rax
	cmpq	N_LET(%rip), %rax
	jne	.LBB96_22
# %bb.21:
	leaq	"??_C@_03HGBNAECB@?$CI?$HL?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 232(%rsp)
	movq	376(%rsp), %rcx
	movl	$4, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_type
	movq	%rax, 224(%rsp)
	leaq	"??_C@_01CLKCMJKC@?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 216(%rsp)
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_load_string
	movq	%rax, %rcx
	callq	m0_print
	movq	%rax, 208(%rsp)
	leaq	"??_C@_03MHLONNLM@?5?$DN?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 200(%rsp)
	movq	376(%rsp), %rcx
	movl	$5, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_expr
	movq	%rax, 192(%rsp)
	leaq	"??_C@_02LNAEAIDO@?$DL?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 184(%rsp)
	movq	376(%rsp), %rcx
	movl	$6, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_expr
	movq	%rax, 176(%rsp)
	leaq	"??_C@_04FHHBEKKD@?$DL?5?$HN?$CJ?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_22:
	movq	360(%rsp), %rax
	cmpq	N_IF(%rip), %rax
	jne	.LBB96_26
# %bb.23:
	leaq	"??_C@_01ODHLEDKK@?$CI?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 168(%rsp)
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_expr
	movq	%rax, 160(%rsp)
	leaq	"??_C@_03MEDKAJNC@?5?$DP?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 152(%rsp)
	movq	376(%rsp), %rcx
	movl	$4, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_expr
	movq	%rax, 144(%rsp)
	leaq	"??_C@_03MCPBMLDJ@?5?3?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 136(%rsp)
	movq	376(%rsp), %rcx
	movl	$5, %edx
	callq	m0_get
	movq	%rax, 128(%rsp)
	cmpq	$0, 128(%rsp)
	je	.LBB96_25
# %bb.24:
	movq	128(%rsp), %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_expr
	movq	%rax, 120(%rsp)
	movq	120(%rsp), %rax
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_25:
	leaq	"??_C@_01GBGANLPD@0?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 112(%rsp)
	movq	112(%rsp), %rax
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_26:
	movq	360(%rsp), %rax
	cmpq	N_MATCH(%rip), %rax
	jne	.LBB96_28
# %bb.27:
	leaq	"??_C@_0BB@GMPNLGNN@?$CI?$HL?5int64_t?5_m?5?$DN?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 104(%rsp)
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_expr
	movq	%rax, 96(%rsp)
	leaq	"??_C@_02LNAEAIDO@?$DL?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 88(%rsp)
	movq	376(%rsp), %rcx
	movl	$4, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	movl	$1, %r8d
	callq	emit_c_expr_arms_ea
	movq	%rax, 80(%rsp)
	leaq	"??_C@_04FHHBEKKD@?$DL?5?$HN?$CJ?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_28:
	movq	360(%rsp), %rax
	cmpq	N_RECORD(%rip), %rax
	jne	.LBB96_30
# %bb.29:
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_load_string
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	lookup_reg
	movq	%rax, 72(%rsp)
	leaq	"??_C@_01ODHLEDKK@?$CI?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 64(%rsp)
	movq	72(%rsp), %rcx
	callq	reg_type
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	callq	emit_c_type
	movq	%rax, 56(%rsp)
	leaq	"??_C@_03MOKBGDEE@?$CJ?$HL?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 48(%rsp)
	movq	376(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, %rdx
	movq	368(%rsp), %rcx
	movl	$1, %r8d
	callq	emit_c_expr_ef
	movq	%rax, 40(%rsp)
	leaq	"??_C@_03GGOGOLDF@?5?$HN?$CJ?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
	jmp	.LBB96_31
.LBB96_30:
	leaq	"??_C@_01GBGANLPD@0?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 384(%rsp)
.LBB96_31:
	movq	384(%rsp), %rax
	.seh_startepilogue
	addq	$392, %rsp                      # imm = 0x188
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_extern;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_extern                     # -- Begin function emit_extern
	.p2align	4
emit_extern:                            # @emit_extern
.seh_proc emit_extern
# %bb.0:
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	80(%rsp), %rcx
	movl	$3, %edx
	callq	m0_load_string
	movq	%rax, 64(%rsp)
	movq	80(%rsp), %rcx
	movl	$4, %edx
	callq	m0_get
	movq	%rax, 56(%rsp)
	movq	56(%rsp), %rdx
	movq	72(%rsp), %rcx
	callq	emit_c_type
	movq	%rax, 48(%rsp)
	leaq	"??_C@_01CLKCMJKC@?5?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 40(%rsp)
	movq	64(%rsp), %rcx
	callq	m0_print
	movq	%rax, 32(%rsp)
	leaq	"??_C@_02NCGPMEBG@?$DL?6?$AA@"(%rip), %rcx
	callq	m0_print
	nop
	.seh_startepilogue
	addq	$88, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_fn;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_fn                         # -- Begin function emit_fn
	.p2align	4
emit_fn:                                # @emit_fn
.seh_proc emit_fn
# %bb.0:
	subq	$152, %rsp
	.seh_stackalloc 152
	.seh_endprologue
	movq	%rdx, 136(%rsp)
	movq	%rcx, 128(%rsp)
	movq	136(%rsp), %rcx
	movl	$3, %edx
	callq	m0_load_string
	movq	%rax, 120(%rsp)
	movq	136(%rsp), %rcx
	movl	$4, %edx
	callq	m0_get
	movq	%rax, 112(%rsp)
	movq	136(%rsp), %rcx
	movl	$6, %edx
	callq	m0_get
	movq	%rax, 104(%rsp)
	movq	136(%rsp), %rcx
	movl	$7, %edx
	callq	m0_get
	movq	%rax, 96(%rsp)
	movq	120(%rsp), %rcx
	leaq	"??_C@_04GHJNJNPO@main?$AA@"(%rip), %rdx
	callq	m0_string_eq
	cmpq	$1, %rax
	sete	%al
	andb	$1, %al
	movzbl	%al, %eax
	movl	%eax, 92(%rsp)
	cmpl	$0, 92(%rsp)
	je	.LBB98_2
# %bb.1:
	leaq	"??_C@_03JBIPMCLC@int?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 80(%rsp)
	movq	80(%rsp), %rax
	movq	%rax, 144(%rsp)
	jmp	.LBB98_3
.LBB98_2:
	movq	104(%rsp), %rdx
	movq	128(%rsp), %rcx
	callq	emit_c_type
	movq	%rax, 144(%rsp)
.LBB98_3:
	movq	144(%rsp), %rax
	.seh_startepilogue
	addq	$152, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_module_pass1;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_module_pass1               # -- Begin function emit_module_pass1
	.p2align	4
emit_module_pass1:                      # @emit_module_pass1
.seh_proc emit_module_pass1
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	56(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB99_2
# %bb.1:
	movq	$0, 64(%rsp)
	jmp	.LBB99_5
.LBB99_2:
	movq	56(%rsp), %rcx
	callq	m0_head
	movq	%rax, 40(%rsp)
	movq	40(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_get
	cmpq	N_TYPE_DECL(%rip), %rax
	jne	.LBB99_4
# %bb.3:
	movq	40(%rsp), %rcx
	movl	$3, %edx
	callq	m0_load_string
	movq	%rax, 32(%rsp)                  # 8-byte Spill
	movq	40(%rsp), %rcx
	movl	$4, %edx
	callq	m0_get
	movq	32(%rsp), %r8                   # 8-byte Reload
	movq	%rax, %rdx
	movq	48(%rsp), %rcx
	callq	emit_typedef
	movq	%rax, 64(%rsp)
	jmp	.LBB99_5
.LBB99_4:
	movq	$0, 64(%rsp)
.LBB99_5:
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_module_pass2;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_module_pass2               # -- Begin function emit_module_pass2
	.p2align	4
emit_module_pass2:                      # @emit_module_pass2
.seh_proc emit_module_pass2
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	56(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB100_2
# %bb.1:
	movq	$0, 64(%rsp)
	jmp	.LBB100_5
.LBB100_2:
	movq	56(%rsp), %rcx
	callq	m0_head
	movq	%rax, 40(%rsp)
	movq	40(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_get
	cmpq	N_EXTERN(%rip), %rax
	jne	.LBB100_4
# %bb.3:
	movq	40(%rsp), %rdx
	movq	48(%rsp), %rcx
	callq	emit_extern
	movq	%rax, 64(%rsp)
	jmp	.LBB100_5
.LBB100_4:
	movq	$0, 64(%rsp)
.LBB100_5:
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_module_pass3;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_module_pass3               # -- Begin function emit_module_pass3
	.p2align	4
emit_module_pass3:                      # @emit_module_pass3
.seh_proc emit_module_pass3
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%rdx, 56(%rsp)
	movq	%rcx, 48(%rsp)
	movq	56(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$1, %rax
	jne	.LBB101_2
# %bb.1:
	movq	$0, 64(%rsp)
	jmp	.LBB101_5
.LBB101_2:
	movq	56(%rsp), %rcx
	callq	m0_head
	movq	%rax, 40(%rsp)
	movq	40(%rsp), %rcx
	xorl	%eax, %eax
	movl	%eax, %edx
	callq	m0_get
	cmpq	N_FN_DECL(%rip), %rax
	jne	.LBB101_4
# %bb.3:
	movq	40(%rsp), %rdx
	movq	48(%rsp), %rcx
	callq	emit_fn
	movq	%rax, 64(%rsp)
	jmp	.LBB101_5
.LBB101_4:
	movq	$0, 64(%rsp)
.LBB101_5:
	movq	64(%rsp), %rax
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	emit_module;
	.scl	2;
	.type	32;
	.endef
	.globl	emit_module                     # -- Begin function emit_module
	.p2align	4
emit_module:                            # @emit_module
.seh_proc emit_module
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	%rcx, 96(%rsp)
	movq	96(%rsp), %rcx
	movl	$4, %edx
	callq	m0_get
	movq	%rax, 88(%rsp)
	movq	m0_nil(%rip), %rdx
	movq	88(%rsp), %rcx
	callq	build_reg
	movq	%rax, 80(%rsp)
	leaq	"??_C@_0BG@PNJNKMEG@?$CDinclude?5?$DMstdint?4h?$DO?6?6?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 72(%rsp)
	movq	88(%rsp), %rdx
	movq	80(%rsp), %rcx
	callq	emit_module_pass1
	movq	%rax, 64(%rsp)
	leaq	"??_C@_01EEMJAFIK@?6?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 56(%rsp)
	movq	88(%rsp), %rdx
	movq	80(%rsp), %rcx
	callq	emit_module_pass2
	movq	%rax, 48(%rsp)
	leaq	"??_C@_01EEMJAFIK@?6?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 40(%rsp)
	movq	88(%rsp), %rdx
	movq	80(%rsp), %rcx
	callq	emit_module_pass3
	movq	%rax, 32(%rsp)
	xorl	%eax, %eax
                                        # kill: def $rax killed $eax
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4
main:                                   # @main
.seh_proc main
# %bb.0:
	subq	$456, %rsp                      # imm = 0x1C8
	.seh_stackalloc 456
	.seh_endprologue
	movl	$0, 452(%rsp)
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	leaq	"??_C@_0M@KFOIBCLG@main?5enter?6?$AA@"(%rip), %rdx
	callq	fprintf
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	callq	fflush
	leaq	"??_C@_09EAGLGKLK@M1_SOURCE?$AA@"(%rip), %rcx
	callq	m0_get_env
	movq	%rax, 440(%rsp)
	movq	440(%rsp), %rcx
	leaq	"??_C@_00CNPNBAHC@?$AA@"(%rip), %rdx
	callq	m0_string_eq
	cmpq	$1, %rax
	jne	.LBB103_2
# %bb.1:
	leaq	"??_C@_0BH@FHPGEPIB@error?3?5no?5source?5file?6?$AA@"(%rip), %rcx
	callq	m0_print
	movq	%rax, 432(%rsp)
	movl	$1, 452(%rsp)
	jmp	.LBB103_5
.LBB103_2:
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	leaq	"??_C@_0L@FKHADIKO@read?5file?6?$AA@"(%rip), %rdx
	callq	fprintf
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	callq	fflush
	movq	440(%rsp), %rcx
	callq	m0_read_file
	movq	%rax, 424(%rsp)
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	leaq	"??_C@_0M@LMJDILKE@lexer?5init?6?$AA@"(%rip), %rdx
	callq	fprintf
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	callq	fflush
	movq	424(%rsp), %rdx
	leaq	392(%rsp), %rcx
	callq	m1_lexer_init
	movq	392(%rsp), %rax
	movq	%rax, 288(%rsp)
	movq	400(%rsp), %rax
	movq	%rax, 296(%rsp)
	movq	408(%rsp), %rax
	movq	%rax, 304(%rsp)
	movq	416(%rsp), %rax
	movq	%rax, 312(%rsp)
	leaq	320(%rsp), %rcx
	leaq	288(%rsp), %rdx
	callq	m1_lexer_next
	leaq	208(%rsp), %rcx
	leaq	320(%rsp), %rdx
	movl	$40, %r8d
	callq	memcpy
	movq	360(%rsp), %rax
	movq	%rax, 248(%rsp)
	movq	368(%rsp), %rax
	movq	%rax, 256(%rsp)
	movq	376(%rsp), %rax
	movq	%rax, 264(%rsp)
	movq	384(%rsp), %rax
	movq	%rax, 272(%rsp)
	movq	$0, 280(%rsp)
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	leaq	"??_C@_0BF@MAFMMOEI@parse_program?5enter?6?$AA@"(%rip), %rdx
	callq	fprintf
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	callq	fflush
	leaq	40(%rsp), %rcx
	leaq	208(%rsp), %rdx
	movl	$80, %r8d
	callq	memcpy
	leaq	120(%rsp), %rcx
	leaq	40(%rsp), %rdx
	callq	parse_program
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	leaq	"??_C@_0BE@CIAJLCHB@parse_program?5done?6?$AA@"(%rip), %rdx
	callq	fprintf
	movl	$2, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rcx
	callq	fflush
	movq	120(%rsp), %rcx
	movl	$3, %edx
	callq	m0_get
	movq	%rax, 32(%rsp)
	movq	32(%rsp), %rcx
	callq	m0_is_nil
	cmpq	$0, %rax
	jne	.LBB103_4
# %bb.3:
	movq	32(%rsp), %rcx
	callq	m0_head
	movq	%rax, %rcx
	callq	emit_module
                                        # kill: def $eax killed $eax killed $rax
	movl	%eax, 452(%rsp)
	jmp	.LBB103_5
.LBB103_4:
	movl	$0, 452(%rsp)
.LBB103_5:
	movl	452(%rsp), %eax
	.seh_startepilogue
	addq	$456, %rsp                      # imm = 0x1C8
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	_vsprintf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_vsprintf_l
	.globl	_vsprintf_l                     # -- Begin function _vsprintf_l
	.p2align	4
_vsprintf_l:                            # @_vsprintf_l
.seh_proc _vsprintf_l
# %bb.0:
	subq	$72, %rsp
	.seh_stackalloc 72
	.seh_endprologue
	movq	%r9, 64(%rsp)
	movq	%r8, 56(%rsp)
	movq	%rdx, 48(%rsp)
	movq	%rcx, 40(%rsp)
	movq	64(%rsp), %rax
	movq	56(%rsp), %r9
	movq	48(%rsp), %r8
	movq	40(%rsp), %rcx
	movq	$-1, %rdx
	movq	%rax, 32(%rsp)
	callq	_vsnprintf_l
	nop
	.seh_startepilogue
	addq	$72, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	_vsnprintf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_vsnprintf_l
	.globl	_vsnprintf_l                    # -- Begin function _vsnprintf_l
	.p2align	4
_vsnprintf_l:                           # @_vsnprintf_l
.seh_proc _vsnprintf_l
# %bb.0:
	subq	$136, %rsp
	.seh_stackalloc 136
	.seh_endprologue
	movq	176(%rsp), %rax
	movq	%r9, 128(%rsp)
	movq	%r8, 120(%rsp)
	movq	%rdx, 112(%rsp)
	movq	%rcx, 104(%rsp)
	movq	176(%rsp), %rax
	movq	%rax, 88(%rsp)                  # 8-byte Spill
	movq	128(%rsp), %rax
	movq	%rax, 80(%rsp)                  # 8-byte Spill
	movq	120(%rsp), %rax
	movq	%rax, 72(%rsp)                  # 8-byte Spill
	movq	112(%rsp), %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	104(%rsp), %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	callq	__local_stdio_printf_options
	movq	56(%rsp), %rdx                  # 8-byte Reload
	movq	64(%rsp), %r8                   # 8-byte Reload
	movq	72(%rsp), %r9                   # 8-byte Reload
	movq	80(%rsp), %r10                  # 8-byte Reload
	movq	%rax, %rcx
	movq	88(%rsp), %rax                  # 8-byte Reload
	movq	(%rcx), %rcx
	orq	$1, %rcx
	movq	%r10, 32(%rsp)
	movq	%rax, 40(%rsp)
	callq	__stdio_common_vsprintf
	movl	%eax, 100(%rsp)
	cmpl	$0, 100(%rsp)
	jge	.LBB105_2
# %bb.1:
	movl	$4294967295, %eax               # imm = 0xFFFFFFFF
	movl	%eax, 52(%rsp)                  # 4-byte Spill
	jmp	.LBB105_3
.LBB105_2:
	movl	100(%rsp), %eax
	movl	%eax, 52(%rsp)                  # 4-byte Spill
.LBB105_3:
	movl	52(%rsp), %eax                  # 4-byte Reload
	.seh_startepilogue
	addq	$136, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	__local_stdio_printf_options;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,__local_stdio_printf_options
	.globl	__local_stdio_printf_options    # -- Begin function __local_stdio_printf_options
	.p2align	4
__local_stdio_printf_options:           # @__local_stdio_printf_options
# %bb.0:
	leaq	__local_stdio_printf_options._OptionsStorage(%rip), %rax
	retq
                                        # -- End function
	.def	_vfprintf_l;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,_vfprintf_l
	.globl	_vfprintf_l                     # -- Begin function _vfprintf_l
	.p2align	4
_vfprintf_l:                            # @_vfprintf_l
.seh_proc _vfprintf_l
# %bb.0:
	subq	$104, %rsp
	.seh_stackalloc 104
	.seh_endprologue
	movq	%r9, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%rcx, 72(%rsp)
	movq	96(%rsp), %rax
	movq	%rax, 64(%rsp)                  # 8-byte Spill
	movq	88(%rsp), %rax
	movq	%rax, 56(%rsp)                  # 8-byte Spill
	movq	80(%rsp), %rax
	movq	%rax, 48(%rsp)                  # 8-byte Spill
	movq	72(%rsp), %rax
	movq	%rax, 40(%rsp)                  # 8-byte Spill
	callq	__local_stdio_printf_options
	movq	40(%rsp), %rdx                  # 8-byte Reload
	movq	48(%rsp), %r8                   # 8-byte Reload
	movq	56(%rsp), %r9                   # 8-byte Reload
	movq	%rax, %rcx
	movq	64(%rsp), %rax                  # 8-byte Reload
	movq	(%rcx), %rcx
	movq	%rax, 32(%rsp)
	callq	__stdio_common_vfprintf
	nop
	.seh_startepilogue
	addq	$104, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.bss
	.globl	TK_EOF                          # @TK_EOF
	.p2align	3, 0x0
TK_EOF:
	.quad	0                               # 0x0

	.data
	.globl	TK_INT                          # @TK_INT
	.p2align	3, 0x0
TK_INT:
	.quad	1                               # 0x1

	.globl	TK_STRING                       # @TK_STRING
	.p2align	3, 0x0
TK_STRING:
	.quad	3                               # 0x3

	.globl	TK_IDENT                        # @TK_IDENT
	.p2align	3, 0x0
TK_IDENT:
	.quad	5                               # 0x5

	.globl	TK_ARROW                        # @TK_ARROW
	.p2align	3, 0x0
TK_ARROW:
	.quad	6                               # 0x6

	.globl	TK_LARROW                       # @TK_LARROW
	.p2align	3, 0x0
TK_LARROW:
	.quad	7                               # 0x7

	.globl	TK_BIDI                         # @TK_BIDI
	.p2align	3, 0x0
TK_BIDI:
	.quad	8                               # 0x8

	.globl	TK_EQ                           # @TK_EQ
	.p2align	3, 0x0
TK_EQ:
	.quad	9                               # 0x9

	.globl	TK_EQEQ                         # @TK_EQEQ
	.p2align	3, 0x0
TK_EQEQ:
	.quad	10                              # 0xa

	.globl	TK_NEQ                          # @TK_NEQ
	.p2align	3, 0x0
TK_NEQ:
	.quad	11                              # 0xb

	.globl	TK_LT                           # @TK_LT
	.p2align	3, 0x0
TK_LT:
	.quad	12                              # 0xc

	.globl	TK_GT                           # @TK_GT
	.p2align	3, 0x0
TK_GT:
	.quad	13                              # 0xd

	.globl	TK_LE                           # @TK_LE
	.p2align	3, 0x0
TK_LE:
	.quad	14                              # 0xe

	.globl	TK_GE                           # @TK_GE
	.p2align	3, 0x0
TK_GE:
	.quad	15                              # 0xf

	.globl	TK_AND                          # @TK_AND
	.p2align	3, 0x0
TK_AND:
	.quad	16                              # 0x10

	.globl	TK_OR                           # @TK_OR
	.p2align	3, 0x0
TK_OR:
	.quad	17                              # 0x11

	.globl	TK_PIPE                         # @TK_PIPE
	.p2align	3, 0x0
TK_PIPE:
	.quad	18                              # 0x12

	.globl	TK_COLON                        # @TK_COLON
	.p2align	3, 0x0
TK_COLON:
	.quad	19                              # 0x13

	.globl	TK_COMMA                        # @TK_COMMA
	.p2align	3, 0x0
TK_COMMA:
	.quad	20                              # 0x14

	.globl	TK_DOT                          # @TK_DOT
	.p2align	3, 0x0
TK_DOT:
	.quad	21                              # 0x15

	.globl	TK_SEMI                         # @TK_SEMI
	.p2align	3, 0x0
TK_SEMI:
	.quad	22                              # 0x16

	.globl	TK_LBRACE                       # @TK_LBRACE
	.p2align	3, 0x0
TK_LBRACE:
	.quad	24                              # 0x18

	.globl	TK_RBRACE                       # @TK_RBRACE
	.p2align	3, 0x0
TK_RBRACE:
	.quad	25                              # 0x19

	.globl	TK_LPAREN                       # @TK_LPAREN
	.p2align	3, 0x0
TK_LPAREN:
	.quad	26                              # 0x1a

	.globl	TK_RPAREN                       # @TK_RPAREN
	.p2align	3, 0x0
TK_RPAREN:
	.quad	27                              # 0x1b

	.globl	TK_LBRACK                       # @TK_LBRACK
	.p2align	3, 0x0
TK_LBRACK:
	.quad	28                              # 0x1c

	.globl	TK_RBRACK                       # @TK_RBRACK
	.p2align	3, 0x0
TK_RBRACK:
	.quad	29                              # 0x1d

	.globl	TK_PLUS                         # @TK_PLUS
	.p2align	3, 0x0
TK_PLUS:
	.quad	30                              # 0x1e

	.globl	TK_MINUS                        # @TK_MINUS
	.p2align	3, 0x0
TK_MINUS:
	.quad	31                              # 0x1f

	.globl	TK_STAR                         # @TK_STAR
	.p2align	3, 0x0
TK_STAR:
	.quad	32                              # 0x20

	.globl	TK_SLASH                        # @TK_SLASH
	.p2align	3, 0x0
TK_SLASH:
	.quad	33                              # 0x21

	.globl	TK_PERCENT                      # @TK_PERCENT
	.p2align	3, 0x0
TK_PERCENT:
	.quad	34                              # 0x22

	.globl	TK_UNIT                         # @TK_UNIT
	.p2align	3, 0x0
TK_UNIT:
	.quad	35                              # 0x23

	.globl	TK_MODULE                       # @TK_MODULE
	.p2align	3, 0x0
TK_MODULE:
	.quad	36                              # 0x24

	.globl	TK_TYPE                         # @TK_TYPE
	.p2align	3, 0x0
TK_TYPE:
	.quad	37                              # 0x25

	.globl	TK_FN                           # @TK_FN
	.p2align	3, 0x0
TK_FN:
	.quad	38                              # 0x26

	.globl	TK_LET                          # @TK_LET
	.p2align	3, 0x0
TK_LET:
	.quad	39                              # 0x27

	.globl	TK_MATCH                        # @TK_MATCH
	.p2align	3, 0x0
TK_MATCH:
	.quad	40                              # 0x28

	.globl	TK_IF                           # @TK_IF
	.p2align	3, 0x0
TK_IF:
	.quad	41                              # 0x29

	.globl	TK_ELSE                         # @TK_ELSE
	.p2align	3, 0x0
TK_ELSE:
	.quad	42                              # 0x2a

	.globl	TK_TRUE                         # @TK_TRUE
	.p2align	3, 0x0
TK_TRUE:
	.quad	43                              # 0x2b

	.globl	TK_FALSE                        # @TK_FALSE
	.p2align	3, 0x0
TK_FALSE:
	.quad	44                              # 0x2c

	.globl	TK_EXTERNAL                     # @TK_EXTERNAL
	.p2align	3, 0x0
TK_EXTERNAL:
	.quad	45                              # 0x2d

	.globl	TK_NOT                          # @TK_NOT
	.p2align	3, 0x0
TK_NOT:
	.quad	46                              # 0x2e

	.globl	TK_FORALL                       # @TK_FORALL
	.p2align	3, 0x0
TK_FORALL:
	.quad	47                              # 0x2f

	.globl	TK_EXISTS                       # @TK_EXISTS
	.p2align	3, 0x0
TK_EXISTS:
	.quad	48                              # 0x30

	.bss
	.globl	N_PROG                          # @N_PROG
	.p2align	3, 0x0
N_PROG:
	.quad	0                               # 0x0

	.data
	.globl	N_MOD                           # @N_MOD
	.p2align	3, 0x0
N_MOD:
	.quad	1                               # 0x1

	.globl	N_TYPE_DECL                     # @N_TYPE_DECL
	.p2align	3, 0x0
N_TYPE_DECL:
	.quad	2                               # 0x2

	.globl	N_PROP_DECL                     # @N_PROP_DECL
	.p2align	3, 0x0
N_PROP_DECL:
	.quad	3                               # 0x3

	.globl	N_FN_DECL                       # @N_FN_DECL
	.p2align	3, 0x0
N_FN_DECL:
	.quad	4                               # 0x4

	.globl	N_EXTERN                        # @N_EXTERN
	.p2align	3, 0x0
N_EXTERN:
	.quad	5                               # 0x5

	.globl	N_INT                           # @N_INT
	.p2align	3, 0x0
N_INT:
	.quad	6                               # 0x6

	.globl	N_STRING                        # @N_STRING
	.p2align	3, 0x0
N_STRING:
	.quad	7                               # 0x7

	.globl	N_BOOL                          # @N_BOOL
	.p2align	3, 0x0
N_BOOL:
	.quad	8                               # 0x8

	.globl	N_UNIT                          # @N_UNIT
	.p2align	3, 0x0
N_UNIT:
	.quad	9                               # 0x9

	.globl	N_NAME                          # @N_NAME
	.p2align	3, 0x0
N_NAME:
	.quad	10                              # 0xa

	.globl	N_BINARY                        # @N_BINARY
	.p2align	3, 0x0
N_BINARY:
	.quad	11                              # 0xb

	.globl	N_NOT                           # @N_NOT
	.p2align	3, 0x0
N_NOT:
	.quad	12                              # 0xc

	.globl	N_FIELD                         # @N_FIELD
	.p2align	3, 0x0
N_FIELD:
	.quad	13                              # 0xd

	.globl	N_CALL                          # @N_CALL
	.p2align	3, 0x0
N_CALL:
	.quad	14                              # 0xe

	.globl	N_LET                           # @N_LET
	.p2align	3, 0x0
N_LET:
	.quad	16                              # 0x10

	.globl	N_LAMBDA                        # @N_LAMBDA
	.p2align	3, 0x0
N_LAMBDA:
	.quad	17                              # 0x11

	.globl	N_MATCH                         # @N_MATCH
	.p2align	3, 0x0
N_MATCH:
	.quad	18                              # 0x12

	.globl	N_IF                            # @N_IF
	.p2align	3, 0x0
N_IF:
	.quad	19                              # 0x13

	.globl	N_RECORD                        # @N_RECORD
	.p2align	3, 0x0
N_RECORD:
	.quad	20                              # 0x14

	.globl	N_LIST                          # @N_LIST
	.p2align	3, 0x0
N_LIST:
	.quad	21                              # 0x15

	.globl	T_NAMED                         # @T_NAMED
	.p2align	3, 0x0
T_NAMED:
	.quad	100                             # 0x64

	.globl	T_FN                            # @T_FN
	.p2align	3, 0x0
T_FN:
	.quad	101                             # 0x65

	.globl	T_RECORD                        # @T_RECORD
	.p2align	3, 0x0
T_RECORD:
	.quad	102                             # 0x66

	.globl	T_SUM                           # @T_SUM
	.p2align	3, 0x0
T_SUM:
	.quad	103                             # 0x67

	.globl	T_APP                           # @T_APP
	.p2align	3, 0x0
T_APP:
	.quad	104                             # 0x68

	.bss
	.globl	OP_ADD                          # @OP_ADD
	.p2align	3, 0x0
OP_ADD:
	.quad	0                               # 0x0

	.data
	.globl	OP_SUB                          # @OP_SUB
	.p2align	3, 0x0
OP_SUB:
	.quad	1                               # 0x1

	.globl	OP_MUL                          # @OP_MUL
	.p2align	3, 0x0
OP_MUL:
	.quad	2                               # 0x2

	.globl	OP_DIV                          # @OP_DIV
	.p2align	3, 0x0
OP_DIV:
	.quad	3                               # 0x3

	.globl	OP_MOD                          # @OP_MOD
	.p2align	3, 0x0
OP_MOD:
	.quad	4                               # 0x4

	.globl	OP_EQ                           # @OP_EQ
	.p2align	3, 0x0
OP_EQ:
	.quad	5                               # 0x5

	.globl	OP_NEQ                          # @OP_NEQ
	.p2align	3, 0x0
OP_NEQ:
	.quad	6                               # 0x6

	.globl	OP_LT                           # @OP_LT
	.p2align	3, 0x0
OP_LT:
	.quad	7                               # 0x7

	.globl	OP_GT                           # @OP_GT
	.p2align	3, 0x0
OP_GT:
	.quad	8                               # 0x8

	.globl	OP_LE                           # @OP_LE
	.p2align	3, 0x0
OP_LE:
	.quad	9                               # 0x9

	.globl	OP_GE                           # @OP_GE
	.p2align	3, 0x0
OP_GE:
	.quad	10                              # 0xa

	.globl	OP_AND                          # @OP_AND
	.p2align	3, 0x0
OP_AND:
	.quad	11                              # 0xb

	.globl	OP_OR                           # @OP_OR
	.p2align	3, 0x0
OP_OR:
	.quad	12                              # 0xc

	.globl	OP_IMPL                         # @OP_IMPL
	.p2align	3, 0x0
OP_IMPL:
	.quad	13                              # 0xd

	.globl	OP_IFF                          # @OP_IFF
	.p2align	3, 0x0
OP_IFF:
	.quad	14                              # 0xe

	.bss
	.globl	P_WILD                          # @P_WILD
	.p2align	3, 0x0
P_WILD:
	.quad	0                               # 0x0

	.data
	.globl	P_LIT                           # @P_LIT
	.p2align	3, 0x0
P_LIT:
	.quad	1                               # 0x1

	.globl	P_CTOR                          # @P_CTOR
	.p2align	3, 0x0
P_CTOR:
	.quad	2                               # 0x2

	.globl	P_NAME                          # @P_NAME
	.p2align	3, 0x0
P_NAME:
	.quad	4                               # 0x4

	.section	.rdata,"dr",discard,"??_C@_01IDAFKMJL@_?$AA@"
	.globl	"??_C@_01IDAFKMJL@_?$AA@"       # @"??_C@_01IDAFKMJL@_?$AA@"
"??_C@_01IDAFKMJL@_?$AA@":
	.asciz	"_"

	.bss
	.globl	pd_cnt                          # @pd_cnt
	.p2align	2, 0x0
pd_cnt:
	.long	0                               # 0x0

	.section	.rdata,"dr",discard,"??_C@_0P@LLIJJCME@pd?5INF?5k?$DN?$CFlld?6?$AA@"
	.globl	"??_C@_0P@LLIJJCME@pd?5INF?5k?$DN?$CFlld?6?$AA@" # @"??_C@_0P@LLIJJCME@pd?5INF?5k?$DN?$CFlld?6?$AA@"
"??_C@_0P@LLIJJCME@pd?5INF?5k?$DN?$CFlld?6?$AA@":
	.asciz	"pd INF k=%lld\n"

	.bss
	.globl	gd_cnt                          # @gd_cnt
	.p2align	2, 0x0
gd_cnt:
	.long	0                               # 0x0

	.section	.rdata,"dr",discard,"??_C@_0BG@FLFFMMNN@gd?5INF?5k?$DN?$CFlld?5e?$DN?$CFlld?6?$AA@"
	.globl	"??_C@_0BG@FLFFMMNN@gd?5INF?5k?$DN?$CFlld?5e?$DN?$CFlld?6?$AA@" # @"??_C@_0BG@FLFFMMNN@gd?5INF?5k?$DN?$CFlld?5e?$DN?$CFlld?6?$AA@"
"??_C@_0BG@FLFFMMNN@gd?5INF?5k?$DN?$CFlld?5e?$DN?$CFlld?6?$AA@":
	.asciz	"gd INF k=%lld e=%lld\n"

	.bss
	.globl	pm_cnt                          # @pm_cnt
	.p2align	2, 0x0
pm_cnt:
	.long	0                               # 0x0

	.section	.rdata,"dr",discard,"??_C@_0P@BFNPGNIE@pm?5INF?5k?$DN?$CFlld?6?$AA@"
	.globl	"??_C@_0P@BFNPGNIE@pm?5INF?5k?$DN?$CFlld?6?$AA@" # @"??_C@_0P@BFNPGNIE@pm?5INF?5k?$DN?$CFlld?6?$AA@"
"??_C@_0P@BFNPGNIE@pm?5INF?5k?$DN?$CFlld?6?$AA@":
	.asciz	"pm INF k=%lld\n"

	.bss
	.globl	gm_cnt                          # @gm_cnt
	.p2align	2, 0x0
gm_cnt:
	.long	0                               # 0x0

	.section	.rdata,"dr",discard,"??_C@_0P@MKLMPNNB@gm?5INF?5k?$DN?$CFlld?6?$AA@"
	.globl	"??_C@_0P@MKLMPNNB@gm?5INF?5k?$DN?$CFlld?6?$AA@" # @"??_C@_0P@MKLMPNNB@gm?5INF?5k?$DN?$CFlld?6?$AA@"
"??_C@_0P@MKLMPNNB@gm?5INF?5k?$DN?$CFlld?6?$AA@":
	.asciz	"gm INF k=%lld\n"

	.section	.rdata,"dr",discard,"??_C@_03DBLNGNIM@Int?$AA@"
	.globl	"??_C@_03DBLNGNIM@Int?$AA@"     # @"??_C@_03DBLNGNIM@Int?$AA@"
"??_C@_03DBLNGNIM@Int?$AA@":
	.asciz	"Int"

	.section	.rdata,"dr",discard,"??_C@_07GDNIBEMG@int64_t?$AA@"
	.globl	"??_C@_07GDNIBEMG@int64_t?$AA@" # @"??_C@_07GDNIBEMG@int64_t?$AA@"
"??_C@_07GDNIBEMG@int64_t?$AA@":
	.asciz	"int64_t"

	.section	.rdata,"dr",discard,"??_C@_05KKPNNHNB@Float?$AA@"
	.globl	"??_C@_05KKPNNHNB@Float?$AA@"   # @"??_C@_05KKPNNHNB@Float?$AA@"
"??_C@_05KKPNNHNB@Float?$AA@":
	.asciz	"Float"

	.section	.rdata,"dr",discard,"??_C@_06BNJCAIGJ@double?$AA@"
	.globl	"??_C@_06BNJCAIGJ@double?$AA@"  # @"??_C@_06BNJCAIGJ@double?$AA@"
"??_C@_06BNJCAIGJ@double?$AA@":
	.asciz	"double"

	.section	.rdata,"dr",discard,"??_C@_06ENNEIMBA@String?$AA@"
	.globl	"??_C@_06ENNEIMBA@String?$AA@"  # @"??_C@_06ENNEIMBA@String?$AA@"
"??_C@_06ENNEIMBA@String?$AA@":
	.asciz	"String"

	.section	.rdata,"dr",discard,"??_C@_05NCJLPPFE@char?$CK?$AA@"
	.globl	"??_C@_05NCJLPPFE@char?$CK?$AA@" # @"??_C@_05NCJLPPFE@char?$CK?$AA@"
"??_C@_05NCJLPPFE@char?$CK?$AA@":
	.asciz	"char*"

	.section	.rdata,"dr",discard,"??_C@_04PCGIEMCI@Bool?$AA@"
	.globl	"??_C@_04PCGIEMCI@Bool?$AA@"    # @"??_C@_04PCGIEMCI@Bool?$AA@"
"??_C@_04PCGIEMCI@Bool?$AA@":
	.asciz	"Bool"

	.section	.rdata,"dr",discard,"??_C@_03JBIPMCLC@int?$AA@"
	.globl	"??_C@_03JBIPMCLC@int?$AA@"     # @"??_C@_03JBIPMCLC@int?$AA@"
"??_C@_03JBIPMCLC@int?$AA@":
	.asciz	"int"

	.section	.rdata,"dr",discard,"??_C@_04IMAAEPPE@Char?$AA@"
	.globl	"??_C@_04IMAAEPPE@Char?$AA@"    # @"??_C@_04IMAAEPPE@Char?$AA@"
"??_C@_04IMAAEPPE@Char?$AA@":
	.asciz	"Char"

	.section	.rdata,"dr",discard,"??_C@_04ENMBGAPA@char?$AA@"
	.globl	"??_C@_04ENMBGAPA@char?$AA@"    # @"??_C@_04ENMBGAPA@char?$AA@"
"??_C@_04ENMBGAPA@char?$AA@":
	.asciz	"char"

	.section	.rdata,"dr",discard,"??_C@_04BOICIEDE@Unit?$AA@"
	.globl	"??_C@_04BOICIEDE@Unit?$AA@"    # @"??_C@_04BOICIEDE@Unit?$AA@"
"??_C@_04BOICIEDE@Unit?$AA@":
	.asciz	"Unit"

	.section	.rdata,"dr",discard,"??_C@_04GKJNKENE@void?$AA@"
	.globl	"??_C@_04GKJNKENE@void?$AA@"    # @"??_C@_04GKJNKENE@void?$AA@"
"??_C@_04GKJNKENE@void?$AA@":
	.asciz	"void"

	.section	.rdata,"dr",discard,"??_C@_01CLKCMJKC@?5?$AA@"
	.globl	"??_C@_01CLKCMJKC@?5?$AA@"      # @"??_C@_01CLKCMJKC@?5?$AA@"
"??_C@_01CLKCMJKC@?5?$AA@":
	.asciz	" "

	.section	.rdata,"dr",discard,"??_C@_02LNAEAIDO@?$DL?5?$AA@"
	.globl	"??_C@_02LNAEAIDO@?$DL?5?$AA@"  # @"??_C@_02LNAEAIDO@?$DL?5?$AA@"
"??_C@_02LNAEAIDO@?$DL?5?$AA@":
	.asciz	"; "

	.section	.rdata,"dr",discard,"??_C@_04HAHAIBGL@_v?$DL?5?$AA@"
	.globl	"??_C@_04HAHAIBGL@_v?$DL?5?$AA@" # @"??_C@_04HAHAIBGL@_v?$DL?5?$AA@"
"??_C@_04HAHAIBGL@_v?$DL?5?$AA@":
	.asciz	"_v; "

	.section	.rdata,"dr",discard,"??_C@_0BC@DJJDKMJG@typedef?5struct?5?$HL?5?$AA@"
	.globl	"??_C@_0BC@DJJDKMJG@typedef?5struct?5?$HL?5?$AA@" # @"??_C@_0BC@DJJDKMJG@typedef?5struct?5?$HL?5?$AA@"
"??_C@_0BC@DJJDKMJG@typedef?5struct?5?$HL?5?$AA@":
	.asciz	"typedef struct { "

	.section	.rdata,"dr",discard,"??_C@_02MJBDPJEM@?$HN?5?$AA@"
	.globl	"??_C@_02MJBDPJEM@?$HN?5?$AA@"  # @"??_C@_02MJBDPJEM@?$HN?5?$AA@"
"??_C@_02MJBDPJEM@?$HN?5?$AA@":
	.asciz	"} "

	.section	.rdata,"dr",discard,"??_C@_02NCGPMEBG@?$DL?6?$AA@"
	.globl	"??_C@_02NCGPMEBG@?$DL?6?$AA@"  # @"??_C@_02NCGPMEBG@?$DL?6?$AA@"
"??_C@_02NCGPMEBG@?$DL?6?$AA@":
	.asciz	";\n"

	.section	.rdata,"dr",discard,"??_C@_0CD@LNDJJAKB@typedef?5struct?5?$HL?5int?5tag?$DL?5union?5@"
	.globl	"??_C@_0CD@LNDJJAKB@typedef?5struct?5?$HL?5int?5tag?$DL?5union?5@" # @"??_C@_0CD@LNDJJAKB@typedef?5struct?5?$HL?5int?5tag?$DL?5union?5@"
"??_C@_0CD@LNDJJAKB@typedef?5struct?5?$HL?5int?5tag?$DL?5union?5@":
	.asciz	"typedef struct { int tag; union { "

	.section	.rdata,"dr",discard,"??_C@_0L@JHLMPDHF@?$HN?5data?$DL?5?$HN?5?$AA@"
	.globl	"??_C@_0L@JHLMPDHF@?$HN?5data?$DL?5?$HN?5?$AA@" # @"??_C@_0L@JHLMPDHF@?$HN?5data?$DL?5?$HN?5?$AA@"
"??_C@_0L@JHLMPDHF@?$HN?5data?$DL?5?$HN?5?$AA@":
	.asciz	"} data; } "

	.section	.rdata,"dr",discard,"??_C@_02KEGNLNML@?0?5?$AA@"
	.globl	"??_C@_02KEGNLNML@?0?5?$AA@"    # @"??_C@_02KEGNLNML@?0?5?$AA@"
"??_C@_02KEGNLNML@?0?5?$AA@":
	.asciz	", "

	.section	.rdata,"dr",discard,"??_C@_06LMHDPKD@?5else?5?$AA@"
	.globl	"??_C@_06LMHDPKD@?5else?5?$AA@" # @"??_C@_06LMHDPKD@?5else?5?$AA@"
"??_C@_06LMHDPKD@?5else?5?$AA@":
	.asciz	" else "

	.section	.rdata,"dr",discard,"??_C@_01MIFGBAGJ@?$CL?$AA@"
	.globl	"??_C@_01MIFGBAGJ@?$CL?$AA@"    # @"??_C@_01MIFGBAGJ@?$CL?$AA@"
"??_C@_01MIFGBAGJ@?$CL?$AA@":
	.asciz	"+"

	.section	.rdata,"dr",discard,"??_C@_01JOAMLHOP@?9?$AA@"
	.globl	"??_C@_01JOAMLHOP@?9?$AA@"      # @"??_C@_01JOAMLHOP@?9?$AA@"
"??_C@_01JOAMLHOP@?9?$AA@":
	.asciz	"-"

	.section	.rdata,"dr",discard,"??_C@_01NBENCBCI@?$CK?$AA@"
	.globl	"??_C@_01NBENCBCI@?$CK?$AA@"    # @"??_C@_01NBENCBCI@?$CK?$AA@"
"??_C@_01NBENCBCI@?$CK?$AA@":
	.asciz	"*"

	.section	.rdata,"dr",discard,"??_C@_01KMDKNFGN@?1?$AA@"
	.globl	"??_C@_01KMDKNFGN@?1?$AA@"      # @"??_C@_01KMDKNFGN@?1?$AA@"
"??_C@_01KMDKNFGN@?1?$AA@":
	.asciz	"/"

	.section	.rdata,"dr",discard,"??_C@_01FGNFDNOH@?$CF?$AA@"
	.globl	"??_C@_01FGNFDNOH@?$CF?$AA@"    # @"??_C@_01FGNFDNOH@?$CF?$AA@"
"??_C@_01FGNFDNOH@?$CF?$AA@":
	.asciz	"%"

	.section	.rdata,"dr",discard,"??_C@_02EGOFBIJA@?$DN?$DN?$AA@"
	.globl	"??_C@_02EGOFBIJA@?$DN?$DN?$AA@" # @"??_C@_02EGOFBIJA@?$DN?$DN?$AA@"
"??_C@_02EGOFBIJA@?$DN?$DN?$AA@":
	.asciz	"=="

	.section	.rdata,"dr",discard,"??_C@_02FDNJECIE@?$CB?$DN?$AA@"
	.globl	"??_C@_02FDNJECIE@?$CB?$DN?$AA@" # @"??_C@_02FDNJECIE@?$CB?$DN?$AA@"
"??_C@_02FDNJECIE@?$CB?$DN?$AA@":
	.asciz	"!="

	.section	.rdata,"dr",discard,"??_C@_01MNNFJEPP@?$DM?$AA@"
	.globl	"??_C@_01MNNFJEPP@?$DM?$AA@"    # @"??_C@_01MNNFJEPP@?$DM?$AA@"
"??_C@_01MNNFJEPP@?$DM?$AA@":
	.asciz	"<"

	.section	.rdata,"dr",discard,"??_C@_01PPODPGHN@?$DO?$AA@"
	.globl	"??_C@_01PPODPGHN@?$DO?$AA@"    # @"??_C@_01PPODPGHN@?$DO?$AA@"
"??_C@_01PPODPGHN@?$DO?$AA@":
	.asciz	">"

	.section	.rdata,"dr",discard,"??_C@_02EHCHHCKH@?$DM?$DN?$AA@"
	.globl	"??_C@_02EHCHHCKH@?$DM?$DN?$AA@" # @"??_C@_02EHCHHCKH@?$DM?$DN?$AA@"
"??_C@_02EHCHHCKH@?$DM?$DN?$AA@":
	.asciz	"<="

	.section	.rdata,"dr",discard,"??_C@_02EEKDKGMJ@?$DO?$DN?$AA@"
	.globl	"??_C@_02EEKDKGMJ@?$DO?$DN?$AA@" # @"??_C@_02EEKDKGMJ@?$DO?$DN?$AA@"
"??_C@_02EEKDKGMJ@?$DO?$DN?$AA@":
	.asciz	">="

	.section	.rdata,"dr",discard,"??_C@_02PPKAJPJL@?$CG?$CG?$AA@"
	.globl	"??_C@_02PPKAJPJL@?$CG?$CG?$AA@" # @"??_C@_02PPKAJPJL@?$CG?$CG?$AA@"
"??_C@_02PPKAJPJL@?$CG?$CG?$AA@":
	.asciz	"&&"

	.section	.rdata,"dr",discard,"??_C@_02NONPIBCD@?$HM?$HM?$AA@"
	.globl	"??_C@_02NONPIBCD@?$HM?$HM?$AA@" # @"??_C@_02NONPIBCD@?$HM?$HM?$AA@"
"??_C@_02NONPIBCD@?$HM?$HM?$AA@":
	.asciz	"||"

	.section	.rdata,"dr",discard,"??_C@_01OGPIMHDM@?$DP?$AA@"
	.globl	"??_C@_01OGPIMHDM@?$DP?$AA@"    # @"??_C@_01OGPIMHDM@?$DP?$AA@"
"??_C@_01OGPIMHDM@?$DP?$AA@":
	.asciz	"?"

	.section	.rdata,"dr",discard,"??_C@_01BJJEKLCA@?$CC?$AA@"
	.globl	"??_C@_01BJJEKLCA@?$CC?$AA@"    # @"??_C@_01BJJEKLCA@?$CC?$AA@"
"??_C@_01BJJEKLCA@?$CC?$AA@":
	.asciz	"\""

	.section	.rdata,"dr",discard,"??_C@_01HIHLOKLC@1?$AA@"
	.globl	"??_C@_01HIHLOKLC@1?$AA@"       # @"??_C@_01HIHLOKLC@1?$AA@"
"??_C@_01HIHLOKLC@1?$AA@":
	.asciz	"1"

	.section	.rdata,"dr",discard,"??_C@_01GBGANLPD@0?$AA@"
	.globl	"??_C@_01GBGANLPD@0?$AA@"       # @"??_C@_01GBGANLPD@0?$AA@"
"??_C@_01GBGANLPD@0?$AA@":
	.asciz	"0"

	.section	.rdata,"dr",discard,"??_C@_01ODHLEDKK@?$CI?$AA@"
	.globl	"??_C@_01ODHLEDKK@?$CI?$AA@"    # @"??_C@_01ODHLEDKK@?$CI?$AA@"
"??_C@_01ODHLEDKK@?$CI?$AA@":
	.asciz	"("

	.section	.rdata,"dr",discard,"??_C@_01PKGAHCOL@?$CJ?$AA@"
	.globl	"??_C@_01PKGAHCOL@?$CJ?$AA@"    # @"??_C@_01PKGAHCOL@?$CJ?$AA@"
"??_C@_01PKGAHCOL@?$CJ?$AA@":
	.asciz	")"

	.section	.rdata,"dr",discard,"??_C@_02LKHPCEFG@?$CI?$CB?$AA@"
	.globl	"??_C@_02LKHPCEFG@?$CI?$CB?$AA@" # @"??_C@_02LKHPCEFG@?$CI?$CB?$AA@"
"??_C@_02LKHPCEFG@?$CI?$CB?$AA@":
	.asciz	"(!"

	.section	.rdata,"dr",discard,"??_C@_01LFCBOECM@?4?$AA@"
	.globl	"??_C@_01LFCBOECM@?4?$AA@"      # @"??_C@_01LFCBOECM@?4?$AA@"
"??_C@_01LFCBOECM@?4?$AA@":
	.asciz	"."

	.section	.rdata,"dr",discard,"??_C@_03HGBNAECB@?$CI?$HL?5?$AA@"
	.globl	"??_C@_03HGBNAECB@?$CI?$HL?5?$AA@" # @"??_C@_03HGBNAECB@?$CI?$HL?5?$AA@"
"??_C@_03HGBNAECB@?$CI?$HL?5?$AA@":
	.asciz	"({ "

	.section	.rdata,"dr",discard,"??_C@_03MHLONNLM@?5?$DN?5?$AA@"
	.globl	"??_C@_03MHLONNLM@?5?$DN?5?$AA@" # @"??_C@_03MHLONNLM@?5?$DN?5?$AA@"
"??_C@_03MHLONNLM@?5?$DN?5?$AA@":
	.asciz	" = "

	.section	.rdata,"dr",discard,"??_C@_04FHHBEKKD@?$DL?5?$HN?$CJ?$AA@"
	.globl	"??_C@_04FHHBEKKD@?$DL?5?$HN?$CJ?$AA@" # @"??_C@_04FHHBEKKD@?$DL?5?$HN?$CJ?$AA@"
"??_C@_04FHHBEKKD@?$DL?5?$HN?$CJ?$AA@":
	.asciz	"; })"

	.section	.rdata,"dr",discard,"??_C@_03MEDKAJNC@?5?$DP?5?$AA@"
	.globl	"??_C@_03MEDKAJNC@?5?$DP?5?$AA@" # @"??_C@_03MEDKAJNC@?5?$DP?5?$AA@"
"??_C@_03MEDKAJNC@?5?$DP?5?$AA@":
	.asciz	" ? "

	.section	.rdata,"dr",discard,"??_C@_03MCPBMLDJ@?5?3?5?$AA@"
	.globl	"??_C@_03MCPBMLDJ@?5?3?5?$AA@"  # @"??_C@_03MCPBMLDJ@?5?3?5?$AA@"
"??_C@_03MCPBMLDJ@?5?3?5?$AA@":
	.asciz	" : "

	.section	.rdata,"dr",discard,"??_C@_0BB@GMPNLGNN@?$CI?$HL?5int64_t?5_m?5?$DN?5?$AA@"
	.globl	"??_C@_0BB@GMPNLGNN@?$CI?$HL?5int64_t?5_m?5?$DN?5?$AA@" # @"??_C@_0BB@GMPNLGNN@?$CI?$HL?5int64_t?5_m?5?$DN?5?$AA@"
"??_C@_0BB@GMPNLGNN@?$CI?$HL?5int64_t?5_m?5?$DN?5?$AA@":
	.asciz	"({ int64_t _m = "

	.section	.rdata,"dr",discard,"??_C@_03MOKBGDEE@?$CJ?$HL?5?$AA@"
	.globl	"??_C@_03MOKBGDEE@?$CJ?$HL?5?$AA@" # @"??_C@_03MOKBGDEE@?$CJ?$HL?5?$AA@"
"??_C@_03MOKBGDEE@?$CJ?$HL?5?$AA@":
	.asciz	"){ "

	.section	.rdata,"dr",discard,"??_C@_03GGOGOLDF@?5?$HN?$CJ?$AA@"
	.globl	"??_C@_03GGOGOLDF@?5?$HN?$CJ?$AA@" # @"??_C@_03GGOGOLDF@?5?$HN?$CJ?$AA@"
"??_C@_03GGOGOLDF@?5?$HN?$CJ?$AA@":
	.asciz	" })"

	.section	.rdata,"dr",discard,"??_C@_04GHJNJNPO@main?$AA@"
	.globl	"??_C@_04GHJNJNPO@main?$AA@"    # @"??_C@_04GHJNJNPO@main?$AA@"
"??_C@_04GHJNJNPO@main?$AA@":
	.asciz	"main"

	.section	.rdata,"dr",discard,"??_C@_0BG@PNJNKMEG@?$CDinclude?5?$DMstdint?4h?$DO?6?6?$AA@"
	.globl	"??_C@_0BG@PNJNKMEG@?$CDinclude?5?$DMstdint?4h?$DO?6?6?$AA@" # @"??_C@_0BG@PNJNKMEG@?$CDinclude?5?$DMstdint?4h?$DO?6?6?$AA@"
"??_C@_0BG@PNJNKMEG@?$CDinclude?5?$DMstdint?4h?$DO?6?6?$AA@":
	.asciz	"#include <stdint.h>\n\n"

	.section	.rdata,"dr",discard,"??_C@_01EEMJAFIK@?6?$AA@"
	.globl	"??_C@_01EEMJAFIK@?6?$AA@"      # @"??_C@_01EEMJAFIK@?6?$AA@"
"??_C@_01EEMJAFIK@?6?$AA@":
	.asciz	"\n"

	.section	.rdata,"dr",discard,"??_C@_0M@KFOIBCLG@main?5enter?6?$AA@"
	.globl	"??_C@_0M@KFOIBCLG@main?5enter?6?$AA@" # @"??_C@_0M@KFOIBCLG@main?5enter?6?$AA@"
"??_C@_0M@KFOIBCLG@main?5enter?6?$AA@":
	.asciz	"main enter\n"

	.section	.rdata,"dr",discard,"??_C@_09EAGLGKLK@M1_SOURCE?$AA@"
	.globl	"??_C@_09EAGLGKLK@M1_SOURCE?$AA@" # @"??_C@_09EAGLGKLK@M1_SOURCE?$AA@"
"??_C@_09EAGLGKLK@M1_SOURCE?$AA@":
	.asciz	"M1_SOURCE"

	.section	.rdata,"dr",discard,"??_C@_00CNPNBAHC@?$AA@"
	.globl	"??_C@_00CNPNBAHC@?$AA@"        # @"??_C@_00CNPNBAHC@?$AA@"
"??_C@_00CNPNBAHC@?$AA@":
	.zero	1

	.section	.rdata,"dr",discard,"??_C@_0BH@FHPGEPIB@error?3?5no?5source?5file?6?$AA@"
	.globl	"??_C@_0BH@FHPGEPIB@error?3?5no?5source?5file?6?$AA@" # @"??_C@_0BH@FHPGEPIB@error?3?5no?5source?5file?6?$AA@"
"??_C@_0BH@FHPGEPIB@error?3?5no?5source?5file?6?$AA@":
	.asciz	"error: no source file\n"

	.section	.rdata,"dr",discard,"??_C@_0L@FKHADIKO@read?5file?6?$AA@"
	.globl	"??_C@_0L@FKHADIKO@read?5file?6?$AA@" # @"??_C@_0L@FKHADIKO@read?5file?6?$AA@"
"??_C@_0L@FKHADIKO@read?5file?6?$AA@":
	.asciz	"read file\n"

	.section	.rdata,"dr",discard,"??_C@_0M@LMJDILKE@lexer?5init?6?$AA@"
	.globl	"??_C@_0M@LMJDILKE@lexer?5init?6?$AA@" # @"??_C@_0M@LMJDILKE@lexer?5init?6?$AA@"
"??_C@_0M@LMJDILKE@lexer?5init?6?$AA@":
	.asciz	"lexer init\n"

	.section	.rdata,"dr",discard,"??_C@_0BF@MAFMMOEI@parse_program?5enter?6?$AA@"
	.globl	"??_C@_0BF@MAFMMOEI@parse_program?5enter?6?$AA@" # @"??_C@_0BF@MAFMMOEI@parse_program?5enter?6?$AA@"
"??_C@_0BF@MAFMMOEI@parse_program?5enter?6?$AA@":
	.asciz	"parse_program enter\n"

	.section	.rdata,"dr",discard,"??_C@_0BE@CIAJLCHB@parse_program?5done?6?$AA@"
	.globl	"??_C@_0BE@CIAJLCHB@parse_program?5done?6?$AA@" # @"??_C@_0BE@CIAJLCHB@parse_program?5done?6?$AA@"
"??_C@_0BE@CIAJLCHB@parse_program?5done?6?$AA@":
	.asciz	"parse_program done\n"

	.lcomm	__local_stdio_printf_options._OptionsStorage,8,8 # @__local_stdio_printf_options._OptionsStorage
	.section	.debug$S,"dr"
	.p2align	2, 0x0
	.long	4                               # Debug section magic
	.long	241
	.long	.Ltmp1-.Ltmp0                   # Subsection size
.Ltmp0:
	.short	.Ltmp3-.Ltmp2                   # Record length
.Ltmp2:
	.short	4353                            # Record kind: S_OBJNAME
	.long	0                               # Signature
	.byte	0                               # Object name
	.p2align	2, 0x0
.Ltmp3:
	.short	.Ltmp5-.Ltmp4                   # Record length
.Ltmp4:
	.short	4412                            # Record kind: S_COMPILE3
	.long	0                               # Flags and language
	.short	208                             # CPUType
	.short	22                              # Frontend version
	.short	1
	.short	6
	.short	0
	.short	22016                           # Backend version
	.short	0
	.short	0
	.short	0
	.asciz	"clang version 22.1.6 (https://github.com/llvm/llvm-project fc4aad7b5db3fff421df9a9637605b9ca5667881)" # Null-terminated compiler version string
	.p2align	2, 0x0
.Ltmp5:
.Ltmp1:
	.p2align	2, 0x0
	.addrsig
	.addrsig_sym _vsnprintf
	.addrsig_sym ps_kind
	.addrsig_sym ps_line
	.addrsig_sym ps_col
	.addrsig_sym ps_str
	.addrsig_sym ps_int
	.addrsig_sym ps_adv
	.addrsig_sym m1_lexer_next
	.addrsig_sym ps_err
	.addrsig_sym mk_pr
	.addrsig_sym nk
	.addrsig_sym m0_alloc
	.addrsig_sym m0_set
	.addrsig_sym n_int
	.addrsig_sym n_str
	.addrsig_sym m0_store_string
	.addrsig_sym n_bool
	.addrsig_sym n_unit
	.addrsig_sym n_name
	.addrsig_sym n_bin
	.addrsig_sym n_not
	.addrsig_sym n_field
	.addrsig_sym n_call
	.addrsig_sym n_let
	.addrsig_sym n_match
	.addrsig_sym n_if
	.addrsig_sym t_name
	.addrsig_sym t_fn
	.addrsig_sym t_record
	.addrsig_sym t_sum
	.addrsig_sym t_app
	.addrsig_sym mk_param
	.addrsig_sym mk_fi
	.addrsig_sym mk_arm
	.addrsig_sym mk_ctor
	.addrsig_sym p_wild
	.addrsig_sym p_lit
	.addrsig_sym p_ctor
	.addrsig_sym p_name
	.addrsig_sym n_type_decl
	.addrsig_sym n_fn_decl
	.addrsig_sym n_extern
	.addrsig_sym n_mod
	.addrsig_sym n_prog
	.addrsig_sym list_rev
	.addrsig_sym m0_is_nil
	.addrsig_sym m0_cons
	.addrsig_sym m0_head
	.addrsig_sym m0_tail
	.addrsig_sym rev
	.addrsig_sym list_len
	.addrsig_sym gather_type_fields
	.addrsig_sym parse_type_expr
	.addrsig_sym gather_ctors
	.addrsig_sym parse_type_atom
	.addrsig_sym parse_type_app_ga
	.addrsig_sym parse_type_app
	.addrsig_sym parse_type_arrow
	.addrsig_sym gather_params
	.addrsig_sym parse_pat_atom
	.addrsig_sym m0_string_eq
	.addrsig_sym gather_args
	.addrsig_sym parse_impl
	.addrsig_sym parse_postfix_loop
	.addrsig_sym parse_postfix
	.addrsig_sym parse_atom
	.addrsig_sym parse_unary
	.addrsig_sym parse_mul_loop
	.addrsig_sym parse_mul
	.addrsig_sym parse_add_loop
	.addrsig_sym parse_add
	.addrsig_sym parse_cmp
	.addrsig_sym parse_and_loop
	.addrsig_sym parse_and
	.addrsig_sym parse_or_loop
	.addrsig_sym parse_or
	.addrsig_sym parse_expr
	.addrsig_sym gather_arms
	.addrsig_sym gather_field_inits
	.addrsig_sym gather_list_elems
	.addrsig_sym parse_decl
	.addrsig_sym fprintf
	.addrsig_sym __acrt_iob_func
	.addrsig_sym fflush
	.addrsig_sym gather_decls
	.addrsig_sym exit
	.addrsig_sym parse_module
	.addrsig_sym gather_modules
	.addrsig_sym parse_program
	.addrsig_sym reg_entry
	.addrsig_sym reg_name
	.addrsig_sym m0_load_string
	.addrsig_sym reg_type
	.addrsig_sym m0_get
	.addrsig_sym lookup_reg
	.addrsig_sym build_reg
	.addrsig_sym emit_c_type
	.addrsig_sym m0_print
	.addrsig_sym emit_typedef_ef
	.addrsig_sym emit_typedef_ec
	.addrsig_sym emit_typedef
	.addrsig_sym emit_c_expr_ea
	.addrsig_sym emit_c_expr_arms_ea
	.addrsig_sym emit_c_expr_ef
	.addrsig_sym emit_c_op
	.addrsig_sym emit_c_expr
	.addrsig_sym m0_print_int
	.addrsig_sym emit_extern
	.addrsig_sym emit_fn
	.addrsig_sym emit_module_pass1
	.addrsig_sym emit_module_pass2
	.addrsig_sym emit_module_pass3
	.addrsig_sym emit_module
	.addrsig_sym m0_get_env
	.addrsig_sym m0_read_file
	.addrsig_sym m1_lexer_init
	.addrsig_sym _vsprintf_l
	.addrsig_sym _vsnprintf_l
	.addrsig_sym __stdio_common_vsprintf
	.addrsig_sym __local_stdio_printf_options
	.addrsig_sym _vfprintf_l
	.addrsig_sym __stdio_common_vfprintf
	.addrsig_sym TK_EOF
	.addrsig_sym TK_INT
	.addrsig_sym TK_STRING
	.addrsig_sym TK_IDENT
	.addrsig_sym TK_ARROW
	.addrsig_sym TK_BIDI
	.addrsig_sym TK_EQEQ
	.addrsig_sym TK_NEQ
	.addrsig_sym TK_LT
	.addrsig_sym TK_GT
	.addrsig_sym TK_LE
	.addrsig_sym TK_GE
	.addrsig_sym TK_AND
	.addrsig_sym TK_OR
	.addrsig_sym TK_PIPE
	.addrsig_sym TK_COMMA
	.addrsig_sym TK_DOT
	.addrsig_sym TK_LBRACE
	.addrsig_sym TK_RBRACE
	.addrsig_sym TK_LPAREN
	.addrsig_sym TK_RPAREN
	.addrsig_sym TK_LBRACK
	.addrsig_sym TK_RBRACK
	.addrsig_sym TK_PLUS
	.addrsig_sym TK_MINUS
	.addrsig_sym TK_STAR
	.addrsig_sym TK_SLASH
	.addrsig_sym TK_PERCENT
	.addrsig_sym TK_UNIT
	.addrsig_sym TK_MODULE
	.addrsig_sym TK_TYPE
	.addrsig_sym TK_FN
	.addrsig_sym TK_LET
	.addrsig_sym TK_MATCH
	.addrsig_sym TK_IF
	.addrsig_sym TK_ELSE
	.addrsig_sym TK_TRUE
	.addrsig_sym TK_FALSE
	.addrsig_sym TK_EXTERNAL
	.addrsig_sym TK_NOT
	.addrsig_sym N_PROG
	.addrsig_sym N_MOD
	.addrsig_sym N_TYPE_DECL
	.addrsig_sym N_FN_DECL
	.addrsig_sym N_EXTERN
	.addrsig_sym N_INT
	.addrsig_sym N_STRING
	.addrsig_sym N_BOOL
	.addrsig_sym N_UNIT
	.addrsig_sym N_NAME
	.addrsig_sym N_BINARY
	.addrsig_sym N_NOT
	.addrsig_sym N_FIELD
	.addrsig_sym N_CALL
	.addrsig_sym N_LET
	.addrsig_sym N_MATCH
	.addrsig_sym N_IF
	.addrsig_sym N_RECORD
	.addrsig_sym T_NAMED
	.addrsig_sym T_FN
	.addrsig_sym T_RECORD
	.addrsig_sym T_SUM
	.addrsig_sym T_APP
	.addrsig_sym OP_ADD
	.addrsig_sym OP_SUB
	.addrsig_sym OP_MUL
	.addrsig_sym OP_DIV
	.addrsig_sym OP_MOD
	.addrsig_sym OP_EQ
	.addrsig_sym OP_NEQ
	.addrsig_sym OP_LT
	.addrsig_sym OP_GT
	.addrsig_sym OP_LE
	.addrsig_sym OP_GE
	.addrsig_sym OP_AND
	.addrsig_sym OP_OR
	.addrsig_sym OP_IMPL
	.addrsig_sym OP_IFF
	.addrsig_sym P_WILD
	.addrsig_sym P_LIT
	.addrsig_sym P_CTOR
	.addrsig_sym P_NAME
	.addrsig_sym m0_nil
	.addrsig_sym pd_cnt
	.addrsig_sym gd_cnt
	.addrsig_sym pm_cnt
	.addrsig_sym gm_cnt
	.addrsig_sym __local_stdio_printf_options._OptionsStorage
