#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

/* Module: M1Ast */
typedef struct {
  char* file;  
  int64_t line;  
  int64_t col;  
} SrcLoc;
typedef struct {
  char* data;  
  int64_t len;  
} StringView;
typedef struct EffectAtom EffectAtom;
struct EffectAtom {
  int tag;
  union {
    struct {
      char* f0;      
      char* f1;      
    } EffRead;    
    struct {
      char* f0;      
      char* f1;      
    } EffWrite;    
    struct {
      char* f0;      
    } EffAlloc;    
    struct {
      char* f0;      
    } EffFree;    
    struct {
      char* f0;      
    } EffTime;    
    struct {
      char* f0;      
      char* f1;      
    } EffNet;    
    char _unused[1];
    } data;
};
enum EffectAtom_tag {
  EffectAtom_EffRead,
  EffectAtom_EffWrite,
  EffectAtom_EffAlloc,
  EffectAtom_EffFree,
  EffectAtom_EffTime,
  EffectAtom_EffNet,
  EffectAtom_EffIO
};
typedef struct {
  int64_t atoms;  
  int64_t count;  
} EffectLabel;
typedef struct Linearity Linearity;
struct Linearity {
  int tag;
  union {
    char _unused[1];
    } data;
};
enum Linearity_tag {
  Linearity_LinLinear,
  Linearity_LinAffine,
  Linearity_LinPersistent
};
typedef struct TypeKind TypeKind;
struct TypeKind {
  int tag;
  union {
    char _unused[1];
    } data;
};
enum TypeKind_tag {
  TypeKind_TyInt,
  TypeKind_TyFloat,
  TypeKind_TyString,
  TypeKind_TyChar,
  TypeKind_TyBool,
  TypeKind_TyUnit,
  TypeKind_TyNamed,
  TypeKind_TyVar,
  TypeKind_TyPi,
  TypeKind_TySigma,
  TypeKind_TyFn,
  TypeKind_TyRecord,
  TypeKind_TySum,
  TypeKind_TyApp,
  TypeKind_TyLinear,
  TypeKind_TyEffect,
  TypeKind_TyEventual,
  TypeKind_TyError
};
typedef struct {
  StringView name;  
  int64_t ty;  
} TypeField;
typedef struct {
  StringView name;  
  int64_t arg;  
} TypeCtor;
typedef struct {
  TypeKind kind;  
  SrcLoc loc;  
  StringView name;  
  StringView param_name;  
  int64_t param_type;  
  int64_t body_type;  
  int64_t fn_params;  
  int64_t fn_count;  
  int64_t fn_ret;  
  int64_t rec_fields;  
  int64_t rec_count;  
  int64_t sum_ctors;  
  int64_t sum_count;  
  int64_t app_base;  
  int64_t app_args;  
  int64_t app_count;  
  int64_t linear_inner;  
  Linearity linear_mod;  
  int64_t effect_inner;  
  EffectLabel effect_label;  
  int64_t eventual_val;  
  int64_t eventual_err;  
} M1Type;
typedef struct PatternKind PatternKind;
struct PatternKind {
  int tag;
  union {
    char _unused[1];
    } data;
};
enum PatternKind_tag {
  PatternKind_PatWildcard,
  PatternKind_PatLiteral,
  PatternKind_PatConstructor,
  PatternKind_PatRecord,
  PatternKind_PatName,
  PatternKind_PatOr,
  PatternKind_PatGuard
};
typedef struct {
  StringView name;  
  int64_t pat;  
} FieldPat;
typedef struct {
  PatternKind kind;  
  SrcLoc loc;  
  int64_t lit_val;  
  StringView ctor_name;  
  int64_t ctor_arg;  
  int64_t rec_fields;  
  int64_t rec_count;  
  StringView var_name;  
  int64_t or_left;  
  int64_t or_right;  
  int64_t guard_pat;  
  int64_t guard_cond;  
} M1Pattern;
typedef struct ExprKind ExprKind;
struct ExprKind {
  int tag;
  union {
    char _unused[1];
    } data;
};
enum ExprKind_tag {
  ExprKind_ExInt,
  ExprKind_ExFloat,
  ExprKind_ExString,
  ExprKind_ExChar,
  ExprKind_ExBool,
  ExprKind_ExUnit,
  ExprKind_ExName,
  ExprKind_ExBinary,
  ExprKind_ExNot,
  ExprKind_ExFieldAccess,
  ExprKind_ExCall,
  ExprKind_ExAnnot,
  ExprKind_ExLet,
  ExprKind_ExLambda,
  ExprKind_ExMatch,
  ExprKind_ExIf,
  ExprKind_ExRecord,
  ExprKind_ExList,
  ExprKind_ExGroup,
  ExprKind_ExQuantForall,
  ExprKind_ExQuantExists,
  ExprKind_ExEffectLabel
};
typedef struct BinaryOp BinaryOp;
struct BinaryOp {
  int tag;
  union {
    char _unused[1];
    } data;
};
enum BinaryOp_tag {
  BinaryOp_OpAdd,
  BinaryOp_OpSub,
  BinaryOp_OpMul,
  BinaryOp_OpDiv,
  BinaryOp_OpMod,
  BinaryOp_OpEq,
  BinaryOp_OpNeq,
  BinaryOp_OpLt,
  BinaryOp_OpGt,
  BinaryOp_OpLe,
  BinaryOp_OpGe,
  BinaryOp_OpAnd,
  BinaryOp_OpOr,
  BinaryOp_OpImpl,
  BinaryOp_OpIff
};
typedef struct {
  StringView name;  
  M1Type ty;  
} Param;
typedef struct {
  StringView name;  
  int64_t value;  
} FieldInit;
typedef struct {
  M1Pattern pattern;  
  int64_t body;  
  int64_t guard;  
} MatchArm;
typedef struct {
  ExprKind kind;  
  SrcLoc loc;  
  M1Type ty;  
  EffectLabel effect;  
  int64_t int_val;  
  int64_t float_val;  
  StringView str_val;  
  int64_t char_val;  
  int64_t bool_val;  
  StringView name_val;  
  BinaryOp bin_op;  
  int64_t bin_left;  
  int64_t bin_right;  
  int64_t not_expr;  
  int64_t field_expr;  
  StringView field_name;  
  int64_t call_expr;  
  int64_t call_args;  
  int64_t call_count;  
  int64_t annot_expr;  
  M1Type annot_type;  
  StringView let_name;  
  M1Type let_type;  
  int64_t let_value;  
  int64_t let_body;  
  int64_t lam_params;  
  int64_t lam_count;  
  M1Type lam_ret;  
  int64_t lam_body;  
  int64_t match_scrut;  
  int64_t match_arms;  
  int64_t match_count;  
  int64_t if_cond;  
  int64_t if_then;  
  int64_t if_else;  
  int64_t rec_fields;  
  int64_t rec_count;  
  int64_t list_elems;  
  int64_t list_count;  
  int64_t group_expr;  
  StringView quant_var;  
  M1Type quant_type;  
  int64_t quant_body;  
  EffectLabel eff_label;  
  int64_t eff_inner;  
} M1Expr;
typedef struct ConstraintKind ConstraintKind;
struct ConstraintKind {
  int tag;
  union {
    char _unused[1];
    } data;
};
enum ConstraintKind_tag {
  ConstraintKind_CkInvariant,
  ConstraintKind_CkAlways,
  ConstraintKind_CkNever,
  ConstraintKind_CkPhysical
};
typedef struct {
  ConstraintKind kind;  
  SrcLoc loc;  
  StringView name;  
  M1Expr body;  
  StringView scope;  
} M1Constraint;
typedef struct DeclKind DeclKind;
struct DeclKind {
  int tag;
  union {
    char _unused[1];
    } data;
};
enum DeclKind_tag {
  DeclKind_DeclType,
  DeclKind_DeclProp,
  DeclKind_DeclFn,
  DeclKind_DeclExtern,
  DeclKind_DeclConstraint
};
typedef struct PropForm PropForm;
struct PropForm {
  int tag;
  union {
    char _unused[1];
    } data;
};
enum PropForm_tag {
  PropForm_FormDerivation,
  PropForm_FormBidirectional,
  PropForm_FormSignature
};
typedef struct {
  DeclKind kind;  
  SrcLoc loc;  
  StringView type_name;  
  M1Type type_body;  
  StringView prop_name;  
  M1Type prop_type;  
  M1Expr prop_body;  
  PropForm prop_form;  
  StringView fn_name;  
  int64_t fn_params;  
  int64_t fn_count;  
  M1Type fn_ret;  
  M1Expr fn_body;  
  StringView ext_cname;  
  M1Type ext_type;  
  M1Constraint constraint;  
} M1Decl;
typedef struct {
  StringView name;  
  int64_t decls;  
  int64_t count;  
} M1Module;
typedef struct {
  int64_t modules;  
  int64_t count;  
} M1Program;
static inline EffectAtom EffRead(char* x0, char* x1) {
  EffectAtom v = { .tag = EffectAtom_EffRead, .data.EffRead = {.f0 = x0, .f1 = x1} };  
  return v;
}
static inline EffectAtom EffWrite(char* x0, char* x1) {
  EffectAtom v = { .tag = EffectAtom_EffWrite, .data.EffWrite = {.f0 = x0, .f1 = x1} };  
  return v;
}
static inline EffectAtom EffAlloc(char* x0) {
  EffectAtom v = { .tag = EffectAtom_EffAlloc, .data.EffAlloc = {.f0 = x0} };  
  return v;
}
static inline EffectAtom EffFree(char* x0) {
  EffectAtom v = { .tag = EffectAtom_EffFree, .data.EffFree = {.f0 = x0} };  
  return v;
}
static inline EffectAtom EffTime(char* x0) {
  EffectAtom v = { .tag = EffectAtom_EffTime, .data.EffTime = {.f0 = x0} };  
  return v;
}
static inline EffectAtom EffNet(char* x0, char* x1) {
  EffectAtom v = { .tag = EffectAtom_EffNet, .data.EffNet = {.f0 = x0, .f1 = x1} };  
  return v;
}
static inline EffectAtom EffIO() {
  EffectAtom v = { .tag = EffectAtom_EffIO, .data = {0} };
  return v;
}
static inline Linearity LinLinear() {
  Linearity v = { .tag = Linearity_LinLinear, .data = {0} };
  return v;
}
static inline Linearity LinAffine() {
  Linearity v = { .tag = Linearity_LinAffine, .data = {0} };
  return v;
}
static inline Linearity LinPersistent() {
  Linearity v = { .tag = Linearity_LinPersistent, .data = {0} };
  return v;
}
static inline TypeKind TyInt() {
  TypeKind v = { .tag = TypeKind_TyInt, .data = {0} };
  return v;
}
static inline TypeKind TyFloat() {
  TypeKind v = { .tag = TypeKind_TyFloat, .data = {0} };
  return v;
}
static inline TypeKind TyString() {
  TypeKind v = { .tag = TypeKind_TyString, .data = {0} };
  return v;
}
static inline TypeKind TyChar() {
  TypeKind v = { .tag = TypeKind_TyChar, .data = {0} };
  return v;
}
static inline TypeKind TyBool() {
  TypeKind v = { .tag = TypeKind_TyBool, .data = {0} };
  return v;
}
static inline TypeKind TyUnit() {
  TypeKind v = { .tag = TypeKind_TyUnit, .data = {0} };
  return v;
}
static inline TypeKind TyNamed() {
  TypeKind v = { .tag = TypeKind_TyNamed, .data = {0} };
  return v;
}
static inline TypeKind TyVar() {
  TypeKind v = { .tag = TypeKind_TyVar, .data = {0} };
  return v;
}
static inline TypeKind TyPi() {
  TypeKind v = { .tag = TypeKind_TyPi, .data = {0} };
  return v;
}
static inline TypeKind TySigma() {
  TypeKind v = { .tag = TypeKind_TySigma, .data = {0} };
  return v;
}
static inline TypeKind TyFn() {
  TypeKind v = { .tag = TypeKind_TyFn, .data = {0} };
  return v;
}
static inline TypeKind TyRecord() {
  TypeKind v = { .tag = TypeKind_TyRecord, .data = {0} };
  return v;
}
static inline TypeKind TySum() {
  TypeKind v = { .tag = TypeKind_TySum, .data = {0} };
  return v;
}
static inline TypeKind TyApp() {
  TypeKind v = { .tag = TypeKind_TyApp, .data = {0} };
  return v;
}
static inline TypeKind TyLinear() {
  TypeKind v = { .tag = TypeKind_TyLinear, .data = {0} };
  return v;
}
static inline TypeKind TyEffect() {
  TypeKind v = { .tag = TypeKind_TyEffect, .data = {0} };
  return v;
}
static inline TypeKind TyEventual() {
  TypeKind v = { .tag = TypeKind_TyEventual, .data = {0} };
  return v;
}
static inline TypeKind TyError() {
  TypeKind v = { .tag = TypeKind_TyError, .data = {0} };
  return v;
}
static inline PatternKind PatWildcard() {
  PatternKind v = { .tag = PatternKind_PatWildcard, .data = {0} };
  return v;
}
static inline PatternKind PatLiteral() {
  PatternKind v = { .tag = PatternKind_PatLiteral, .data = {0} };
  return v;
}
static inline PatternKind PatConstructor() {
  PatternKind v = { .tag = PatternKind_PatConstructor, .data = {0} };
  return v;
}
static inline PatternKind PatRecord() {
  PatternKind v = { .tag = PatternKind_PatRecord, .data = {0} };
  return v;
}
static inline PatternKind PatName() {
  PatternKind v = { .tag = PatternKind_PatName, .data = {0} };
  return v;
}
static inline PatternKind PatOr() {
  PatternKind v = { .tag = PatternKind_PatOr, .data = {0} };
  return v;
}
static inline PatternKind PatGuard() {
  PatternKind v = { .tag = PatternKind_PatGuard, .data = {0} };
  return v;
}
static inline ExprKind ExInt() {
  ExprKind v = { .tag = ExprKind_ExInt, .data = {0} };
  return v;
}
static inline ExprKind ExFloat() {
  ExprKind v = { .tag = ExprKind_ExFloat, .data = {0} };
  return v;
}
static inline ExprKind ExString() {
  ExprKind v = { .tag = ExprKind_ExString, .data = {0} };
  return v;
}
static inline ExprKind ExChar() {
  ExprKind v = { .tag = ExprKind_ExChar, .data = {0} };
  return v;
}
static inline ExprKind ExBool() {
  ExprKind v = { .tag = ExprKind_ExBool, .data = {0} };
  return v;
}
static inline ExprKind ExUnit() {
  ExprKind v = { .tag = ExprKind_ExUnit, .data = {0} };
  return v;
}
static inline ExprKind ExName() {
  ExprKind v = { .tag = ExprKind_ExName, .data = {0} };
  return v;
}
static inline ExprKind ExBinary() {
  ExprKind v = { .tag = ExprKind_ExBinary, .data = {0} };
  return v;
}
static inline ExprKind ExNot() {
  ExprKind v = { .tag = ExprKind_ExNot, .data = {0} };
  return v;
}
static inline ExprKind ExFieldAccess() {
  ExprKind v = { .tag = ExprKind_ExFieldAccess, .data = {0} };
  return v;
}
static inline ExprKind ExCall() {
  ExprKind v = { .tag = ExprKind_ExCall, .data = {0} };
  return v;
}
static inline ExprKind ExAnnot() {
  ExprKind v = { .tag = ExprKind_ExAnnot, .data = {0} };
  return v;
}
static inline ExprKind ExLet() {
  ExprKind v = { .tag = ExprKind_ExLet, .data = {0} };
  return v;
}
static inline ExprKind ExLambda() {
  ExprKind v = { .tag = ExprKind_ExLambda, .data = {0} };
  return v;
}
static inline ExprKind ExMatch() {
  ExprKind v = { .tag = ExprKind_ExMatch, .data = {0} };
  return v;
}
static inline ExprKind ExIf() {
  ExprKind v = { .tag = ExprKind_ExIf, .data = {0} };
  return v;
}
static inline ExprKind ExRecord() {
  ExprKind v = { .tag = ExprKind_ExRecord, .data = {0} };
  return v;
}
static inline ExprKind ExList() {
  ExprKind v = { .tag = ExprKind_ExList, .data = {0} };
  return v;
}
static inline ExprKind ExGroup() {
  ExprKind v = { .tag = ExprKind_ExGroup, .data = {0} };
  return v;
}
static inline ExprKind ExQuantForall() {
  ExprKind v = { .tag = ExprKind_ExQuantForall, .data = {0} };
  return v;
}
static inline ExprKind ExQuantExists() {
  ExprKind v = { .tag = ExprKind_ExQuantExists, .data = {0} };
  return v;
}
static inline ExprKind ExEffectLabel() {
  ExprKind v = { .tag = ExprKind_ExEffectLabel, .data = {0} };
  return v;
}
static inline BinaryOp OpAdd() {
  BinaryOp v = { .tag = BinaryOp_OpAdd, .data = {0} };
  return v;
}
static inline BinaryOp OpSub() {
  BinaryOp v = { .tag = BinaryOp_OpSub, .data = {0} };
  return v;
}
static inline BinaryOp OpMul() {
  BinaryOp v = { .tag = BinaryOp_OpMul, .data = {0} };
  return v;
}
static inline BinaryOp OpDiv() {
  BinaryOp v = { .tag = BinaryOp_OpDiv, .data = {0} };
  return v;
}
static inline BinaryOp OpMod() {
  BinaryOp v = { .tag = BinaryOp_OpMod, .data = {0} };
  return v;
}
static inline BinaryOp OpEq() {
  BinaryOp v = { .tag = BinaryOp_OpEq, .data = {0} };
  return v;
}
static inline BinaryOp OpNeq() {
  BinaryOp v = { .tag = BinaryOp_OpNeq, .data = {0} };
  return v;
}
static inline BinaryOp OpLt() {
  BinaryOp v = { .tag = BinaryOp_OpLt, .data = {0} };
  return v;
}
static inline BinaryOp OpGt() {
  BinaryOp v = { .tag = BinaryOp_OpGt, .data = {0} };
  return v;
}
static inline BinaryOp OpLe() {
  BinaryOp v = { .tag = BinaryOp_OpLe, .data = {0} };
  return v;
}
static inline BinaryOp OpGe() {
  BinaryOp v = { .tag = BinaryOp_OpGe, .data = {0} };
  return v;
}
static inline BinaryOp OpAnd() {
  BinaryOp v = { .tag = BinaryOp_OpAnd, .data = {0} };
  return v;
}
static inline BinaryOp OpOr() {
  BinaryOp v = { .tag = BinaryOp_OpOr, .data = {0} };
  return v;
}
static inline BinaryOp OpImpl() {
  BinaryOp v = { .tag = BinaryOp_OpImpl, .data = {0} };
  return v;
}
static inline BinaryOp OpIff() {
  BinaryOp v = { .tag = BinaryOp_OpIff, .data = {0} };
  return v;
}
static inline ConstraintKind CkInvariant() {
  ConstraintKind v = { .tag = ConstraintKind_CkInvariant, .data = {0} };
  return v;
}
static inline ConstraintKind CkAlways() {
  ConstraintKind v = { .tag = ConstraintKind_CkAlways, .data = {0} };
  return v;
}
static inline ConstraintKind CkNever() {
  ConstraintKind v = { .tag = ConstraintKind_CkNever, .data = {0} };
  return v;
}
static inline ConstraintKind CkPhysical() {
  ConstraintKind v = { .tag = ConstraintKind_CkPhysical, .data = {0} };
  return v;
}
static inline DeclKind DeclType() {
  DeclKind v = { .tag = DeclKind_DeclType, .data = {0} };
  return v;
}
static inline DeclKind DeclProp() {
  DeclKind v = { .tag = DeclKind_DeclProp, .data = {0} };
  return v;
}
static inline DeclKind DeclFn() {
  DeclKind v = { .tag = DeclKind_DeclFn, .data = {0} };
  return v;
}
static inline DeclKind DeclExtern() {
  DeclKind v = { .tag = DeclKind_DeclExtern, .data = {0} };
  return v;
}
static inline DeclKind DeclConstraint() {
  DeclKind v = { .tag = DeclKind_DeclConstraint, .data = {0} };
  return v;
}
static inline PropForm FormDerivation() {
  PropForm v = { .tag = PropForm_FormDerivation, .data = {0} };
  return v;
}
static inline PropForm FormBidirectional() {
  PropForm v = { .tag = PropForm_FormBidirectional, .data = {0} };
  return v;
}
static inline PropForm FormSignature() {
  PropForm v = { .tag = PropForm_FormSignature, .data = {0} };
  return v;
}