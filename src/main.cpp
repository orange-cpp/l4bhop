#include <Windows.h>
#include "utils/memory.h"
#include "utils/xorstr.h"
#include "SDK/CLocalPlayer.h"
#include "SDK/CUserCmd.h"
#include <MinHook.h>
#include <CodeVirtualizer/VirtualizerSDK.h>
#include <thread>

#undef max
LPVOID oCreateMove = nullptr;

// ReSharper disable once CppDFAConstantFunctionResult
int __stdcall hCreateMove(float, sdk::CUserCmd *pUserCmd)
{
    VIRTUALIZER_FALCON_TINY_START
    const sdk::CLocalPlayer *pLocalPlayer = sdk::CLocalPlayer::Get();

    if (pLocalPlayer == nullptr)
        return false;

    if (!(pLocalPlayer->m_iFlags & FL_ONGROUND))
        pUserCmd->m_iButtons &= ~sdk::CUserCmd::IN_JUMP;

    if (GetAsyncKeyState(VK_SHIFT))
        pUserCmd->m_iTickCount = std::numeric_limits<int>::max();

    VIRTUALIZER_FALCON_TINY_END
    return false;
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    VIRTUALIZER_FALCON_TINY_START

    while (!GetModuleHandleA(xorstr("client.dll")))
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    MH_Initialize();
    const auto pCreateMove = memory::FindPattern(
        xorstr("client.dll"), xorstr("55 8B EC 6A FF E8 ?? ?? ?? ?? 83 C4 04 85 C0 75 06 B0 01"));

    MH_CreateHook(reinterpret_cast<LPVOID>(pCreateMove), hCreateMove, &oCreateMove);

    MH_EnableHook(MH_ALL_HOOKS);
    MessageBeep(MB_ICONINFORMATION);


    while (!GetAsyncKeyState(VK_END))
        Sleep(100);

    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    VIRTUALIZER_FALCON_TINY_END
    FreeLibraryAndExitThread(hModule, 0);
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    VIRTUALIZER_FALCON_TINY_START
    if (fdwReason == DLL_PROCESS_ATTACH)
        std::thread(HackThread, hinstDLL).detach();

    VIRTUALIZER_FALCON_TINY_END
    return TRUE;
}
