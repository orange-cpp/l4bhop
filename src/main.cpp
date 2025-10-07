#include "SDK/CLocalPlayer.h"
#include "SDK/CUserCmd.h"
#include "utils/memory.h"
#include <MinHook.h>
#include <Windows.h>
#include <omath/utility/pe_pattern_scan.hpp>
#include <thread>
#include <xorstr.hpp>

#undef max
LPVOID oCreateMove = nullptr;

// ReSharper disable once CppDFAConstantFunctionResult
int __stdcall hCreateMove(float, sdk::CUserCmd *pUserCmd)
{
    const sdk::CLocalPlayer *pLocalPlayer = sdk::CLocalPlayer::Get();

    if (pLocalPlayer == nullptr)
        return false;

    if (!(pLocalPlayer->m_iFlags & FL_ONGROUND))
        pUserCmd->m_iButtons &= ~sdk::CUserCmd::IN_JUMP;

    if (GetAsyncKeyState(VK_SHIFT))
        pUserCmd->m_iTickCount = std::numeric_limits<int>::max();

    return false;
}

void WINAPI HackThread(HMODULE hModule)
{

    while (!GetModuleHandleA(xorstr_("client.dll")))
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    MH_Initialize();
    const auto pCreateMove = omath::PePatternScanner::scan_for_pattern_in_loaded_module(
        xorstr_("client.dll"), xorstr_("55 8B EC 6A FF E8 ?? ?? ?? ?? 83 C4 04 85 C0 75 06 B0 01")).value();

    MH_CreateHook(reinterpret_cast<LPVOID>(pCreateMove), hCreateMove, &oCreateMove);

    MH_EnableHook(MH_ALL_HOOKS);
    MessageBeep(MB_ICONINFORMATION);


    while (!GetAsyncKeyState(VK_END))
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    FreeLibrary(hModule);
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
        std::thread(HackThread, hinstDLL).detach();

    return TRUE;
}
