#include "LLParser.h"


LLPARSER::LLPARSER(){
    init_terminator();  //初始化终结符表
}

//初始化终结符表
void LLPARSER::init_terminator(){

    _Vt["*"] = _Vt["/"] = _Vt["{"] = _Vt["}"] = _Vt["("] = _Vt[")"] = _Vt["!="] \
    = _Vt["=="] = _Vt["+"] = _Vt["-"] = _Vt["<="] = _Vt[">="] = _Vt["<"] = _Vt[">"] \
    = _Vt["if"] = _Vt["while"] = _Vt["for"] = _Vt["write"] = _Vt["read"] = _Vt["int"] \
    = _Vt[";"] = 1;
}

//LL（1）表驱动主控程序
void LLPARSER::grammar_analysis(){
    LA.text_analysis(); //词法分析

    cout << "------------语法分析-----------" << endl;
    stack<string>ss;    //符号栈symbol_stack
    ss.push("#");
    ss.push("_A");
    int no = 0, len = LA.m_str.size();
    string ch = LA.m_str[no++];
    bool flag = true;
    bool success_flag = true;
    while(flag){
        string x = ss.top();

        if(x == "e_"){
            ss.pop();
            continue;
        }

        if(LA.m_str_attribute[no-1] == 1)   ch = "ID_";
        else if(LA.m_str_attribute[no-1] == 3)   ch = "NUM_";

        if(x == if_deal_symbol && ch == "else"){       //if的特殊处理
            ss.push("_E");
            ss.push("else");
            x = ss.top();
        }
        else if(x == if_deal_symbol && ch != "else"){
            ss.pop();
            continue;
        }

        if(_Vt[x] == 1 || (x != "#" && x.at(0) != '_') ){
            if(ch == x || (x == "ID_" && LA.m_str_attribute[no-1] == 1) || (x == "NUM_" && LA.m_str_attribute[no-1] == 3)){
                ss.pop();
                if(no < len)    ch = LA.m_str[no++];
                else if(no == len)  ch = "#";
            }
            else{
                if(x == ";" || x == ")" || x == "}"){
                    ss.pop();
                    success_flag = false;
                    cout << "错误类型（1），在行号为：" << LA.m_str_lineNum[no-1] <<  "的单词\""<< LA.m_str[no-1] << "\"前面，缺失符号\"" << x << "\"" << endl;
                }
                else{
                    success_flag = false;
                    cout << "错误类型（0），在行号为：" << LA.m_str_lineNum[no-1] <<  "上，存在错误代码\"" << LA.m_str[no-1] << "\"" << endl;
                    ch = LA.m_str[no++];
                }
            }
        }
        else if(x == "#"){
            if(success_flag)    cout << "报告：分析成功，无语法错误！" << endl;
            else cout << "报告：程序存在语法问题，请检查！" << endl;
            flag = false;
        }
        else if(ll_1_table._Go[make_pair(x, ch)] != 0){
            ss.pop();
            int rno = ll_1_table._Go[make_pair(x, ch)]; //产生式右部位于_right数组的下标

            //if的特殊处理，添加一个标志
            if(rno == 14){
                ss.push(if_deal_symbol);
            }
            //正常操作
            int rlen = ll_1_table._right[rno].size();
            for(int i = rlen-1; i >= 0; i--){
                ss.push(ll_1_table._right[rno][i]);     //按反push产生式的右部
            }

            //expression的特殊处理：超前读一位
            if(rno == 24){
                if(ch == "ID_" && LA.m_str[no] == "="){
                    ss.push("=");
                    ss.push("ID_");
                }
            }
        }
        else{
            success_flag = false;
            cout << "错误类型（未知），在行号为：" << LA.m_str_lineNum[no-1] <<  "上，存在错误代码\"" << LA.m_str[no-1] << "\"" << endl;
//            ch = LA.m_str[no++];
//            if(ll_1_table._Go[make_pair(x, ";")] || ll_1_table._Go[make_pair(x, ")")] || ll_1_table._Go[make_pair(x, "}")]){
//                ss.pop();
//                cout << "错误类型（1），在行号为：" << LA.m_str_lineNum[no-1] <<  "的单词\""<< LA.m_str[no-1] << "\"前面，缺失符号\"" << x << "\"" << endl;
//            }
//            else{
//                ss.push(x);
//                cout << "错误类型（0），在行号为：" << LA.m_str_lineNum[no-1] <<  "上，存在错误代码\"" << LA.m_str[no-1] << "\"" << endl;
//                ch = LA.m_str[no++];
//            }
            try{
                if(no >= len)   throw runtime_error("提示：词语数组下标越界，请检查你的程序。");
                ch = LA.m_str[no++];
            }
            catch(runtime_error err_str){
                success_flag = false;
                cout << err_str.what() << endl;
            }
            ss.pop();
        }
    }
    cout << "------------分析结束-----------" << endl << endl;
}


