#pragma once

#include "smsdk_ext.h"

class JailbreakExtension : public SDKExtension
{
public:
	//virtual bool SDK_OnLoad(char *error, size_t maxlen, bool late);
	//virtual void SDK_OnUnload();
	void SDK_OnAllLoaded() override;
	//virtual void SDK_OnPauseChange(bool paused);
	//virtual bool QueryRunning(char *error, size_t maxlen);
public:
#if defined SMEXT_CONF_METAMOD
	//virtual bool SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late);
	//virtual bool SDK_OnMetamodUnload(char* error, size_t maxlen);
#endif
};
