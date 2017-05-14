/***
*类名：PARSER（TEST语法分析器）
*
*作者：yeates
***/

#ifndef __PARSER_H__
#define __PARSER_H__

#include "Lexical_analyzer.h"

class PARSER{
private:
    TDFA LA;    //词法分析器
//--------各个状态的FIRST和FOLLOW集合-------//
    vector<string>first_declaration_stat;
    vector<string>first_declaration_list;
    vector<string>first_program;
    vector<string>first_if_stat;
    vector<string>first_tmp_if_stat;
    vector<string>first_for_stat;
    vector<string>first_write_stat;
    vector<string>first_while_stat;
    vector<string>first_read_stat;
    vector<string>first_compound_stat;
    vector<string>first_expression_stat;
    vector<string>first_expression;
    vector<string>first_factor;
    vector<string>first_tmp_term;
    vector<string>first_term;
    vector<string>first_tmp_additive_expr;
    vector<string>first_additive_expr;
    vector<string>first_tmp_bool_expr;
    vector<string>first_bool_expr;
    vector<string>first_statement;
    vector<string>first_statement_list;
    vector<string>follow_declaration_list;
    vector<string>follow_statement_list;
    vector<string>follow_tmp_bool_expr;
    vector<string>follow_tmp_additive_expr;
    vector<string>follow_tmp_term;
    vector<string>follow_expression;
    vector<string>follow_bool_expr;
    vector<string>follow_term;

//----------------------------------------//
//--------各个非终结符的函数---------------//
    int f_program(int no);       //都带了f_前缀
    int f_declaration_list(int no);
    int f_declaration_stat(int no);
    int f_statement_list(int no);
    int f_statement(int no);
    int f_if_stat(int no);
    int f_while_stat(int no);
    int f_read_stat(int no);
    int f_for_stat(int no);
    int f_write_stat(int no);
    int f_compound_stat(int no);
    int f_expression_stat(int no);
    int f_expression(int no);
    int f_bool_expr(int no);
    int f_tmp_bool_expr(int no);
    int f_additive_expr(int no);
    int f_tmp_additive_expr(int no);
    int f_term(int no);
    int f_tmp_term(int no);
    int f_factor(int no);
//----------------------------------------//
    bool is_include(int no, vector<string>first);   //相当于数学意义上的∈
    int error_handle(int no);   //第一种错误处理方式：报异常错误，读取下一个单词
    int defect_handle(int no, string str);  //第二种错误处理方式：报缺失错误，不读取下一个单词
public:
    PARSER();   //构造函数，用于初始化FIRST和FOLLOW集合
    void grammar_analysis();    //主要分析函数
};

#endif // __PARSER_H__
