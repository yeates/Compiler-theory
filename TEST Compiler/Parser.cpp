#include "Lexical_analyzer.h"

int main(){
    freopen("./data/input.txt", "r", stdin);
    //freopen("./data/output.txt", "w", stdout);

    TDFA tdfa;
    tdfa.text_analysis();       //�����ı�
    tdfa.disp_result();     //������

    return 0;
}
