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

int PARSER::f_program(int no){
    string ch = LA.m_str[no];
    if(ch == "{")   ch = LA.m_str[++no];
    else{}  //TODO：记录错误信息
    if(is_include(no, first_declaration_list)){
        no = f_declaration_list(ch, no);
        ch = LA.m_str[no];      //这儿不用++
                                //TODO:记录错误信息
        if(is_include(no, first_statement_list)){
            no = f_statement_list(ch, no);
            //TODO：做结束处理
        }
        else{}  //TODO:错误处理
    }
    else if(is_include(no, follow_declaration_list)){


    }
    else{}  //TODO：记录错误信息
}

int PARSER::f_declaration_list(int no){
    if(is_include(no, first_declaration_stat)){
        no = f_declaration_stat(no);
        if(is_include(no, first_declaration_list)){
            no = f_declaration_list(no);
        }
    }
}
int PARSER::f_declaration_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "int") ch = LA.m_str[++no];
    else{}
    if(LA.m_str_attribute[no] == 1) ch = LA.m_str[++no];    //1表示ID，具体查词法分析器
    else{}
}
int PARSER::f_statement_list(int no){
    if(is_include(no, first_statement)){
        no = f_statement(no);
        if(is_include(first_statement_list)){
            no = f_statement_list(no);
            // 结束
        }
    }
}
int PARSER::f_statement(int no){
    if(is_include(no, first_if_stat)){
        no = f_for_stat(no);
    }

    if(is_include(no, first_while_stat)){
        no = f_while_stat(no);
    }

    if(is_include(no, first_for_stat)){
        no = f_for_stat(no);
    }

    if(is_include(no, first_write_stat)){
        no = f_write_stat(no);
    }

    if(is_include(no, first_read_stat)){
        no = f_read_stat(no);
    }

    if(is_include(no, first_compound_stat)){
        no = f_compound_stat(no);
    }

    if(is_include(no, first_expression_stat)){
        no = f_expression_stat(no);
    }
}
int PARSER::f_if_stat(int no){

}
int PARSER::f_while_stat(int no){
    //TODO：错误处理
    string ch = LA.m_str[no];
    if(ch == "while"){
        ch = LA.m_str[++no];
        if(ch == "("){
            ch = LA.m_str[++no];
            if(is_include(no, first_expression)){
                no = f_expression(no);
                ch = LA.m_str[no];
                if(ch == ")"){
                    ch = LA.m_str[++no];
                    if(is_include(no, first_statement)){
                        no = f_statement(no);
                        //结束
                    }
                }
            }
        }
    }

}
int PARSER::f_read_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "read"){
        ch = LA.m_str[++no];
        if(LA.m_str_attribute[no] == 1){
            ch = LA.m_str[++no];
            if(ch == ";"){

                //结束
            }
        }
    }
}
int PARSER::f_for_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "for") ch = LA.m_str[++no];
    if(ch == "(")   ch = LA.m_str[++no];
    if(is_include(no, first_expression)){
        no = f_expression(no);
        ch = LA.m_str[no];
    }
    if(ch == ";")   ch = LA.m_str[++no];
    if(is_include(no, first_expression)){
        no = f_expression(no);
        ch = LA.m_str[no];
    }
    if(ch == ";")   ch = LA.m_str[++no];
    if(is_include(no, first_expression)){
        no = f_expression(no);
        ch = LA.m_str[no];
    }
    if(ch == ")")   ch = LA.m_str[++no];
    if(is_include(no, first_statement)){
        no = f_statement(no);
        //结束
    }
}
int PARSER::f_write_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "write"){
        ch = LA.m_str[++no];
        if(is_include(no, first_expression)){
            no = f_expression(no);
            ch = LA.m_str[no];
            if(ch == ";"){
                //结束
            }
        }
    }
}
int PARSER::f_compound_stat(int no){
    string ch = LA.m_str[no];
    if(ch == "{"){
        ch = LA.m_str[++no];
        if(is_include(no, first_statement_list)){   //TODO：处理_E
            no = f_statement_list(no);
            ch = LA.m_str[no];
            if(ch == "}")   //结束
        }
    }
}
int PARSER::f_expression_stat(int no){
    string ch = LA.m_str[no];
    if(is_include(no, first_expression)){   //TODO：处理_E
        no = f_expression(no);
        ch = LA.m_str[no];
        if(ch == ";"){
            //结束
        }
    }
    else{}  //TODO:错误
    if(ch == ";")   //结束
}
int PARSER::f_expression(int no){
    string ch = LA.m_str[no];
    if(LA.m_str_attribute[no] == 1){

    }
}
int PARSER::f_bool_expr(int no){
    if(is_include(no, first_additive_expr)){
        no = f_additive_expr(no);
        if(is_include(no, first_tmp_additive_expr)){
            no = f_tmp_additive_expr(no);
            //结束
        }
    }
}
int PARSER::f_tmp_bool_expr(int no){    //TODO：考虑_E
    string ch = LA.m_str[no];
    if(ch == ">" || ch == "<" || ch == ">=" || ch == "<=" || ch == "==" || ch == "!="){
        ch = LA.m_str[++no];
        if(is_include(no, first_additive_expr)){
            no = f_additive_expr(no);
            //结束
        }
    }
}
int PARSER::f_additive_expr(int no){
    if(is_include(no, first_term)){
        no = f_term(no);
        if(is_include(no, first_tmp_additive_expr)){
            no = f_tmp_additive_expr(no);
            //结束
        }
    }
}
int PARSER::f_tmp_additive_expr(int no){
    string ch = LA.m_str[no];
    if(ch == "+" || ch == "-"){
        ch = LA.m_str[++no];
        if(is_include(no, first_term)){
            no = f_term(no);
            if(is_include(no, first_tmp_additive_expr)){
                no = f_tmp_additive_expr(no);
                //结束
            }
        }
    }
}
int PARSER::f_term(int no){
    if(is_include(no, first_factor)){
        no = f_factor(no);
        if(is_include(no, first_tmp_term){
            no = f_tmp_term(no);
            //结束
        }
    }
}
int PARSER::f_tmp_term(int no){
    string ch = LA.m_str[no];
    if(ch == "*" || ch == "/"){
        ch = LA.m_str[no];
        if(is_include(no, first_factor)){
            no = f_factor(no);
            if(is_include(no, first_tmp_term)){
                no = f_tmp_term(no);
                //结束
            }
        }
    }
}
int PARSER::f_factor(int no){
    string ch = LA.m_str[no];
    if(ch == "("){
        ch = LA.m_str[++no];
        if(is_include(no, first_expression)){
            no = f_expression(no);
            ch = LA.m_str[no];
            if(ch == ")"){
                //结束
            }
        }
    }
    else{}

    if(LA.m_str_attribute[no] == 1){
        //结束
    }

    if(LA.m_str_attribute[no] == 3){
        //结束
    }
}

bool PARSER::is_include(int no, vector<string>first){
    string ch = LA.m_str[no];
    for(string i:first){
        if(i == "_ID"){
            if(LA.m_str[no] == 1)   return true;
            else continue;
        }
        else if (i == "_NUM"){
            if(LA.m_str[no] == 3)   return true;
            else continue;
        }
        if(ch == i) return true;
    }
    else return false;
}
int main(){
    freopen("./data/input.txt", "r", stdin);
    //freopen("./data/output.txt", "w", stdout);

    TDFA tdfa;
    tdfa.text_analysis();       //分析文本
    tdfa.disp_result();     //输出结果

    return 0;
}
