/************************  calc1.y           *******************/

%{
#include "tl13bnf.h"
#include <stdio.h>
#include <stdarg.h>
int yylex(void);
void yyerror(char *);
%}

//symbols
%union
{
  int numVal;
  char* sVal;
  nodeType *nPtr;
};
%start program
%left LP RP ASGN SC OP2 OP3 OP4 IF THEN ELSE BEGIN_ END WHILE DO PROGRAM VAR AS INT BOOL WRITEINT READINT
%token <numVal> num
%token <sVal> boollit ident

%type <nPtr> program declarations type statementSequence statement assignment ifStatement elseClause whileStatement writeInt expression simpleExpression term factor
/* %left declarations
%left type
%left statementSequence
%left statement
%left assignment
%left ifStatement
%left elseClause
%left writeInt
%left expression
%left simpleExpression
%left term
%left factor
 %left '|' 
 %left '&' 
 %left '+' '-' 
 */
%%                   /* beginning of rules section */
program:  PROGRAM declarations BEGIN_ statementSequence END {$$ = prgm($2, $4); ex($$);}
         ;
declarations:    VAR ident AS type SC declarations {$$ = decl(id($2), $4, $6); }
         |
         /*empty */ {$$ = NULL;}
         ;
type:    INT {$$ = type(INT); }
         |
         BOOL {$$ = type(BOOL); }
         ;
statementSequence: statement SC statementSequence {$$ = stmtSeq($1, $3); }
                    |
                    /*empty */{$$ = NULL;}
                    ;
statement: assignment { $$ = stmt($1); }
           |
           ifStatement { $$ = stmt($1); }
           |
           whileStatement { $$ = stmt($1); }
           |
           writeInt { $$ = stmt($1); }
           ;
assignment: ident ASGN expression {$$ = asgn(id($1), $3); }
            |
            ident ASGN READINT {$$ = asgn(id($1), NULL); }
            ;
ifStatement: IF expression THEN statementSequence elseClause END {$$ = if0($2, $4, $5); }
            ;
elseClause: ELSE statementSequence {$$ = else0($2); }
            |
  /*empty */{$$ = NULL; }
            ;
whileStatement: WHILE expression DO statementSequence END {$$ = while0($2, $4); }
            ;
writeInt: WRITEINT expression {$$ = writeInt($2); }
          ;

expression: simpleExpression {$$ = expr($1, NULL); }
            |
            simpleExpression OP4 simpleExpression {$$ = expr($1, $3); }
            ;

simpleExpression: term OP3 term {$$ = simpExpr($1, $3); }
                  |
                  term {$$ = simpExpr($1, NULL); }
                  ;

term: factor OP2 factor {$$ = term($1, $3); }
      |
      factor { $$ = term($1,NULL); }
      ;
factor: ident { $$ = factor(id($1)); }
      |
      num {$$ = factor(nf($1)); }
      |
      boollit {$$ = factor(bb($1)); }
      |
      LP expression RP { $$ = factor($2); }
      ;

%%

nodeType *nf(int val){
  nodeType *p;
  if((p = malloc(sizeof(numNodeType))) == NULL)
  {
    yyerror("out of memory");
  }

  p->type = typeNum;
  p->n.value = val;
  printf("created numNode: %d\n", val);
  return p;
}

nodeType *id(char* s){
  nodeType* p;
  if((p = malloc(sizeof(idNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeId;
  p->id.str = s;
  printf("created idNode: %s\n", s);
  return p;
}

nodeType *bb(char* s){
  nodeType* p;
  if((p = malloc(sizeof(bNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeB;
  p->b.tf = s;
  printf("created boolNode: %s\n", s);
  return p;
}

nodeType *opr(int oper, int nops, ...) {
	va_list ap;
	nodeType *p;
	size_t size;
	int i;
	/* allocate node */
	size = sizeof(oprNodeType) + (nops - 1) * sizeof(nodeType*);
	if ((p = malloc(size)) == NULL)
		yyerror("out of memory");
	/* copy information */
	p->type = typeOpr;
	p->opr.oper = oper;
	p->opr.nops = nops;
	va_start(ap, nops);
	for (i = 0; i < nops; i++)
		p->opr.op[i] = va_arg(ap, nodeType*);
	va_end(ap);
  printf("created innerNode: \n");
	return p;
}

nodeType *prgm(nodeType *decl, nodeType *stmtSeq) {
	nodeType *p;
	if((p = malloc(sizeof(prgmNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typePrgm;
  p->p.decl = decl;
  p->p.stmtSeq = stmtSeq;
  printf("created prgmNode: \n");
  return p;
}

nodeType *decl(nodeType *typ, nodeType *id, nodeType *decl) {
	nodeType *p;
	if((p = malloc(sizeof(declNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeDecl;
  p->d.typ = typ;
  p->d.id = id;
  p->d.decl = decl;
  printf("created declNode: \n");
  return p;
}

nodeType *type(int t) {
	nodeType *p;
	if((p = malloc(sizeof(typeNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeType;
  p->ty.t = t;
  printf("created typeNode: \n");
  return p;
}

nodeType *stmtSeq(nodeType *stmt, nodeType *stmtSeq) {
	nodeType *p;
	if((p = malloc(sizeof(stmtSeqNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeStmtSeq;
  p->ss.stmt = stmt;
  p->ss.stmtSeq = stmtSeq;
  printf("created stmtSeqNode: \n");
  return p;
}

nodeType *stmt(nodeType *stmtType) {
	nodeType *p;
	if((p = malloc(sizeof(stmtNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeStmt;
  p->s.stmtType = stmtType;
  p->s.childType = stmtType->type;
  printf("created stmtNode: \n");
  return p;
}

nodeType *asgn(nodeType *id, nodeType *expr) {
	nodeType *p;
	if((p = malloc(sizeof(asgnNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeAsgn;
  p->a.id = id;
  p->a.expr = expr;
  printf("created asgnNode: \n");
  return p;
}

nodeType *if0(nodeType *expr, nodeType *stmtSeq, nodeType *else0) {
	nodeType *p;
	if((p = malloc(sizeof(ifNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeIf;
  p->i.expr = expr;
  p->i.stmtSeq = stmtSeq;
  p->i.else0 = else0;
  printf("created ifNode: \n");
  return p;
}

nodeType *else0(nodeType *stmtSeq) {
	nodeType *p;
	if((p = malloc(sizeof(elseNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeElse;
  p->el.stmtSeq = stmtSeq;
  printf("created elseNode: \n");
  return p;
}

nodeType *while0(nodeType *expr, nodeType *stmtSeq) {
	nodeType *p;
	if((p = malloc(sizeof(whileNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeWhile;
  p->w.expr = expr;
  p->w.stmtSeq = stmtSeq;
  printf("created exprNode: \n");
  return p;
}

nodeType *writeInt(nodeType *expr) {
	nodeType *p;
	if((p = malloc(sizeof(writeIntNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeWriteInt;
  p->wi.expr = expr;
  printf("created writeIntNode: \n");
  return p;
}

nodeType *expr(nodeType *simpExpr0, nodeType *simpExpr1) {
	nodeType *p;
	if((p = malloc(sizeof(exprNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeExpr;
  p->ex.simpExpr0 = simpExpr0;
  p->ex.simpExpr1 = simpExpr1;
  p->ex.numOps = 2;
  if(simpExpr1 == NULL)
    p->ex.numOps = 1;
  printf("created exprNode: \n");
  return p;
}

nodeType *simpExpr(nodeType *term0, nodeType *term1) {
	nodeType *p;
	if((p = malloc(sizeof(simpExprNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeSimpExpr;
  p->se.term0 = term0;
  p->se.term1 = term1;
  p->se.numOps = 2;
  if(term1 == NULL)
    p->se.numOps = 1;
  printf("created simpExprNode: \n");
  return p;
}

nodeType *term(nodeType *factor0, nodeType *factor1) {
	nodeType *p;
	if((p = malloc(sizeof(termNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeTerm;
  p->te.factor0 = factor0;
  p->te.factor1 = factor1;
  p->te.numOps = 2;
  if(factor1 == NULL)
    p->te.numOps = 1;
  printf("created termNode: \n");
  return p;
}

nodeType *factor(nodeType *fn) {
	nodeType *p;
	if((p = malloc(sizeof(factorNodeType)))==NULL)
    yyerror("out of memory");
  p->type = typeFactor;
  p->f.fn = fn;
  p->f.childType = fn->type;
  printf("created factorNode: \n");
  return p;
}

int main()
{
 return(yyparse());
 printf("SUCCESS\n");
}


void yyerror(char *s)
{
  fprintf(stderr, "%s\n",s);
}



int yywrap()
{
  //return(1);
}

