
#pragma once

#define DLL_EXPORTS extern "C" __declspec(dllexport)


DLL_EXPORTS char * GetInfo();
DLL_EXPORTS char * GetCommand();
DLL_EXPORTS char * ExecuteCommand(const char * command);
DLL_EXPORTS void Config();
DLL_EXPORTS char * GetUsage();


