
#include "includes.h"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

void set_clan_tag(const char *tag, const char *name);

void Misc::bunnyHop(){
		if (!menu->Toggles.bunnyhop)
			return;

		BYTE flags = *(BYTE*)(tm->GetLocalPlayer() + m_fFlags);
		if (GetAsyncKeyState(VK_SPACE)) {
			if (flags && (1 << 0)) {
				*(DWORD*)(tm->cDLL.dwBase + tm->offsets.dwForceJump) = 6;
				
			}
			else {
				*(DWORD*)(tm->cDLL.dwBase + tm->offsets.dwForceJump) = 4;
			}
		}
}

void Misc::radarHack() {

	if (!menu->Toggles.radar) return; 

	for (int i = 1; i < 64; i++)
	{
		if (*(int*)(tm->cDLL.dwBase + tm->offsets.dwEntityList + i * 0x10) == 0) continue;

		int dwEntity = dwEntity = *(int*)(tm->cDLL.dwBase + tm->offsets.dwEntityList + i * 0x10);

		bool dormant = *(BOOL*)(dwEntity + m_bDormant); 

		if (dormant) continue; 

		int pEntTeam = *(INT*)(dwEntity + m_iTeamNum); 

		if (pEntTeam == *(INT*)(tm->GetLocalPlayer() + m_iTeamNum)) continue;

		*(int*)(dwEntity + m_bSpotted) = 1; 
	}
}

void Misc::triggerBot() {
	if (!menu->Toggles.triggerbot) return;

	int lInCross = *(int*)(tm->GetLocalPlayer() + m_iCrosshairId) - 1;
	int lTeam = *(int*)(tm->GetLocalPlayer() + m_iTeamNum);
	DWORD tEntityBase = *(DWORD*)(tm->cDLL.dwBase + tm->offsets.dwEntityList + ((lInCross) * 0x10));
	int tEntityTeam = *(bool*)(tEntityBase + m_iTeamNum);
	bool tDormant = *(bool*)(tEntityBase + m_bDormant);

	if (GetAsyncKeyState(VK_MENU)) 
	{
		if ((lInCross > 0 && lInCross <= 64) && (tEntityBase != NULL) && (tEntityTeam != lTeam) && (!tDormant))
		{
			Sleep(55);
			*(int*)(tm->cDLL.dwBase + tm->offsets.dwForceAttack) = 6;
			Sleep(100);
		}
	}
}

void Misc::clantag() {
	std::string clantagText = "eternium.cc ";
	size_t clantagSize = clantagText.length();
	std::string spacesText(clantagSize, ' ');
	clantagText = spacesText + clantagText + spacesText;

	while (true) {
		if (tm->GetLocalPlayer() == NULL) continue;
		if (!menu->Toggles.clantag) continue;

		for (int i = 0; i < clantagSize * 2; i++) {
			if (!menu->Toggles.clantag) {
				set_clan_tag("", "");
				break;
			}
			std::string clantag = clantagText.substr(i, clantagSize);
			const char *cstr = clantag.c_str();
			set_clan_tag(cstr, "eternium.cc");
			if (i == clantagSize) {
				Sleep(2500);
			}
			else {
				Sleep(350);
			}
		}
		Sleep(5);
	}
}


void set_clan_tag(const char *tag, const char *name)
{
	unsigned char Shellcode[] =
		"\x51"
		"\x52"
		"\xB9\x00\x00\x00\x00"
		"\xBA\x00\x00\x00\x00"
		"\xE8\x00\x00\x00\x00"
		"\x83\x04\x24\x0A"
		"\x68\x00\x00\x00\x00"
		"\xC3"
		"\x5A"
		"\x59"
		"\xC3"
		"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
		"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

	static unsigned int SHELLCODE_SIZE = sizeof(Shellcode) - 0x21;
	unsigned int TAG_SIZE = (strlen(tag) > 15) ? 15 : strlen(tag);
	unsigned int NAME_SIZE = (strlen(name) > 15) ? 15 : strlen(name);
	unsigned int DATA_SIZE = TAG_SIZE + NAME_SIZE + 2;
	LPVOID pShellCodeAdress = VirtualAllocEx(
		tm->hProc,
		0,
		SHELLCODE_SIZE + DATA_SIZE,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE);

	DWORD tagAdress = (DWORD)pShellCodeAdress + SHELLCODE_SIZE;
	DWORD nameAdress = (DWORD)pShellCodeAdress + SHELLCODE_SIZE + TAG_SIZE + 1;
	//DWORD fnSetClanAddress = grabSig(m->eDll.dwBase, m->eDll.dwSize, (PBYTE) "\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15", (char*)("xxxxxxxxx")); //Engine.dll + 0x9AC90 0x895D0
	DWORD fnSetClanAddress = tm->eDLL.dwBase + dwSetClanTag;
	memcpy(Shellcode + 0x3, &tagAdress, sizeof(DWORD));
	memcpy(Shellcode + 0x8, &nameAdress, sizeof(DWORD));
	memcpy(Shellcode + 0x16, &fnSetClanAddress, sizeof(DWORD));
	memcpy(Shellcode + SHELLCODE_SIZE, tag, TAG_SIZE);
	memcpy(Shellcode + SHELLCODE_SIZE + TAG_SIZE + 1, name, NAME_SIZE);

	WriteProcessMemory(tm->hProc, pShellCodeAdress, Shellcode, SHELLCODE_SIZE + DATA_SIZE, 0);

	HANDLE hThread = CreateRemoteThread(tm->hProc, NULL, NULL, (LPTHREAD_START_ROUTINE)pShellCodeAdress, NULL, NULL, NULL);
	WaitForSingleObject(hThread, INFINITE);
	VirtualFreeEx(tm->hProc, pShellCodeAdress, 0, MEM_RELEASE);
}