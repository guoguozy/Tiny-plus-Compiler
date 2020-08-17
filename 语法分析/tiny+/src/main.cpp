//
// Created by guozy on 2020.6.22.
//
#include "scan.h"
#include "print.h"
#include "parser.h"
#include "generate.h"
#include <iostream>

/* allocate global variables */
int lineno = 0;
FILE *source;
FILE *listing;
FILE *code;
bool is_optimized;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

int main(int argc, char *argv[])
{

    //std::cout << "输入TINY++源程序文件名: ";
    //char *srcfile_name = new char[50];
    //std::cin >> srcfile_name;

    char *srcfile_name = const_cast<char *>("../test.tny");

    if (argc >= 2)
        srcfile_name = argv[1];

    if (!strchr(srcfile_name, '.'))
        strcat(srcfile_name, ".tny");

    FILE *src_file = fopen(srcfile_name, "r");

    if (src_file == nullptr)
    {
        std::cerr << "噢噢，文件打不开!" << std::endl;
        exit(1);
    }

    source = src_file;

    //if (argc >= 2)
    if (argc >= 3 && !strcmp(argv[2], "tokens")) //仅输出token
    {
        if (argc > 3) //if (argc > 2)
            listing = fopen("tokens", "w");
        else
            listing = stdout;
        fprintf(listing, "TOKENS序列：\n");
        do
        {
            int line = 0;
            auto tmp = getToken(line);
            if (tmp.first == ENDFILE)
                break;
            printToken(tmp.first, tmp.second.c_str(), line);
        } while (true);
        std::cout << "DONE" << std::endl;
        return 0;
    }

    if ((argc >= 3 && !strcmp(argv[2], "tree")) || argc >= 0)
    { //仅输出tree
        listing = stdout;
        has_error = false;
        TreeNode *root = parse();
        if (has_error)
        {
            fprintf(listing, "error");
        }
        std::cout << "\n语法树如下：" << std::endl;
        printTree(root);
        return 0;
    }

    //输出文件路径，默认输出到屏幕
    if (argc >= 3)
    {
        code = fopen(argv[2], "w");
    }
    else
    {
        code = stdout;
    }
    //报告文件路径，默认输出到屏幕
    if (argc >= 4)
        listing = fopen(argv[3], "w");
    else
        listing = stdout;

    is_optimized = false;
    if (argc >= 5)
        if (strcmp(argv[4], "optimize") == 0 || strcmp(argv[4], "Optimize") == 0)
            is_optimized = true;

    fprintf(listing, "\nTINY COMPILATION: %s\n", srcfile_name);
    cgen();
    std::cout << "DONE" << std::endl;
}
