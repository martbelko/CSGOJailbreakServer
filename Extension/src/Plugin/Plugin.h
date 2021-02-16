#pragma once

#include "BasePlugin.h"
#include "Menu.h"

#include "Shop/Shop.h"
#include "VIP.h"

class Plugin : public BasePlugin
{
public:
	virtual void OnPluginStart() override;
	virtual void OnPluginEnd() override;

	virtual void OnClientPutInServer(int client) override;
private:
	static Action OnRoundStartPost(EventHandle eventHandle, const char* name, bool dontBroadcast);

	static void OnSpawnPost(int client);

	static Action CMDShopCallbackStatic(int client, std::string& command, int argc);
private:
	Shop m_TShop;
	Shop m_CTShop;

	Handle m_ShopDisableTimer = INVALID_HANDLE;
};
