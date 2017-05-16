/* --- ___main___主程序入口 --- */

#include "Parser.h"
#include "LLParser.h"

int main(){

    //freopen("./data/output.txt", "w", stdout);
    bool flag = true;
    cout << "--->请输入使用的语法分析器：（递归下降输入'D', LL（1）表驱动输入'E'）" << endl;
    cout << "\t";
    while(flag){
        string tp;
        cin >> tp;
        if(tp == "D")   {PARSER Parser; freopen("./data/input.txt", "r", stdin); Parser.grammar_analysis(); flag = false;}
        else if(tp == "E")  {LLPARSER Parser; freopen("./data/input.txt", "r", stdin); Parser.grammar_analysis(); flag = false;}
        else{
            cout << "--->输入错误，请重新输入" << endl << "\t";
        }
    }
    return 0;
}
