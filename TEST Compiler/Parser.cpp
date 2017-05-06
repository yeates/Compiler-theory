#include "Parser.h"

//�﷨��������Ĺ��캯��
PARSER::PARSER(){
    /*��ʼ��FIRST����*/
    first_program.push_back("(");
    first_declaration_list.push_back("int");
    first_declaration_list.push_back("_E");    //_E��ʾ��
    first_declaration_stat.push_back("int");
    first_statement.push_back("if");
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
    first_if_stat.push_back("if");
    first_while_stat.push_back("while");
    first_for_stat.push_back("for");
    first_write_stat.push_back("write");
    first_read_stat.push_back("read");
    first_compound_stat.push_back("{");
    first_expression_stat.push_back("_ID");
    first_expression_stat.push_back("_NUM");
    first_expression_stat.push_back("(");
    first_expression_stat.push_back(";");
    first_expression.push_back("_ID");
    first_expression.push_back("_NUM");
    first_expression.push_back("(");
    first_factor.push_back("_ID");
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

    /*��ʼ��FOLLOW����*/
    follow_declaration_list.push_back("if");
    follow_declaration_list.push_back("while");
    follow_declaration_list.push_back("for");
    follow_declaration_list.push_back("write");
    follow_declaration_list.push_back("read");
    follow_declaration_list.push_back("{");
    follow_declaration_list.push_back("}");
    follow_declaration_list.push_back("_ID");
    follow_declaration_list.push_back("_NUM");
    follow_declaration_list.push_back("(");
    follow_declaration_list.push_back(";");
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
    follow_expression.push_back(")");
    follow_expression.push_back(";");
    follow_bool_expr.push_back(";");
    follow_bool_expr.push_back(")");
    follow_term.push_back(";");
    follow_term.push_back(")");
    follow_term.push_back("+");
    follow_term.push_back("-");
    follow_term.push_back(">");
    follow_term.push_back("<");
    follow_term.push_back("<=");
    follow_term.push_back(">=");
    follow_term.push_back("==");
    follow_term.push_back("!=");

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
    if(no >= LA.m_str.size())   return no;
    ch = LA.m_str[no];
    if(ch == "}"){
        return ++no;
    }
    else{
        cout << "���кţ�" << LA.m_str_lineNum[LA.m_str.size()-1] << "�����ţ�\"" << LA.m_str[LA.m_str.size()-1] << "\" �ĺ󷽣�ȱʧ����: \"}\"" << endl;
        return no;
    }
}
//#2
int PARSER::f_declaration_list(int no){
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
    else    no = error_handle(no);
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
    else    return no = defect_handle(no, ";");
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
//#6���ж��� if (<expression>) <statement > ��,�ж��Ƿ���һ���ַ�Ϊelse����������ж�else <statement>������������
int PARSER::f_if_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "if")  ch = LA.m_str[++no];
    else    no = error_handle(no);
    if(ch == "(")  ch = LA.m_str[++no];
    else    no = defect_handle(no, "(");
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ")")  ch = LA.m_str[++no];
    else    no = defect_handle(no, ")");
    no = f_statement(no);
    ch = LA.m_str[no];
    if(ch == "else"){
        no++;
        no = f_statement(no);
    }
    return no;
}
//#7
int PARSER::f_while_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "while")   ch = LA.m_str[++no];
    else    no = error_handle(no);
    if(ch == "(")   ch = LA.m_str[++no];
    else    no = defect_handle(no, "(");
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ")")   ch = LA.m_str[++no];
    else    no = defect_handle(no, ")");
    no = f_statement(no);
    return no;
}
//#8
int PARSER::f_for_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "for") ch = LA.m_str[++no];
    else    no = error_handle(no);
    if(ch == "(")   ch = LA.m_str[++no];
    else    no = defect_handle(no, "(");
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ";")   ch = LA.m_str[++no];
    else    no = defect_handle(no, ";");
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ";")   ch = LA.m_str[++no];
    else    no = defect_handle(no, ";");
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ")")   ch = LA.m_str[++no];
    else    no = defect_handle(no, ")");
    no = f_statement(no);
    return no;
}
//#9
int PARSER::f_write_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "write")   ch = LA.m_str[++no];
    else    no = error_handle(no);
    no = f_expression(no);
    ch = LA.m_str[no];
    if(ch == ";")   return ++no;
    else    return no = defect_handle(no, ";");
}
//#10
int PARSER::f_read_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "read")    ch = LA.m_str[++no];
    else    no = error_handle(no);
    if(LA.m_str_attribute[no] == 1) ch = LA.m_str[++no];
    else    no = error_handle(no);
    if(ch == ";")   return ++no;
    else    return no = defect_handle(no, ";");
}
//#11
int PARSER::f_compound_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "{")   ch = LA.m_str[++no];
    else    no = defect_handle(no, "{");
    no = f_statement_list(no);
    if(no >= LA.m_str.size())   return no;
    ch = LA.m_str[no];
    if(ch == "}")   return ++no;
    else    return no = defect_handle(no, "}");
}
//#12
int PARSER::f_expression_stat(int no){
    string ch = LA.m_str[no];
    if(ch == ";")   return ++no;
    else{
        no = f_expression(no);
        ch = LA.m_str[no];
        if(ch == ";")   return ++no;
        else return no = defect_handle(no, ";");
    }
}
//#13
int PARSER::f_expression(int no){
    string ch = LA.m_str[no];
    if(LA.m_str_attribute[no] == 1 && LA.m_str[no+1] == "="){
        ch = LA.m_str[++no];
        ch = LA.m_str[++no];
        no = f_bool_expr(no);
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
    if(ch == ">" || ch == "<" || ch == ">=" || ch == "<=" || ch == "==" || ch == "!="){
        ch = LA.m_str[++no];
        no = f_additive_expr(no);
    }
    //���ch����first���У���follow�������ҵ�������ϵ����ôreturn
    else if(is_include(no, follow_tmp_bool_expr))   return no;
    else    return no;
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
    else    return no;      //���ֱ�ӷ��أ�����Ҫ������ʹ��error_handle��������Ϊerror_handle��������no++
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
    else    return no;
    return no;
}
//#20
int PARSER::f_factor(int no){
    string ch = LA.m_str[no];

    //��chΪID����NUMʱ��return
    if(LA.m_str_attribute[no] == 1 || LA.m_str_attribute[no] == 3)
        return ++no;
    else if(ch == "("){
        ch = LA.m_str[++no];
        no = f_expression(no);
        ch = LA.m_str[no];
        if(ch == ")")   return ++no;
        else    return no = defect_handle(no, ")");
    }
    else    return no = error_handle(no);  //���ﲻ���ϸ�����ķ���������Ϊ�˴���������ֻ�������������������²Żᷢ������������������⴦��
}

//�൱����ѧ�����ϵ�����
bool PARSER::is_include(int no, vector<string>first){
    if(no >= LA.m_str.size())   return true;    //������no�����������Ŀ�ȣ���ô����

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
    if(no >= LA.m_str.size())   return LA.m_str.size()-1;
        cout << "��������(0)�����кţ�" << LA.m_str_lineNum[no] << "�������﷨�������\"" << LA.m_str[no] << "\"" << endl;
    return ++no;
}

int PARSER::defect_handle(int no, string str){
    if(no >= LA.m_str.size())   return LA.m_str.size()-1;
        cout << "��������(1)�����кţ�" << LA.m_str_lineNum[no] << "���ϵĵ��ʣ�\"" << LA.m_str[no] << "\"��ǰ��ȱʧ��һ�����ţ�\"" << str << "\"" << endl;
    return no;
}


void PARSER::grammar_analysis(){
    LA.text_analysis();     //�ʷ�������������
    cout << "------------�﷨����-----------" << endl;
    f_program(0);
    cout << "------------��������-----------" << endl << endl;
    LA.disp_result(); //�ʷ�����������
    LA.disp_wronginfo();
}
