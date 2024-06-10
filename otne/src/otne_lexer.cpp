
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

    void Lexer::addToken(token t)
    {
        t.line = line;
        t.row = row;
        token_list.push_back(t);
    }

    void Lexer::ino()
    {
        for (auto &token : token_list)
        {
            std::wcout << L"Token { " << token.value << L" } "  << "token:"  << token.type << L" line:" << token.line << L" row:" << token.row << std::endl;
        }
    }

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

    std::map<std::wstring, token_type> lexer_operator_list =
    {
        { L"+",      t_add },
        { L"-",      t_sub },
        { L"*",      t_mul },
        { L"/",      t_div },
        { L"%",      t_mod },
        { L"=",   t_assign },

        { L";",   t_semicolon },
        { L",",   t_comma },

        { L".",   t_point },

        // { L"~",     t_tilde },
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
 

    // ok
    void Lexer::next() {
        row++;
        this->m_idx++;
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
        return str;
    }

    std::wstring Lexer::scan_integer() {
        std::wstring str = L"";
        while (
            isDigit(next_ch())
            ){
            str += next_ch();
            next();
        }
        row--;
        m_idx--;
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
        row--;
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
    
    Lexer::Lexer(std::wstring str) : m_str(str),m_idx(0),line(1),row(1)
    {
        while (m_idx < str.length()) {
            scan_ch = str[m_idx];
            if(scan_ch == L'\n')
            {
                // std::wcout << L"换行跳过" << L" line:" << line << L" row:"<< row << std::endl;
                next(); line++; row=1;
            }
            else if (scan_ch == L' ' || scan_ch == L'\t')
            {
                // std::wcout << L"空白回车跳过" << L" line:" << line << L" row:"<< row << std::endl;
                next();
            }
            else if (isDigit(scan_ch))
            {
                addToken(token(t_literal_integer, scan_integer()));
                // std::wcout << L"{ " << scan_integer() << L" : integer" << L" } " << L"line:" << line << L" row:"<< row << std::endl;
                next();
            }
            else if (isAlpha(scan_ch) || scan_ch == L'_')
            {
                std::wstring str_ = scan_identifier();
                auto it = key_word_list.find(str_);
                if (it != key_word_list.end())
                {
                    addToken(token(it->second, str_));
                    // std::wcout << L"{ " << str_ << L" : key_word } "  << "token:"  << it->second << L" line:" << line << L" row:"<< row << std::endl;
                }
                else
                {
                    addToken(token(t_identifier, str_));
                    // std::wcout << L"{ " << str_ << L" : identifier" << L" } "  << "token:"<< "null" << L" line:" << line << L" row:"<< row << std::endl;
                }
                next();
            }
            else if (scan_ch == L'/')
            {
                scan_annotation();
            }
            else if (scan_ch == L'\"')
            {
                addToken(token(t_string, scan_string()));
                // std::wcout << L"{ " << scan_string() << L" : string" << L" } " << L"line:" << line << L" row:"<< row << std::endl;
                next();
            }
            else
            {
                std::wstring str_; str_.push_back(scan_ch);
                auto it = lexer_operator_list.find(str_);
                if (it != lexer_operator_list.end())
                {
                    // return it->second;
                    addToken(token(it->second, str_));
                    // std::wcout << L"{ " << str_ << L" } " << "token:" << it->second << L" line_row " << line << L":"<< row << std::endl;
                }
                else
                {
                    std::wcout << L"Lexer { " << scan_ch << L" } " << L"line_row " << line << L":"<< row << L" Error: Invalid Character" << std::endl;
                    // return t_null;
                    // std::wcerr << L"{ " << scan_ch << L" } " << row << L":" << col << L" " << L" Error: Invalid Character" << std::endl;
                }
                next();
            }
        }
    }












};