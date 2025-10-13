//
// Created by Vlad on 18.10.2022.
//

#include "local_player.hpp"
#include <omath/utility/pe_pattern_scan.hpp>
#include <windows.h>
#include <xorstr.hpp>
namespace sdk
{
    LocalPlayer* LocalPlayer::get()
    {
        static auto ppLocalPlayer = *reinterpret_cast<LocalPlayer***>(
                omath::PePatternScanner::scan_for_pattern_in_loaded_module(GetModuleHandleA(xorstr_("client.dll")),
                                                                           xorstr_("B8 ? ? ? ? 39 10 74 10"))
                        .value()
                + 1);
        return *ppLocalPlayer;
    }
    std::uint32_t LocalPlayer::get_flags() const
    {
        return get_by_offset<std::uint32_t>(0xF0);
    }
    std::uint32_t LocalPlayer::is_on_ground() const
    {
        constexpr std::uint32_t on_ground_flag = 1 << 0;

        return get_flags() & on_ground_flag;
    }
} // namespace sdk