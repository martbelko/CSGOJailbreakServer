#pragma once

enum class VipMode
{
	NONE = 0,
	VIP,
	EXTRA_VIP
};

class VIPManager
{
public:
	static VipMode GetClientVipMode(int client)
	{
		// TODO: Implement through database
		return VipMode::VIP;
	}
};
