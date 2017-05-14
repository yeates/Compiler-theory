/***
*������TDFA��TEST Language Lexical analyzer, TEST���Դʷ���������
*
*���ߣ�yeates
***/

#ifndef __LEXICAL_ANALYZER_H__
#define __LEXICAL_ANALYZER_H__

#include "stdafx.h"

class TDFA{
public:
    void text_analysis();
    void disp_wronginfo();
    void disp_result();

    bool is_alpha(char CheckStr);
    bool is_digit(char CheckStr);
    bool is_delimiter(char CheckStr);
    bool is_operator(char CheckStr);

    int identifier_DFA(string& LineStr, int no, int LineNum);
    int unsigned_integer_DFA(string& LineStr, int no, int LineNum);
    int operator_DFA(string& LineStr, int no, int LineNum);
    int delimiter_DFA(string& LineStr, int no, int LineNum);
    int slash_DFA(string& LineStr, int no, int LineNum);        //ע�����ﲢ����ע�ͷ�DFA����ΪҪ����DFA����������б��/��ͷ��DFA

    vector<string>m_str;            //���Ϊi�ĵ��ʵ��ַ���
    vector<int>m_str_attribute;  //���Ϊi�ĵ��ʵĵ�������
    vector<int>m_str_lineNum;    //���Ϊi�ĵ������ڵ��к�
private:

    const string m_KeyWord[7] = {"Null", "Identifier", "Reserved word", "Unsigned integer","Operator", "Delimiter", "Annotator"};
    const string m_reserved_word[8] = {"if", "else", "for", "while", "do", "int", "write", "read"};
    const int m_reserved_word_num = 8;
    bool m_is_in_annotator = false;     //��ǰ�����Ƿ���ע����

};

#endif
