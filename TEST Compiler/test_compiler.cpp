/* --- ___main___��������� --- */

#include "Parser.h"
#include "LLParser.h"

int main(){

    //freopen("./data/output.txt", "w", stdout);
    bool flag = true;
    cout << "--->������ʹ�õ��﷨�����������ݹ��½�����'D', LL��1������������'E'��" << endl;
    cout << "\t";
    while(flag){
        string tp;
        cin >> tp;
        if(tp == "D")   {PARSER Parser; freopen("./data/input.txt", "r", stdin); Parser.grammar_analysis(); flag = false;}
        else if(tp == "E")  {LLPARSER Parser; freopen("./data/input.txt", "r", stdin); Parser.grammar_analysis(); flag = false;}
        else{
            cout << "--->�����������������" << endl << "\t";
        }
    }
    return 0;
}
