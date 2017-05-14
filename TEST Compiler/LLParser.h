#ifndef __LLPARSER_H__
#define __LLPARSER_H__

#include "stdafx.h"
#include "Lexical_analyzer.h"
#include "LLTable.h"

class LLPARSER{
private:
    map<string, int>_Vt;
    void init_terminator(); //初始化终结符表
    LLTABLE ll_1_table;     //LL(1)表
    TDFA LA;                //词法分析器
public:
    LLPARSER();
    void grammar_analysis();
};

#endif
