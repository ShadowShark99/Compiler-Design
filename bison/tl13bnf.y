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
program:  PROGRAM declarations BEGIN_ statementSequence END {$$ = opr(PROGRAM, 2, $2, $4);}
         ;
declarations:    VAR ident AS type SC declarations {$$ = opr(VAR, 3, id($2), $4, $6); }
         |
         /*empty */ {$$ = NULL;}
         ;
type:    INT {$$ = NULL; }
         |
         BOOL {$$ = NULL; }
         ;
statementSequence: statement SC statementSequence {$$ = opr(SC, 2, $1, $3); }
                    |
                    /*empty */{$$ = NULL;}
                    ;
statement: assignment { $$ = $1; }
           |
           ifStatement { $$ = $1; }
           |
           whileStatement { $$ = $1; }
           |
           writeInt { $$ = $1; }
           ;
assignment: ident ASGN expression {$$ = opr(ASGN, 2, id($1), $3); }
            |
            ident ASGN READINT {$$ = id($1); }
            ;
ifStatement: IF expression THEN statementSequence elseClause END {$$ = opr(IF, 3, $2, $4, $5); }
            ;
elseClause: ELSE statementSequence {$$ = $2; }
            |
  /*empty */{$$ = NULL; }
            ;
whileStatement: WHILE expression DO statementSequence END {$$ = opr(WHILE, 2, $2, $4); }
            ;
writeInt: WRITEINT expression {$$ = $2; }
          ;

expression: simpleExpression {$$ = $1; }
            |
            simpleExpression OP4 simpleExpression {$$ = opr(OP4, 2, $1, $3); }
            ;

simpleExpression: term OP3 term {$$ = opr(OP3, 2, $1, $3); }
                  |
                  factor {$$ = $1; }
                  ;

term: factor OP2 factor {$$ = opr(OP2, 2, $1, $3); }
      |
      factor { $$ = $1; }
      ;
factor: ident { $$ = id($1); }
      |
      num {$$ = nf($1); }
      |
      boollit {$$ = bb($1); }
      |
      LP expression RP { $$ = $2; }
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

