#include "WheelOfFortune.h"

#include "Plugin/Plugin.h"

Timer WheelOfFortune::sTimer[MAXPLAYERS];
float WheelOfFortune::sRemainingTime[MAXPLAYERS];
WheelOfFortune::WheelOfFortuneCallback* WheelOfFortune::sCallbackClass;

Action WheelOfFortune::OnTimerTick(Timer*, void* data)
{
	int client = reinterpret_cast<int>(data);
	if (sRemainingTime[client - 1] <= 0.0f)
	{
		std::vector<ShopItem>& items = Plugin::GetTShop().GetItems();

		std::vector<int> usableItems;
		for (int i = 0; i < static_cast<int>(items.size()); ++i)
		{
			VipMode vipMode = items[i].GetVipMode();
			if (vipMode <= VIPManager::GetClientVipMode(client))
				usableItems.push_back(i);
		}

		int randIndex = PM::GetRandomInt(0, usableItems.size() - 1);
		sCallbackClass->OnEnd(client, &items[randIndex]);
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
	return nullptr;
}
