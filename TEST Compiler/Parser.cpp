#include "Parser.h"

//语法分析器类的构造函数
PARSER::PARSER(){
    first_declaration_stat.push_back("int");
    first_declaration_list.push_back("int");
    first_declaration_list.push_back("_E");    //_E表示ε
    first_program.push_back("int");
    first_program.push_back("_E");
    first_if_stat;    //TODO，没推出来
    first_while_stat.push_back("while");
    first_for_stat.push_back("for");
    first_write_stat.push_back("write");
    first_read_stat.push_back("read");
    first_compound_stat.push_back("{");
    first_expression_stat.push_back("for");     //TODO：没推出来
    first_expression;//TODO：补全
    first_factor.push_back("_ID");      //表示
    first_factor.push_back("_NUM");
    first_factor.push_back("(");
    first_tmp_term.push_back("*");
    first_tmp_term.push_back("/");
    first_term.push_back("_ID");
    first_term.push_back("_NUM");
    first_term.push_back("(");
    first_tmp_additive_expr.push_back("+");
    first_tmp_additive_expr.push_back("-");
    first_additive_expr.push_back("_ID");
    first_additive_expr.push_back("_NUM");
    first_additive_expr.push_back("(");
    first_tmp_bool_expr.push_back("_E");
    first_tmp_bool_expr.push_back(">");
    first_tmp_bool_expr.push_back("<");
    first_tmp_bool_expr.push_back(">=");
    first_tmp_bool_expr.push_back("<=");
    first_tmp_bool_expr.push_back("==");
    first_tmp_bool_expr.push_back("!=");
    first_bool_expr.push_back("_ID");
    first_bool_expr.push_back("_NUM");
    first_bool_expr.push_back("(");
    first_statement;    //TODO:补全
    first_statement_list.push_back("while");
    first_statement_list.push_back("for");
    first_statement_list.push_back("write");
    first_statement_list.push_back("read");
    first_statement_list.push_back("{");
    first_statement_list.push_back(",");
    first_statement_list.push_back("_E");
    follow_declaration_list.push_back("!=");    //TODO：补全
    follow_statement_list.push_back("!=");  //TODO：补全
    follow_tmp_bool_expr.push_back("!=");   //TODO：补全
}
//#1
int PARSER::f_program(int no){
    string ch = LA.m_str[no];
    if(ch == "{"){
        ch = LA.m_str[++no];
    }
    else{
        cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    }
    no = f_declaration_list(no);
    no = f_statement_list(no);
    ch = LA.m_str[no];
    if(ch == "}"){
        //结束
    }
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
}
//#2
int PARSER::f_declaration_list(int no){//TODO
    if(is_include(no, follow_declaration_list)){
        return no;
    }
    else{
        no = f_declaration_stat(no);
        no = f_declaration_list(no);
        return no;
    }
}
//#3
int PARSER::f_declaration_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "int"){
        ch = LA.m_str[++no];
    }
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    if(LA.m_str_attribute[no] == 1){
        ch = LA.m_str[++no];
    }
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    if(ch == ";")   return ++no;
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
}
//#4
int PARSER::f_statement_list(int no){
    if(is_include(no, follow_statement_list)){
        return no;
    }
    else{
        no = f_statement(no);
        no = f_statement_list(no);
        return no;
    }
}
//#5
int PARSER::f_statement(int no){
    if(is_include(no, first_if_stat)){
        no = f_if_stat(no);
    }
    else if(is_include(no, first_while_stat)){
        no = f_while_stat(no);
    }
    else if(is_include(no, first_for_stat)){
        no = f_for_stat(no);
    }
    else if(is_include(no, first_write_stat)){
        no = f_write_stat(no);
    }
    else if(is_include(no, first_read_stat)){
        no = f_read_stat(no);
    }
    else if(is_include(no, first_compound_stat)){
        no = f_compound_stat(no);
    }
    else if(is_include(no, first_expression_stat)){
        no = f_expression_stat(no);
    }
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    return no;
}
//#6
int PARSER::f_if_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "if")  ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    if(ch == "(")  ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    no = f_expression(no);
    if(ch == ")")  ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    no = f_statement(no);
    no = f_tmp_if_stat(no);
    return no;
}
//#7
int PARSER::f_while_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "while")   ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    if(ch == "(")   ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ")")   ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    no = f_statement(no);
    return no;
}
//#8
int PARSER::f_for_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "for") ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    if(ch == "(")   ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ";")   ch = LA.m_str[++no];
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ";")   ch = LA.m_str[++no];
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ")")   ch = LA.m_str[++no];
    no = f_statement(no);
    return no;
}
//#9
int PARSER::f_write_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "write")   ch = LA.m_str[++no];
    else{}
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ";")   return ++no;
    else{}
}
//#10
int PARSER::f_read_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "read")    ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    if(LA.m_str_attribute[no] == 1) ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    if(ch == ";")   return ++no;
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
}
//#11
int PARSER::f_compound_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "{")   ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    no = f_statement_list(no);
    ch = LA.m_str[no];
    if(ch == "}")   return ++no;
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
}
//#12
int PARSER::f_expression_stat(int no){      //TODO
    string ch = LA.m_str[no];
    if(ch == ";")   return ++no;
    else{
        no = f_expression(no);
        ch = LA.m_str[no];
        if(ch == ";")   return ++no;
        else cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    }
}
//#13
int PARSER::f_expression(int no){       //TODO
    string ch = LA.m_str[no];
    if(LA.m_str_attribute[no] == 1){

    }
}
//#14
int PARSER::f_bool_expr(int no){
    no = f_additive_expr(no);
    no = f_tmp_additive_expr(no);
    return no;
}
//#15
int PARSER::f_tmp_bool_expr(int no){    //TODO：考虑_E
    string ch = LA.m_str[no];
    if(is_include(no, follow_tmp_bool_expr)){
        return no;
    }

    if(ch == ">" || ch == "<" || ch == ">=" || ch == "<=" || ch == "==" || ch == "!="){
        ch = LA.m_str[++no];
    }
    else{}
    no = f_additive_expr(no);
}
//#16
int PARSER::f_additive_expr(int no){
    no = f_term(no);
    no = f_tmp_additive_expr(no);
    return no;
}
//#17
int PARSER::f_tmp_additive_expr(int no){
    string ch = LA.m_str[no];
    if(ch == "+" || ch == "-")  ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    no = f_term(no);
    no = f_tmp_additive_expr(no);
    return no;
}
//#18
int PARSER::f_term(int no){
    no = f_factor(no);
    no = f_tmp_term(no);
    return no;
}
//#19
int PARSER::f_tmp_term(int no){
    string ch = LA.m_str[no];
    if(ch == "*" || ch == "/")  ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    no = f_factor(no);
    no = f_tmp_term(no);
    return no;
}
//#20
int PARSER::f_factor(int no){
    string ch = LA.m_str[no];
    if(LA.m_str_attribute[no] == 1 || LA.m_str_attribute[no] == 3)
        return ++no;
    if(ch == "(")   ch = LA.m_str[++no];
    else    cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码 " << LA.m_str[no] <<endl;
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ")")   return ++no;
}
//#21
int PARSER::f_tmp_if_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "else"){
        ch = LA.m_str[++no];
        no = f_statement(no);
        return no;
    }
    else    return no;
}
bool PARSER::is_include(int no, vector<string>first){
    string ch = LA.m_str[no];
    for(string i:first){
        if(i == "_ID"){
            if(LA.m_str_attribute[no] == 1)   return true;
            else continue;
        }
        else if (i == "_NUM"){
            if(LA.m_str_attribute[no] == 3)   return true;
            else continue;
        }
        if(ch == i) return true;
    }
    return false;
}


void PARSER::grammar_analysis(){
    LA.text_analysis();     //词法分析器处理单词
    f_program(0);
}
