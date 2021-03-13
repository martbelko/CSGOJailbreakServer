#include "WheelOfFortune.h"

#include "Plugin/Plugin.h"

Action WheelOfFortune::OnTimerTick(Timer*, void* data)
{
	int client = reinterpret_cast<int>(data);
	if (sRemainingTime[client - 1] <= 0.0f)
	{
		const std::vector<ShopItem>& items = Plugin::GetTShop().GetItems();

		std::vector<int> usableItems;
		for (int i = 0; i < items.size(); ++i)
		{
			VipMode vipMode = items[i].GetVipMode();
			if (vipMode <= VIPManager::GetClientVipMode(client))
				usableItems.push_back(i);
		}

		sCallbackClass->OnEnd(client);
		sRemainingTime[client - 1] = 0.0f;
		return Plugin_Stop;
	}
	else
	{
		sCallbackClass->OnUpdate(client, sRemainingTime[client - 1]);
		sRemainingTime[client - 1] -= sTimerInterval;
	}

	return Plugin_Continue;
}

ShopItem* WheelOfFortune::GetRandomItem(int client)
{

}
