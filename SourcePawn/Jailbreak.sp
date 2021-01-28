native int native_OnRoundStartPre();
native int native_OnRoundStartPost();
native int native_CMDCallback(char[] command, char[] args);
native int native_OnPluginStart();

public void OnPluginStart()
{
	HookEvent("round_start", OnRoundStartPre, EventHookMode_Pre);
	HookEvent("round_start", OnRoundStartPost, EventHookMode_Post);
	
	native_OnPluginStart();
}

public Action CMDCallback(int client, int argc)
{
	char cmd[32];
	GetCmdArg(0, cmd, sizeof(cmd));
	char args[255];
	GetCmdArgString(args, sizeof(args));
	native_CMDCallback(cmd, args);
}

public Action OnRoundStartPre(Handle event, const char[] name, bool dontBroadcast) { native_OnRoundStartPre(); }

public Action OnRoundStartPost(Handle event, const char[] name, bool dontBroadcast) { native_OnRoundStartPost(); }

public void public_PrintToChat(int client, const char[] message) { PrintToChat(client, message); }

public void public_PrintToChatAll(const char[] message) { PrintToChatAll(message); }

public void public_RegConsoleCmd(const char[] command, const char[] description, int flags) { RegConsoleCmd(command, CMDCallback, description, flags); }
