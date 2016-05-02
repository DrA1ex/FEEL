#pragma unmanaged

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <tchar.h>

void initDllImport()
{
#if defined(_M_IX86) || defined(__i386__)
	const TCHAR* libSubFolderPart = TEXT("x86;");
#else
	const TCHAR* libSubFolderPart = TEXT("x64;");
#endif

	const TCHAR* pathEnvName = TEXT("Path");

	TCHAR newSearchPath[4096];
	::GetModuleFileName(NULL, newSearchPath, sizeof(newSearchPath) * sizeof(newSearchPath[0]));

	LPTSTR pos = _tcsrchr(newSearchPath, TEXT('\\'));
	if (pos)
	{
		*(pos + 1) = TEXT('\0');

		//append bin
		_tcscat_s(newSearchPath, MAX_PATH, libSubFolderPart);
		size_t length = _tcslen(newSearchPath);

		//append existing Path
		::GetEnvironmentVariable(pathEnvName, newSearchPath + length, 4096 - length);
		::SetEnvironmentVariable(pathEnvName, newSearchPath);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		initDllImport();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}
