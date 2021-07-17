#pragma once

#include <cstdint>
#include <string>

struct Admin
{
	uint64_t id;
	std::string name;
	std::string steamID;
	int flags;
};
