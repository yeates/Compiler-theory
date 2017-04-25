#include "Parser.h"

//语法分析器类的构造函数
PARSER::PARSER(){
    first_declaration_stat.push_back("int");
    first_declaration_list.push_back("int");
    first_declaration_list.push_back("_E");    //_E表示ε
    first_program.push_back("(");
    first_if_stat.push_back("if");
    first_tmp_if_stat.push_back("_E");
    first_tmp_if_stat.push_back("else");
    first_while_stat.push_back("while");
    first_for_stat.push_back("for");
    first_write_stat.push_back("write");
    first_read_stat.push_back("read");
    first_compound_stat.push_back("{");
    first_expression_stat.push_back("_ID");     //TODO：没推出来
    first_expression_stat.push_back("_NUM");     //TODO：没推出来
    first_expression_stat.push_back("(");     //TODO：没推出来
    first_expression_stat.push_back(";");     //TODO：没推出来
    first_expression.push_back("_ID");//TODO：补全
    first_expression.push_back("_NUM");//TODO：补全
    first_expression.push_back("(");//TODO：补全
    first_factor.push_back("_ID");      //表示
    first_factor.push_back("_NUM");
    first_factor.push_back("(");
    first_tmp_term.push_back("*");
    first_tmp_term.push_back("/");
    first_tmp_term.push_back("_E");
    first_term.push_back("_ID");
    first_term.push_back("_NUM");
    first_term.push_back("(");
    first_tmp_additive_expr.push_back("+");
    first_tmp_additive_expr.push_back("-");
    first_tmp_additive_expr.push_back("_E");
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
    first_statement.push_back("if");    //TODO:补全
    first_statement.push_back("while");
    first_statement.push_back("for");
    first_statement.push_back("write");
    first_statement.push_back("read");
    first_statement.push_back("{");
    first_statement.push_back("_ID");
    first_statement.push_back("_NUM");
    first_statement.push_back("(");
    first_statement.push_back(";");
    first_statement_list.push_back("if");
    first_statement_list.push_back("while");
    first_statement_list.push_back("for");
    first_statement_list.push_back("write");
    first_statement_list.push_back("read");
    first_statement_list.push_back("{");
    first_statement_list.push_back("_ID");
    first_statement_list.push_back("_NUM");
    first_statement_list.push_back("(");
    first_statement_list.push_back(";");
    first_statement_list.push_back("_E");

    follow_declaration_list.push_back("if");
    follow_declaration_list.push_back("while");
    follow_declaration_list.push_back("for");
    follow_declaration_list.push_back("write");
    follow_declaration_list.push_back("read");
    follow_declaration_list.push_back("{");
    follow_declaration_list.push_back("_ID");
    follow_declaration_list.push_back("_NUM");
    follow_declaration_list.push_back("(");
    follow_declaration_list.push_back(";");
    follow_declaration_list.push_back("}");
    follow_tmp_if_stat.push_back("if");
    follow_tmp_if_stat.push_back("while");
    follow_tmp_if_stat.push_back("for");
    follow_tmp_if_stat.push_back("write");
    follow_tmp_if_stat.push_back("read");
    follow_tmp_if_stat.push_back("{");
    follow_tmp_if_stat.push_back("_ID");
    follow_tmp_if_stat.push_back("_NUM");
    follow_tmp_if_stat.push_back("(");
    follow_tmp_if_stat.push_back(";");
    follow_statement_list.push_back("}");
    follow_tmp_bool_expr.push_back(";");
    follow_tmp_bool_expr.push_back(")");
    follow_tmp_additive_expr.push_back(";");
    follow_tmp_additive_expr.push_back(")");
    follow_tmp_additive_expr.push_back(">");
    follow_tmp_additive_expr.push_back("<");
    follow_tmp_additive_expr.push_back("<=");
    follow_tmp_additive_expr.push_back(">=");
    follow_tmp_additive_expr.push_back("==");
    follow_tmp_additive_expr.push_back("!=");
    follow_tmp_term.push_back(";");
    follow_tmp_term.push_back(")");
    follow_tmp_term.push_back("+");
    follow_tmp_term.push_back("-");
    follow_tmp_term.push_back(">");
    follow_tmp_term.push_back("<");
    follow_tmp_term.push_back("<=");
    follow_tmp_term.push_back(">=");
    follow_tmp_term.push_back("==");
    follow_tmp_term.push_back("!=");


    swi_wrong_state = false;
}
//#1
int PARSER::f_program(int no){
    string ch = LA.m_str[no];
    if(ch == "{"){
        ch = LA.m_str[++no];
    }
    else{
        return no = error_handle(no);
    }
    no = f_declaration_list(no);
    no = f_statement_list(no);
    ch = GetNextSymbol(no);
    if(ch == "}"){
        return ++no;
    }
    else{
        cout << "在行号：" << LA.m_str_lineNum[LA.m_str.size()-1] << "，符号：\"" << LA.m_str[LA.m_str.size()-1] << "\" 的后方，缺失符号: \"}\"" << endl;
        return no;
    }
}
//#2
int PARSER::f_declaration_list(int no){
//    //当出现错误时的错误处理
//    while(swi_wrong_state == true){
//        //如果能进入下一个状态说明，当前字符是正确的
//        if(!is_include(no, first_declaration_stat) && is_include(no, follow_declaration_list)){
//            swi_wrong_state = false;
//        }
//        else if(is_include(no, first_declaration_stat)) swi_wrong_state = false;
//        else no++;
//    }
    if(!is_include(no, first_declaration_stat) && is_include(no, follow_declaration_list)){
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
    else    return no = error_handle(no);
    if(LA.m_str_attribute[no] == 1){
        ch = LA.m_str[++no];
    }
    else{
        no = error_handle(no);
        while(LA.m_str_attribute[no] != 2 && LA.m_str_attribute[no] != 5)   no++;
        if(LA.m_str_attribute[no] == 2) return no;
        ch = LA.m_str[no];
    }
    if(ch == ";")   return ++no;
    else{
        cout << "在行号：" << LA.m_str_lineNum[no-1] << "，符号：\"" << LA.m_str[no-1] << "\" 的后方，缺失符号: \";\"" << endl;
        return no;
    }
}
//#4
int PARSER::f_statement_list(int no){
    if(no >= LA.m_str.size() || (!is_include(no, first_statement) && is_include(no, follow_statement_list))){
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
    else    return no = error_handle(no);
    return no;
}
//#6
int PARSER::f_if_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "if")  ch = LA.m_str[++no];
    else    return no = error_handle(no);
    if(ch == "(")  ch = LA.m_str[++no];
    else    return no = error_handle(no);
    no = f_expression(no);
    if(ch == ")")  ch = LA.m_str[++no];
    else    return no = error_handle(no);
    no = f_statement(no);
    no = f_tmp_if_stat(no);
    return no;
}
//#7
int PARSER::f_while_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "while")   ch = LA.m_str[++no];
    else    return no = error_handle(no);
    if(ch == "(")   ch = LA.m_str[++no];
    else    return no = error_handle(no);
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ")")   ch = LA.m_str[++no];
    else    return no = error_handle(no);
    no = f_statement(no);
    return no;
}
//#8
int PARSER::f_for_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "for") ch = LA.m_str[++no];
    else    return no = error_handle(no);
    if(ch == "(")   ch = LA.m_str[++no];
    else    return no = error_handle(no);
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
    else    return no = error_handle(no);
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ";")   return ++no;
    else    return no = error_handle(no);
}
//#10
int PARSER::f_read_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "read")    ch = LA.m_str[++no];
    else    return no = error_handle(no);
    if(LA.m_str_attribute[no] == 1) ch = LA.m_str[++no];
    else    return no = error_handle(no);
    if(ch == ";")   return ++no;
    else    return no = error_handle(no);
}
//#11
int PARSER::f_compound_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "{")   ch = LA.m_str[++no];
    else    return no = error_handle(no);
    no = f_statement_list(no);
    ch = LA.m_str[no];
    if(ch == "}")   return ++no;
    else    return no = error_handle(no);
}
//#12
int PARSER::f_expression_stat(int no){      //TODO
    string ch = LA.m_str[no];
    if(ch == ";")   return ++no;
    else{
        no = f_expression(no);
        ch = LA.m_str[no];
        if(ch == ";")   return ++no;
        else return no = error_handle(no);
    }
}
//#13
int PARSER::f_expression(int no){       //TODO
    string ch = LA.m_str[no];
    if(LA.m_str_attribute[no] == 1 && LA.m_str[no+1] == "="){
        ch = LA.m_str[++no];
        ch = LA.m_str[++no];
        no =f_bool_expr(no);
        return no;
    }
    else{
        no = f_bool_expr(no);
        return no;
    }
}
//#14
int PARSER::f_bool_expr(int no){
    no = f_additive_expr(no);
    no = f_tmp_bool_expr(no);
    return no;
}
//#15
int PARSER::f_tmp_bool_expr(int no){
    string ch = LA.m_str[no];
    if(is_include(no, follow_tmp_bool_expr)){
        return no;
    }

    if(ch == ">" || ch == "<" || ch == ">=" || ch == "<=" || ch == "==" || ch == "!="){
        ch = LA.m_str[++no];
    }
    else    return no = error_handle(no);
    no = f_additive_expr(no);
    return no;
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
    if(ch == "+" || ch == "-"){
        ch = LA.m_str[++no];
        no = f_term(no);
        no = f_tmp_additive_expr(no);
    }
    else if(is_include(no, follow_tmp_additive_expr))   return no;
    else    return no = error_handle(no);
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
    if(ch == "*" || ch == "/"){
        ch = LA.m_str[++no];
        no = f_factor(no);
        no = f_tmp_term(no);
    }
    else if(is_include(no, follow_tmp_term))    return no;
    else    return no = error_handle(no);
    return no;
}
//#20
int PARSER::f_factor(int no){
    string ch = LA.m_str[no];
    if(LA.m_str_attribute[no] == 1 || LA.m_str_attribute[no] == 3)
        return ++no;
    if(ch == "(")   ch = LA.m_str[++no];
    else    return no = error_handle(no);
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ")")   return ++no;
    else    return no = error_handle(no);
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
    if(no >= LA.m_str.size())   return true;    //如果序号no大于了容器的宽度，那么返回

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
int PARSER::error_handle(int no){
    swi_wrong_state = true;
    if(no >= LA.m_str.size())   return LA.m_str.size()-1;
        cout << "在行号：" << LA.m_str_lineNum[no] << "，存在语法错误代码\"" << LA.m_str[no] << "\"" << endl;
    return no;
}

string PARSER::GetNextSymbol(int no){
    if(no >= LA.m_str.size())   return "_W";
    else return LA.m_str[no];
}

void PARSER::grammar_analysis(){
    LA.text_analysis();     //词法分析器处理单词
    //LA.disp_result();
    f_program(0);
}
