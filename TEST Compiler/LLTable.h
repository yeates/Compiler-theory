#ifndef __LLTABLE_H__
#define __LLTABLE_H__


#include "stdafx.h"
class LLTABLE{
private:
    typedef pair<string, string> GO;
    void init_right();      //��ʼ������ʽ�Ҳ���
    void init_ll();         //��ʼ��LL��1�������
public:
    LLTABLE();  //���캯��
    map<GO, int>_Go;
    vector<string>_right[44];
};

#endif // __LLTABLE_H__
