/***
*类名：TDFA（TEST Language Lexical analyzer, TEST语言词法分析器）
*
*作者：yeates
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
    int slash_DFA(string& LineStr, int no, int LineNum);        //注意这里并不是注释符DFA，因为要根据DFA来看，这是斜杠/开头的DFA

    vector<string>m_str;            //编号为i的单词的字符串
    vector<int>m_str_attribute;  //编号为i的单词的单词属性
    vector<int>m_str_lineNum;    //编号为i的单词所在的行号
private:

    const string m_KeyWord[7] = {"Null", "Identifier", "Reserved word", "Unsigned integer","Operator", "Delimiter", "Annotator"};
    const string m_reserved_word[8] = {"if", "else", "for", "while", "do", "int", "write", "read"};
    const int m_reserved_word_num = 8;
    bool m_is_in_annotator = false;     //当前单词是否在注释内

};

#endif
