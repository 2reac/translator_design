
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
     IF = 258,
     ELSE = 259,
     RETURN = 260,
     INT = 261,
     VOID = 262,
     WHILE = 263,
     ID = 264,
     NUM = 265,
     Op_lessequal = 266,
     Op_greaterequal = 267,
     Op_equal = 268,
     Op_notequal = 269,
     LeftPrnts = 270,
     RightPrnts = 271,
     LeftBrack = 272,
     RightBrack = 273,
     LeftBrace = 274,
     RightBrace = 275,
     Op_add = 276,
     Op_subtract = 277,
     Op_multiply = 278,
     Op_divide = 279,
     Op_mod = 280,
     Op_less = 281,
     Op_greater = 282,
     Op_assign = 283,
     Semicolon = 284,
     Comma = 285,
     Eps = 286
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define RETURN 260
#define INT 261
#define VOID 262
#define WHILE 263
#define ID 264
#define NUM 265
#define Op_lessequal 266
#define Op_greaterequal 267
#define Op_equal 268
#define Op_notequal 269
#define LeftPrnts 270
#define RightPrnts 271
#define LeftBrack 272
#define RightBrack 273
#define LeftBrace 274
#define RightBrace 275
#define Op_add 276
#define Op_subtract 277
#define Op_multiply 278
#define Op_divide 279
#define Op_mod 280
#define Op_less 281
#define Op_greater 282
#define Op_assign 283
#define Semicolon 284
#define Comma 285
#define Eps 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


