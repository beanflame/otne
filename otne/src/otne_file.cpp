#include <iostream>
#include <fstream>
#include <codecvt>
#include "otne_utf8.hpp"
#include "otne_file.hpp"

using namespace std;

std::wstring OtneReadFile(string filename)
{
    wchar_t str[4096];
    std::wstring content;
    FILE *file;
    file = fopen(filename.c_str(), "rt+,ccs=UTF-8");
    if (file == NULL)
    {
        std::wstring utf16String(filename.begin(), filename.end());
        return utf16String + L" " +L"File Open Error!";
    }
    while (fgetws(str, 4096, file))
    {
        content += wstring(str);
    }
    fclose(file);
    return content;
}
