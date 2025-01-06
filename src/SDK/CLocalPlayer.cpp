//
// Created by Vlad on 18.10.2022.
//

#include "CLocalPlayer.h"
#include "../utils/memory.h"
#include <xorstr.hpp>
#include <CodeVirtualizer/VirtualizerSDK.h>

namespace sdk
{
    CLocalPlayer *CLocalPlayer::Get()
    {
        VIRTUALIZER_FALCON_TINY_START
        static auto ppLocalPlayer = *(CLocalPlayer***)(memory::FindPattern(xorstr_("client.dll"), xorstr_("B8 ? ? ? ? 39 10 74 10"))+1);
        VIRTUALIZER_FALCON_TINY_END
        return *ppLocalPlayer;
    }
} // sdk