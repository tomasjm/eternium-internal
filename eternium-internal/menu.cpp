#include <iostream>
#include "menu.h"
#include <cstdio>
#include <Windows.h>
#include "includes.h"

void Menu::menuToggleBhop() {
	this->Toggles.bunnyhop = !this->Toggles.bunnyhop;
	this->printMenu();
}

void Menu::menuToggleRadar() {
	this->Toggles.radar = !this->Toggles.radar;
	this->printMenu();
}
void Menu::menuToggleTriggerBot() {
	this->Toggles.triggerbot = !this->Toggles.triggerbot;
	this->printMenu();
}
void Menu::menuToggleClantag() {
	this->Toggles.clantag = !this->Toggles.clantag;
	this->printMenu();
}
void Menu::menuToggleNoflash() {
	this->Toggles.noflash = !this->Toggles.noflash;
	this->printMenu();
}
void Menu::menuToggleGlowhack() {
	this->Toggles.glowhack = !this->Toggles.glowhack;
	this->printMenu();
}

void Menu::printMenu() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	system("cls");
	std::cout << "|------------------------------------------------------|" << std::endl;
	std::cout << "|                                                      |" << std::endl;
	std::cout << "|              ETERNIUM CS:GO LEGIT CHEAT              |" << std::endl;
	std::cout << "|                                                      |" << std::endl;
	std::cout << "|               private release 14-02-2019             |" << std::endl;
	std::cout << "|                                                      |" << std::endl;
	std::cout << "|                    Written by mtZ                    |" << std::endl;
	std::cout << "|                    internal beta                     |" << std::endl;
	std::cout << "|                                                      |" << std::endl;
	std::cout << "|                 http://eternium.cc                   |" << std::endl;
	std::cout << "|                                                      |" << std::endl;
	std::cout << "|------------------------------------------------------|" << std::endl << std::endl << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " > BunnyHop F1: ";
	if (this->Toggles.bunnyhop) {
		SetConsoleTextAttribute(hConsole, 10); 
		std::cout << "[ON]" << std::endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "[OFF]" << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " > Radar F2: ";
	if (this->Toggles.radar) {
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "[ON]" << std::endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "[OFF]" << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " > Triggerbot F3: ";
	if (this->Toggles.triggerbot) {
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "[ON]" << std::endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "[OFF]" << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " > Clantag Animado F4: ";
	if (this->Toggles.clantag) {
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "[ON]" << std::endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "[OFF]" << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " > NoFlash F5: ";
	if (this->Toggles.noflash) {
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "[ON]" << std::endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "[OFF]" << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << " > Glow F6: ";
	if (this->Toggles.glowhack) {
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "[ON]" << std::endl;
	}
	else {
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "[OFF]" << std::endl;
	}
	
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << std::endl << "Desactivar y quitar el cheat [END]" << std::endl;

	
}

void Menu::checkToggles() {
	if (GetAsyncKeyState(VK_F1)) {
		this->menuToggleBhop();
		Sleep(350);
	}
	if (GetAsyncKeyState(VK_F2)) {
		this->menuToggleRadar();
		Sleep(350);
	}
	if (GetAsyncKeyState(VK_F3)) {
		this->menuToggleTriggerBot();
		Sleep(350);
	}
	if (GetAsyncKeyState(VK_F4)) {
		this->menuToggleClantag();
		Sleep(350);
	}
	if (GetAsyncKeyState(VK_F5)) {
		this->menuToggleNoflash();
		Sleep(350);
	}
	if (GetAsyncKeyState(VK_F6)) {
		this->menuToggleGlowhack();
		Sleep(350);
	}
	if (GetAsyncKeyState(VK_END)) {
		this->disableToggles();
		Sleep(350);
	}
}
void Menu::disableToggles() {
	this->Toggles.disableToggles = true;
	this->Toggles.bunnyhop = false;
	this->Toggles.radar = false;
	this->Toggles.triggerbot = false;
	this->Toggles.clantag = false;
	this->Toggles.noflash = false;
	this->Toggles.glowhack = false;
	this->printMenu();
}