#ifndef _PATTERN_H_
#define _PATTERN_H_

#include "dllmain.h"

class Pattern
{
	private:
		DWORD base;
		DWORD size;

	public:
		Pattern(HANDLE process, HMODULE module_handle);
		DWORD FindPattern(char *pattern, char *mask);
};

#endif
