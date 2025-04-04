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
     LP = 258,
     RP = 259,
     ASGN = 260,
     SC = 261,
     OP2 = 262,
     OP3 = 263,
     OP4 = 264,
     IF = 265,
     THEN = 266,
     ELSE = 267,
     BEGIN_ = 268,
     END = 269,
     WHILE = 270,
     DO = 271,
     PROGRAM = 272,
     VAR = 273,
     AS = 274,
     INT = 275,
     BOOL = 276,
     WRITEINT = 277,
     READINT = 278,
     num = 279,
     boollit = 280,
     ident = 281
   };
#endif
/* Tokens.  */
#define LP 258
#define RP 259
#define ASGN 260
#define SC 261
#define OP2 262
#define OP3 263
#define OP4 264
#define IF 265
#define THEN 266
#define ELSE 267
#define BEGIN_ 268
#define END 269
#define WHILE 270
#define DO 271
#define PROGRAM 272
#define VAR 273
#define AS 274
#define INT 275
#define BOOL 276
#define WRITEINT 277
#define READINT 278
#define num 279
#define boollit 280
#define ident 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 11 "tl13bnf.y"
{
  char *sval;
}
/* Line 1529 of yacc.c.  */
#line 105 "tl13bnf.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

