/************************  calc1.y           *******************/

%{
#include <stdio.h>
int yylex(void);
void yyerror(char *);
%}

//symbols
%union
{
  char *sval;
};
%start program
%token LP RP ASGN SC OP2 OP3 OP4 IF THEN ELSE BEGIN_ END WHILE DO PROGRAM VAR AS INT BOOL WRITEINT READINT
%token num boollit ident
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
 
%%                   /* beginning of rules section */
program:  PROGRAM declarations BEGIN_ statementSequence END
         ;
declarations:    VAR ident AS type SC declarations
         |
         /*empty */
         ;
type:    INT
         |
         BOOL
         ;
statementSequence: statement SC statementSequence
                    |
                    /*empty */
                    ;
statement: assignment
           |
           ifStatement
           |
           whileStatement
           |
           writeInt
           ;
assignment: ident ASGN expression
            |
            ident ASGN READINT
            ;
ifStatement: IF expression THEN statementSequence elseClause END
            ;
elseClause: ELSE statementSequence
            |
  /*empty */
            ;
whileStatement: WHILE expression DO statementSequence END
            ;
writeInt: WRITEINT expression
          ;

expression: simpleExpression
            |
            simpleExpression OP4 simpleExpression
            ;

simpleExpression: term OP3 term
                  |
                  factor
                  ;

term: factor OP2 factor
      |
      factor
      ;
factor: ident
      |
      num
      |
      boollit
      |
      LP expression RP
      ;

%%

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

