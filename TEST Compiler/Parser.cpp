#include "Lexical_analyzer.h"

int main(){
    freopen("./data/input.txt", "r", stdin);
    //freopen("./data/output.txt", "w", stdout);

    TDFA tdfa;
    tdfa.text_analysis();       //分析文本
    tdfa.disp_result();     //输出结果

    return 0;
}
