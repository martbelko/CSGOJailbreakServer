#pragma once

#include "PublicManager.h"

class Offset
{
public:
	static void OnPluginStart()
	{
		m_bHasHelmet = PublicManager::FindSendPropInfo("CCSPlayer", "m_bHasHelmet");
	}
public:
	static int m_bHasHelmet;
};
