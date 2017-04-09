#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#define Max(a, b) a > b? a : b
#define Min(a, b) a < b? a : b
using namespace std;


/***
*������TDFA��TEST Language DFA, TEST���Դʷ���������
*
*���ߣ�������
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
//////////���ߺ���//////////
    bool is_alpha(char CheckStr);
    bool is_digit(char CheckStr);
    bool is_delimiter(char CheckStr);
    bool is_operator(char CheckStr);
///////////////////////////
    int identifier_DFA(string CheckStr);
    bool unsigned_integer_DFA(string CheckStr);
    bool operator_DFA(string CheckStr);
    bool delimiter_DFA(string CheckStr);
    int slash_DFA(string CheckStr);        //ע�����ﲢ����ע�ͷ�DFA����ΪҪ����DFA����������б��/��ͷ��DFA


private:

    vector<string>m_str;            //���Ϊi�ĵ��ʵ��ַ���
    vector<int>m_str_attribute;  //���Ϊi�ĵ��ʵĵ�������
    vector<int>m_str_lineNum;    //���Ϊi�ĵ������ڵ��к�
    const string m_KeyWord[7] = {"Null", "Identifier", "Reserved word", "Unsigned integer","Operator", "Delimiter", "Annotator"};
    const string m_reserved_word[8] = {"if", "else", "for", "while", "do", "int", "write", "read"};
    const int m_reserved_word_num = 8;
    vector<WRINFO>m_wr_info;
    bool m_is_in_annotator = false;     //��ǰ�����Ƿ���ע����
};

void TDFA::read_text(){
    string line, str;
    int lineNum = 1;
    while(getline(cin, line)){
        stringstream ss(line);  //��ss����ķ��������Զ�ȥ���ո�ĸ��ţ��Ե������ʽ��з���
        while(ss >> str){
            m_str.push_back(str);
            m_str_attribute.push_back(0);
            m_str_lineNum.push_back(lineNum);
        }
        lineNum++;
    }
}

void TDFA::lexical_analysis(){
    int StockLen = m_str.size();   //m_str�ĳ���
    for(int i = 0; i < StockLen; i++){
        //if(m_is_in_annotator)   continue;
        m_str_attribute[i] = use_DFA(m_str[i]);
        if(m_str_attribute[i] == 0){
            m_wr_info.push_back(WRINFO(m_str_lineNum[i], m_str[i]));
        }
    }
}

int TDFA::use_DFA(string CheckStr){
    string& cs = CheckStr;  //������
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
            return 0;       //TODO����¼�к�
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
    //����Ϊ0�����
    if(cs[0] == '0'){
        if(len == 1)    return true;    //�������ַ�����һ��0����ô������ȷ
        else return false;      //TODO����¼�к�
    }
    //�����Ŀ�ͷ��Ϊ0�����
    while(i < len){
        if(!is_digit(cs[i]))    return false;       //TODO����¼�к�
        i++;
    }
    return true;
}

bool TDFA::operator_DFA(string CheckStr){
    string& cs = CheckStr;
    int len = cs.size();
    //��Ϊ�����ֻ��1��2�ĳ��ȣ�����ֱ��ifelse����
    if(len == 1){
        if(cs[0] == '!')    return false;   //TODO����¼�к�
        else return true;
    }
    else if(len == 2){
        if(cs[1] == '=' && (cs[0] == '>' || cs[0] == '<' || cs[0] == '=' || cs[0] == '!'))
            return true;
        else return false;
    }
}

bool TDFA::delimiter_DFA(string CheckStr){      //TODO�����������⣬��Ϊ���Ǻ��˽�ָ����ĺ���
    int len = CheckStr.size();
    if(len == 1)    return true;
    else return false;
}

int TDFA::slash_DFA(string CheckStr){
    string& cs = CheckStr;
    int len = cs.size(), i = 2;
    if(len == 1)    return 4;
    if(cs[1] != '*')    return 0;       //TODO����¼�����к�
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
                state_now = 3;  //�ڶ�����̬
                i++;
            }
            else if(cs[i] == '/' && i != len - 1)   return 0;   //��¼�����к�
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
    int StockLen = m_str.size();   //m_str�ĳ���
    int WrInfoLen = m_wr_info.size();
    for(int i = 0; i < WrInfoLen; i++){
        cout << "���кţ�" << m_wr_info[i].line_num << "�д������ " << m_wr_info[i].wr_str <<endl;
    }
    for(int i = 0; i < StockLen; i++){
        cout << "���ʣ�" << m_str[i] << "  ���ԣ�";
        cout << m_KeyWord[m_str_attribute[i]] << endl;
    }
}

int main(){

    freopen("input.txt", "r", stdin);

    TDFA tdfa;                  //��������
    tdfa.read_text();           //��ȡ�ı�
    tdfa.lexical_analysis();    //�ʷ�����
    tdfa.disp_result();         //������
    return 0;
}
