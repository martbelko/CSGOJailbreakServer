#include "Invisibility.h"

Timer Invisibility::sTimer[MAXPLAYERS];
float Invisibility::sRemainingTime[MAXPLAYERS];
Invisibility::InvisibilityCallback* Invisibility::sCallbackClass;
