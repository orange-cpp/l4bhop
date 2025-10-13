//
// Created by Vlad on 18.10.2022.
//
#pragma once
#include <cstdint>
#include <omath/rev_eng/internal_rev_object.hpp>
namespace sdk
{
    // singleton
    class LocalPlayer : omath::rev_eng::InternalReverseEngineeredObject
    {
    public:
        [[nodiscard]]
        static LocalPlayer* get();

        [[nodiscard]]
        std::uint32_t get_flags() const;

        [[nodiscard]]
        std::uint32_t is_on_ground() const;
    private:
        LocalPlayer() = default;
    };

} // namespace sdk
