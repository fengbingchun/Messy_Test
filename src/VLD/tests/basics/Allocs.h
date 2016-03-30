#pragma once
#include "LeakOption.h"

void AllocF(LeakOption type, bool bFree);

void AllocE(LeakOption type, bool bFree);

void AllocD(LeakOption type, bool bFree);

void AllocC(LeakOption type, bool bFree);

void AllocB(LeakOption type, bool bFree);

void AllocA(LeakOption type, bool bFree);

void Alloc(LeakOption type, bool bFree = false);

