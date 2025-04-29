#ifndef TL13BNF_H
#define TL13BNF_H

typedef enum
{
  /*typeCon,
  typeId,
  typeOpr*/
  typePrgm,
  typeNum,
  typeId,
  typeB,
  typeDecl,
  typeType,
  typeStmtSeq,
  typeStmt,
  typeAsgn,
  typeIf,
  typeElse,
  typeWhile,
  typeWriteInt,
  typeExpr,
  typeSimpExpr,
  typeTerm,
  typeFactor,
  typeOpr,
} nodeEnum;

typedef union nodeTypeTag nodeType;

/* constants */
typedef struct
{
  nodeEnum type; /* type of node */
  int value;     /* value of constant */
} numNodeType;

/* identifiers */
typedef struct
{
  nodeEnum type; /* type of node */
  char *str;     /* subscript to ident array */
} idNodeType;

/* operators */
typedef struct
{
  nodeEnum type; /* type of node */
  char *tf;      /* boolean "true" or "false" */
} bNodeType;

// program node
typedef struct
{
  nodeEnum type; /* type of node */
  // char *str;     /* program name */
  union nodeTypeTag *decl;    /* declarations */
  union nodeTypeTag *stmtSeq; /* statement sequence */
} prgmNodeType;

typedef struct
{
  nodeEnum type;
  union nodeTypeTag *typ;  /* type of declaration */
  union nodeTypeTag *id;   /* identifier */
  union nodeTypeTag *decl; /* next declaration */
} declNodeType;

typedef struct
{
  nodeEnum type; /* type of node */
  int t;
} typeNodeType;

typedef struct
{
  nodeEnum type;              /* type of node */
  union nodeTypeTag *stmt;    /* identifier */
  union nodeTypeTag *stmtSeq; /* statement sequence */
} stmtSeqNodeType;

typedef struct
{
  nodeEnum type;
  /*
  union nodeTypeTag asgn;
  union nodeTypeTag if0;
  union nodeTypeTag while0;
  union nodeTypeTag writeInt;
  */
  nodeEnum childType;
  union nodeTypeTag *stmtType;
} stmtNodeType;

typedef struct
{
  nodeEnum type;           /* type of node */
  union nodeTypeTag *id;   /* identifier */
  union nodeTypeTag *expr; /* expression */
} asgnNodeType;

typedef struct
{
  nodeEnum type;              /* type of node */
  union nodeTypeTag *expr;    /* expression */
  union nodeTypeTag *stmtSeq; /* statement */
  union nodeTypeTag *else0;   /* statement */
} ifNodeType;

typedef struct
{
  nodeEnum type;              /* type of node */
  union nodeTypeTag *stmtSeq; /* statement */
} elseNodeType;

typedef struct
{
  nodeEnum type;              /* type of node */
  union nodeTypeTag *expr;    /* expression */
  union nodeTypeTag *stmtSeq; /* statement */
} whileNodeType;

typedef struct
{
  nodeEnum type;           /* type of node */
  union nodeTypeTag *expr; /* expression */
} writeIntNodeType;

typedef struct
{
  nodeEnum type; /* type of node */
  int numOps;
  union nodeTypeTag *simpExpr0; /* simple expression */
  union nodeTypeTag *simpExpr1; /* simple expression */
} exprNodeType;

typedef struct
{
  nodeEnum type; /* type of node */
  int numOps;
  union nodeTypeTag *term0; /* term */
  union nodeTypeTag *term1; /* expression */
} simpExprNodeType;

typedef struct
{
  nodeEnum type; /* type of node */
  int numOps;
  union nodeTypeTag *factor0; /* factor */
  union nodeTypeTag *factor1; /* term */
} termNodeType;
typedef struct
{
  nodeEnum type; /* type of node */
                 /*
                 union nodeTypeTag *id;
                 int poop;
                 union nodeTypeTag b;
                 union nodeTypeTag expr;
                 */
  nodeEnum childType;
  union nodeTypeTag *fn;
} factorNodeType;

// template struct productions
typedef struct
{
  nodeEnum type;            /* type of node */
  int oper;                 /* operator */
  int nops;                 /* number of operands */
  union nodeTypeTag *op[1]; /* operands (expandable) */
} oprNodeType;

typedef union nodeTypeTag
{
  nodeEnum type; /* type of node */
  numNodeType n; /* constants */
  idNodeType id; /* identifiers */
  bNodeType b;   /* boollit */
  prgmNodeType p;
  declNodeType d;
  typeNodeType ty;
  stmtSeqNodeType ss;
  stmtNodeType s;
  asgnNodeType a;
  ifNodeType i;
  elseNodeType el;
  whileNodeType w;
  writeIntNodeType wi;
  exprNodeType ex;
  simpExprNodeType se;
  termNodeType te;
  factorNodeType f;
  oprNodeType opr; /* operators */
} nodeType;

// extern int sym[26];
/* Function declarations */
nodeType *nf(int val);
nodeType *id(char *s);
nodeType *bb(char *s);
nodeType *opr(int oper, int nops, ...);
nodeType *prgm(nodeType *decl, nodeType *stmtSeq);
nodeType *decl(nodeType *type, nodeType *id, nodeType *decl);
nodeType *type(int t);
nodeType *stmtSeq(nodeType *stmt, nodeType *stmtSeq);
nodeType *stmt(nodeType *stmtType);
nodeType *asgn(nodeType *id, nodeType *expr);
nodeType *if0(nodeType *expr, nodeType *stmtSeq, nodeType *else0);
nodeType *else0(nodeType *stmtSeq);
nodeType *while0(nodeType *expr, nodeType *stmtSeq);
nodeType *writeInt(nodeType *expr);
nodeType *expr(nodeType *simpExpr0, nodeType *simpExpr1);
nodeType *simpExpr(nodeType *term0, nodeType *term1);
nodeType *term(nodeType *factor0, nodeType *factor1);
nodeType *factor(nodeType *fn);

int ex(nodeType *p); // Your code-generation function
void freeNode(nodeType *p);

#endif