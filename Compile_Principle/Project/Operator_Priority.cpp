// 输入文件的行数为non-terminal的个数

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

# define MAX 50

// 变量声明
char grammar[20][MAX];//grammar:输入文法
char relation[20][20]; //relationship
vector<string> terminal;
int n; // the number of non-terminals
string input_file[2] = {"in.txt", "in1.txt"};
string output_file[2] = {"out.txt", "out1.txt"};

struct non_terminal{
    char name=' '; //自身的名字，如E
    vector<string> firstVT; //非终止符的firstVT集合
    vector<string> lastVT; //非终止符的lastVT集合
};

vector<non_terminal> Nonterminals;

/* 函数：print_dline
 * 输入：需要打印到的文件指针
 * 输出：---------
 */
void print_dline(FILE * outFile){
    fprintf(outFile, " --------- ");
    for (int i = 0; i < terminal.size(); i++)
        fprintf(outFile, " ---------");
    fprintf(outFile, "\n");
}


/* 函数：find_matchedNT
 * 输入：非终结符E
 * 输出：E在Nonterminals中的下标
 */
int find_matchedNT(char c){
    int matched = -1;
    for (int i = 0; i < Nonterminals.size(); ++i) {
        if (c == Nonterminals[i].name){
            matched = i;
            break;
        }
    }
    if (matched == -1)
        printf("error happened, non-terminal %c can not match\n", c);
    return matched;
}


/* 函数：find_matchedT
 * 输入：终结符s
 * 输出：s在terminal中的下标
 */
int find_matchedT(const string& s){
    int matched = -1;
    for (int i = 0; i < terminal.size(); ++i) {
        if (s == terminal[i]){
            matched = i;
            break;
        }
    }
    if (matched == -1)
        printf("error happened, terminal %s can not match\n", s.c_str());
    return matched;
}


/* 函数：constructVT
 * 输入：grammar
 * 输出：各个非终止符的firstVT和lastVT
 * 功能：根据读入的grammar得到各个非终止符的firstVT和lastVT
 */
void constructVT(char text[][MAX])   // 自下向上分析，得到firstVT和lastVT
{
    // text的格式是E->E*E
    char *line;
    string nowS;
    int len, matchNT, matchT;
    non_terminal lastOne;

    for (int i = n - 1; i >= 0; --i) {
        line = text[i];
        //cout << line;
        len = strlen(line);
        if (find_matchedNT(line[0]) == -1){
            Nonterminals.emplace_back(); //为当前处理的非终结符在队列中新建一个，之后都对Nonterminals.end()操作
            Nonterminals.back().name = line[0];
        }
        //在给定的文法中不会出现两个不同行开始的非终止符不同的情况   

        //开始构造firstVT
        //std::cout << "constructing firstVT" <<std::endl;
        
        for (int j = 5; j < len; ++j) {
            //cout << "j: " <<j << " " << nowS << endl;
            if (line[j] == '|') j += 2; //跳过|和后面连着的一个空格

            //没遇到空格，不处理
            if (line[j] != ' '){
                nowS += line[j];
                continue;
            }
            
            //遇到空格，处理，如果是非终结符Q，把firstVT（Q）加入first(V),并继续寻找终结符
            if (nowS.length() == 1 && nowS[0] > 'A' && nowS[0] < 'Z'){ //如果遇到的第一个字符是非终止符
                matchNT = find_matchedNT(nowS[0]);
                for (const auto& first : Nonterminals[matchNT].firstVT)
                    if (count(Nonterminals.back().firstVT.begin(), Nonterminals.back().firstVT.end(), first) == 0) //判断该终止符是否已经出现在firstVT中，若存在，则不进行处理，若不存在，则将之加入firstVT
                        Nonterminals.back().firstVT.push_back(first);
            }
            
            //否则是终结符，直接将其加入firstVT(Q)
            else{
                //cout << nowS;
                matchT = find_matchedT(nowS);
                if (matchT == -1){
                    terminal.push_back(nowS); //识别到一个新的终止符
                }

                //cout << nowS;
                int flag = 1;
                for (const auto& first : Nonterminals.back().firstVT){
                    if(nowS == first)
                        flag = 0;
                }
                if(flag)
                    Nonterminals.back().firstVT.push_back(nowS);

                while (j < len && line[j] != '|' ) //除非遇到下一个表达式，否则忽略后面的内容
                    ++j;
                if (line[j] == '|'){
                    j++; //跳过'|'后面的空格
                }
            }
            nowS = ""; //初始化nowS，重新开始循环
        }

        nowS = "";
        //lastVT
        //std::cout << "constructing lastVT" <<std::endl;
        for (int j = len-3; j >= 4; j--) {
            //cout << "j: " << j << ' ' << nowS <<endl;
            if (line[j] == '|') j -= 2; //跳过|和后面连着的一个空格

            //没遇到空格，加入nowS，表示当前需要处理的string
            if (line[j] != ' '){
                nowS.insert(0, 1, line[j]);
                continue;
            }

            //遇到空格，处理，如果是非终结符Q，把lastVT（Q）加入last(V),并继续寻找终结符
            if (nowS.length() == 1 && nowS[0] > 'A' && nowS[0] < 'Z'){
                matchNT = find_matchedNT(nowS[0]);
                for (const auto & last : Nonterminals[matchNT].lastVT){
                    if (count(Nonterminals.back().lastVT.begin(), Nonterminals.back().lastVT.end(), last) == 0)
                        Nonterminals.back().lastVT.push_back(last);
                }
            }
            //否则是终结符，直接将其加入lastVT(Q)
            else{
                matchT = find_matchedT(nowS);
                if (matchT == -1){
                    terminal.push_back(nowS);
                }

                //如果终结符不在lastVT中，那么加入该终结符
                int flag = 1;
                for (const auto& last : Nonterminals.back().lastVT){
                    if(nowS == last)
                        flag = 0;
                }
                if(flag)
                    Nonterminals.back().lastVT.push_back(nowS);

                while (j >= 4 && line[j] != '|' ) //除非遇到下一个表达式，否则忽略后面的内容
                    --j;
                if (line[j] == '|'){
                    j--; //跳过'|'后面的空格
                }
            }
            nowS = ""; //初始化nowS，重新开始循环
        }
    }
}

/* 函数：constructOp
 * 输入：grammar
 * 输出：无
 * 功能：在已知所有终结符的first和last的基础上，构造relation数组
 */
int constructOp (char text[][MAX])
{
    int nowB, lastNT_B, lastT_B, lastT, lastNT; //nowB表示当前字符串的开始,lastNT_B表示上一个非终结符的开始，lastT_B表示上一个终结符的开始，lastT表示上一个终结符，lastNT表示上一个非终结符
    string nowS; //nowS为最后一个读到的字符串
    int matchT, matchNT; // NT表示当前表达式对应non_terminal中的哪一个非终结符
    int res = 0; //返回值，0-正确，-1-出错

    for (int i = 0; i < n; ++i){
        //cout << "i:" << i << std::endl;
        nowB = -1;
        lastNT_B = lastT_B = lastNT = lastT = -1;
        nowS = "";
        for (int j = 5; j < strlen(text[i]); ++j) {
            //std::cout << "j:" << j << " "  << nowS << std::endl;
            //遇到|，开始新表达式
            if (text[i][j] == '|'){
                nowB = -1;
                nowS = "";
                lastNT_B = lastT_B = lastNT = lastT = -1;
                continue;
            }

            //没遇到空格，不处理
            if (text[i][j] != ' '){
                nowS += text[i][j];
                nowB = (nowB == -1)? j : nowB;
                continue;
            }

            //遇到空格，开始处理
            //非终止符Q，只需处理aQ情况，a < firstVT(Q)
            if (nowS.length() == 1 && nowS[0] > 'A' && nowS[0] < 'Z'){
                matchNT = find_matchedNT(nowS[0]);
                if (lastNT_B < lastT_B && lastT_B > 0){
                    //std::cout << "<!!!!!" << lastNT << endl;
                    for (const auto & first : Nonterminals[matchNT].firstVT){
                        matchT = find_matchedT(first);
                        if (relation[lastT][matchT] != '\0' && relation[lastT][matchT] != '<'){
                            relation[lastT][matchT] = '?';
                            res = -1;
                        }
                        else
                            relation[lastT][matchT] = '<';
                    }
                }
                lastNT_B = nowB;
                lastNT = matchNT;
            }
            //终止符，需要考虑ba，bQa, Qa
            else{
                //cout << lastT_B << " " <<lastNT_B <<endl;
                matchT = find_matchedT(nowS);
                if (lastNT_B < lastT_B) {   //ba, b=a    
                    relation[lastT][matchT] = '=';
                }
                else if (lastT_B < lastNT_B){ //Qa，加入lastVT(Q)>a
                    int matchT_Q;
                    for (const auto& last : Nonterminals[lastNT].lastVT){
                        matchT_Q = find_matchedT(last);
                        if (relation[matchT_Q][matchT] != '\0' && relation[matchT_Q][matchT] != '>'){
                            relation[matchT_Q][matchT] = '?';
                            res = -1;
                        }
                        else
                            relation[matchT_Q][matchT] = '>';
                    }
                    if (lastT_B > -1){ //bQa, b=a
                        //std::cout << "=!!!!!" << endl;
                        if (relation[lastT][matchT] != '\0' && relation[lastT][matchT]!='='){
                            relation[lastT][matchT] = '?';
                            res = -1;
                        }
                        else
                            relation[lastT][matchT] = '=';
                    }
                }
                lastT_B = nowB;
                lastT = matchT;
            }
            //cout << lastT_B << " " <<lastNT_B <<endl;
            nowB = -1;
            nowS = "";
        }
    }
    return res;
}


/* 函数：Output
 * 输入：int res, 表明该文法是否是二义性文法
 * 输出：算符优先分析表到out.txt
 * 功能：根据relation输出算符优先分析表
 */
void Output(int res, string file){
    FILE *outFile;
    outFile = fopen(file.c_str(), "w");
    
    if (res != 0){
        fprintf(outFile, "ambiguous grammar\n");
    }
    
    print_dline(outFile);
    fprintf(outFile, "|         |");
    for (auto & t : terminal)
        fprintf(outFile, "    %-5s|", t.c_str());

    fprintf(outFile, "\n");
    print_dline(outFile);
    for (int i = 0; i < terminal.size(); ++i){
        fprintf(outFile, "|    %-5s|", terminal[i].c_str());
        for (int j = 0; j < terminal.size(); ++j)
            fprintf(outFile, "    %c    |", relation[i][j]);
        fprintf(outFile, "\n");
        print_dline(outFile);
    }
}


/* 函数：Input
 * 输入：文法
 * 输出：grammar
 * 功能：将输入文法读入到全局变量grammar中
 */
void Input(string fileName){
    FILE *fp;
    fp = fopen(fileName.c_str(), "r");

    //将输入文法读入到全局变量grammar中
    n=1;
    strcpy(grammar[0], "A -> $ E $ \n");

    while (true){
        fgets(grammar[n], MAX, fp);
        n++;
        if (feof(fp))
            break;
    }

    grammar[0][7] = grammar[1][0]; //将上式中的E改为实际的非终止符
    grammar[n-1][strlen(grammar[n-1])] = '\n'; //保持每一行结尾都是\n的统一性
    
    //输出grammar，查看读入是否正确
    puts("grammar:");
    for (auto &line:grammar)
        printf("%s", line);
    printf("\nn=%d\n", n);
    
}

/* 函数：Print_VT
 * 输入：无
 * 输出：各个非终止符的firstVT和lastVT
 * 功能：输出每个非终止符的fistVT和lastVT
 */
void Print_VT(){

    for (auto & Nonterminal : Nonterminals){
        cout << Nonterminal.name;
        cout << ':' <<endl;
        cout << "FirstVT: ";
        for (auto & first:Nonterminal.firstVT)
            cout << first.c_str() << ' ';
        cout << endl;

        cout << "LastVT: ";
        for (auto & first:Nonterminal.lastVT)
            cout << first.c_str() << ' ';
        cout << endl;
    }   
}



int main(){
    for (int i=0; i<2; ++i){
        
        Input(input_file[i]);

        constructVT(grammar);

        int res = constructOp(grammar);

        Print_VT();

        Output(res, output_file[i]);

        //clear the array and vectors
        for (int j = 0; j< 20; ++j){
            for (auto & c :grammar[j])
                c = '\0';
            for (auto & c : relation[j])
                c = '\0';
        }
        Nonterminals.clear();
        terminal.clear();


    }
   
    
    return 0;
}