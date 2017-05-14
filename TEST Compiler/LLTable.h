#ifndef __LLTABLE_H__
#define __LLTABLE_H__


#include "stdafx.h"
class LLTABLE{
private:
    typedef pair<string, string> GO;
    void init_right();      //初始化产生式右部表
    void init_ll();         //初始化LL（1）构造表
public:
    LLTABLE();  //构造函数
    map<GO, int>_Go;
    vector<string>_right[44];
};

#endif // __LLTABLE_H__
