/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     READINT = 258,
     WRITEINT = 259,
     BOOL = 260,
     INT = 261,
     AS = 262,
     VAR = 263,
     PROGRAM = 264,
     DO = 265,
     WHILE = 266,
     END = 267,
     BEGIN_ = 268,
     ELSE = 269,
     THEN = 270,
     IF = 271,
     OP4 = 272,
     OP3 = 273,
     OP2 = 274,
     SC = 275,
     ASGN = 276,
     RP = 277,
     LP = 278,
     num = 279,
     boollit = 280,
     ident = 281
   };
#endif
/* Tokens.  */
#define READINT 258
#define WRITEINT 259
#define BOOL 260
#define INT 261
#define AS 262
#define VAR 263
#define PROGRAM 264
#define DO 265
#define WHILE 266
#define END 267
#define BEGIN_ 268
#define ELSE 269
#define THEN 270
#define IF 271
#define OP4 272
#define OP3 273
#define OP2 274
#define SC 275
#define ASGN 276
#define RP 277
#define LP 278
#define num 279
#define boollit 280
#define ident 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 13 "tl13bnf.y"
{
  int numVal;
  char* sVal;
  nodeType *nPtr;
}
/* Line 1529 of yacc.c.  */
#line 107 "tl13bnf.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

