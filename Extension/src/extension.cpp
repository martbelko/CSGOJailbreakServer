#include "extension.h"

Sample g_Sample;		/**< Global singleton for extension's main interface */

SMEXT_LINK(&g_Sample);

using ConCmd = int (*)(int, int);

static int Callback(int client, int argc)
{
	rootconsole->ConsolePrint("CALLBACK");
	return 0;
}

static cell_t OnRoundStartPre(IPluginContext* pContext, const cell_t* params)
{
	rootconsole->ConsolePrint("PRE");
	return 0;
}

static cell_t OnRoundStartPost(IPluginContext* pContext, const cell_t* params)
{
	rootconsole->ConsolePrint("POST");

/*
// 	IPluginFunction* f = pContext->GetFunctionByName("public_RegConsoleCmd");
// 	f->PushString("sm_test");
// 	f->PushCell(*(int*)&Callback);
// 	f->PushString("WTF");
// 	f->PushCell(0);
// 	cell_t res;
// 	f->Execute(&res);
*/

	return 0;
}

static cell_t CMDCallback(IPluginContext* pContext, const cell_t* params)
{
	char* cmd;
	pContext->LocalToString(params[1], &cmd);
	char* args;
	pContext->LocalToString(params[2], &args);
	std::string r = std::string(cmd) + std::string(args);
	rootconsole->ConsolePrint("---------------");
	rootconsole->ConsolePrint(r.c_str());
	rootconsole->ConsolePrint("---------------");
	return 0;
}

IPluginFunction* RegConsoleCmdFunction = nullptr;

static cell_t OnPluginStart(IPluginContext* pContext, const cell_t* params)
{
	RegConsoleCmdFunction = pContext->GetFunctionByName("public_RegConsoleCmd");
	RegConsoleCmdFunction->PushString("sm_test");
	RegConsoleCmdFunction->PushString("Testing");
	RegConsoleCmdFunction->PushCell(0);
	cell_t res;
	RegConsoleCmdFunction->Execute(&res);

	return 0;
}

const sp_nativeinfo_t MyNatives[] =
{
	{ "native_OnRoundStartPre", OnRoundStartPre },
	{ "native_OnRoundStartPost", OnRoundStartPost },
	{ "native_CMDCallback", CMDCallback },
	{ "native_OnPluginStart", OnPluginStart },
	{ NULL, NULL }
};

void Sample::SDK_OnAllLoaded()
{
	sharesys->AddNatives(myself, MyNatives);
}
