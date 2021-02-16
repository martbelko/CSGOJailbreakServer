#include "Shop.h"

std::unordered_map<MenuHandle, Shop*> Shop::s_ShopHashmap;
std::array<int, MAXPLAYERS> Shop::s_PlayerPoints;
