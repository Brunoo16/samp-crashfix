#include "pattern.h"

Pattern::Pattern(HANDLE process, HMODULE module_handle)
{
	MODULEINFO module_info = { NULL };

	GetModuleInformation(process, module_handle, &module_info, sizeof(MODULEINFO));

	this->base = reinterpret_cast<DWORD>(module_info.lpBaseOfDll);
	this->size = module_info.SizeOfImage;
}

DWORD Pattern::FindPattern(char *pattern, char *mask)
{
	DWORD patternLength = static_cast<DWORD>(strlen(mask));

	for (DWORD i = 0; i < this->size - patternLength; i++)
	{
		bool found = true;
		for (DWORD j = 0; j < patternLength; j++)
		{
			found &= mask[j] == '?' || pattern[j] == *reinterpret_cast<char*>((this->base + i + j));
		}

		if (found)
		{
			return this->base + i;
		}
	}
	return NULL;
}