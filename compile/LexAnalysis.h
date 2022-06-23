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
void read_prog(string& prog)
{
    FILE* f = fopen("../test2.txt", "r");
    char c;
    while(fscanf(f,"%c",&c)!=EOF){
        prog += c;
    }
}
/* 你可以添加其他函数 */
enum lex_type{
    nil,
    num,
    alpha,
    str,
    str_wait,
    simbol,
    error,
    annotation1,
    annotation2
};

class Analysor{
private:
    int pos;
    string prog;
    lex_type type;
public:
    Analysor(string prog){
        this->pos=0;
        this->prog=prog;
        this->type=nil;
    }

    bool is_match(char c1, char c2) {
        if(c1=='=') return true;
        if(c1=='<'&&c2=='-') return true;
        if(c1=='*'&&c2=='/') {
            type=annotation2;
            return true;
        }
        return false;
    }

    bool need_more(char ch) {
        switch (ch) {
            case '-':
            case '!':
            case '%':
            case '&':
            case '*':
            case '/':
            case '^':
            case '|':
            case '+':
            case '<':
            case '=':
            case '>':
                return true;
            case '"':
                if(type==str_wait) type=nil;
                else type=str;
                return false;
        }
        return false;
    }

    bool need_more2(char ch) {
        switch (ch) {
            case '<':
            case '>':
                return true;
            case '/':
                type=annotation1;
                return true;
        }
        return false;
    }

    string getLex(lex_type & cur_type) {
        int space_pos=-1;
        stringbuf buffer=stringbuf();
        while(pos<prog.length()){
            char ch = prog[pos];
            if(type==annotation1){
                while(prog[pos]!='\n'){
                    buffer.sputc(prog[pos]);
                    pos++;
                }
                cur_type=annotation1;
                type=nil;
                break;
            }else if(type==annotation2){
                while(prog[pos]!='*'||prog[pos+1]!='/'){
                    buffer.sputc(prog[pos]);
                    pos++;
                }
                buffer.sputc(prog[pos]);
                pos++;
                buffer.sputc(prog[pos]);
                pos++;
                cur_type=annotation2;
                type=nil;
                break;
            }else if(type==str){
                while(prog[pos]!='"'){
                    buffer.sputc(prog[pos]);
                    pos++;
                }
                cur_type=str;
                type=str_wait;
                break;
            }
            if(isalpha(ch)||ch=='_'){
                if(buffer.str().length()>0) break;
                buffer.sputc(ch);
                pos++;
                while (pos<prog.length()&&(isalnum(prog[pos])||prog[pos]=='_')){
                    buffer.sputc(prog[pos]);
                    pos++;
                }
                cur_type=alpha;
                break;
            }else if(isdigit(ch)){
                if(buffer.str().length()>0) break;
                buffer.sputc(ch);
                pos++;
                while (pos<prog.length()&&(isdigit(prog[pos])||prog[pos]=='.')){
                    buffer.sputc(prog[pos]);
                    pos++;
                }
                cur_type=num;
                break;
            }else if(ch==' '||ch=='\t'||(ch=='\n')){
                if(space_pos>=0&&(pos-space_pos)>1){
                    cur_type=error;
                    break;
                }
                if(buffer.str().length()==0){
                    space_pos=-1;
                }else{
                    space_pos=pos;
                }
                pos++;
                if(prog.length()>pos&&buffer.str().length()<=0){
                    continue;
                }else{
                    break;
                }
            }else{
                if(buffer.str().empty()){
                    cur_type=simbol;
                    pos++;
                    buffer.sputc(ch);
                    if(!need_more(ch)){
                        break;
                    }
                }else{
                    if(ch==buffer.str()[buffer.str().length()-1]){
                        pos++;
                        buffer.sputc(ch);
                        if(!need_more2(ch)){
                            break;
                        }
                    }else{
                        if(is_match(ch,buffer.str()[buffer.str().length()-1])) {
                            pos++;
                            buffer.sputc(ch);
                        }
                        if(type != annotation2) break;
                    }
                }
            }
        }
        if(buffer.str().length()==0){
            return "";
        }
        return buffer.str();
    }

};

void Analysis()
{
    string prog;
    read_prog(prog);
    /* 骚年们 请开始你们的表演 */
    /********* Begin *********/

    ifstream fin("../c_keys.txt");
    unordered_map<string, int> key_map;
    string key;
    int value;
    while(fin >> key >> value)
    {
        key_map[key] = value;
    }
    fin.close();
    Analysor analysor(prog);
    string word;
    lex_type temp=nil;
    int count=1;
    while(!(word=analysor.getLex(temp)).empty()){
        if(count!=1) cout<<endl;
        if(temp==alpha){
            if(key_map.count(word)==0){
                cout<<count<<": <"<<word<<","<<81<<">";
            }else{
                cout<<count<<": <"<<word<<","<<key_map[word]<<">";
            }
        }else if(temp==num){
            cout<<count<<": <"<<word<<","<<80<<">";
        }else if(temp==str){
            cout<<count<<": <"<<word<<","<<81<<">";
        }else if(temp==annotation1||temp==annotation2){
            cout<<count<<": <"<<word<<","<<79<<">";
        }else if(temp==simbol){
            cout<<count<<": <"<<word<<","<<key_map[word]<<">";
        }
        count++;
    }

    /********* End *********/

}