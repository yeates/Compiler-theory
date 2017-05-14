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
    stack<string>ss;    //符号栈symbol_stack
    ss.push("#");
    ss.push("_A");
    int no = 0, len = LA.m_str.size();
    string ch = LA.m_str[no++];
    bool flag = true;

    while(flag){
        string x = ss.top();
        ss.pop();
        if(_Vt[x] == 1){
            if(ch == x){
                if(no < len)    ch = LA.m_str[no++];
                else    {cout << "分析已达错误边界，停止分析!" << endl; break;}
            }
            else    cout << "在行号为：" << LA.m_str_lineNum[no] <<  "上，存在错误代码\"" << ch << "\"" << endl;
        }
        else if(x == "#"){
            if(ch == x) {cout << "报告：分析成功！" << endl; flag = false;}
            else    cout << "在行号为：" << LA.m_str_lineNum[no] <<  "上，存在错误代码\"" << ch << "\"" << endl;
        }
        else if(ll_1_table._Go[make_pair(x, ch)] != 0){
            int rno = ll_1_table._Go[make_pair(x, ch)]; //产生式右部位于_right数组的下标
            int len = ll_1_table._right[rno].size();
            for(int i = len-1; i >= 0; i--){
                ss.push(ll_1_table._right[rno][i]);     //按反push产生式的右部
            }
        }
        else    cout << "在行号为：" << LA.m_str_lineNum[no] <<  "上，存在错误代码\"" << ch << "\"" << endl;
    }
}


