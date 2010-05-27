
#pragma once

//#define DLL_EXPORTS extern "C" __declspec(dllexport)

int roll(int dice);
char * parse (const char * expr, int diceface=20);
int str2int(const char * str);

void CleanResult();


