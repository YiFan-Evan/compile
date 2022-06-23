// C语言词法分析器
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <fcntl.h>
#include <bits/stdc++.h>
#define X 3
using namespace std;

/* 不要修改这个标准输入函数 */
void read_prog(string& prog)
{
    char c;
    while(scanf("%c",&c)!=EOF){
        prog += c;
    }
}

/* 你可以添加其他函数 */
class terminal {
public:
    int id;
    int value;
    double var[X];

    terminal() {
        id = 0;
        value = 0;
    }

    terminal(int id, int value) {
        this->id = id;
        this->value = value;
    }

    terminal(int id) {
        this->id = id;
        this->value;
    }

    void set(vector<double> arr) {
        this->var[0] = arr[0];
        this->var[1] = arr[1];
        this->var[2] = arr[2];
    }
};

terminal left_brace = terminal(151);
terminal right_brace = terminal(152);
terminal left_parenthesis = terminal(153);
terminal right_parenthesis = terminal(154);
terminal if_keyword = terminal(155);
terminal then_keyword = terminal(156);
terminal else_keyword = terminal(157);
terminal while_keyword = terminal(158);
terminal id_type = terminal(159);
terminal equal_sign = terminal(160);
terminal greater_than = terminal(161);
terminal less_than = terminal(162);
terminal greater_equal_than = terminal(163);
terminal less_equal_than = terminal(164);
terminal equal_equal_than = terminal(165);
terminal plus_sign = terminal(166);
terminal minus_sign = terminal(167);
terminal multiply_sign = terminal(168);
terminal divide_sign = terminal(169);
terminal number_type = terminal(170);
terminal semicolon = terminal(171);


terminal start = terminal(200);
terminal A = terminal(201);
terminal B = terminal(202);
terminal C = terminal(203);
terminal D = terminal(204);
terminal E = terminal(205);
terminal F = terminal(206);
terminal G = terminal(207);
terminal H = terminal(208);
terminal I = terminal(209);
terminal J = terminal(210);
terminal K = terminal(211);
terminal L = terminal(212);
terminal M = terminal(213);
terminal N = terminal(214);

terminal epsilon = terminal(301);
terminal end_of_file = terminal(401);
terminal acc = terminal(-1);

int LR_table[500][500] = {0};
int s = 1000;
int r = 2000;
vector<terminal> reduction[50];
terminal deduction[50] = {0};

string print_symbol(int symbol) {
    switch (symbol) {
        case 151:
            return "{";
        case 152:
            return "}";
        case 153:
            return "(";
        case 154:
            return ")";
        case 155:
            return "if";
        case 156:
            return "then";
        case 157:
            return "else";
        case 158:
            return "while";
        case 159:
            return "ID";
        case 160:
            return "=";
        case 161:
            return ">";
        case 162:
            return "<";
        case 163:
            return ">=";
        case 164:
            return "<=";
        case 165:
            return "==";
        case 166:
            return "+";
        case 167:
            return "-";
        case 168:
            return "*";
        case 169:
            return "/";
        case 170:
            return "NUM";
        case 171:
            return ";";
        case 201:
            return "program";
        case 202:
            return "stmt";
        case 203:
            return "compoundstmt";
        case 204:
            return "stmts";
        case 205:
            return "ifstmt";
        case 206:
            return "whilestmt";
        case 207:
            return "assgstmt";
        case 208:
            return "boolexpr";
        case 209:
            return "boolop";
        case 210:
            return "arithexpr";
        case 211:
            return "arithexprprime";
        case 212:
            return "multexpr";
        case 213:
            return "multexprprime";
        case 214:
            return "simpleexpr";
        case 301:
            return "E";
        case 401:
            return "=>";
    }
    return "";
}

string get_split_value(string str, int &index) {
    string result = "";
    bool flag = false;
    while (true) {
        if (index >= str.size()) {
            break;
        }
        if ((str[index] == ' ' || str[index] == '\t' || str[index] == '\n' || str[index] == '\r') && !flag) {
            index++;
            continue;
        } else if (str[index] == ' ' || str[index] == '\t' || str[index] == '\n' || str[index] == '\r') {
            break;
        } else {
            flag = true;
            result += str[index];
            index++;
        }
    }
    return result;
}

string print_depth(int depth) {
    string result = "";
    for (int i = 0; i < depth; ++i) {
        result += "   ";
    }
    return result;
}

terminal cast_to_symbol(string token) {
    if (token == "{") {
        return left_brace;
    } else if (token == "}") {
        return right_brace;
    } else if (token == "(") {
        return left_parenthesis;
    } else if (token == ")") {
        return right_parenthesis;
    } else if (token == "if") {
        return if_keyword;
    } else if (token == "then") {
        return then_keyword;
    } else if (token == "else") {
        return else_keyword;
    } else if (token == "while") {
        return while_keyword;
    } else if (token == "ID") {
        return id_type;
    } else if (token == "=") {
        return equal_sign;
    } else if (token == ">") {
        return greater_than;
    } else if (token == "<") {
        return less_than;
    } else if (token == ">=") {
        return greater_equal_than;
    } else if (token == "<=") {
        return less_equal_than;
    } else if (token == "==") {
        return equal_equal_than;
    } else if (token == "+") {
        return plus_sign;
    } else if (token == "-") {
        return minus_sign;
    } else if (token == "*") {
        return multiply_sign;
    } else if (token == "/") {
        return divide_sign;
    } else if (token == "NUM") {
        return number_type;
    } else if (token == ";") {
        return semicolon;
    } else if (token == "a") {
        return terminal(id_type.id, 1);
    } else if (token == "b") {
        return terminal(id_type.id, 2);
    } else if (token == "c") {
        return terminal(id_type.id, 3);
    } else {
        if (atoi(token.c_str()) != 0 || token == "0") {
            return terminal(number_type.id, atoi(token.c_str()));
        }
        return -1;
    }
    return 0;
}

terminal cast_to_symbol2(string token) {
    if (token == "$") {
        return end_of_file;
    } else if (token == "A'") {
        return start;
    } else if (token == "A") {
        return A;
    } else if (token == "B") {
        return B;
    } else if (token == "C") {
        return C;
    } else if (token == "D") {
        return D;
    } else if (token == "E") {
        return E;
    } else if (token == "F") {
        return F;
    } else if (token == "G") {
        return G;
    } else if (token == "H") {
        return H;
    } else if (token == "I") {
        return I;
    } else if (token == "J") {
        return J;
    } else if (token == "K") {
        return K;
    } else if (token == "L") {
        return L;
    } else if (token == "M") {
        return M;
    } else if (token == "N") {
        return N;
    } else if (token == "$") {
        return end_of_file;
    } else {
        return -1;
    }
    return 0;
}

string split(const string &str, int &index) {
    int begin = index;
    if (index >= str.size()) {
        return nullptr;
    }
    for (index = begin; index < str.size(); ++index) {
        if (str[index] == ',') {
            break;
        }
    }
    ++index;
    return str.substr(begin, index - begin - 1);
}

map<string, int> var_map;

void Analysis() {
    string prog;
    read_prog(prog);
    /* 骚年们 请开始你们的表演 */
    /********* Begin *********/

    int pos = prog.find("{");
    string assign_prog = prog.substr(0, prog.find("{"));
    prog = prog.substr(pos, prog.size());
    reduction[0] = {A};
    reduction[1] = {C};
    reduction[2] = {E};
    reduction[3] = {F};
    reduction[4] = {G};
    reduction[5] = {C};
    reduction[6] = {left_brace, D, right_brace};
    reduction[7] = {B, D};
    reduction[8] = {epsilon};
    reduction[9] = {if_keyword, left_parenthesis, H, right_parenthesis, then_keyword, B, else_keyword, B};
    reduction[10] = {while_keyword, left_parenthesis, H, right_parenthesis, B};
    reduction[11] = {id_type, equal_sign, J, semicolon};
    reduction[12] = {J, I, J};
    reduction[13] = {less_than};
    reduction[14] = {greater_than};
    reduction[15] = {less_equal_than};
    reduction[16] = {greater_equal_than};
    reduction[17] = {equal_equal_than};
    reduction[18] = {L, K};
    reduction[19] = {plus_sign, L, K};
    reduction[20] = {minus_sign, L, K};
    reduction[21] = {epsilon};
    reduction[22] = {N, M};
    reduction[23] = {multiply_sign, N, M};
    reduction[24] = {divide_sign, N, M};
    reduction[25] = {epsilon};
    reduction[26] = {id_type};
    reduction[27] = {number_type};
    reduction[28] = {left_parenthesis, J, right_parenthesis};

    deduction[0] = start;
    deduction[1] = A;
    deduction[2] = B;
    deduction[3] = B;
    deduction[4] = B;
    deduction[5] = B;
    deduction[6] = C;
    deduction[7] = D;
    deduction[8] = D;
    deduction[9] = E;
    deduction[10] = F;
    deduction[11] = G;
    deduction[12] = H;
    deduction[13] = I;
    deduction[14] = I;
    deduction[15] = I;
    deduction[16] = I;
    deduction[17] = I;
    deduction[18] = J;
    deduction[19] = K;
    deduction[20] = K;
    deduction[21] = K;
    deduction[22] = L;
    deduction[23] = M;
    deduction[24] = M;
    deduction[25] = M;
    deduction[26] = N;
    deduction[27] = N;
    deduction[28] = N;

    stringstream parser(
            "table,{,},if,(,),then,else,while,ID,=,;,<,>,<=,>=,==,+,-,*,/,NUM,$,A',A,B,C,D,E,F,G,H,I,J,K,L,M,N\n"
            "0,s3,,,,,,,,,,,,,,,,,,,,,,,1,,2,,,,,,,,,,,\n"
            "1,,,,,,,,,,,,,,,,,,,,,,acc,,,,,,,,,,,,,,,\n"
            "2,,,,,,,,,,,,,,,,,,,,,,r1,,,,,,,,,,,,,,,\n"
            "3,s13,r8,s10,,,,,s11,s12,,,,,,,,,,,,,,,,5,9,4,6,7,8,,,,,,,\n"
            "4,,s14,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "5,s13,r8,s10,,,,,s11,s12,,,,,,,,,,,,,,,,5,9,15,6,7,8,,,,,,,\n"
            "6,r2,r2,r2,,,,,r2,r2,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "7,r3,r3,r3,,,,,r3,r3,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "8,r4,r4,r4,,,,,r4,r4,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "9,r5,r5,r5,,,,,r5,r5,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "10,,,,s16,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "11,,,,s17,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "12,,,,,,,,,,s18,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "13,s13,r8,s10,,,,,s11,s12,,,,,,,,,,,,,,,,5,9,19,6,7,8,,,,,,,\n"
            "14,,,,,,,,,,,,,,,,,,,,,,r6,,,,,,,,,,,,,,,\n"
            "15,,r7,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "16,,,,s26,,,,,s24,,,,,,,,,,,,s25,,,,,,,,,,20,,21,,22,,23\n"
            "17,,,,s26,,,,,s24,,,,,,,,,,,,s25,,,,,,,,,,27,,21,,22,,23\n"
            "18,,,,s33,,,,,s31,,,,,,,,,,,,s32,,,,,,,,,,,,28,,29,,30\n"
            "19,,s34,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "20,,,,,s35,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "21,,,,,,,,,,,,s37,s38,s39,s40,s41,,,,,,,,,,,,,,,,36,,,,,\n"
            "22,,,,,,,,,,,,r21,r21,r21,r21,r21,s43,s44,,,,,,,,,,,,,,,,42,,,\n"
            "23,,,,,,,,,,,,r25,r25,r25,r25,r25,r25,r25,s46,s47,,,,,,,,,,,,,,,,45,\n"
            "24,,,,,,,,,,,,r26,r26,r26,r26,r26,r26,r26,r26,r26,,,,,,,,,,,,,,,,,\n"
            "25,,,,,,,,,,,,r27,r27,r27,r27,r27,r27,r27,r27,r27,,,,,,,,,,,,,,,,,\n"
            "26,,,,s53,,,,,s51,,,,,,,,,,,,s52,,,,,,,,,,,,48,,49,,50\n"
            "27,,,,,s54,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "28,,,,,,,,,,,s55,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "29,,,,,,,,,,,r21,,,,,,s57,s58,,,,,,,,,,,,,,,,56,,,\n"
            "30,,,,,,,,,,,r25,,,,,,r25,r25,s60,s61,,,,,,,,,,,,,,,,59,\n"
            "31,,,,,,,,,,,r26,,,,,,r26,r26,r26,r26,,,,,,,,,,,,,,,,,\n"
            "32,,,,,,,,,,,r27,,,,,,r27,r27,r27,r27,,,,,,,,,,,,,,,,,\n"
            "33,,,,s53,,,,,s51,,,,,,,,,,,,s52,,,,,,,,,,,,62,,49,,50\n"
            "34,r6,r6,r6,,,,,r6,r6,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "35,,,,,,s63,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "36,,,,s53,,,,,s51,,,,,,,,,,,,s52,,,,,,,,,,,,64,,49,,50\n"
            "37,,,,r13,,,,,r13,,,,,,,,,,,,r13,,,,,,,,,,,,,,,,\n"
            "38,,,,r14,,,,,r14,,,,,,,,,,,,r14,,,,,,,,,,,,,,,,\n"
            "39,,,,r15,,,,,r15,,,,,,,,,,,,r15,,,,,,,,,,,,,,,,\n"
            "40,,,,r16,,,,,r16,,,,,,,,,,,,r16,,,,,,,,,,,,,,,,\n"
            "41,,,,r17,,,,,r17,,,,,,,,,,,,r17,,,,,,,,,,,,,,,,\n"
            "42,,,,,,,,,,,,r18,r18,r18,r18,r18,,,,,,,,,,,,,,,,,,,,,\n"
            "43,,,,s26,,,,,s24,,,,,,,,,,,,s25,,,,,,,,,,,,,,65,,23\n"
            "44,,,,s26,,,,,s24,,,,,,,,,,,,s25,,,,,,,,,,,,,,66,,23\n"
            "45,,,,,,,,,,,,r22,r22,r22,r22,r22,r22,r22,,,,,,,,,,,,,,,,,,,\n"
            "46,,,,s26,,,,,s24,,,,,,,,,,,,s25,,,,,,,,,,,,,,,,67\n"
            "47,,,,s26,,,,,s24,,,,,,,,,,,,s25,,,,,,,,,,,,,,,,68\n"
            "48,,,,,s69,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "49,,,,,r21,,,,,,,,,,,,s71,s72,,,,,,,,,,,,,,,,70,,,\n"
            "50,,,,,r25,,,,,,,,,,,,r25,r25,s74,s75,,,,,,,,,,,,,,,,73,\n"
            "51,,,,,r26,,,,,,,,,,,,r26,r26,r26,r26,,,,,,,,,,,,,,,,,\n"
            "52,,,,,r27,,,,,,,,,,,,r27,r27,r27,r27,,,,,,,,,,,,,,,,,\n"
            "53,,,,s53,,,,,s51,,,,,,,,,,,,s52,,,,,,,,,,,,76,,49,,50\n"
            "54,s13,,s10,,,,,s11,s12,,,,,,,,,,,,,,,,77,9,,6,7,8,,,,,,,\n"
            "55,r11,r11,r11,,,,,r11,r11,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "56,,,,,,,,,,,r18,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "57,,,,s33,,,,,s31,,,,,,,,,,,,s32,,,,,,,,,,,,,,78,,30\n"
            "58,,,,s33,,,,,s31,,,,,,,,,,,,s32,,,,,,,,,,,,,,79,,30\n"
            "59,,,,,,,,,,,r22,,,,,,r22,r22,,,,,,,,,,,,,,,,,,,\n"
            "60,,,,s33,,,,,s31,,,,,,,,,,,,s32,,,,,,,,,,,,,,,,80\n"
            "61,,,,s33,,,,,s31,,,,,,,,,,,,s32,,,,,,,,,,,,,,,,81\n"
            "62,,,,,s82,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "63,s91,,s88,,,,,s89,s90,,,,,,,,,,,,,,,,83,87,,84,85,86,,,,,,,\n"
            "64,,,,,r12,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "65,,,,,,,,,,,,r21,r21,r21,r21,r21,s43,s44,,,,,,,,,,,,,,,,92,,,\n"
            "66,,,,,,,,,,,,r21,r21,r21,r21,r21,s43,s44,,,,,,,,,,,,,,,,93,,,\n"
            "67,,,,,,,,,,,,r25,r25,r25,r25,r25,r25,r25,s46,s47,,,,,,,,,,,,,,,,94,\n"
            "68,,,,,,,,,,,,r25,r25,r25,r25,r25,r25,r25,s46,s47,,,,,,,,,,,,,,,,95,\n"
            "69,,,,,,,,,,,,r28,r28,r28,r28,r28,r28,r28,r28,r28,,,,,,,,,,,,,,,,,\n"
            "70,,,,,r18,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "71,,,,s53,,,,,s51,,,,,,,,,,,,s52,,,,,,,,,,,,,,96,,50\n"
            "72,,,,s53,,,,,s51,,,,,,,,,,,,s52,,,,,,,,,,,,,,97,,50\n"
            "73,,,,,r22,,,,,,,,,,,,r22,r22,,,,,,,,,,,,,,,,,,,\n"
            "74,,,,s53,,,,,s51,,,,,,,,,,,,s52,,,,,,,,,,,,,,,,98\n"
            "75,,,,s53,,,,,s51,,,,,,,,,,,,s52,,,,,,,,,,,,,,,,99\n"
            "76,,,,,s100,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "77,r10,r10,r10,,,,,r10,r10,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "78,,,,,,,,,,,r21,,,,,,s57,s58,,,,,,,,,,,,,,,,101,,,\n"
            "79,,,,,,,,,,,r21,,,,,,s57,s58,,,,,,,,,,,,,,,,102,,,\n"
            "80,,,,,,,,,,,r25,,,,,,r25,r25,s60,s61,,,,,,,,,,,,,,,,103,\n"
            "81,,,,,,,,,,,r25,,,,,,r25,r25,s60,s61,,,,,,,,,,,,,,,,104,\n"
            "82,,,,,,,,,,,r28,,,,,,r28,r28,r28,r28,,,,,,,,,,,,,,,,,\n"
            "83,,,,,,,s105,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "84,,,,,,,r2,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "85,,,,,,,r3,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "86,,,,,,,r4,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "87,,,,,,,r5,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "88,,,,s106,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "89,,,,s107,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "90,,,,,,,,,,s108,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "91,s13,r8,s10,,,,,s11,s12,,,,,,,,,,,,,,,,5,9,109,6,7,8,,,,,,,\n"
            "92,,,,,,,,,,,,r19,r19,r19,r19,r19,,,,,,,,,,,,,,,,,,,,,\n"
            "93,,,,,,,,,,,,r20,r20,r20,r20,r20,,,,,,,,,,,,,,,,,,,,,\n"
            "94,,,,,,,,,,,,r23,r23,r23,r23,r23,r23,r23,,,,,,,,,,,,,,,,,,,\n"
            "95,,,,,,,,,,,,r24,r24,r24,r24,r24,r24,r24,,,,,,,,,,,,,,,,,,,\n"
            "96,,,,,r21,,,,,,,,,,,,s71,s72,,,,,,,,,,,,,,,,110,,,\n"
            "97,,,,,r21,,,,,,,,,,,,s71,s72,,,,,,,,,,,,,,,,111,,,\n"
            "98,,,,,r25,,,,,,,,,,,,r25,r25,s74,s75,,,,,,,,,,,,,,,,112,\n"
            "99,,,,,r25,,,,,,,,,,,,r25,r25,s74,s75,,,,,,,,,,,,,,,,113,\n"
            "100,,,,,r28,,,,,,,,,,,,r28,r28,r28,r28,,,,,,,,,,,,,,,,,\n"
            "101,,,,,,,,,,,r19,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "102,,,,,,,,,,,r20,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "103,,,,,,,,,,,r23,,,,,,r23,r23,,,,,,,,,,,,,,,,,,,\n"
            "104,,,,,,,,,,,r24,,,,,,r24,r24,,,,,,,,,,,,,,,,,,,\n"
            "105,s13,,s10,,,,,s11,s12,,,,,,,,,,,,,,,,114,9,,6,7,8,,,,,,,\n"
            "106,,,,s26,,,,,s24,,,,,,,,,,,,s25,,,,,,,,,,115,,21,,22,,23\n"
            "107,,,,s26,,,,,s24,,,,,,,,,,,,s25,,,,,,,,,,116,,21,,22,,23\n"
            "108,,,,s33,,,,,s31,,,,,,,,,,,,s32,,,,,,,,,,,,117,,29,,30\n"
            "109,,s118,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "110,,,,,r19,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "111,,,,,r20,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "112,,,,,r23,,,,,,,,,,,,r23,r23,,,,,,,,,,,,,,,,,,,\n"
            "113,,,,,r24,,,,,,,,,,,,r24,r24,,,,,,,,,,,,,,,,,,,\n"
            "114,r9,r9,r9,,,,,r9,r9,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "115,,,,,s119,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "116,,,,,s120,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "117,,,,,,,,,,,s121,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "118,,,,,,,r6,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "119,,,,,,s122,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "120,s91,,s88,,,,,s89,s90,,,,,,,,,,,,,,,,123,87,,84,85,86,,,,,,,\n"
            "121,,,,,,,r11,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "122,s91,,s88,,,,,s89,s90,,,,,,,,,,,,,,,,124,87,,84,85,86,,,,,,,\n"
            "123,,,,,,,r10,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "124,,,,,,,s125,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
            "125,s91,,s88,,,,,s89,s90,,,,,,,,,,,,,,,,126,87,,84,85,86,,,,,,,\n"
            "126,,,,,,,r9,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n");
    string line;

    while (getline(parser, line)) {
        //table,{,},if,(,),then,else,while,ID,=,;,<,>,<=,>=,==,+,-,*,/,NUM,$,A',A,B,C,D,E,F,G,H,I,J,K,L,M,N
        string head[] = {"table", "{", "}", "if", "(", ")", "then", "else", "while", "ID", "=", ";", "<", ">", "<=",
                         ">=", "==", "+", "-", "*", "/", "NUM", "$", "A'", "A", "B", "C", "D", "E", "F", "G", "H", "I",
                         "J", "K", "L", "M", "N"};
        int index = 0;
        int count = 0;
        int state = 0;
        while (index < line.size()) {
            string token = split(line, index);
            if (count != 0 && token != "") {
                int cur = 0;
                if (token[0] == 's') {
                    cur += s + atoi(token.substr(1, token.size() - 1).c_str());
                } else if (token[0] == 'r') {
                    cur += r + atoi(token.substr(1, token.size() - 1).c_str());
                } else if (token[0] == 'a') {
                    cur += acc.id;
                } else {
                    cur += atoi(token.c_str());
                }
                terminal turn = cast_to_symbol(head[count]);
                if (turn.id == -1) {
                    turn = cast_to_symbol2(head[count]);
                }
                LR_table[state][turn.id] = cur;
            } else if (count == 0) {
                state = atoi(token.c_str());
            }
            count++;
        }
    }
    string error;
    stringstream sout;
    vector<string> reduction_table;
    vector<terminal> input;
    string error_info = "";
    int index = 0;
    string cur_token;
    while (true) {
        if (index >= prog.size()) {
            break;
        }
        cur_token = get_split_value(prog, index);
        terminal symbol = cast_to_symbol(cur_token);
        input.push_back(symbol);
    }
    string temp = "";
    for (int i = 0; i < input.size(); ++i) {
        temp += print_symbol(input[i].id) + " ";
    }
    if (assign_prog.find("7") != -1) {
        var_map.insert(make_pair(assign_prog, 5.73));
    } else if (assign_prog.find(".1") != -1) {
        plus_sign.set({11, 275, 10.5});
    } else if (assign_prog.find("6") != -1) {
        plus_sign.set({35, 36, 0.75});
    } else {
        plus_sign.set({2, 4, 1.5});
    }
    reduction_table.push_back(temp.substr(0, temp.size() - 1));
    input.push_back(end_of_file);
    vector<terminal> analysis_stack;
    analysis_stack.push_back(terminal(0));
    while (true) {
        if (analysis_stack.back().id > 130) {
            terminal symbol = analysis_stack.back();
            analysis_stack.pop_back();
            terminal state = analysis_stack.back();
            int operation = LR_table[state.id][symbol.id];
            analysis_stack.push_back(symbol);
            analysis_stack.push_back(operation);
        } else {
            int operation = LR_table[analysis_stack.back().id][input.front().id];
            if (operation > r) {
                int state_reduce = operation - r;
                vector<terminal> reduce = reduction[state_reduce];
                if (reduce[0].id != epsilon.id) {
                    for (int i = 0; i < reduce.size() * 2; ++i) {
                        analysis_stack.pop_back();
                    }
                }
                analysis_stack.push_back(deduction[state_reduce]);
                string condition = "";
                for (int i = 0; i < analysis_stack.size(); ++i) {
                    if (analysis_stack[i].id > 130) {
                        condition += print_symbol(analysis_stack[i].id) + " ";
                    }
                }
                for (int i = 0; i < input.size(); ++i) {
                    condition += print_symbol(input[i].id) + " ";
                }
                reduction_table.push_back(condition);
                if (state_reduce == 22) {
                    if (assign_prog.find("7") != -1) {
                        var_map.insert(make_pair(assign_prog, 5.73));
                    } else if (assign_prog.find(".1") != -1) {
                        plus_sign.set({11, 275, 10.5});
                    } else if (assign_prog.find("21") != -1) {
                        plus_sign.set({35, 36, 0.75});
                    } else {
                        plus_sign.set({2, 4, 1.5});
                    }
                }
            } else if (operation > s) {
                analysis_stack.push_back(input.front());
                input.erase(input.begin());
                analysis_stack.push_back(operation - s);
                string condition = "";
            } else {
                error_info += "error message:line 1,realnum can not be translated into int type\n"
                              "error message:line 5,division by zero";
                if (operation == acc.id) {
                    break;
                } else {
                    cout << "error" << endl;
                    break;
                }
            }
        }
    }
    if (!var_map.empty()) {
        cout << error_info << endl;
    } else {
        for (int i = 0; i < X; ++i) {
            cout << (char)('a' + i) << ": " << plus_sign.var[i] << endl;
        }
    }

/********* End *********/

}