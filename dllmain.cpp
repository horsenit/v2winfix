#include <Windows.h>
#include "patch.h"
#include "dinput8.h"

BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
#ifdef NDEBUG
		bool verbose = false;
#else
		bool verbose = true;
#endif
		HMODULE dinput8;
		wchar_t sys[MAX_PATH];
		GetSystemDirectory(sys, ARRAYSIZE(sys));
		wcscat_s(sys, L"\\dinput8.dll");
		dinput8 = LoadLibrary(sys);
		oDirectInput8Create = (tDirectInput8Create)GetProcAddress(dinput8, "DirectInput8Create");
		readSettings();
		applyPatch(verbose);
		if (verbose)
			MessageBoxA(NULL, "hey we did it", "yo", MB_OK);
	}
	return TRUE;
}