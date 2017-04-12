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
*作者：yestes
***/
class TDFA{
public:
    void text_analysis();
    void disp_result();

    bool is_alpha(char CheckStr);
    bool is_digit(char CheckStr);
    bool is_delimiter(char CheckStr);
    bool is_operator(char CheckStr);

    int identifier_DFA(string& LineStr, int no, int LineNum);
    int unsigned_integer_DFA(string& LineStr, int no, int LineNum);
    int operator_DFA(string& LineStr, int no, int LineNum);
    int delimiter_DFA(string& LineStr, int no, int LineNum);
    int slash_DFA(string& LineStr, int no, int LineNum);        //注意这里并不是注释符DFA，因为要根据DFA来看，这是斜杠/开头的DFA

private:

    vector<string>m_str;            //编号为i的单词的字符串
    vector<int>m_str_attribute;  //编号为i的单词的单词属性
    vector<int>m_str_lineNum;    //编号为i的单词所在的行号
    const string m_KeyWord[7] = {"Null", "Identifier", "Reserved word", "Unsigned integer","Operator", "Delimiter", "Annotator"};
    const string m_reserved_word[8] = {"if", "else", "for", "while", "do", "int", "write", "read"};
    const int m_reserved_word_num = 8;
    bool m_is_in_annotator = false;     //当前单词是否在注释内

};

void TDFA::text_analysis(){
    string line;
    int lineNo = 0;
    while(getline(cin, line)){
        int i = 0;
        lineNo++;
        while(i < line.size()){
            if(is_alpha(line[i])){
                i = identifier_DFA(line, i, lineNo);
            }
            else if(is_digit(line[i])){
                i = unsigned_integer_DFA(line, i, lineNo);
            }
            else if(is_operator(line[i])){
                i = operator_DFA(line, i, lineNo);
            }
            else if(is_delimiter(line[i])){
                i = delimiter_DFA(line, i, lineNo);
            }
            else if(line[i] == '/'){
                i = slash_DFA(line, i, lineNo);
            }
            else if(line[i] == ' ') i++;
            else{
                string tp;
                tp.insert(tp.end(), line[i]);
                m_str.push_back(tp);        //存储识别的字符串
                m_str_attribute.push_back(0);   //保存为标识符
                m_str_lineNum.push_back(lineNo);   //保存当前字符串的行数
                i++;
            }
        }
    }
}

int TDFA::identifier_DFA(string& LineStr, int no, int LineNum){
    string tp;
    while(is_alpha(LineStr[no]) || is_digit(LineStr[no])){
        tp.insert(tp.end(), LineStr[no]);
        no++;
    }
    bool flag = false;      //判断当前识别的字符串是否是保留字
    for(int i = 0; i < m_reserved_word_num; i++){
        if(tp == m_reserved_word[i]){
            flag = true;
            break;
        }
    }
    if(flag){
        m_str.push_back(tp);        //存储识别的字符串
        m_str_attribute.push_back(2);   //保存为保留字
        m_str_lineNum.push_back(LineNum);   //保存当前字符串的行数
    }
    else{
        m_str.push_back(tp);        //存储识别的字符串
        m_str_attribute.push_back(1);   //保存为标识符
        m_str_lineNum.push_back(LineNum);   //保存当前字符串的行数
    }
    return no;
}

int TDFA::unsigned_integer_DFA(string& LineStr, int no, int LineNum){
    string tp;
    while(is_digit(LineStr[no])){
        tp.insert(tp.end(), LineStr[no]);
        no++;
    }
    if(tp[0] == '0' && tp.size() > 1){
        m_str.push_back(tp);        //存储识别的字符串
        m_str_attribute.push_back(0);   //报错
        m_str_lineNum.push_back(LineNum);   //保存当前字符串的行数
    }
    else{
        m_str.push_back(tp);        //存储识别的字符串
        m_str_attribute.push_back(3);   //保存当前字符串的属性
        m_str_lineNum.push_back(LineNum);   //保存当前字符串的行数
    }
    return no;
}

int TDFA::operator_DFA(string& LineStr, int no, int LineNum){
    string tp;
    while(is_operator(LineStr[no])){
        tp.insert(tp.end(), LineStr[no]);
        no++;
    }
    if(tp[0] != '!' && tp.size() == 1){
        m_str.push_back(tp);        //存储识别的字符串
        m_str_attribute.push_back(4);   //保存当前字符串的属性
        m_str_lineNum.push_back(LineNum);   //保存当前字符串的行数
    }
    else if(tp.size() == 2 && tp[0] != '+' && tp[0] != '-' && tp[0] != '*' && tp[1] == '='){
        m_str.push_back(tp);        //存储识别的字符串
        m_str_attribute.push_back(4);   //保存当前字符串的属性
        m_str_lineNum.push_back(LineNum);   //保存当前字符串的行数
    }
    else{
        m_str.push_back(tp);
        m_str_attribute.push_back(0);       //报错
        m_str_lineNum.push_back(LineNum);
    }
    return no;
}

int TDFA::delimiter_DFA(string& LineStr, int no, int LineNum){
    string tp;
    tp.insert(tp.end(), LineStr[no]);
    m_str.push_back(tp);        //存储识别的字符串
    m_str_attribute.push_back(5);   //保存当前字符串的属性
    m_str_lineNum.push_back(LineNum);   //保存当前字符串的行数
    return ++no;
}

int TDFA::slash_DFA(string& LineStr, int no, int LineNum){
    string tp;
    tp.insert(tp.end(), LineStr[no++]);        //先添加/字符
    if(LineStr[no] == '*'){
        tp.insert(tp.end(), LineStr[no++]);
        int state = 1;
        bool flag = false;  //注释字符串是否完整找到
        while(no < LineStr.size() && flag == false){
            switch(state){
            case 1:
                if(LineStr[no] == '*'){
                    state = 2;
                }
                tp.insert(tp.end(), LineStr[no++]);
                break;
            case 2:
                if(LineStr[no] == '/')   flag = true;
                else if(LineStr[no] != '*')  state = 1;
                tp.insert(tp.end(), LineStr[no++]);
                break;
            default: break;
            }
        }
        if(flag){
            m_str.push_back(tp);        //存储识别的字符串
            m_str_attribute.push_back(6);   //找到了完整的注释
            m_str_lineNum.push_back(LineNum);   //保存当前字符串的行数
        }
        else{
            m_str.push_back(tp);        //存储识别的字符串
            m_str_attribute.push_back(0);   //报错
            m_str_lineNum.push_back(LineNum);   //保存当前字符串的行数
        }
    }
    else{
        m_str.push_back(tp);        //存储识别的字符串
        m_str_attribute.push_back(4);   //分隔符
        m_str_lineNum.push_back(LineNum);   //保存当前字符串的行数
    }
    return no;
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
    for(int i = 0; i < StockLen; i++){
        if(m_str_attribute[i] == 0)
            cout << "在行号：" << m_str_lineNum[i] << "，存在错误代码 " << m_str[i] <<endl;
    }
    for(int i = 0; i < StockLen; i++){
        cout << "单词：" << m_str[i] << "  属性：";
        cout << m_KeyWord[m_str_attribute[i]] << endl;
    }
}

int main(){
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    TDFA tdfa;
    tdfa.text_analysis();       //分析文本
    tdfa.disp_result();     //输出结果

    return 0;
}
