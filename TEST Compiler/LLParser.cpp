#include "LLParser.h"


LLPARSER::LLPARSER(){
    init_terminator();  //初始化终结符表
}

void LLPARSER::init_terminator(){

    _Vt["*"] = _Vt["/"] = _Vt["{"] = _Vt["}"] = _Vt["("] = _Vt[")"] = _Vt["!="] \
    = _Vt["=="] = _Vt["+"] = _Vt["-"] = _Vt["<="] = _Vt[">="] = _Vt["<"] = _Vt[">"] \
    = _Vt["if"] = _Vt["while"] = _Vt["for"] = _Vt["write"] = _Vt["read"] = _Vt["int"] \
    = _Vt[";"] = 1;
}

void LLPARSER::grammar_analysis(){
    LA.text_analysis(); //词法分析

    stack<string>ss;    //符号栈symbol_stack
    ss.push("#");
    ss.push("_A");
    int no = 0, len = LA.m_str.size();
    string ch = LA.m_str[no++];
    bool flag = true;

    while(flag){
        string x = ss.top();

        if(x == "e_"){
            ss.pop();
            continue;
        }
        if(_Vt[x] == 1 || (x != "#" && x.at(0) != '_') ){
            if(ch == x || (x == "ID_" && LA.m_str_attribute[no-1] == 1) || (x == "NUM_" && LA.m_str_attribute[no-1] == 3)){
                ss.pop();
                if(no < len)    ch = LA.m_str[no++];
            }
            else    {cout << "在行号为：" << LA.m_str_lineNum[no-1] <<  "上，存在错误代码\"" << ch << "\"" << endl; ch = LA.m_str[no++];}
        }
        else if(x == "#"){
            cout << "报告：分析成功！" << endl;
            flag = false;
        }
        else if(ll_1_table._Go[make_pair(x, ch)] != 0){
            ss.pop();
            int rno = ll_1_table._Go[make_pair(x, ch)]; //产生式右部位于_right数组的下标
            int rlen = ll_1_table._right[rno].size();
            for(int i = rlen-1; i >= 0; i--){
                ss.push(ll_1_table._right[rno][i]);     //按反push产生式的右部
            }
        }
        else    {cout << "在行号为：" << LA.m_str_lineNum[no-1] <<  "上，存在错误代码\"" << ch << "\"" << endl; ch = LA.m_str[no++];}

    }
}


