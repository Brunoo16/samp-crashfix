#include "dllmain.h"

static void Thread()
{
	Pattern pattern(GetCurrentProcess(), GetModuleHandleA("samp.dll"));

	DWORD offset = NULL, OldProtect = NULL;

	offset = pattern.FindPattern("\xE8\x00\x00\x00\x00\x83\xC4\x14\xA1\x00\x00\x00\x00\x83\xF8\x0A\x7D\x0E\x40\xA3\x00\x00\x00\x00\xB8\x00\x00\x00\x00\xC2\x0C\x00", "x????xxxx????xxxxxxx????x????xxx") + 0x13;

	VirtualProtect((void*)offset, 5, PAGE_EXECUTE_READWRITE, &OldProtect);

	memset((void*)offset, 0x90, 5);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, 0, 0, 0);
	}
	return 1;
}