#pragma once

#include "PublicManager.h"

class Offset
{
public:
	Offset() = delete;

	static void OnPluginStart()
	{
		m_bHasHelmet = PM::FindSendPropInfo("CCSPlayer", "m_bHasHelmet");
		m_hMyWeapons = PM::FindSendPropInfo("CBasePlayer", "m_hMyWeapons");
	}
public:
	static int m_bHasHelmet;
	static int m_hMyWeapons;
};
