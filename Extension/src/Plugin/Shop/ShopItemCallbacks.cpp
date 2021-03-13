#include "ShopItemCallbacks.h"

#include "Plugin/Plugin.h"

void ShopItemCallback::TShopFortune(int client, const ShopItem* tItem)
{
	const std::vector<ShopItem>& items = Plugin::GetTShop().GetItems();

	std::vector<int> usableItems;
	for (int i = 0; i < items.size(); ++i)
	{
		VipMode vipMode = items[i].GetVipMode();
		if (vipMode <= VIPManager::GetClientVipMode(client))
			usableItems.push_back(i);
	}

	NotifyHud(client, sDefaultHoldTime, "%t", "GotWheelOfFortuneHud");
	char name[MAX_NAME_LENGTH];
	PublicManager::GetClientName(client, name, sizeof(name));
	NotifyTeamChat(CS_TEAM_T, client, "%t", "GotWheelOfFortuneChat", name);
}
