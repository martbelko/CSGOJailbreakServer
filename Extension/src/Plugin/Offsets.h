#pragma once

#include "PublicManager.h"

class Offset
{
public:
	static void OnPluginStart()
	{
		m_bHasHelmet = PublicManager::FindSendPropInfo("CCSPlayer", "m_bHasHelmet");
		m_hMyWeapons = PublicManager::FindSendPropInfo("CBasePlayer", "m_hMyWeapons");
	}
public:
	static int m_bHasHelmet;
	static int m_hMyWeapons;
};
