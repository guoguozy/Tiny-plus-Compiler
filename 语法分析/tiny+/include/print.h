/****************************************************/
/* File: print.h                                     */
/* Created by guozy on 2020/6/22.                   */  
/* Utility functions for the TINY compiler          */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
#ifndef _PRINT_H_
#define _PRINT_H_
#include "global.h"
/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken(TokenType, const char *, const int &);

void printError(const int &error_code, const int &lineno, char *error_details = nullptr);

void printTree(TreeNode *root);
#endif
