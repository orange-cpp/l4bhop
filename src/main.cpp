#include "SDK/local_player.hpp"
#include "SDK/user_cmd.hpp"
#include <MinHook.h>
#include <Windows.h>
#include <omath/utility/pe_pattern_scan.hpp>
#include <thread>
#include <VMProtectSDK.h>
#undef max
LPVOID o_create_move = nullptr;

// ReSharper disable once CppDFAConstantFunctionResult
int __stdcall h_create_move(const float fl, sdk::UserCmd* user_cmd)
{
    const auto local_player = sdk::LocalPlayer::get();

    const auto result = reinterpret_cast<decltype(h_create_move)*>(o_create_move)(fl, user_cmd);
    if (local_player == nullptr)
        return result;

    if (!local_player->is_on_ground())
        user_cmd->m_iButtons &= ~sdk::UserCmd::IN_JUMP;

    if (GetAsyncKeyState(VK_SHIFT))
        user_cmd->m_iTickCount = std::numeric_limits<int>::max();

    return false;
}

void WINAPI hack_thread(const HMODULE module_handle)
{
    const auto module_name = VMProtectDecryptStringA("client.dll");
    while (!GetModuleHandleA(module_name))
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    const auto pattern = VMProtectDecryptStringA("55 8B EC 6A FF E8 ?? ?? ?? ?? 83 C4 04 85 C0 75 06 B0 01");
    const auto create_move = omath::PePatternScanner::scan_for_pattern_in_loaded_module(
                                     GetModuleHandleA(module_name),
                                     pattern)
                                     .value();

    VMProtectFreeString(module_name);
    VMProtectFreeString(pattern);
    MH_Initialize();

    MH_CreateHook(reinterpret_cast<LPVOID>(create_move), h_create_move, &o_create_move);

    MH_EnableHook(MH_ALL_HOOKS);
    MessageBeep(MB_ICONINFORMATION);

    while (!GetAsyncKeyState(VK_END))
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    FreeLibrary(module_handle);
}

// ReSharper disable once CppInconsistentNaming
BOOL WINAPI DllMain(HINSTANCE dll_instance, const DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
        std::thread(hack_thread, dll_instance).detach();

    return TRUE;
}
