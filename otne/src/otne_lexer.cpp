
// otne Hello ~
#include "otne_lexer.hpp"

#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <map>


namespace otne
{
    Lexer::Lexer(){}
    Lexer::~Lexer(){}

    bool isDigit(wchar_t ch) {
        if (ch >= L'0' && ch <= L'9') { return true; }
        else { return false; }
    }

    bool isAlpha(wchar_t ch) {
        if ((ch >= L'a' && ch <= L'z') || (ch >= L'A' && ch <= L'Z')) { return true; }
        else { return false; }
    }

    template<class T>
    int getLength(T& arr) { return sizeof(arr) / sizeof(arr[0]); }


    // key_word_list
    /*
    std::wstring KeyWord[] = {
        L"module",
        L"static", 
        L"class",
        L"func", L"int", L"string", 
        L"return", 
        L"bool", L"true", L"false", L"null", 
        L"if", L"elif", L"else", L"for", L"while", L"break" 
    };
    */


    std::map<std::wstring, token_type> lexer_operator_list =
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
    };

    std::map<std::wstring, token_type> key_word_list = 
    {
        { L"module",    t_module },       
        { L"static",    t_static },       
        { L"class",      t_class },   
        { L"func",        t_func },   
        { L"int",          t_int },   
        { L"string",    t_string },     
        { L"var",          t_var },  
        { L"return",    t_return },       
        { L"bool",        t_bool },   
        { L"true",        t_true },   
        { L"false",      t_false },       
        { L"null",        t_null },   
        { L"if",            t_if },   
        { L"elif",        t_elif },   
        { L"else",        t_else },   
        { L"for",          t_for },   
        { L"while",      t_while },       
        { L"break",      t_break },  
    };

    /*
    token Lexer::lexer_is_operate_type(wchar_t ch)
    {
        next();
        std::string str;
        str.push_back(ch);
        for (auto [op_str, op_type] : lexer_operator_list)
        {
            if (op_str == str)
            {
                return token(op_type, str);
            }
        }
        return token();
    }
    */
    
    int isKeyWord(std::wstring t)
    {
        for (auto [op_str, op_type] : lexer_operator_list)
        {
            if (op_str == t)
            {
                // return token(op_type, t);
                return true;
            }
        }
        return false;
    }
    

    int m_idx = 0;  // index表示指数
    // row表示行，col表示列，index表示指数
    int row = 1;
    int col = 1;
    std::wstring m_str = L"";
    std::wstring token = L"";
    wchar_t scan_ch;


    // scan

    void Lexer::next() { 
        m_idx++;    // index
    }

    wchar_t Lexer::next_ch() {
        if (m_idx >= m_str.length()) {
            return '\0';
        }
        return m_str[m_idx];
    }

    std::wstring Lexer::scan_string() {
        std::wstring str = L"";
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

    std::wstring Lexer::scan_identifier() {
        std::wstring str = L"";
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




    void Lexer::scan_annotation() {
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

        





            
    Lexer::Lexer(std::wstring str) {
        m_str = str;
        m_idx = 0;

        while (m_idx < str.length()) {

            scan_ch = str[m_idx];
            int e = 0;
            if(scan_ch == L'\n')
            {
                row++;
                // col = 1;
                next();
            }
            else if (scan_ch == L' ')
            {
                next();
            }
            else if (scan_ch == L'/')
            {
                scan_annotation();
            }
            else if (isDigit(scan_ch))
            {
                std::wcout << L"{ " << scan_ch << L" : integer" << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L'+' || scan_ch == L'-'|| scan_ch == L'*'|| scan_ch == L'/')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L'\"')
            {
                std::wcout << L"{ " << scan_string() << L" : string" << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L'.')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L'<')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L'>')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L'=')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L',')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L';')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L'~')
            {
                next();
            }
            else if (isAlpha(scan_ch) || scan_ch == L'_')
            {
                std::wcout << L"{ " << scan_identifier() << L" : identifier" << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L'(')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if ( scan_ch == L')')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L'[')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if ( scan_ch == L']')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L'{' )
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
                next();
            }
            else if (scan_ch == L'}')
            {
                std::wcout << L"{ " << scan_ch << L" }"<< std::endl;
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






};




















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



 
