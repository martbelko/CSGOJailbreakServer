#include "LastRequestMenuManager.h"

#include "Plugin/LastRequest/LastRequest.h"

std::vector<LastRequest*> LastRequestMenuManager::sLastRequests;

Menu LastRequestMenuManager::sMainMenus[MAXPLAYERS];

void LastRequestMenuManager::Init(std::vector<LastRequest*>& lastRequests)
{
	sLastRequests = std::move(lastRequests);
}

void LastRequestMenuManager::Shutdown()
{
	for (Menu& menu : sMainMenus)
		menu.Delete();
}

void LastRequestMenuManager::RefreshItemsForClient(int client, const char* title)
{
	Menu& menu = sMainMenus[client - 1];
	menu.SetTitle(title);
	menu.RemoveAllItems();
	for (const LastRequest* lastRequest : sLastRequests)
	{
		const char* defaultName = lastRequest->GetName();
		char translatedName[64];
		PM::Format(translatedName, sizeof(translatedName), "%T", client, translatedName);
		menu.AddItem(translatedName);
	}
}

void LastRequestMenuManager::DisplayMenuForClient(int client)
{

}
