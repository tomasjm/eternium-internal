#pragma once
class Visuals {
public:
	struct glow_t {
		DWORD dwBase;
		float r;
		float g;
		float b;
		float m_flGlowAlpha;
		char m_unk[4];
		float m_flUnk;
		float m_flBloomAmount;
		float m_flUnk1;
		bool m_bRenderWhenOccluded;
		bool m_bRenderWhenUnoccluded;
		bool m_bFullBloomRender;
		char m_unk1;
		int m_nFullBloomStencilTestValue;
		int m_nGlowStyle;
		int m_nSplitScreenSlot;
		int m_nNextFreeSlot;
	};

	struct Color
	{
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE a;
	};
	void noFlash();
	void glowHack();
	void vChams();
};