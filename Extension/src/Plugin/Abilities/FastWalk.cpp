#include "FastWalk.h"

Timer FastWalk::sTimer[MAXPLAYERS];
float FastWalk::sRemainingTime[MAXPLAYERS];
FastWalk::FastWalkCallback* FastWalk::sCallbackClass;
