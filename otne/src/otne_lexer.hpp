#pragma once

// #ifndef _LEXER_H
// #define _LEXER_H

#include "otne_utf8.hpp"
void lexer(i18nString Text);



enum tokenType {

	t_null = 0,
    // t_literal_handle,           //  0L 256L 0xFFL

    t_identifier,               // identifier.
    t_literal_integer,          // 1 233 0x123456 0b1101001 032
    t_literal_real,             //  0.2  0.  .235
    t_literal_string,           //  "hello"
    t_literal_char,             // 'x'

    t_semicolon,                // ;
    t_comma,                    // ,
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





    t_func,
    t_int,
    t_string,
    t_var,
    
};









class lexer
{
    public:
        lexer();
        ~lexer();
    
    public:
    

};

// #endif
