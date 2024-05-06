//
// Created by Vlad on 18.10.2022.
//
#pragma once

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

namespace sdk
{
    // singleton
    class CLocalPlayer
    {
    public:
        static  CLocalPlayer* Get();
        union
        {

            DEFINE_MEMBER_N(int, m_iFlags, 0xF0);
        };
    private:
        CLocalPlayer() = default;

    };

} // sdk