#pragma once

#include "PublicManager.h"

#include <unordered_map>

class Timer
{
public:
	using NewTimerCallbackFunc = Action(*)(Timer* timer, void* data);
public:
	Timer()
		: mTimer(INVALID_HANDLE), mInterval(0.0f), mCallback(nullptr), mData(nullptr), mElapsedTime(0.0f), mDeleteData(false) {}

	Timer(float interval, NewTimerCallbackFunc callback, void* data = nullptr, int flags = 0, bool deleteData = false)
		: mInterval(interval), mCallback(callback), mData(data), mElapsedTime(0.0f), mDeleteData(deleteData)
	{
		mTimer = PublicManager::CreateTimer(interval, Timer::OnTimerTick, data, flags);
		sTimers[mTimer] = this;
	}

	Timer(const Timer& other) = delete;
	Timer(Timer&& other) noexcept
		:
		mTimer(std::move(other.mTimer)),
		mInterval(std::move(other.mInterval)),
		mCallback(std::move(other.mCallback)),
		mData(std::move(other.mData)),
		mElapsedTime(std::move(other.mElapsedTime)),
		mDeleteData(std::move(other.mDeleteData))
	{
		sTimers[mTimer] = this;
	}

	Timer& operator=(const Timer& other) = delete;
	Timer& operator=(Timer&& other) noexcept
	{
		if (this == &other)
			return *this;

		mTimer = std::move(other.mTimer);
		mInterval = std::move(other.mInterval);
		mCallback = std::move(other.mCallback);
		mData = std::move(other.mData);
		mElapsedTime = std::move(other.mElapsedTime);
		mDeleteData = std::move(other.mDeleteData);
		sTimers[mTimer] = this;

		return *this;
	}

	~Timer() = default;

	void Kill(bool autoClose = false, bool deleteData = false)
	{
		PublicManager::KillTimer(mTimer, autoClose);
		mTimer = INVALID_HANDLE;
		if (deleteData)
			delete mData;
	}

	bool IsValid() const { return mTimer != INVALID_HANDLE; }
	Handle GetHandle() const { return mTimer; }
	float GetInterval() const { return mInterval; }
	void* GetData() const { return mData; }
	float GetElapsedTime() const { return mElapsedTime; }

	operator bool() const { return IsValid(); }

	static Action OnTimerTick(Handle handle, void* data)
	{
		Timer* timer = sTimers[handle];
		Action res = timer->mCallback(timer, data);
		if (res == Plugin_Stop)
		{
			sTimers[handle] = INVALID_HANDLE;
			timer->mTimer = INVALID_HANDLE;
			if (timer->mDeleteData)
				delete timer->mData;
			return Plugin_Stop;
		}

		return res;
	}
private:
	Handle mTimer;
	float mInterval;
	NewTimerCallbackFunc mCallback;
	void* mData;
	float mElapsedTime;
	bool mDeleteData;
private:
	static std::unordered_map<Handle, Timer*> sTimers;
};
