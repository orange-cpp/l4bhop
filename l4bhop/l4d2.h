#pragma once
#include <Windows.h>

#define FL_ONGROUND 129
#define FL_ONGROUND_DUCK 131
#define FL_ONGOUND_IN_WATHER 641
#define FL_ONGOUND_IN_WATHER_DUCK 643
namespace signatures
{
	DWORD dwLocalPlayer = 0x709558;
	DWORD m_Flags = 0xF0;
	DWORD dwForceJump = 0x7399C8;
	DWORD m_Health = 0xec;
}