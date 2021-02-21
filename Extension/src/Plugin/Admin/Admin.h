#pragma once

class Admin
{
public:
	static bool IsClientAdmin(int client)
	{
		return client == 2;
	}
};
