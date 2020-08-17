//
// Created by guozy on June.22 2020
//

#include "global.h"
#include "print.h"
#include "errors.h"
#include <iostream>


void printToken(TokenType token, const char *tokenString, const int &lineno)
{
    switch (token)
    {
    case TK_TRUE:
    case TK_FALSE:
    case TK_OR:
    case TK_AND:
    case TK_NOT:
    case TK_INT:
    case TK_BOOL:
    case TK_STRING:
    case TK_WHILE:
    case TK_DO:
    case TK_IF:
    case TK_THEN:
    case TK_ELSE:
    case TK_END:
    case TK_REPEAT:
    case TK_UNTIL:
    case TK_READ:
    case TK_WRITE:
        fprintf(listing, "(KEY, %s)\n", tokenString);
        break;
    case TK_GTR:
        fprintf(listing, "(TK_GTR, >)\n");
        break;
    case TK_LEQ:
        fprintf(listing, "(TK_LEQ, <=)\n");
        break;
    case TK_GEQ:
        fprintf(listing, "(TK_GEQ, >=)\n");
        break;
    case TK_COMMA:
        fprintf(listing, "(TK_COMMA, ,)\n");
        break;
    case TK_SEMICOLON:
        fprintf(listing, "(TK_SEMICOLON, ;)\n");
        break;
    case TK_ASSIGN:
        fprintf(listing, "(TK_ASSIGN, :=)\n");
        break;
    case TK_ADD:
        fprintf(listing, "(TK_ADD, +)\n");
        break;
    case TK_SUB:
        fprintf(listing, "(TK_SUB, -)\n");
        break;
    case TK_MUL:
        fprintf(listing, "(TK_MUL, *)\n");
        break;
    case TK_DIV:
        fprintf(listing, "(TK_DIV, /)\n");
        break;
    case TK_LP:
        fprintf(listing, "(TK_LP, ()\n");
        break;
    case TK_RP:
        fprintf(listing, "(TK_RP, ))\n");
        break;
    case TK_LSS:
        fprintf(listing, "(TK_LSS, <)\n");
        break;
    case TK_EQU:
        fprintf(listing, "(TK_EQU, =)\n");
        break;
    case ID:
        fprintf(listing, "(ID, %s)\n", tokenString);
        break;
    case NUM:
        fprintf(listing, "(NUM, %s)\n", tokenString);
        break;
    case ERROR:
        fprintf(listing, "\033[1;;31mAn Error is detected at line %d: %s \033[0m\n", lineno, tokenString);
        break;
    case STRING:
        fprintf(listing, "(STR, %s)\n", tokenString);
        break;
    default:
        fprintf(listing, "Unknown token: %d\n", token);
    }
}

void printError(const int &error_code, const int &lineno, char *error_details)
{
    if (listing == stdout) //输出到控制台可以带有颜色
        fprintf(listing, "\033[1;;31mAn Error is detected at line %d: %s \033[0m\n", lineno,
                error_items[error_code].error_description.c_str());
    else
        fprintf(listing, "An Error is detected at line %d: %s\n", lineno,
                error_items[error_code].error_description.c_str());

    if (error_code != SEMANTIC_MISSING_SEMICOLON) //如果报的错是严重错误，就不生成中间代码文件了
        has_error = true;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno += 2
#define UNINDENT indentno -= 2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{
    for (int i = 0; i < indentno; i++)
        std::cout<<" ";
}
void printTree(TreeNode *root)
{
    if (root->nodeType != STMT_SEQUENCE)
        INDENT;
    if (root)
    {
        printSpaces();
        switch (root->nodeType)
        {
        case STMT_SEQUENCE:
            //声明语句就算了，不输出了，占地！
            /*if (root->valType == VT_INT)
                fprintf(listing, "Int Declaration\n");
            else if (root->valType == VT_BOOL)
                fprintf(listing, "Bool Declaration\n");
            else
                fprintf(listing, "Str Declaration\n");
            */
            break;
        case IF_STMT:
            fprintf(listing, "If\n");
            if (root->tk)
                std::cout << root->tk->s_val << std::endl;
            break;
        case REPEAT_STMT:
            std::cout << "Repeat\n";
            break;
        case ASSIGN_STMT:
            if (root->tk)
                std::cout << "Assign to " + root->tk->s_val << std::endl;
            break;
        case READ_STMT:
            if (root->tk)
                std::cout << "READ " + root->tk->s_val << std::endl;
            break;
        case WRITE_STMT:
            std::cout << "Write" << std::endl;
            break;
        case WHILE_STMT:
            fprintf(listing, "While\n");
            if (root->tk)
                std::cout << root->tk->s_val << std::endl;
            break;
        case GTR_EXP:
            std::cout << "Op: (SYM,>)\n";
            break;
        case GEQ_EXP:
            std::cout << "Op: (SYM,>=)\n";
            break;
        case LEQ_EXP:
            std::cout << "Op: (SYM,<=)\n";
            break;
        case LSS_EXP:
            std::cout << "Op: (SYM,<)\n";
            break;
        case EQU_EXP:
            std::cout << "Op: (SYM,==)\n";
            break;
        case LOG_OR_EXP:
            std::cout << "LogicOp: (KEY,or)\n";
            break;
        case LOG_AND_EXP:
            std::cout << "LogicOp: (KEY,and)\n";
            break;
        case LOG_NOT_EXP:
            std::cout << "LogicOp: (KEY,not)\n";
            break;
        case ADD_EXP:
            std::cout << "Op: (SYM,+)\n";
            break;
        case SUB_EXP:
            std::cout << "Op: (SYM,-)\n";
            break;
        case MUL_EXP:
            std::cout << "Op: (SYM,*)\n";
            break;
        case DIV_EXP:
            std::cout << "Op: (SYM,/)\n";
            break;
        case FACTOR:
            if (root->tk)
            {
                switch (root->tk->kind)
                {
                case TK_TRUE:
                    std::cout << "Bool: true" << std::endl;
                    break;
                case TK_FALSE:
                    std::cout << "Bool: false" << std::endl;
                    break;
                case NUM:
                    std::cout << "Const: ";
                    std::cout << root->tk->i_val << std::endl;
                    break;
                case ID:
                    std::cout << "ID: " + root->tk->s_val << std::endl;
                    break;
                case STRING:
                    std::cout << "Str: \'" + root->tk->s_val + "\'" << std::endl;
                    break;
                }
            }
            else
            { //tk为空的唯一一种情况是括号嵌套的结构
                /*s1_str = analyzingStack.pop().val;
                t_str = get_t_num_str();
                emit(C_ASSIGN, t_str, s1_str);
                analyzingStack.push(root, t_str);*/
                //fixed 应该不要做任何操作，因为嵌套的后一次都已经搞定好中间变量了，而且只有一个中间变量
            }
            break;
        default:
            fprintf(listing, "UNKOWN NODE\n");
            break;
        }

        for (int i = 0; i < MAXCHILDREN; i++)
            if (root->child[i])
                printTree(root->child[i]);
    }
    if (root->nodeType != STMT_SEQUENCE)
        UNINDENT;
}