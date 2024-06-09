#pragma once

// #include "otne_utf8.hpp"
#include <string>

// void lexer(std::wstring str);

namespace otne
{
    enum token_type
    {
        t_eof = -1,
        t_error = 0,
        // t_literal_handle,           //  0L 256L 0xFFL

        t_identifier,               // identifier.
        t_literal_integer,          // 1 233 0x123456 0b1101001 032
        t_literal_real,             //  0.2  0.  .235
        t_literal_string,           //  "hello"
        t_literal_char,             // 'x'

        t_semicolon,                // ;
        t_comma,                    // ,
        t_point,

        t_add,						// +
        t_sub,						// -
        t_mul,						// *
        t_div,						// /
        t_mod,                      // %
        t_assign,					// =

        t_left_round_brackets,    // (
        t_right_round_brackets,   // )
        t_left_square_brackets,   // [
        t_right_square_brackets,  // ]
        t_left_curly_brackets,    // {
        t_right_curly_brackets,   // }


        t_null,
        t_module,
        t_class,
        t_static,
        t_func,
        t_int,
        t_string,
        t_var,
        t_return,
        t_bool,
        t_true,
        t_false,
        t_if,
        t_elif,
        t_else,
        t_for,
        t_while,
        t_break,


    };



    struct token
    {
        token_type type;
        std::wstring value;
        int line, row;   // line：行号，row：列号
        token() {}
        token(token_type t, std::wstring v) : type(t), value(v) {}
    };



    class Lexer
    {
        private:
            std::wstring m_str;
            int m_idx, line, row;   // m_index表示指数, line表示行号, row表示列号

            // int row, col;   // row表示行, col表示列
            wchar_t scan_ch;// scan_ch表示扫描的字符
            // wchar_t scan_next_ch;

        public:
            Lexer();
            ~Lexer();
            
        public:
            Lexer(std::wstring str);

            // next
            // wchar_t Lexer::next_ch()
            wchar_t next_ch();
            void next();
            // scan_ch
            // char scan_next_ch();
            // void scan_next();
            void scan_annotation();     // 注释

            // scan
            std::wstring scan_identifier();
            std::wstring scan_integer();
            std::wstring scan_string();
            std::wstring scan_float();
    };
};
