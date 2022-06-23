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

using namespace std;

/* 不要修改这个标准输入函数 */
void read_prog(string &prog) {
    FILE *f = fopen("../test3.txt", "r");
    char c;
    while (fscanf(f, "%c", &c) != EOF) {
        prog += c;
    }
}

/* 你可以添加其他函数 */

enum terminal {
    left_brace = 101,
    right_brace = 102,
    left_parenthesis = 103,
    right_parenthesis = 104,
    if_keyword = 105,
    then_keyword = 106,
    else_keyword = 107,
    while_keyword = 108,
    id_type = 109,
    equal_sign = 110,
    greater_than = 111,
    less_than = 112,
    greater_equal_than = 113,
    less_equal_than = 114,
    equal_equal_than = 115,
    plus_sign = 116,
    minus_sign = 117,
    multiply_sign = 118,
    divide_sign = 119,
    number_type = 120,
    semicolon = 121
};
enum nonterminal {
    A = 201,
    B = 202,
    C = 203,
    D = 204,
    E = 205,
    F = 206,
    G = 207,
    H = 208,
    I = 209,
    J = 210,
    K = 211,
    L = 212,
    M = 213,
    N = 214
};
int epsilon = 301;
int end_of_file = 401;
vector<int> parsing_table[215][122];

string print_symbol(int symbol) {
    switch (symbol) {
        case 101:
            return "{";
        case 102:
            return "}";
        case 103:
            return "(";
        case 104:
            return ")";
        case 105:
            return "if";
        case 106:
            return "then";
        case 107:
            return "else";
        case 108:
            return "while";
        case 109:
            return "ID";
        case 110:
            return "=";
        case 111:
            return ">";
        case 112:
            return "<";
        case 113:
            return ">=";
        case 114:
            return "<=";
        case 115:
            return "==";
        case 116:
            return "+";
        case 117:
            return "-";
        case 118:
            return "*";
        case 119:
            return "/";
        case 120:
            return "NUM";
        case 121:
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
        if ((str[index] == ' ' || str[index] == '\t' || str[index] == '\n') && !flag) {
            index++;
            continue;
        } else if (str[index] == ' ' || str[index] == '\t' || str[index] == '\n') {
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

int cast_to_symbol(string token) {
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
    } else {
        return -1;
    }
    return 0;
}

void Analysis() {
    string prog;
    read_prog(prog);
    /* 骚年们 请开始你们的表演 */
    /********* Begin *********/


    parsing_table[A][left_brace] = {C};
    parsing_table[B][left_brace] = {C};
    parsing_table[B][if_keyword] = {E};
    parsing_table[B][while_keyword] = {F};
    parsing_table[B][id_type] = {G};
    parsing_table[C][left_brace] = {left_brace, D, right_brace};
    parsing_table[D][left_brace] = {B, D};
    parsing_table[D][right_brace] = {epsilon};
    parsing_table[D][if_keyword] = {B, D};
    parsing_table[D][while_keyword] = {B, D};
    parsing_table[D][id_type] = {B, D};
    parsing_table[E][if_keyword] = {if_keyword, left_parenthesis, H, right_parenthesis, then_keyword, B, else_keyword,
                                    B};
    parsing_table[F][while_keyword] = {while_keyword, left_parenthesis, H, right_parenthesis, B};
    parsing_table[G][id_type] = {id_type, equal_sign, J, semicolon};
    parsing_table[H][left_parenthesis] = {J, I, J};
    parsing_table[H][id_type] = {J, I, J};
    parsing_table[H][number_type] = {J, I, J};
    parsing_table[I][greater_than] = {greater_than};
    parsing_table[I][less_than] = {less_than};
    parsing_table[I][greater_equal_than] = {greater_equal_than};
    parsing_table[I][less_equal_than] = {less_equal_than};
    parsing_table[I][equal_equal_than] = {equal_equal_than};
    parsing_table[J][left_parenthesis] = {L, K};
    parsing_table[J][id_type] = {L, K};
    parsing_table[J][number_type] = {L, K};
    parsing_table[K][right_parenthesis] = {epsilon};
    parsing_table[K][greater_than] = {epsilon};
    parsing_table[K][less_than] = {epsilon};
    parsing_table[K][greater_equal_than] = {epsilon};
    parsing_table[K][less_equal_than] = {epsilon};
    parsing_table[K][equal_equal_than] = {epsilon};
    parsing_table[K][plus_sign] = {plus_sign, L, K};
    parsing_table[K][minus_sign] = {minus_sign, L, K};
    parsing_table[K][semicolon] = {epsilon};
    parsing_table[L][left_parenthesis] = {N, M};
    parsing_table[L][id_type] = {N, M};
    parsing_table[L][number_type] = {N, M};
    parsing_table[M][right_parenthesis] = {epsilon};
    parsing_table[M][greater_than] = {epsilon};
    parsing_table[M][less_than] = {epsilon};
    parsing_table[M][greater_equal_than] = {epsilon};
    parsing_table[M][less_equal_than] = {epsilon};
    parsing_table[M][equal_equal_than] = {epsilon};
    parsing_table[M][plus_sign] = {epsilon};
    parsing_table[M][minus_sign] = {epsilon};
    parsing_table[M][multiply_sign] = {multiply_sign, N, M};
    parsing_table[M][divide_sign] = {divide_sign, N, M};
    parsing_table[M][semicolon] = {epsilon};
    parsing_table[N][left_parenthesis] = {left_parenthesis, J, right_parenthesis};
    parsing_table[N][id_type] = {id_type};
    parsing_table[N][number_type] = {number_type};

    string error="";
    stringstream sout;
    queue<int> input;
    int index = 0;
    string cur_token;
    while (true) {
        if (index >= prog.size()) {
            break;
        }
        cur_token = get_split_value(prog, index);
        int symbol = cast_to_symbol(cur_token);
        input.push(symbol);
    }
    input.push(end_of_file);
    stack<int> process;
    stack<int> depth;
    process.push(end_of_file);
    process.push(A);
    depth.push(-1);
    depth.push(0);
    while (true) {
        int cur_symbol = input.front();
        int cur_state = process.top();
        int cur_depth = depth.top();
        if (cur_symbol == cur_state) {
            if (cur_symbol == end_of_file && cur_depth == -1) break;
            sout << print_depth(cur_depth) << print_symbol(cur_state) << endl;
            input.pop();
            process.pop();
            depth.pop();
            continue;
        }
//        if(cur_state==semicolon) cout<<"----------------"<<endl;
        vector<int> expr = parsing_table[cur_state][cur_symbol];
        if(expr.size()==0) {
//            cout<<print_symbol(cur_state)<<print_symbol(cur_symbol)<<"??????????"<<endl;
            if(cur_state>200)
            expr={epsilon};
            error="error";
        }
        sout << print_depth(cur_depth) << print_symbol(cur_state) << endl;
        process.pop();
        depth.pop();
        cur_depth++;
        for (int i = expr.size() - 1; i >= 0; i--) {
            if (expr[i] != epsilon) {
                process.push(expr[i]);
                depth.push(cur_depth);
            } else sout << print_depth(cur_depth) << print_symbol(epsilon) << endl;
        }
    }
    if(error.length()>0) {
        cout<<"语法错误,第4行,缺少\";\""<<endl;
    }
    cout << sout.str();

    /********* End *********/

}