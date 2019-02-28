#include "tomMem.h" 
#include "csgo.hpp"

HANDLE TomMem::GetProcessHandle(const char* process) {
	HANDLE hProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 proc;
	BOOL processList;
	bool success = false;
	proc.dwSize = sizeof(proc);
	do {
		if (!strcmp(proc.szExeFile, process)) {
			this->pid = proc.th32ProcessID;
			success = true;
			CloseHandle(hProc);
			break;
		}
	} while (Process32Next(hProc, &proc));
	if (success) {
		std::cout << "Handle creado correctamente." << std::endl;
	}
	else {
		std::cout << "Error al crear handle, proceso no encontrado." << std::endl;
	}
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->pid);
}

Module TomMem::GetModule(const char* moduleName) {
	Module foundModule;
	DWORD dwModuleBaseAddress;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->pid);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(MODULEENTRY32);
	bool success = false;
	do
	{
		if (!strcmp(mEntry.szModule, moduleName))
		{
			dwModuleBaseAddress = (DWORD)mEntry.modBaseAddr;
			foundModule.dwBase = dwModuleBaseAddress;
			foundModule.dwSize = mEntry.modBaseSize;
			success = true;
			break;
		}
	} while (Module32Next(hSnapshot, &mEntry));
	if (success) {
		std::cout << "Se ha conseguido el modulo " << moduleName << " correctamente: ";
		this->hcout<DWORD>(foundModule.dwBase);
	} else {
		std::cout << "Error al conseguir el modulo " << moduleName << std::endl;
	}
	return foundModule;
}

DWORD TomMem::GetLocalPlayer() {
	return *(DWORD*)(this->cDLL.dwBase + hazedumper::signatures::dwLocalPlayer);
}

TomMem::TomMem() {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	SetConsoleTitle(TEXT("eternium.cc by mtZ"));
	this->hProc = this->GetProcessHandle("csgo.exe");
	this->cDLL = this->GetModule("client_panorama.dll");
	this->eDLL = this->GetModule("engine.dll");
	this->getOffsets();
}

DWORD TomMem::FindPattern(const char *pattern, const char *mask)
{
	DWORD patternLength = (DWORD)strlen(mask);

	for (DWORD i = 0; i < this->cDLL.dwSize - patternLength; i++)
	{
		bool found = true;
		for (DWORD j = 0; j < patternLength; j++)
		{
			found &= mask[j] == '?' || pattern[j] == *(char*)(this->cDLL.dwBase + i + j);
		}
		if (found)
		{
			return this->cDLL.dwBase + i;
		}
	}
	return NULL;
}

void TomMem::getOffsets() {
	std::cout << "pattern scanning..." << std::endl;
	this->offsets.dwForceJump = *(DWORD*)(this->FindPattern("\x8B\x0D\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x02", "xx????xxxxxxx") + 2) - this->cDLL.dwBase;
	this->offsets.dwLocalPlayer = *(DWORD*)(this->FindPattern("\x8D\x34\x85\x00\x00\x00\x00\x89\x15\x00\x00\x00\x00\x8B\x41\x08\x8B\x48\x00", "XXX????XX????XXXXX?") + 3) + 0x4 - this->cDLL.dwBase;
	this->offsets.m_bDormant = *(DWORD*)(this->FindPattern("\x8A\x81\x00\x00\x00\x00\xC3\x32\xC0", "XX????XXx") + 2) + 0x8 - this->cDLL.dwBase;
	this->offsets.dwEntityList = *(DWORD*)(this->FindPattern("\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8", "x????xxxxx????xx") + 1) - this->cDLL.dwBase;
	this->offsets.dwForceAttack = *(DWORD*)(this->FindPattern("\x89\x0D\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x8B\xF2\x8B\xC1\x83\xCE\x04", "xx????xx????xxxxxxx") + 2) - this->cDLL.dwBase;
	this->offsets.dwGlowObjectManager = *(DWORD*)(this->FindPattern("\xA1\x00\x00\x00\x00\xA8\x01\x75\x4B", "x????xxxx") + 1) + 0x4 - this->cDLL.dwBase;
	std::cout << "success..." << std::endl;
}

