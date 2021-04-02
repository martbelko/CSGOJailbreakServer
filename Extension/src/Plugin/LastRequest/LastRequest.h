#pragma once

class LastRequest
{
	friend class LastRequestManager;
public:
	virtual void OnEnd(int loser, int winner) = 0;

	virtual int GetPlayerT() const = 0;
	virtual int GetPlayerCT() const = 0;
	virtual const char* GetName() const = 0;
protected:
	virtual ~LastRequest() = default;

};

class LastRequestManager
{
public:
	template<typename T, typename ... Args>
	static void Set(Args&& ... args)
	{
		sActiveLastRequest = new T(args...);
	}

	static void Unset(int loser = -1, int winner = -1);

	static LastRequest* GetActiveLastRequest() { return sActiveLastRequest; }

	static void OnPlayerDeath(int victim);
private:
	static LastRequest* sActiveLastRequest;
};
