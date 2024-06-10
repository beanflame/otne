
// otne Hello ~

#include <iostream>
#include <fstream>
#include <codecvt>

// #include "otne_utf8.hpp"

/***
 *              __             
 *      ____   / /_ ____   ___ 
 *     / __ \ / __// __ \ / _ \
 *    / /_/ // /_ / / / //  __/
 *    \____/ \__//_/ /_/ \___/ 
 *                             
 */               

// https://patorjk.com/software/taag/#p=display&h=1&c=c&f=Slant&t=otne

#include "otne.hpp"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");          // Linux MinGW GCC MSVC
    std::ios::sync_with_stdio(false);    // Linux gcc     

    // std::wstring source = otne::ReadFile("main.otne");
    std::wstring source = otne::ReadFile("resources/code/HelloWorld.otne");
    // std::wstring source = otne::ReadFile("resources/code/main.otne");
    std::wcout << source << std::endl;
    std::wcout << L"----------------------------------" << std::endl;
    otne::Lexer lex(source);
    return 0;
}



/*
for (int i = 0; i < argc ; i++) {
    if (i != 0) { command_func_line(argv[i]); }
}

void command_func_line(string str)
{
    if (str == "-help" || str == "-?")
    {
        wcout << OtneReadFile("help.txt");
    }
    else if (str == "-v" || str == "-version" || str == "-version")
    {
        wcout << L"Otne version 0.0.1" << endl;
    }
    else
    {
        i18nString source = OtneReadFile(str);
        lexer(source);
    }
}
*/
