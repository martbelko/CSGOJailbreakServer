#include "Blind.h"

float BlindAbility::sRemainingBlindTime;
Handle BlindAbility::sTimer = INVALID_HANDLE;
BlindAbilityCallback* BlindAbility::sCallbackClass;
bool BlindAbility::sBlinded[MAXPLAYERS];
