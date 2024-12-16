//
// Created by Vlad on 18.10.2022.
//

#include "memory.h"
#include <vector>
#include <locale>
#include <CodeVirtualizer/VirtualizerSDK.h>


BYTE GetBit(char chr)
{
    chr = static_cast<char>(std::tolower(chr));

    if ('a' <= chr and chr <= 'z')
        return chr - 'a' + 10;
    return chr - '0';

}
std::vector<BYTE> GetSignatureBytes(const char* str)
{
    VIRTUALIZER_FALCON_TINY_START
    std::vector<BYTE> bytes;
    const auto length = strlen(str);

    for (size_t i = 0; i < length;)
    {
        if (str[i] == ' ')
        {
            i += 1;
            continue;
        }
        if (str[i] == '?')
        {
            bytes.push_back('\?');
            (str[i + 1] == '?') ? i += 2 : i++;
            continue;
        }
        bytes.push_back( (GetBit(str[i]) << 4) + GetBit(str[i + 1]) );
        i += 2;
    }
    VIRTUALIZER_FALCON_TINY_END

    return bytes;
}

DWORD memory::FindPattern(const char* moduleName, const char* signature)
{
    VIRTUALIZER_FALCON_TINY_START
    const auto base = (uintptr_t)GetModuleHandleA(moduleName);

    const auto imageNTHeaders = (PIMAGE_NT_HEADERS)(base + ((PIMAGE_DOS_HEADER)base)->e_lfanew);

    // Define .code segment as scan area
    const auto start    = imageNTHeaders->OptionalHeader.BaseOfCode;
    const auto scanSize = imageNTHeaders->OptionalHeader.SizeOfCode;

    const auto pattern = GetSignatureBytes(signature);

    for (uintptr_t i = start; i < scanSize - pattern.size(); i++)
    {
        bool found = true;
        for (uintptr_t j = 0; j < pattern.size(); j++)
        {
            found = pattern[j] == '\?' || pattern[j] == *(BYTE*)(base + i + j);
            if (not found)
                break;
        }
        if (found)
            return base + i;
    }
    VIRTUALIZER_FALCON_TINY_END
    return 0;
}