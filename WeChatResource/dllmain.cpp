// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi")
#include "dllhijack.h"

VOID DllHijack(HMODULE hMod)
{
	TCHAR tszDllPath[MAX_PATH] = { 0 };

	GetModuleFileName(hMod, tszDllPath, MAX_PATH);
	PathRemoveFileSpec(tszDllPath);
	PathAppend(tszDllPath, TEXT("WeChatResource.dll.1"));

	SuperDllHijack(L"WeChatResource.dll", tszDllPath);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		DllHijack(hModule);
		FakeRevokeMsg();
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

