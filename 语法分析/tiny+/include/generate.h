//
// Created by guozy on 2020/6/22.
//

#ifndef TINY_GENERATE_H
#define TINY_GENERATE_H

#include "global.h"

void codeGen(TreeNode* syntaxTree);
void traversal_back(TreeNode *root);

int emit(CodeType type, const std::string &t = "", const std::string &s1 = "", const std::string &s2 = "");
void cgen();

#endif //TINY_GENERATE_H
