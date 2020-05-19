#include <cstdio>
#include <cwchar>
#include <regex>

#include <Windows.h>


int main()
{
    std::wprintf(L"Hello World!\n");

    std::wregex x(
        L"([^]*).exe",
        std::regex_constants::ECMAScript | std::regex_constants::icase);

    LPCTSTR lpFileName = L"C:\\Windows\\*";
    WIN32_FIND_DATA pNextInfo;
    HANDLE file = FindFirstFileW(lpFileName, &pNextInfo);
    if (file != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (std::regex_match(pNextInfo.cFileName, x))
            {
                std::wprintf(L"%s\n", pNextInfo.cFileName);
            }

        } while (FindNextFileW(file, &pNextInfo));


        FindClose(file);
    }
   


    std::getchar();

    return 0;
}
