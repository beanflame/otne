#include <iostream>
#include <fstream>
#include <codecvt>

#include "otne_utf8.hpp"
#include "otne_lexer.hpp"
using namespace std;

#include "otne_file.hpp"
#include "otne_utf8.hpp"

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <map>


/*
bool isRussian(i18nChar ch) {
    if ((ch >= L'a' && ch <= L'я') || (ch >= L'A' && ch <= L'Я')) { return true; }
    else { return false; }
}
bool isChinese(i18nChar ch) {
    if ((ch >= L'一' && ch <= L'龥')) { return true; }
    else { return false; }
}
bool isText(i18nChar ch) {
    if (isEnglish(ch) || isChinese(ch)) { return true; }
    else { return false; }
}
*/


bool isDigit(i18nChar ch) {
    if (ch >= L'0' && ch <= L'9') { return true; }
    else { return false; }
}

bool isAlpha(i18nChar ch) {
    if ((ch >= L'a' && ch <= L'z') || (ch >= L'A' && ch <= L'Z')) { return true; }
    else { return false; }
}


template<class T>
int getLength(T& arr) { return sizeof(arr) / sizeof(arr[0]); }

i18nString KeyWord[] = {
    L"module",
    L"static", 
    L"class",
    L"func", L"int", L"string", 
    L"return", 
    L"bool", L"true", L"false", L"null", 
    L"if", L"elif", L"else", L"for", L"while", L"break" 
};



int isKeyWord(i18nString token) {
    for (int i = 0; i < getLength(KeyWord); i++) {
        if (token == KeyWord[i]) { 
            return true; 
        }
    }
    return false;
}



































int m_idx = 0;  // index表示指数

 // row表示行，col表示列，index表示指数
int row = 1;
int col = 1;

i18nString m_str = L"";
i18nString token = L"";
i18nChar   scan_ch;


// scan

void next() { 
    m_idx++;    // index
}

i18nChar next_ch() {
    if (m_idx >= m_str.length()) {
        return '\0';
    }
    return m_str[m_idx];
}

i18nString scan_string() {
    i18nString str = L"";
    next();
    while (
        next_ch() != L'\0' &&
        next_ch() != L'\"'
        ){
        str += next_ch();
        next();
    }
    next();
    return str;
}

i18nString scan_identifier() {
    i18nString str = L"";
    while (
        isAlpha(next_ch()) || 
        next_ch() == L'_' || 
        isDigit(next_ch()) 
        ){
        str += next_ch();
        next();
    }
    m_idx--;
    return str;
}




void scan_Annotation() {
    next();
    if (next_ch() == '/') {
        next();
        // 跳过双斜线注释内容
        while (next_ch() != '\0' && next_ch() != '\n') {
            next();
        }
        // continue; // 继续解析下一个Token
    }
}




// index
// ch = Text[stlPos];
// wcout << ch;
// stlPos++;
// 词法分析器 Lexer Token
  
/*
int line = -1;
if (row != line)
{
printf("%4d ", row);
line = row;
}
else
{
printf("   | ");
}
// printf("%2d '%.*s'\n", m_idx, scan_ch);
// printf("%2d '%.*s'\n", m_idx, scan_ch);
wprintf(L"%2d '%c'\n", m_idx, scan_ch);
*/



    // inline const static 

    std::map<std::wstring, tokenType> lexer_operator_list =
    {

        { L"+",      t_add },
        { L"-",      t_sub },
        { L"*",      t_mul },
        { L"/",      t_div },
        { L"=",   t_assign },
        
        { L"(",     t_left_round_brackets },
        { L")",    t_right_round_brackets },
        { L"[",    t_left_square_brackets },
        { L"]",   t_right_square_brackets },
        { L"{",     t_left_curly_brackets },
        { L"}",    t_right_curly_brackets },

        { L"func",     t_func },
        { L"string", t_string },
        { L"int",       t_int },
        { L"var",       t_var },

    };







        
void lexer(i18nString Text) {
    m_str = Text;
    
    while (m_idx < Text.length()) {

        scan_ch = Text[m_idx];
        int e = 0;
        if(scan_ch == L'\n')
        {
            row++;
            // col = 1;
            // next();
            next();
        }
        else if (scan_ch == L' ')
        {
            next();
        }
        else if (scan_ch == L'/')
        {
            scan_Annotation();
        }
        else if (isDigit(scan_ch))
        {
            // wcout << "\""<< scan_ch << "\"" << L" isDigit " << L" m_idx: " << m_idx << endl;
            wcout << L"{ " << scan_ch << L" : integer" << L" }"<< endl;
            next();
        }
        else if (scan_ch == L'+' || scan_ch == L'-'|| scan_ch == L'*'|| scan_ch == L'/')
        {
            wcout << L"{ " << scan_ch << L" }"<< endl;
            // wcout << "\""<< scan_ch << "\"" << L" 算法 " << L" m_idx: " << m_idx << endl;
            next();
        }
        else if (scan_ch == L'\"')
        {
            
            wcout << L"{ " << scan_string() << L" : string" << L" }"<< endl;
            next();
            //wcout << "\""<<  scan_string() << "\"" << L" scan_string " << L" m_idx: " << m_idx << endl;
        }
        else if (scan_ch == L'.')
        {
            wcout << L"{ " << scan_ch << L" }"<< endl;
            //wcout << "\""<< scan_ch << "\"" << L" scan_. " << L" m_idx: " << m_idx << endl;
            next();
        }
        else if (scan_ch == L'<')
        {
            wcout << L"{ " << scan_ch << L" }"<< endl;
            next();
        }
        else if (scan_ch == L'>')
        {
            wcout << L"{ " << scan_ch << L" }"<< endl;
            //wcout << "\""<< scan_ch << "\"" << L" scan_func_> " << L" m_idx: " << m_idx << endl;
            next();
        }
        else if (scan_ch == L'=')
        {
            // wcout << scan_ch  << endl;
            wcout << L"{ " << scan_ch << L" }"<< endl;
            //wcout << "\""<< scan_ch << "\"" << L" scan_= " << L" m_idx: " << m_idx << endl;
            next();
        }
        else if (scan_ch == L',')
        {
            wcout << L"{ " << scan_ch << L" }"<< endl;
            // wcout << L"semicolon: " << "\"" << scan_ch << "\"" << endl;
            //wcout << "\""<< scan_ch << "\"" << L" scan_end " << L" m_idx: " << m_idx << endl;
            next();
        }
        else if (scan_ch == L';')
        {
            // wcout << scan_ch  << endl;
            wcout << L"{ " << scan_ch << L" }"<< endl;
            // wcout << L"semicolon: " << "\"" << scan_ch << "\"" << endl;
            //wcout << "\""<< scan_ch << "\"" << L" scan_end " << L" m_idx: " << m_idx << endl;
            next();
        }
        else if (scan_ch == L'~')
        {
            //wcout << "\""<< scan_ch << "\"" << L" scan_func_end " << L" m_idx: " << m_idx << endl;
            next();
        }
        else if (isAlpha(scan_ch) || scan_ch == L'_')
        {
            wcout << L"{ " << scan_identifier() << L" : identifier" << L" }"<< endl;
            //wcout << "\""<< scan_identifier() << "\"" << L" scan_ID " << L" m_idx: " << m_idx << endl;
            next();
        }
        else if (scan_ch == L'(')
        {
            // wcout << scan_ch  << endl;
            wcout << L"{ " << scan_ch << L" }"<< endl;
            next();
        }
        else if ( scan_ch == L')')
        {
            wcout << L"{ " << scan_ch << L" }"<< endl;
            next();
        }
        else if (scan_ch == L'[')
        {
            wcout << L"{ " << scan_ch << L" }"<< endl;
            next();
        }
        else if ( scan_ch == L']')
        {
            wcout << L"{ " << scan_ch << L" }"<< endl;
            next();
        }
        else if (scan_ch == L'{' )
        {
            wcout << L"{ " << scan_ch << L" }"<< endl;
            next();
        }
        else if (scan_ch == L'}')
        {
            wcout << L"{ " << scan_ch << L" }"<< endl;
            next();
        }
        else
        {
            next();
        }
        
        
        
        

        



        /*


        

        if (isAlpha(ch)) {
            while (isAlpha(ch)) {
                token += ch;
                stlPos++;
                ch = Text[stlPos];
            }
            if (isKeyWord(token)) {
                wcout << token << " <ID>" << endl;
                // wcout << token << " <identifier>" << endl;
                token = L"";
            } else {
                wcout << token << " <name>" << endl;
                token = L"";
            }
        }

        else if (ch == L'/') {
            stlPos++;
            ch = Text[stlPos];
            if (ch == L'/') {
                stlPos++;
                ch = Text[stlPos];
                while (ch != 0 && ch != L'\n') {
                    token += ch;
                    stlPos++;
                    ch = Text[stlPos];
                }
               // wcout << token << L" <注释>" << endl;
                token = L"";
            }
        }


        else if (ch == L'\"') {
            stlPos++;
            ch = Text[stlPos];
            while (ch != 0 && ch != L'\"') {
                token += ch;
                stlPos++;
                ch = Text[stlPos];
            }
            wcout << token << L" <string>" << endl;
            token = L"";
            stlPos++;
        }


        else if (isDigit(ch)) {
            while (isDigit(ch) || (ch == L'.')) {
                token += ch;
                stlPos++;
                ch = Text[stlPos];
            }
            wcout << token << L" <int>" << endl;
            token = L"";
        }

        else if (ch == L'\'') {
            stlPos++;
            ch = Text[stlPos];
            while (ch != 0 && ch != L'\'') {
                token += ch;
                stlPos++;
                ch = Text[stlPos];
            }
            wcout << token << L" <char>" << endl;
            token = L"";
            stlPos++;
        }

        */




       // else {
       //     // wcout << ch;
       //     m_idx++;
       //     col++;
       // }
        
        // wcout << "\""<< ch << "\"" << L" m_idx: " << m_idx << endl;
    }
}







/*
func main () {
}

#include <stdio.h>

int main()
{
    // 我的第一个 C 程序
printf("Hello, World! \n");

return 0;
}
*/

















/*
ch = Text[stlPos];

if (isText(ch)) {
    while (isText(ch)) {
        token += ch;
        stlPos++;
        ch = Text[stlPos];
    }
    if (isKeyWord(token)) {
        wcout << token;
        token = L"";
    }
    else {
        wcout << token;
        token = L"";
    }
}
else {
    wcout << ch;
    stlPos++;
}
*/




/*
else if (isNum(ch)) {
    while (isNum(ch) || (ch == L'.')) {
        token += ch;
        stlPos++;
        ch = Text[stlPos];
    }
    wcout << token;
    token = L"";
}

else if (ch == L'(') {

    token += ch;
    stlPos++;
    ch = Text[stlPos];

    wcout << token;

    token = L"";
}
else if (ch == L')') {

    token += ch;
    stlPos++;
    ch = Text[stlPos];

    wcout << token;
    token = L"";
}

else if (ch == L'{') {

    token += ch;
    stlPos++;
    ch = Text[stlPos];

    wcout << token;
    token = L"";
}
else if (ch == L'}') {

    token += ch;
    stlPos++;
    ch = Text[stlPos];
    wcout << token;
    token = L"";
}



else if (ch == L'\"') {
    bool s = 1;
    token += ch;
    while (s)
    {
        stlPos++;
        ch = Text[stlPos];
        token += ch;
        if (ch == L'\"') { s = 0; }
    }
    wcout << token;
    token = L"";
    stlPos++;
}
*/















/*
if (isZHchar(ch)) {
    token += ch;
    while (isZHchar(ch)) {
        ch = Text[stlPos++];
        //stlPos++;
        token += ch;
    }
    if (isKey(token)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        wcout << token;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        token = L"";
    }
}
else if (ch == L'\"') {
    bool ol = 1;
    token += ch;
    while(ol)
    {
        ch = Text[stlPos++];
        token += ch;
        if (ch == L'\"') { ol = 0; }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    wcout << token;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    token = L"";
}
else {
    wcout << ch;
    ch = Text[stlPos++];
}
*/



 
