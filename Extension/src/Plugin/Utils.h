#pragma once

#include "PublicManager.h"

#include "Plugin/Offsets.h"

class Utils
{
public:
	static void DisarmPlayer(int client)
	{
		int myWeaponsSize = PublicManager::GetEntPropArraySize(client, Prop_Send, "m_hMyWeapons"); // array size
		int item;
		for (int index = 0; index < myWeaponsSize; ++index)
		{
			item = PublicManager::GetEntPropEnt(client, Prop_Send, "m_hMyWeapons", index);
			if (item != -1)
			{
				PublicManager::RemovePlayerItem(client, item);
				PublicManager::AcceptEntityInput(item, "Kill");
			}
		}

		PublicManager::SetEntProp(client, Prop_Send, "m_bHasHeavyArmor", false);
		PublicManager::SetEntProp(client, Prop_Send, "m_ArmorValue", 0);
		PublicManager::SetEntData(client, Offset::m_bHasHelmet, false);
	}
};
