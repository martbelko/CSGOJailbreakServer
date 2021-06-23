#include "Ban.h"

Ban::Ban(uint64_t id, Type type, const std::string& reason, const PlayerInfo& playerInfo)
	: mID(id), mType(type), mReason(reason), mPlayerInfo(playerInfo)
{
}

uint64_t Ban::GetID() const
{
	return mID;
}

Ban::Type Ban::GetType() const
{
	return mType;
}

const std::string& Ban::GetReason() const
{
	return mReason;
}

const Ban::PlayerInfo& Ban::GetPlayerInfo() const
{
	return mPlayerInfo;
}
