#include "includes.h"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;


void Visuals::noFlash() {
	float flashopacity = 255.f;
	if (!menu->Toggles.noflash && flashopacity == 0.f) 
	{
		*(float*)(tm->GetLocalPlayer() + m_flFlashMaxAlpha) = 255.f;
		flashopacity = 255.f; 
		return; 
	}
	if (menu->Toggles.noflash)
	{
		if (*(float*)(tm->GetLocalPlayer() + m_flFlashMaxAlpha) > 0.0f)
		{
			*(float*)(tm->GetLocalPlayer() + m_flFlashMaxAlpha) = 0.0f; 
			flashopacity = 0.f; 
		}
	}
}

void Visuals::glowHack() {

	if (!menu->Toggles.glowhack) return;

	static DWORD objGlowArray = 0; // declare the static dword
	static int objCount = 0; // declare static integer

	//objGlowArray = tm->mRead<DWORD>(tm->cDLL.dwBase + dwGlowObjectManager); // Getting the dwGlowObject Array
	objGlowArray = *(DWORD*)(tm->cDLL.dwBase + tm->offsets.dwGlowObjectManager);
	objCount = *(DWORD*)(tm->cDLL.dwBase + tm->offsets.dwGlowObjectManager + 0x4); // Getting the object count its similar to the entity list loop

	if (objGlowArray == 0) return; // return when objGlowArray equals 0

	for (int i = 1; i < objCount; i++) // scanning through the object count
	{
		DWORD mObj = objGlowArray + i * sizeof(glow_t);
		glow_t vGlowObj = tm->mRead<glow_t>(mObj);

		if (tm -> mRead<int>(vGlowObj.dwBase + m_iHealth) <=0) continue;

		if (tm->mRead<bool>(vGlowObj.dwBase + m_bDormant)) continue;

		DWORD dwClientNetworkable = tm->mRead<int>(vGlowObj.dwBase + 0x8); // IClientNetworkable VTABLE Location
		DWORD dwGetClientClassFn = tm->mRead<int>(dwClientNetworkable + 2 * 0x4); // Third function in the vtable /GetClientClass/
		DWORD dwEntityClientClass = tm->mRead<int>(dwGetClientClassFn + 1); //pointer to ClientClass struct

		if (!tm->mRead<int>(dwEntityClientClass + 0x14) == 38) continue; // Player is 38 now thx nci love u // CCSPlayer(DT_CSPlayer):110 1709 == 38

		if (tm->mRead<int>(tm->GetLocalPlayer() + m_iTeamNum) == tm->mRead<int>(vGlowObj.dwBase + m_iTeamNum)) {
			//vGlowObj.r = .176f; // setting Red color in glow
		//vGlowObj.m_flGlowAlpha = 1.f; // setting Alpha in glow
		//vGlowObj.g = .015f; // setting green color in glow
		//vGlowObj.b = .337f; // setting blue color in glow
			vGlowObj.r = .0f; // setting Red color in glow
			vGlowObj.m_flGlowAlpha = 1.f; // setting Alpha in glow
			vGlowObj.g = .0f; // setting green color in glow
			vGlowObj.b = .75f; // setting blue color in glow
			vGlowObj.m_bRenderWhenOccluded = true; // writing that to true so glow will show through tha walls
			vGlowObj.m_bRenderWhenUnoccluded = false;
			vGlowObj.m_bFullBloomRender = false;
			vGlowObj.m_nGlowStyle = 0; // Standard glowstyle
		}
		else {
			//vGlowObj.r = .176f; // setting Red color in glow
		//vGlowObj.m_flGlowAlpha = 1.f; // setting Alpha in glow
		//vGlowObj.g = .015f; // setting green color in glow
		//vGlowObj.b = .337f; // setting blue color in glow
			vGlowObj.r = .75f; // setting Red color in glow
			vGlowObj.m_flGlowAlpha = 1.f; // setting Alpha in glow
			vGlowObj.g = .0f; // setting green color in glow
			vGlowObj.b = .0f; // setting blue color in glow
			vGlowObj.m_bRenderWhenOccluded = true; // writing that to true so glow will show through tha walls
			vGlowObj.m_bRenderWhenUnoccluded = false;
			vGlowObj.m_bFullBloomRender = false;
			vGlowObj.m_nGlowStyle = 0; // Standard glowstyle
		}


		tm->mWrite(mObj, vGlowObj); // writing our object
	}
}