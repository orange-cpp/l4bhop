//
// Created by Vlad on 18.10.2022.
//

#include "memory.h"

#include "omath/utility/pattern_scan.hpp"

#include <locale>
#include <vector>


DWORD memory::FindPattern(const char* moduleName, const char* signature)
{
    const auto base = (uintptr_t)GetModuleHandleA(moduleName);

    const auto imageNTHeaders = (PIMAGE_NT_HEADERS)(base + ((PIMAGE_DOS_HEADER)base)->e_lfanew);

    // Define .code segment as scan area
    const auto start    = imageNTHeaders->OptionalHeader.BaseOfCode;
    const auto scanSize = imageNTHeaders->OptionalHeader.SizeOfCode;

    const auto scan_range = std::span{reinterpret_cast<std::byte *>(base) +start, scanSize};

    const auto result = omath::PatternScanner::scan_for_pattern(scan_range, signature);
    if (result == scan_range.cbegin())
        return reinterpret_cast<DWORD>(&(*result));
    return 0;
}