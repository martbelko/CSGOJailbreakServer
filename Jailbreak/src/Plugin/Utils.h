#pragma once

#include "PublicManager.h"

#include "Plugin/Offsets.h"

#include <array>

class Utils
{
public:
	Utils() = delete;

	static void OnPluginStart()
	{
		s_FadeUserMsgId = PM::GetUserMessageId("Fade");
	}

	static bool IsClientValid(int client)
	{
		return client > 0 && client <= PM::GetMaxClients() &&
			PM::IsClientInGame(client);
	}

	static void HidePlayerFromScoreboard(int client, bool hide = true)
	{
		s_HiddenInScoreboard[client] = hide;
	}

	static void SetPlayerArmor(int client, int armorValue)
	{
		PM::SetEntProp(client, Prop_Send, "m_ArmorValue", armorValue); // TODO: Remove m_ArmorValue, use offset
	}

	static void SetPlayerHelmet(int client, bool helmet)
	{
		PM::SetEntData(client, Offset::m_bHasHelmet, helmet);
	}

	static void SetPlayerHeavyArmor(int client, bool hasHeavyArmor)
	{
		PM::SetEntProp(client, Prop_Send, "m_bHasHeavyArmor", hasHeavyArmor);
	}

	static void DisarmPlayer(int client)
	{
		int myWeaponsSize = PM::GetEntPropArraySize(client, Prop_Send, "m_hMyWeapons");
		for (int i = 0; i < myWeaponsSize; i += 4)
		{
			int item = PM::GetEntDataEnt2(client, Offset::m_hMyWeapons + i);
			if (item != -1)
			{
				PM::RemovePlayerItem(client, item);
				PM::AcceptEntityInput(item, "Kill");
			}
		}

		SetPlayerHeavyArmor(client, false);
		SetPlayerArmor(client, 0);
		SetPlayerHelmet(client, false);
	}

	static bool HasWeapon(int client, const char* weaponName)
	{
		int myWeaponsSize = PM::GetEntPropArraySize(client, Prop_Send, "m_hMyWeapons");
		char name[64];
		for (int i = 0; i < myWeaponsSize; i += 4)
		{
			int ent = PM::GetEntDataEnt2(client, Offset::m_hMyWeapons + i);
			if (ent != -1)
			{
				PM::GetEdictClassname(ent, name, sizeof(name));
				if (PM::StrEqualCaseSensitive(weaponName, name))
					return true;
			}
		}

		return false;
	}

	static void FadeUserMessage(int clients[], int clientCount, const int color[4], int flags = FADE_IN | FADE_STAYOUT | FADE_PURGE, int duration = INT_MAX, int holdtime = INT_MAX)
	{
		Handle message = PM::StartMessageEx(s_FadeUserMsgId, clients, clientCount);
		if (PM::GetUserMessageType() == UM_Protobuf)
		{
			ProtobufHandle pb = PM::UserMessageToProtobuf(message);
			PM::PbSetInt(pb, "duration", duration);
			PM::PbSetInt(pb, "hold_time", holdtime);
			PM::PbSetInt(pb, "flags", flags);
			PM::PbSetColor(pb, "clr", color);
		}
		else
		{
			BfWriteHandle bf = PM::UserMessageToBfWrite(message);
			PM::BfWriteShort(bf, duration);
			PM::BfWriteShort(bf, holdtime);
			PM::BfWriteShort(bf, flags);
			PM::BfWriteByte(bf, color[0]);
			PM::BfWriteByte(bf, color[1]);
			PM::BfWriteByte(bf, color[2]);
			PM::BfWriteByte(bf, color[3]);
		}

		PM::EndMessage();
	}
private:
	static void OnThinkPostCSPlayerManager(int manager)
	{
		int isConnected[65];
		int isConnectedOffset = PM::FindSendPropInfo("CPlayerResource", "m_bConnected");
		PM::GetEntDataArray(manager, isConnectedOffset, isConnected, 65);
		for (int i = 1; i <= PM::GetMaxClients(); ++i)
			if (PM::IsClientInGame(i))
				isConnected[i] = !s_HiddenInScoreboard[i - 1];
		PM::SetEntDataArray(manager, isConnectedOffset, isConnected, 65);
	}
private:
	static bool s_HiddenInScoreboard[MAXPLAYERS];

	static int s_FadeUserMsgId;

	friend class Plugin;
};
