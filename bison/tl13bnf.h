#ifndef TL13BNF_H
#define TL13BNF_H

typedef enum
{
  /*typeCon,
  typeId,
  typeOpr*/
  typeNum,
  typeId,
  typeB,
  /*
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
  */
  typeOpr,
} nodeEnum;

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

typedef struct
{
  nodeEnum type;            /* type of node */
  int oper;                 /* operator */
  int nops;                 /* number of operands */
  union nodeTypeTag *op[1]; /* operands (expandable) */
} oprNodeType;

typedef union nodeTypeTag
{
  nodeEnum type;   /* type of node */
  numNodeType n;   /* constants */
  idNodeType id;   /* identifiers */
  bNodeType b;     /* boollit */
  oprNodeType opr; /* operators */
} nodeType;

// extern int sym[26];
/* Function declarations */
nodeType *nf(int val);
nodeType *id(char *s);
nodeType *bb(char *s);
nodeType *opr(int oper, int nops, ...);

#endif