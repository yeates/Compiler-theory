#ifndef __LLPARSER_H__
#define __LLPARSER_H__

#include "stdafx.h"
#include "Lexical_analyzer.h"
#include "LLTable.h"

class LLPARSER{
private:
    map<string, int>_Vt;
    void init_terminator(); //��ʼ���ս����
    LLTABLE ll_1_table;     //LL(1)��
    TDFA LA;                //�ʷ�������
public:
    LLPARSER();
    void grammar_analysis();
};

#endif

