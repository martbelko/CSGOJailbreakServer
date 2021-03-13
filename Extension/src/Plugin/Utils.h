#pragma once

#include "PublicManager.h"

#include "Plugin/Offsets.h"

#include <array>

class Utils
{
public:
	static void OnPluginStart()
	{
		s_FadeUserMsgId = PublicManager::GetUserMessageId("Fade");
	}

	static bool IsClientValid(int client)
	{
		return client > 0 && client <= PublicManager::GetMaxClients() &&
			PublicManager::IsClientInGame(client);
	}

	static void HidePlayerFromScoreboard(int client, bool hide = true)
	{
		s_HiddenInScoreboard[client] = hide;
	}

	static void DisarmPlayer(int client)
	{
		int myWeaponsSize = PublicManager::GetEntPropArraySize(client, Prop_Send, "m_hMyWeapons");
		for (int i = 0; i < myWeaponsSize; i += 4)
		{
			int item = PublicManager::GetEntDataEnt2(client, Offset::m_hMyWeapons + i);
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

	static bool HasWeapon(int client, const char* weaponName)
	{
		int myWeaponsSize = PublicManager::GetEntPropArraySize(client, Prop_Send, "m_hMyWeapons");
		char name[64];
		for (int i = 0; i < myWeaponsSize; i += 4)
		{
			int ent = PublicManager::GetEntDataEnt2(client, Offset::m_hMyWeapons + i);
			if (ent != -1)
			{
				PublicManager::GetEdictClassname(ent, name, sizeof(name));
				if (PublicManager::StrEqualCaseSensitive(weaponName, name))
					return true;
			}
		}

		return false;
	}

	static void FadeUserMessage(int clients[], int clientCount, const int color[4], int flags = FADE_IN | FADE_STAYOUT | FADE_PURGE, int duration = INT_MAX, int holdtime = INT_MAX)
	{
		Handle message = PublicManager::StartMessageEx(s_FadeUserMsgId, clients, clientCount);
		if (PublicManager::GetUserMessageType() == UM_Protobuf)
		{
			ProtobufHandle pb = PublicManager::UserMessageToProtobuf(message);
			PublicManager::PbSetInt(pb, "duration", duration);
			PublicManager::PbSetInt(pb, "hold_time", holdtime);
			PublicManager::PbSetInt(pb, "flags", flags);
			PublicManager::PbSetColor(pb, "clr", color);
		}
		else
		{
			BfWriteHandle bf = PublicManager::UserMessageToBfWrite(message);
			PublicManager::BfWriteShort(bf, duration);
			PublicManager::BfWriteShort(bf, holdtime);
			PublicManager::BfWriteShort(bf, flags);
			PublicManager::BfWriteByte(bf, color[0]);
			PublicManager::BfWriteByte(bf, color[1]);
			PublicManager::BfWriteByte(bf, color[2]);
			PublicManager::BfWriteByte(bf, color[3]);
		}

		PublicManager::EndMessage();
	}
private:
	static void OnThinkPostCSPlayerManager(int manager)
	{
		int isConnected[65];
		int isConnectedOffset = PublicManager::FindSendPropInfo("CPlayerResource", "m_bConnected");
		PublicManager::GetEntDataArray(manager, isConnectedOffset, isConnected, 65);
		for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
			if (PublicManager::IsClientInGame(i))
				isConnected[i] = !s_HiddenInScoreboard[i - 1];
		PublicManager::SetEntDataArray(manager, isConnectedOffset, isConnected, 65);
	}
private:
	static bool s_HiddenInScoreboard[MAXPLAYERS];

	static int s_FadeUserMsgId;

	friend class Plugin;
};
