#include "LLParser.h"


LLPARSER::LLPARSER(){
    init_terminator();  //��ʼ���ս����
}

//��ʼ���ս����
void LLPARSER::init_terminator(){

    _Vt["*"] = _Vt["/"] = _Vt["{"] = _Vt["}"] = _Vt["("] = _Vt[")"] = _Vt["!="] \
    = _Vt["=="] = _Vt["+"] = _Vt["-"] = _Vt["<="] = _Vt[">="] = _Vt["<"] = _Vt[">"] \
    = _Vt["if"] = _Vt["while"] = _Vt["for"] = _Vt["write"] = _Vt["read"] = _Vt["int"] \
    = _Vt[";"] = 1;
}

//LL��1�����������س���
void LLPARSER::grammar_analysis(){
    LA.text_analysis(); //�ʷ�����

    cout << "------------�﷨����-----------" << endl;
    stack<string>ss;    //����ջsymbol_stack
    ss.push("#");
    ss.push("_A");
    int no = 0, len = LA.m_str.size();
    string ch = LA.m_str[no++];
    bool flag = true;
    bool success_flag = true;
    while(flag){
        string x = ss.top();

        if(x == "e_"){
            ss.pop();
            continue;
        }

        if(LA.m_str_attribute[no-1] == 1)   ch = "ID_";
        else if(LA.m_str_attribute[no-1] == 3)   ch = "NUM_";

        if(x == if_deal_symbol && ch == "else"){       //if�����⴦��
            ss.push("_E");
            ss.push("else");
            x = ss.top();
        }
        else if(x == if_deal_symbol && ch != "else"){
            ss.pop();
            continue;
        }

        if(_Vt[x] == 1 || (x != "#" && x.at(0) != '_') ){
            if(ch == x || (x == "ID_" && LA.m_str_attribute[no-1] == 1) || (x == "NUM_" && LA.m_str_attribute[no-1] == 3)){
                ss.pop();
                if(no < len)    ch = LA.m_str[no++];
                else if(no == len)  ch = "#";
            }
            else{
                if(x == ";" || x == ")" || x == "}"){
                    ss.pop();
                    success_flag = false;
                    cout << "�������ͣ�1�������к�Ϊ��" << LA.m_str_lineNum[no-1] <<  "�ĵ���\""<< LA.m_str[no-1] << "\"ǰ�棬ȱʧ����\"" << x << "\"" << endl;
                }
                else{
                    success_flag = false;
                    cout << "�������ͣ�0�������к�Ϊ��" << LA.m_str_lineNum[no-1] <<  "�ϣ����ڴ������\"" << LA.m_str[no-1] << "\"" << endl;
                    ch = LA.m_str[no++];
                }
            }
        }
        else if(x == "#"){
            if(success_flag)    cout << "���棺�����ɹ������﷨����" << endl;
            else cout << "���棺��������﷨���⣬���飡" << endl;
            flag = false;
        }
        else if(ll_1_table._Go[make_pair(x, ch)] != 0){
            ss.pop();
            int rno = ll_1_table._Go[make_pair(x, ch)]; //����ʽ�Ҳ�λ��_right������±�

            //if�����⴦�����һ����־
            if(rno == 14){
                ss.push(if_deal_symbol);
            }
            //��������
            int rlen = ll_1_table._right[rno].size();
            for(int i = rlen-1; i >= 0; i--){
                ss.push(ll_1_table._right[rno][i]);     //����push����ʽ���Ҳ�
            }

            //expression�����⴦����ǰ��һλ
            if(rno == 24){
                if(ch == "ID_" && LA.m_str[no] == "="){
                    ss.push("=");
                    ss.push("ID_");
                }
            }
        }
        else{
            success_flag = false;
            cout << "�������ͣ�δ֪�������к�Ϊ��" << LA.m_str_lineNum[no-1] <<  "�ϣ����ڴ������\"" << LA.m_str[no-1] << "\"" << endl;
//            ch = LA.m_str[no++];
//            if(ll_1_table._Go[make_pair(x, ";")] || ll_1_table._Go[make_pair(x, ")")] || ll_1_table._Go[make_pair(x, "}")]){
//                ss.pop();
//                cout << "�������ͣ�1�������к�Ϊ��" << LA.m_str_lineNum[no-1] <<  "�ĵ���\""<< LA.m_str[no-1] << "\"ǰ�棬ȱʧ����\"" << x << "\"" << endl;
//            }
//            else{
//                ss.push(x);
//                cout << "�������ͣ�0�������к�Ϊ��" << LA.m_str_lineNum[no-1] <<  "�ϣ����ڴ������\"" << LA.m_str[no-1] << "\"" << endl;
//                ch = LA.m_str[no++];
//            }
            try{
                if(no >= len)   throw runtime_error("��ʾ�����������±�Խ�磬������ĳ���");
                ch = LA.m_str[no++];
            }
            catch(runtime_error err_str){
                success_flag = false;
                cout << err_str.what() << endl;
            }
            ss.pop();
        }
    }
    cout << "------------��������-----------" << endl << endl;
}


