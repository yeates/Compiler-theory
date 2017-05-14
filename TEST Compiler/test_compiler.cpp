/* --- ___main___主程序入口 --- */

#include "Parser.h"
#include "LLParser.h"

int main(){
    freopen("./data/input.txt", "r", stdin);
    //freopen("./data/output.txt", "w", stdout);

    LLPARSER Parser;
    Parser.grammar_analysis();

    return 0;
}
