#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#define Max(a, b) a > b? a : b
#define Min(a, b) a < b? a : b
using namespace std;


/***
*类名：TDFA（TEST Language DFA, TEST语言词法分析器）
*
*作者：喻永生
***/
class TDFA{
public:

    struct WRINFO{
        int line_num;
        string wr_str;
        WRINFO(int l, string s):line_num(l), wr_str(s){};
    };

    void read_text();
    void disp_result();
    void lexical_analysis();
    int use_DFA(string CheckStr);
//////////工具函数//////////
    bool is_alpha(char CheckStr);
    bool is_digit(char CheckStr);
    bool is_delimiter(char CheckStr);
    bool is_operator(char CheckStr);
///////////////////////////
    int identifier_DFA(string CheckStr);
    bool unsigned_integer_DFA(string CheckStr);
    bool operator_DFA(string CheckStr);
    bool delimiter_DFA(string CheckStr);
    int slash_DFA(string CheckStr);        //注意这里并不是注释符DFA，因为要根据DFA来看，这是斜杠/开头的DFA


private:

    vector<string>m_str;            //编号为i的单词的字符串
    vector<int>m_str_attribute;  //编号为i的单词的单词属性
    vector<int>m_str_lineNum;    //编号为i的单词所在的行号
    const string m_KeyWord[7] = {"Null", "Identifier", "Reserved word", "Unsigned integer","Operator", "Delimiter", "Annotator"};
    const string m_reserved_word[8] = {"if", "else", "for", "while", "do", "int", "write", "read"};
    const int m_reserved_word_num = 8;
    vector<WRINFO>m_wr_info;
    bool m_is_in_annotator = false;     //当前单词是否在注释内
};

void TDFA::read_text(){
    string line, str;
    int lineNum = 1;
    while(getline(cin, line)){
        stringstream ss(line);  //用ss输入的方法，可自动去掉空格的干扰，对单个单词进行分析
        while(ss >> str){
            m_str.push_back(str);
            m_str_attribute.push_back(0);
            m_str_lineNum.push_back(lineNum);
        }
        lineNum++;
    }
}

void TDFA::lexical_analysis(){
    int StockLen = m_str.size();   //m_str的长度
    for(int i = 0; i < StockLen; i++){
        //if(m_is_in_annotator)   continue;
        m_str_attribute[i] = use_DFA(m_str[i]);
        if(m_str_attribute[i] == 0){
            m_wr_info.push_back(WRINFO(m_str_lineNum[i], m_str[i]));
        }
    }
}

int TDFA::use_DFA(string CheckStr){
    string& cs = CheckStr;  //简化名称
    if(cs.size() == 0)  return 0;
    if(is_alpha(cs[0])){
        return identifier_DFA(cs);
    }
    else if(is_digit(cs[0])){
        if(unsigned_integer_DFA(cs))    return 3;
        else return 0;
    }
    else if(is_operator(cs[0])){
        if(operator_DFA(cs))    return 4;
        else return 0;
    }
    else if(is_delimiter(cs[0])){
        if(delimiter_DFA(cs))   return 5;
        else return 0;
    }
    else if(cs[0] == '/'){
        return slash_DFA(cs);
    }
    else return 0;
}

int TDFA::identifier_DFA(string CheckStr){
    string& cs = CheckStr;
    int i = 1, len = cs.size();
    while(i < len){
        if(!is_alpha(cs[i]) && !is_digit(cs[i]))
            return 0;       //TODO：记录行号
        i++;
    }
    for(int i = 0; i < m_reserved_word_num; i++){
        if(CheckStr == m_reserved_word[i])
            return 2;
    }
    return 1;
}

bool TDFA::unsigned_integer_DFA(string CheckStr){
    string& cs = CheckStr;
    int i = 1, len = cs.size();
    //当数为0的情况
    if(cs[0] == '0'){
        if(len == 1)    return true;    //如果这个字符就是一个0，那么输入正确
        else return false;      //TODO：记录行号
    }
    //当数的开头不为0的情况
    while(i < len){
        if(!is_digit(cs[i]))    return false;       //TODO：记录行号
        i++;
    }
    return true;
}

bool TDFA::operator_DFA(string CheckStr){
    string& cs = CheckStr;
    int len = cs.size();
    //因为运算符只有1或2的长度，所以直接ifelse讨论
    if(len == 1){
        if(cs[0] == '!')    return false;   //TODO：记录行号
        else return true;
    }
    else if(len == 2){
        if(cs[1] == '=' && (cs[0] == '>' || cs[0] == '<' || cs[0] == '=' || cs[0] == '!'))
            return true;
        else return false;
    }
}

bool TDFA::delimiter_DFA(string CheckStr){      //TODO：这里有问题，因为不是很了解分隔符的含义
    int len = CheckStr.size();
    if(len == 1)    return true;
    else return false;
}

int TDFA::slash_DFA(string CheckStr){
    string& cs = CheckStr;
    int len = cs.size(), i = 2;
    if(len == 1)    return 4;
    if(cs[1] != '*')    return 0;       //TODO：记录报错行号
    int state_now = 1;
    while(i < len){
        switch(state_now){
        case 1:
            if(cs[i] == '*'){
                state_now = 2;
                i++;
            }
            else i++;
            break;
        case 2:
            if(cs[i] == '*')    i++;
            else if(cs[i] == '/' && i == len - 1){
                state_now = 3;  //第二个终态
                i++;
            }
            else if(cs[i] == '/' && i != len - 1)   return 0;   //记录报错行号
            else{
                state_now = 1;
                i++;
            }
            break;
        default:break;
        }
    }
    if(state_now == 3)
        return 6;
    else return 0;
}

bool TDFA::is_alpha(char CheckStr){
    if((CheckStr >= 'a' && CheckStr <= 'z') || (CheckStr >= 'A' && CheckStr <= 'Z'))
        return true;
    else return false;
}

bool TDFA::is_digit(char CheckStr){
    if(CheckStr >= '0' && CheckStr <= '9')
        return true;
    else return false;
}

bool TDFA::is_delimiter(char CheckStr){
    switch(CheckStr){
        case '(':   return true;
        case ')':   return true;
        case '{':   return true;
        case '}':   return true;
        case ';':   return true;
        default:    return false;
    }
}

bool TDFA::is_operator(char CheckStr){
    switch(CheckStr){
        case '+':   return true;
        case '-':   return true;
        case '*':   return true;
        case '!':   return true;
        case '<':   return true;
        case '>':   return true;
        case '=':   return true;
        default:    return false;
    }
}

void TDFA::disp_result(){
    int StockLen = m_str.size();   //m_str的长度
    int WrInfoLen = m_wr_info.size();
    for(int i = 0; i < WrInfoLen; i++){
        cout << "在行号：" << m_wr_info[i].line_num << "有错误代码 " << m_wr_info[i].wr_str <<endl;
    }
    for(int i = 0; i < StockLen; i++){
        cout << "单词：" << m_str[i] << "  属性：";
        cout << m_KeyWord[m_str_attribute[i]] << endl;
    }
}

int main(){

    freopen("input.txt", "r", stdin);

    TDFA tdfa;                  //声明对象
    tdfa.read_text();           //读取文本
    tdfa.lexical_analysis();    //词法分析
    tdfa.disp_result();         //输出结果
    return 0;
}
