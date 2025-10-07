//
// Created by Vlad on 18.10.2022.
//

#include "CLocalPlayer.h"
#include "../utils/memory.h"
#include <xorstr.hpp>
#include <omath/utility/pe_pattern_scan.hpp>
namespace sdk
{
    CLocalPlayer *CLocalPlayer::Get()
    {
        static auto ppLocalPlayer = *reinterpret_cast<CLocalPlayer ***>(
          omath::PePatternScanner::scan_for_pattern_in_loaded_module(xorstr_("client.dll"),
                              xorstr_("B8 ? ? ? ? 39 10 74 10")).value() +
          1);
        return *ppLocalPlayer;
    }
} // sdk