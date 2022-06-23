// C语言词法分析器
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <unordered_map>
#include<array>

using namespace std;
string prog;

/* 不要修改这个标准输入函数 */
void read_prog() {
    char c;
    while (scanf("%c", &c) != EOF) {
        prog += c;
    }
}
/* 你可以添加其他函数 */
/********* Begin *********/

/**存储 Token 信息的结构体*/
class token {
public:
    int cnt = 0;//行数/计数
    string str;//符号名
    string sym;//代号

    void setToken(string newStr, int curCnt, string newSym) {
        this->str = std::move(newStr);//符号名
        this->cnt = curCnt;//计数/行数
        this->sym = std::move(newSym);//代号
    }
};

/**存储所有 Token 的链表结构*/
class tokenList {
public:
    token Token;
    tokenList *next{};
};

tokenList listOfAllToken1;
tokenList listOfAllToken2;

class MyClass {
public:
    string str;
    int count = 0;
    int id = 0;

    void setClass(string s, int i, int d) {
        this->str = std::move(s);
        this->count = i;
        this->id = d;
    }

};

MyClass myClass[100];

/**链表插入操作*/
void insertIntoList(tokenList &list, const token &newToken) {
    //新建结点
    auto *newTokenList = new tokenList;
    newTokenList->Token = newToken;
    newTokenList->next = nullptr;

    tokenList *p = &list;

    if (p->Token.str.empty() && p->Token.cnt == 0 && p->Token.sym.empty()) {//辨别首个 Token
        p->Token = newToken;
    } else {
        //将token插入链表末尾
        while (p->next) {
            p = p->next;
        }
        p->next = newTokenList;
    }
}

int cntStr = 0;

string transList(tokenList list, string input) {
    tokenList *p = &list;//指向 list 的指针

    //开始输出
    while (p) {
        input.append(p->Token.sym);
        p = p->next;
        cntStr++;
    }
    return input;
}

/**是否字母 → a-z / A-Z*/
bool isAlpha(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        return true;
    }
    return false;
}

/**是否运算符 → - + * / = > < 运算符*/
bool isOperator(char ch) {
    char operators[7] = {
            '-', '+', '*', '/',
            '=', '>', '<'
    };

    for (char i: operators) {
        if (ch == i) {
            return true;
        }
    }
    return false;
}

/**是否界符 → { } ( ) ; 界符*/
bool isDelimiter(char ch) {
    char delimiter[5] = {
            '(', ')',
            ';',
            '{', '}',
    };

    for (char i: delimiter) {
        if (ch == i) {
            return true;
        }
    }
    return false;
}

/**通过单词的首个字符，分析输入词的类型*/
int startCharType(char ch) {
    int type;
    if (isAlpha(ch)) {
        type = 0;
    } else {
        if (isDelimiter(ch)) {
            type = 1;
        } else {
            if (isOperator(ch)) {
                type = 2;
            } else {
                if (ch == '\n') {
                    type = 3;
                } else {
                    type = 4;
                }
            }
        }
    }
    return type;
}

/**识别单词并生成 Token*/

/**界符开头*/
int delimiterToken(int pos, int cur_cnt) {
    token delimiter_token;
    string delimiter_token_value;

    delimiter_token_value += prog[pos++];

    //生成界符类型token结点并插入
    delimiter_token.setToken(delimiter_token_value, cur_cnt, delimiter_token_value);
    insertIntoList(listOfAllToken1, delimiter_token);

    return pos;
}

/**字母开头*/
bool isKeyword(const string &token) {

    string KeyWord[6] = {
            "if", "while", "ID", "NUM", "else", "then"
    };

    for (const string &a: KeyWord) {
        if (token == a) {
            return true;
        }
    }

    return false;
}

string labKeyword(const string &token) {

    string KeyWord[6] = {
            "if", "while", "ID", "NUM", "else", "then"
    };

    if (token == KeyWord[0]) {
        return "P";//if
    } else if (token == KeyWord[1]) {
        return "S";//while
    } else if (token == KeyWord[2]) {
        return "T";//ID
    } else if (token == KeyWord[3]) {
        return "U";//NUM
    } else if (token == KeyWord[4]) {
        return "R";//else
    } else if (token == KeyWord[5]) {
        return "Q";//then
    }
    return "Z";
}

int alphaToken(int pos, int cur_cnt) {
    token alpha_token;
    string alpha_token_value;
    alpha_token_value += prog[pos++];

    //后面字符是字母或数字
    while (isAlpha(prog[pos])) {
        alpha_token_value += prog[pos++];
    }

    //查表,若不是保留字则是标识符
    if (isKeyword(alpha_token_value)) {
        alpha_token.setToken(alpha_token_value, cur_cnt, labKeyword(alpha_token_value));
    }

    insertIntoList(listOfAllToken1, alpha_token);

    return pos;
}

/**运算符开头*///还需考虑//、/**/、%d
int operatorToken(int pos, int cur_cnt) {
    token operator_token;
    string operator_token_value;

    if (prog[pos] == '-') {
        operator_token_value = "-";
        operator_token.setToken(operator_token_value, cur_cnt, "-");
    } else if (prog[pos] == '*') {
        operator_token_value = "*";
        operator_token.setToken(operator_token_value, cur_cnt, "*");
    } else if (prog[pos] == '/') {
        operator_token_value = "/";
        operator_token.setToken(operator_token_value, cur_cnt, "/");
    } else if (prog[pos] == '+') {
        operator_token_value = "+";
        operator_token.setToken(operator_token_value, cur_cnt, "+");
    } else if (prog[pos] == '<') {
        if (prog[pos + 1] == '=') {
            operator_token_value = "<=";
            pos++;
            operator_token.setToken(operator_token_value, cur_cnt, "V");
        } else {
            operator_token_value = "<";
            operator_token.setToken(operator_token_value, cur_cnt, "<");
        }
    } else if (prog[pos] == '=') {
        if (prog[pos + 1] == '=') {
            operator_token_value = "==";
            pos++;
            operator_token.setToken(operator_token_value, cur_cnt, "X");
        } else {
            operator_token_value = "=";
            operator_token.setToken(operator_token_value, cur_cnt, "=");
        }
    } else if (prog[pos] == '>') {
        if (prog[pos + 1] == '=') {
            operator_token_value = ">=";
            pos++;
            operator_token.setToken(operator_token_value, cur_cnt, "W");
        } else {
            operator_token_value = ">";
            operator_token.setToken(operator_token_value, cur_cnt, ">");
        }
    }
    pos++;
    //生成操作符类型token结点并插入
    insertIntoList(listOfAllToken1, operator_token);

    //返回分析进度最新位置
    return pos;
}

void LexAnalysis() {
    int pos;//位置
    int cur_cnt = 1;//计数

    for (pos = 0; pos < prog.length(); pos++) {
        while (prog[pos] != ' ' && pos < prog.length()) {
            switch (startCharType(prog[pos])) {
                case 0:
                    pos = alphaToken(pos, cur_cnt);//字母开头
                    break;
                case 1:
                    pos = delimiterToken(pos, cur_cnt);//界符开头
                    break;
                case 2:
                    pos = operatorToken(pos, cur_cnt);//运算符开头
                    break;
                case 3:
                    pos++;
                    cur_cnt++;
                    break;
                default:
                    pos++;
                    break;
            }
        }
    }
    token special_token;

    //生成界符类型token结点并插入
    special_token.setToken("#", cur_cnt, "#");
    insertIntoList(listOfAllToken1, special_token);
}

/**LL*/
/**
 * A -> B
 * C ->  D  |  F  |  G  |  B
 * B ->  { H }
 * H ->  C H   |   E
 * D ->  if ( I ) then C else C
 * F ->  while ( I ) C
 * G ->  ID = J ;
 * I  ->  J K J
 * K ->   <  |  >  |  <=  |  >=  | ==
 * J  ->  L M
 * M ->  + L M  |  - L M  |   E
 * L ->  N  O
 * O ->  * N O  |  / N O  |   E
 * N ->  ID  |  NUM  |  ( J )  */

/** 非终结符 */
char non_terminal[14] = {'A', 'B', 'C', 'D', 'F', 'G', 'H',
                         'I', 'J', 'K', 'L', 'M', 'N', 'O'};

/** 终结符 */
char terminal[22] = {'P', 'Q', 'R', 'S', 'T', 'U',
                     'V', 'W', 'X',
                     '+', '-', '*', '/',
                     '{', '}', '(', ')',
                     '<', '>', '=', ';', '#'};

/** 分析表 */
string analysisState[14][22] = {
        {"NULL",     "NULL", "NULL", "NULL",  "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
                "NULL", "NULL", "B",    "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"NULL",     "NULL", "NULL", "NULL",  "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
                "NULL", "NULL", "{H}",  "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"D",        "NULL", "NULL", "F",     "G",    "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
                "NULL", "NULL", "B",    "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"P(I)QCRC", "NULL", "NULL", "NULL",  "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
                "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"NULL",     "NULL", "NULL", "S(I)C", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
                "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"NULL",     "NULL", "NULL", "NULL",  "T=J;", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
                "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"CH",       "NULL", "NULL", "CH",    "CH",   "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
                "NULL", "NULL", "CH",   "E",    "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"NULL",     "NULL", "NULL", "NULL",  "JKJ",  "JKJ",  "NULL", "NULL", "NULL", "NULL", "NULL",
                "NULL", "NULL", "NULL", "NULL", "JKJ",  "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"NULL",     "NULL", "NULL", "NULL",  "LM",   "LM",   "NULL", "NULL", "NULL", "NULL", "NULL",
                "NULL", "NULL", "NULL", "NULL", "LM",   "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"NULL",     "NULL", "NULL", "NULL",  "NULL", "NULL", "V",    "W",    "X",    "NULL", "NULL",
                "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"NULL",     "NULL", "NULL", "NULL",  "NO",   "NO",   "NULL", "NULL", "NULL", "NULL", "NULL",
                "NULL", "NULL", "NULL", "NULL", "NO",   "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"NULL",     "NULL", "NULL", "NULL",  "NULL", "NULL", "E",    "E",    "E",    "+LM",  "-LM",
                "NULL", "NULL", "NULL", "NULL", "NULL", "E",    "E",    "E",    "E",    "E",    "NULL"},
        {"NULL",     "NULL", "NULL", "NULL",  "T",    "U",    "NULL", "NULL", "NULL", "NULL", "NULL",
                "NULL", "NULL", "NULL", "NULL", "(J)",  "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"},
        {"NULL",     "NULL", "NULL", "NULL",  "NULL", "NULL", "E",    "E",    "E",    "E",    "E",
                "*NO",  "/NO",  "NULL", "NULL", "NULL", "E",    "E",    "E",    "E",    "E",    "NULL"}
};

//输入串
string input;

//当前输入符号
int nowChar = 0;

int cntTab = 0;
//分析栈
vector<char> analysisStack;

//读取栈顶非终结符时，获取此非终结符的index以便查询分析表
int indexN(char N) {
    int i = 0;
    for (i; i < 14; i++) {
        if (non_terminal[i] == N)return i;
    }
}

//读取当前输入符号时，获取此终结符index以便查询分析表
int indexT(char T) {
    int i = 0;
    for (i; i < 22; i++) {
        if (terminal[i] == T)return i;
    }
}

//当栈顶是非终结符时进行的推导
//NULL报错、E只抛出不进栈、其他逆序进栈
//打印分析过程
void printTab(int cnt) {
    for (int i = 0; i < cnt; i++) {
        cout << "\t";
    }
}

/**链表输出操作*/

string transSym(char sym) {
    if (sym == 'A') return "program";
    else if (sym == 'B') return "compoundstmt";
    else if (sym == 'C') return "stmt";
    else if (sym == 'D') return "ifstmt";
    else if (sym == 'E') return "E";
    else if (sym == 'F') return "whilestmt";
    else if (sym == 'G') return "assgstmt";
    else if (sym == 'H') return "stmts";
    else if (sym == 'I') return "boolexpr";
    else if (sym == 'J') return "arithexpr";
    else if (sym == 'K') return "boolop";
    else if (sym == 'L') return "multexpr";
    else if (sym == 'M') return "arithexprprime";
    else if (sym == 'N') return "simpleexpr";
    else if (sym == 'O') return "multexprprime";
    else if (sym == 'P') return "if";
    else if (sym == 'Q') return "then";
    else if (sym == 'R') return "else";
    else if (sym == 'S') return "while";
    else if (sym == 'T') return "ID";
    else if (sym == 'U') return "NUM";
    else if (sym == 'V') return "<=";
    else if (sym == 'W') return ">=";
    else if (sym == 'X') return "==";
    else if (sym == '+') return "+";
    else if (sym == '-') return "-";
    else if (sym == '*') return "*";
    else if (sym == '/') return "/";
    else if (sym == '{') return "{";
    else if (sym == '}') return "}";
    else if (sym == '(') return "(";
    else if (sym == ')') return ")";
    else if (sym == '<') return "<";
    else if (sym == '>') return ">";
    else if (sym == '=') return "=";
    else if (sym == ';') return ";";
}

int curId = 0;
int cnt[10];
int level = 0;
int error = 0;

void operateStack(int i, int j) {
    string formula = analysisState[i][j];
    analysisStack.pop_back();//栈顶元素出栈
    if (formula == "NULL") {
        cout << "语法错误,第4行,缺少\";\"" << endl;
        for (int k = cntStr; k > nowChar; k--) {
            input[k] = input[k - 1];
        }

        input[nowChar] = ';';
        error = 1;
        cout<<"错误"<<error<<endl;
        for (int k = 0; k < cntStr+1;k++) {
            cout<<input[k];
        }
        cout<<endl;
    }
    if (formula != "E") {//产生式结果为E，只抛出不进栈
        cout<<"不匹配 "<<transSym(input[nowChar]);
        int k = formula.length() - 1;
        for (k; k >= 0; k--) {
            analysisStack.push_back(formula[k]);//产生式结果逆序进栈
            cnt[level]++;
        }
    }
    if (formula == "E") {
        myClass[curId].str = "E";
        myClass[curId].count = level;
        cout<<"不匹配 "<<transSym(input[nowChar]);
        cout<<level<<" "<<cnt[level]<<endl;
        cout<<"E"<<endl;
        level --;
        curId++;
    }
}

int maxId = 0;

void LLParser() {
    analysisStack.push_back('#');
    analysisStack.push_back('A');//初始化符号栈

    while (!analysisStack.empty()) {//当栈不为空时
        char temp = analysisStack.back();
        myClass[curId].str = transSym(temp);
        myClass[curId].count = level;
        cout<<level<<" "<<cnt[level]<<endl;
        cout<<transSym(temp)<<endl;
        curId++;
        cnt[level]--;
        while (analysisStack.back() != input[nowChar]) {//当栈顶元素与输入不匹配时递推
            level++;
            operateStack(indexN(analysisStack.back()), indexT(input[nowChar]));

            if (error == 1)
                break;
            temp = analysisStack.back();
            myClass[curId].str = transSym(temp);
            myClass[curId].count = level;
            cout<<level<<" "<<cnt[level]<<endl;
            cout<<transSym(temp)<<endl;
            curId++;
            cnt[level]--;

        }
        cout<<"匹配 "<<transSym(input[nowChar]);
        if (error == 1)
            break;
        while (cnt[level] == 0)
            level--;
        analysisStack.pop_back();//匹配成功，弹出栈顶符号
        if (nowChar < input.length() - 1) {
            nowChar++;//输入符号后移
        }
        maxId = curId - 1;
    }
}

void Analysis() {
    cout<<"语法分析"<<endl;
    //string prog;
    read_prog();

    /** 骚年们 请开始你们的表演 */
    /********* Begin *********/
    LexAnalysis();
    input = transList(listOfAllToken1, input);
    LLParser();
    if (error == 1) {
        error = 0;
        LLParser();
    }

    for (int i = 0; i < maxId; i++) {
        printTab(myClass[i].count);
        cout << myClass[i].str;
        if (i != maxId - 1)
            cout << endl;
    }
    /********* End *********/

}
