#include "LLTable.h"
#define mp make_pair
#define f first
#define s second


//构造函数，初始化TEST语言的LL（1）构造表
LLTABLE::LLTABLE(){
    init_right();   //初始化产生式右部表
    init_ll();      //初始化LL（1）构造表
}


//终结符前面加一个下划线，ID、NUM、e这类非终结符后方加一个下划线，一般非终结符不加任何下划线
void LLTABLE::init_right(){
    vector<string>tp;
    int no = 1;
    tp = {"{", "_B", "_D", "}"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_C", "_B"};
    _right[no++] = tp;
    tp.clear();

    tp = {"e_"};
    _right[no++] = tp;
    tp.clear();

    tp = {"int", "ID_", ";"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_E", "_D"};
    _right[no++] = tp;
    tp.clear();

    tp = {"e_"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_F"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_G"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_H"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_I"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_J"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_K"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_L"};
    _right[no++] = tp;
    tp.clear();

    tp = {"if", "(", "_M", ")", "_E"};
    _right[no++] = tp;
    tp.clear();

    tp = {"if", "(", "_M", ")", "_E", "else", "_E"};
    _right[no++] = tp;
    tp.clear();

    tp = {"while", "(", "_M", ")", "_E"};
    _right[no++] = tp;
    tp.clear();

    tp = {"for", "(", "_M", ")", "_E"};
    _right[no++] = tp;
    tp.clear();

    tp = {"write", "_M", ";"};
    _right[no++] = tp;
    tp.clear();

    tp = {"read", "ID_", ";"};
    _right[no++] = tp;
    tp.clear();

    tp = {"{", "ID_", "}"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_M", ";"};
    _right[no++] = tp;
    tp.clear();

    tp = {";"};
    _right[no++] = tp;
    tp.clear();

    tp = {"ID_", "=", "_N"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_N"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_P", "_O"};
    _right[no++] = tp;
    tp.clear();

    tp = {"e_"};
    _right[no++] = tp;
    tp.clear();

    tp = {">", "_P"};
    _right[no++] = tp;
    tp.clear();

    tp = {"<", "_P"};
    _right[no++] = tp;
    tp.clear();

    tp = {">=", "_P"};
    _right[no++] = tp;
    tp.clear();

    tp = {"<=", "_P"};
    _right[no++] = tp;
    tp.clear();

    tp = {"==", "_P"};
    _right[no++] = tp;
    tp.clear();

    tp = {"!=", "_P"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_R", "_Q"};
    _right[no++] = tp;
    tp.clear();

    tp = {"+", "_R", "_Q"};
    _right[no++] = tp;
    tp.clear();

    tp = {"-", "_R", "_Q"};
    _right[no++] = tp;
    tp.clear();

    tp = {"e_"};
    _right[no++] = tp;
    tp.clear();

    tp = {"_T", "_S"};
    _right[no++] = tp;
    tp.clear();

    tp = {"*", "_T", "_S"};
    _right[no++] = tp;
    tp.clear();

    tp = {"/", "_T", "_S"};
    _right[no++] = tp;
    tp.clear();

    tp = {"e_"};
    _right[no++] = tp;
    tp.clear();

    tp = {"(", "_M", ")"};
    _right[no++] = tp;
    tp.clear();

    tp = {"ID_"};
    _right[no++] = tp;
    tp.clear();

    tp = {"NUM_"};
    _right[no++] = tp;
    tp.clear();

}

void LLTABLE::init_ll(){
    GO tp;

    tp = mp("_A", "{");
    _Go[tp] = 1;            //代表所对应产生式，在_right数组的下标

    tp = mp("_B", "int");
    _Go[tp] = 2;

    tp = mp("_B", "NUM_");
    _Go[tp] = 3;

    tp = mp("_B", "ID_");
    _Go[tp] = 3;

    tp = mp("_B", "{");
    _Go[tp] = 3;

    tp = mp("_B", "}");
    _Go[tp] = 3;

    tp = mp("_B", "(");
    _Go[tp] = 3;

    tp = mp("_B", "if");
    _Go[tp] = 3;

    tp = mp("_B", "while");
    _Go[tp] = 3;

    tp = mp("_B", "for");
    _Go[tp] = 3;

    tp = mp("_B", "write");
    _Go[tp] = 3;

    tp = mp("_B", "read");
    _Go[tp] = 3;

    tp = mp("_B", ";");
    _Go[tp] = 3;

    tp = mp("_C", "int");
    _Go[tp] = 4;

    tp = mp("_D", "if");
    _Go[tp] = 5;

    tp = mp("_D", "while");
    _Go[tp] = 5;

    tp = mp("_D", "for");
    _Go[tp] = 5;

    tp = mp("_D", "write");
    _Go[tp] = 5;

    tp = mp("_D", "read");
    _Go[tp] = 5;

    tp = mp("_D", "}");
    _Go[tp] = 6;

    tp = mp("_E", "ID");
    _Go[tp] = 13;

    tp = mp("_E", "NUM");
    _Go[tp] = 13;

    tp = mp("_E", "(");
    _Go[tp] = 13;

    tp = mp("_E", ";");
    _Go[tp] = 13;

    tp = mp("_E", "{");
    _Go[tp] = 12;

    tp = mp("_E", "if");
    _Go[tp] = 7;

    tp = mp("_E", "while");
    _Go[tp] = 8;

    tp = mp("_E", "for");
    _Go[tp] = 9;

    tp = mp("_E", "write");
    _Go[tp] = 10;

    tp = mp("_E", "read");
    _Go[tp] = 11;

    //if-stat 特殊处理

    tp = mp("_G", "while");
    _Go[tp] = 16;

    tp = mp("_H", "for");
    _Go[tp] = 17;

    tp = mp("_I", "write");
    _Go[tp] = 18;

    tp = mp("_J", "read");
    _Go[tp] = 19;

    tp = mp("_K", "{");
    _Go[tp] = 20;

    tp = mp("_L", "ID_");
    _Go[tp] = 21;

    tp = mp("_L", "NUM_");
    _Go[tp] = 21;

    tp = mp("_L", "(");
    _Go[tp] = 21;

    tp = mp("_L", ";");
    _Go[tp] = 22;

    //expression的特殊处理

    tp = mp("_N", "ID_");
    _Go[tp] = 25;

    tp = mp("_N", "NUM_");
    _Go[tp] = 25;

    tp = mp("_N", "(");
    _Go[tp] = 25;

    tp = mp("_O", ">");
    _Go[tp] = 27;

    tp = mp("_O", "<");
    _Go[tp] = 28;

    tp = mp("_O", ">=");
    _Go[tp] = 29;

    tp = mp("_O", "<=");
    _Go[tp] = 30;

    tp = mp("_O", "==");
    _Go[tp] = 31;

    tp = mp("_O", "!=");
    _Go[tp] = 32;

    tp = mp("_O", ")");
    _Go[tp] = 26;

    tp = mp("_O", ";");
    _Go[tp] = 26;

    tp = mp("_P", "ID_");
    _Go[tp] = 33;

    tp = mp("_P", "NUM_");
    _Go[tp] = 33;

    tp = mp("_P", "(");
    _Go[tp] = 33;

    tp = mp("_Q", "+");
    _Go[tp] = 34;

    tp = mp("_Q", "-");
    _Go[tp] = 35;

    tp = mp("_Q", ")");
    _Go[tp] = 36;

    tp = mp("_Q", ";");
    _Go[tp] = 36;

    tp = mp("_Q", ">");
    _Go[tp] = 36;

    tp = mp("_Q", "<");
    _Go[tp] = 36;

    tp = mp("_Q", ">=");
    _Go[tp] = 36;

    tp = mp("_Q", "<=");
    _Go[tp] = 36;

    tp = mp("_Q", "==");
    _Go[tp] = 36;

    tp = mp("_Q", "!=");
    _Go[tp] = 36;

    tp = mp("_R", "ID_");
    _Go[tp] = 37;

    tp = mp("_R", "NUM_");
    _Go[tp] = 37;

    tp = mp("_R", "(");
    _Go[tp] = 37;

    tp = mp("_S", "*");
    _Go[tp] = 38;

    tp = mp("_S", "/");
    _Go[tp] = 39;

    tp = mp("_S", ";");
    _Go[tp] = 40;

    tp = mp("_S", ")");
    _Go[tp] = 40;

    tp = mp("_S", "+");
    _Go[tp] = 40;

    tp = mp("_S", "-");
    _Go[tp] = 40;

    tp = mp("_S", ">");
    _Go[tp] = 40;

    tp = mp("_S", "<");
    _Go[tp] = 40;

    tp = mp("_S", ">=");
    _Go[tp] = 40;

    tp = mp("_S", "<=");
    _Go[tp] = 40;

    tp = mp("_S", "==");
    _Go[tp] = 40;

    tp = mp("_S", "!=");
    _Go[tp] = 40;

    tp = mp("_T", "ID_");
    _Go[tp] = 42;

    tp = mp("_T", "NUM_");
    _Go[tp] = 43;

    tp = mp("_T", "(");
    _Go[tp] = 41;

}

