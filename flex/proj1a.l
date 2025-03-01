/* 
*/
%{

%}

/*** matches each lexeme with its token
***/

%%
if      printf("if is the IF keyword\n");
then    printf("then is the THEN keyword\n");
else    printf("else is the ELSE keyword\n");
begin   printf("begin is the BEGIN keyword\n");
end     printf("end is the END keyword\n");
while   printf("while is the WHILE keyword\n");
do      printf("do is the DO keyword\n");
program printf("program is the PROGRAM keyword\n");
var     printf("var is the VAR keyword\n");
as      printf("as is the AS keyword\n");
int     printf("int is the INT keyword\n");
bool    printf("bool is the BOOL keyword\n");
writeInt       printf("writeInt is the WRITEINT built-in procedure\n");
readInt        printf("readInt is the READINT build-in procedure\n");
"\("      printf("\( is the LP symbol\n");
")"      printf(") is the RP symbol\n");
:=      printf(":= is the ASGN symbol\n");
";"      printf("; is the SC symbol\n");
"*"|"div"|"mod"       { printf("%s is an OP2 operator\n", yytext); }
"+"|"-"                 { printf("%s is an OP3 operator\n", yytext); }
"="|"!="|"<"|">"|"<="|">=" { printf("%s is an OP4 operator\n", yytext); }
[1-9][0-9]*|0      printf("%s is a num\n", yytext);
"false" | "true"      printf("%s is a boollit\n", yytext);
[A-Z][A-Z0-9]*        printf("%s is an ident\n", yytext);
[ \t\n]        ;
.     printf("error: %s not recognized\n", yytext);
%%

/*** User code section***/
int yywrap(){}

int main(int argc, char **argv)
{

FILE *fp;
char filename[50];
printf("Enter the filename: \n");
scanf("%s",filename);
fp = fopen(filename,"r");
yyin = fp;



yylex();


return 0;
}
