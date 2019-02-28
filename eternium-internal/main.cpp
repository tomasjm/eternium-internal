/*
	Autor: www.mtzgod.pw
	Discord: toM#7631
	Discord server: https://discord.gg/k6VZge 
*/

#include "includes.h"
#include <thread>

void checkToggles();
void unloadDll();
int main();

HANDLE hCheckToggles = checkToggles;
HANDLE hClanTag = misc->clantag;
HANDLE hMain = main;

HINSTANCE cheatDLL;

int main() {
	menu->printMenu();
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)hCheckToggles, NULL, NULL, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)hClanTag, NULL, NULL, NULL);
	while (true) {
		Sleep(1);
		if (tm->GetLocalPlayer() == NULL) continue;
		misc->bunnyHop();
		misc->radarHack();
		misc->triggerBot();
		visual->noFlash();
		visual->glowHack();
		Sleep(1);
	}
	return 0;
}

void checkToggles() {
	while (!menu->Toggles.disableToggles) {
		menu->checkToggles();
		Sleep(5);
	}
	// quitando el DLL.
	unloadDll();
}

void unloadDll() {
	std::cout << "quitando dll..." << std::endl;
	CloseHandle(hCheckToggles);
	std::cout << "quitando thread #1..." << std::endl;
	CloseHandle(hClanTag);
	std::cout << "quitando thread #2..." << std::endl;
	CloseHandle(hMain);
	std::cout << "quitando main thread" << std::endl;
	std::cout << "terminando..." << std::endl;
	std::cout << "ya puedes cerrar la consola" << std::endl;
	fclose(stdout);
	FreeConsole();
	ExitThread(1);
	FreeLibraryAndExitThread(LoadLibrary("eternium-internal.dll"),0);
}
BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)  // reserved
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		cheatDLL = hinstDLL;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)hMain, NULL, NULL, NULL);
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}