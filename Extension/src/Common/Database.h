#pragma once

#include "Common/BanSystem/Ban.h"

#include <string_view>
#include <vector>

class Database
{
public:
	Database() = delete;

	static void ExecCommand(std::string_view command);

	// TODO: Remove
	static std::vector<Ban> mBans;
};
