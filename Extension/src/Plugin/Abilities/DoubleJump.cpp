#include "DoubleJump.h"

int DoubleJump::s_JumpCount[MAXPLAYERS];
int DoubleJump::s_LastButtons[MAXPLAYERS];
int DoubleJump::s_LastFlags[MAXPLAYERS];
bool DoubleJump::sEnabled[MAXPLAYERS];
