#pragma once
class Menu {
public:
	struct FeatureToggles {
		bool bunnyhop = false;
		bool radar = false;
		bool triggerbot = false;
		bool clantag = false;
		bool noflash = false;
		bool glowhack = false;
		bool disableToggles = false;
	};
	
	FeatureToggles Toggles;
	void printMenu();
	void menuToggleBhop();
	void menuToggleRadar();
	void menuToggleTriggerBot();
	void menuToggleClantag();
	void menuToggleNoflash();
	void menuToggleGlowhack();
	void disableToggles();
	void checkToggles();
};
