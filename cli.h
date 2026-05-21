#pragma once

#include <iostream>

#include "ObjectManager.h"
#include <cstdlib>

class Cli
{
public:
	void Run();

private:
	bool work = true;
	ObjectManager objsManager = ObjectManager();

	void showStartMenu();

	void clearConsole(){
		std::system("cls");
	}

	void readObjectsChoice() {
		objsManager.LoadFromFile("objects.txt");
		objsManager.PrintObjects();
	}

	void addObjectChoice();

	void groupObjectsChoice() {};

	void processCommand(int choice);
};
