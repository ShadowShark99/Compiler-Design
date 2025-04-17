/* 
*/
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "tl13bnf.h"
  #include "tl13bnf.tab.h"
  
  //extern int yylval;
%}

/*** matches each lexeme with its token
***/

%%
if      return(IF);
then    return(THEN);
else    return(ELSE);
begin   return(BEGIN_);
end     return(END);
while   return(WHILE);
do      return(DO);
program return(PROGRAM);
var     return(VAR);
as      return(AS);
int     return(INT);
bool    return(BOOL);
writeInt       return(WRITEINT);
readInt        return(READINT);
"\("      return(LP);
")"      return(RP);
:=      return(ASGN);
";"      return(SC);
"*"|"div"|"mod"       { return(OP2); }
"+"|"-"                 { return(OP3); }
"="|"!="|"<"|">"|"<="|">=" { return(OP4); }
[1-9][0-9]*|0      {
                    yylval.numVal = atoi(yytext); 
                    return(num);
                    }
"false"|"true"      {
                        yylval.sVal = malloc(strlen(yytext)+1);
                        strncpy(yylval.sVal, yytext, strlen(yytext));
                        return(boollit);
                      }
[A-Z][A-Z0-9]*        {
                        yylval.sVal = malloc(strlen(yytext)+1);
                        strncpy(yylval.sVal, yytext, strlen(yytext));
                        return(ident);
  }
[ \t\n]        ;
.     printf("error: %s not recognized\n", yytext);



