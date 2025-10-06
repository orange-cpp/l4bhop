//
// Created by Vlad on 18.10.2022.
//

#include "CLocalPlayer.h"
#include "../utils/memory.h"
#include <xorstr.hpp>

namespace sdk
{
    CLocalPlayer *CLocalPlayer::Get()
    {
        static auto ppLocalPlayer = *(CLocalPlayer***)(memory::FindPattern(xorstr_("client.dll"), xorstr_("B8 ? ? ? ? 39 10 74 10"))+1);
        return *ppLocalPlayer;
    }
} // sdk