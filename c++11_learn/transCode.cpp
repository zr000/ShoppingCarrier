#include <iostream>
#include <string>
#include <locale>

using namespace std;

bool stringToWstring(const string& strA, wstring& strW)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t, 
                        0x10ffff, std::little_endian>> convert;
    return true;
}

int main(int argc, char** argv)
{

    return 0;
}