#pragma once

#include <iostream>

#include "ObjectManager.h"

class Cli
{
public:
	void Run();

private:
	bool work = true;
	ObjectManager objsManager;

	void showStartMenu();

	void showGroupMenu();

	void clearConsole();

	void readObjectsChoice();

	void addObjectChoice();

	void groupObjectsChoice();

	void saveGroupChoice();

	void processCommand(int choice);
};
