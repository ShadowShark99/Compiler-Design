#include <stdio.h>
#include "tl13bnf.h"
#include "tl13bnf.tab.h"
static int lbl;
int ex(nodeType *p)
{
  int lbl1, lbl2;
  if (!p)
    return 0;
  switch (p->type)
  {
  case typeNum:
    printf("%d", p->n.value);
    break;
  case typeId:
    printf("%s", p->id.str);
    break;
  case typeB:
    printf("%s", p->b.tf);
    break;
  case typePrgm:
    printf("int main(){\n");
    ex(p->p.decl);
    ex(p->p.stmtSeq);
    printf("return 0; \n}\n");
    break;
  case typeDecl:
    ex(p->d.typ);
    ex(p->d.id);
    printf(";\n");
    ex(p->d.decl);
    break;
  case typeType:
    printf("%d ", p->ty.t);
    break;
  case typeStmtSeq:
    ex(p->ss.stmt);
    // asgn statements use ; while does not use ;
    printf("\n");
    ex(p->ss.stmtSeq);
    break;
  case typeStmt:
    switch (p->s.childType)
    {
    case typeAsgn:
      ex(p->s.stmtType);
      break;
    case typeIf:
      ex(p->s.stmtType);
      break;
    case typeWhile:
      ex(p->s.stmtType);
      break;
    case typeWriteInt:
      ex(p->s.stmtType);
      break;
    default:
      printf("Unknown statement type\n");
    }
    // ex(p->s.stmtType);
    break;
  case typeAsgn:
    ex(p->a.id);
    printf(" = ");
    ex(p->a.expr);
    printf(";");
    break;
  case typeIf:
    printf("if (");
    ex(p->i.expr);
    printf("){ \n");
    ex(p->i.stmtSeq);
    printf("}");
    if (p->i.else0)
    {
      /* if else */
      ex(p->i.else0);
    }
    break;
  case typeElse:
    printf("else {\n");
    ex(p->el.stmtSeq);
    printf("}");
    break;
  case typeWhile:
    printf("while (");
    ex(p->w.expr);
    printf("){\n");
    ex(p->w.stmtSeq);
    printf("}");
    break;
  case typeWriteInt:
    printf("writeInt(");
    ex(p->wi.expr);
    printf(");");
    break;
  case typeExpr:
    ex(p->ex.simpExpr0);
    if (p->ex.simpExpr1)
    {
      printf(" == ");
      ex(p->ex.simpExpr1);
    }
    break;
  case typeSimpExpr:
    ex(p->se.term0);
    if (p->se.term1)
    {
      printf(" + ");
      ex(p->se.term1);
    }
    break;
  case typeTerm:
    ex(p->te.factor0);
    if (p->te.factor1)
    {
      printf(" * ");
      ex(p->te.factor1);
    }
    break;
  case typeFactor:
    ex(p->f.fn);
    break;
  }
}