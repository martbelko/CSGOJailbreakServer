#pragma once

#include "BasePlugin.h"

using P = PublicManager;

class Plugin : public BasePlugin
{
public:
	virtual void OnPluginStart() override;

	virtual void OnClientPutInServer(int client) override;

	Action OnEventHookPre(EventHandle eventHandle, const char* name, bool dontBroadcast);
	Action OnEventHookPost(EventHandle eventHandle, const char* name, bool dontBroadcast);
	Action ConCmdCallback(int client, std::string& command, int argc);
};
