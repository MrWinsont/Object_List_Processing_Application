#pragma once

#include <iostream>

#include "ObjectManager.h"

class Cli
{
public:
	void Run();

private:
	bool work = true;
	ObjectManager objsManager = ObjectManager();

	void showStartMenu();

	void showGroupMenu();

	void clearConsole(){
		std::system("cls");
	}

	void readObjectsChoice() {
		objsManager.LoadFromFile("objects.txt");
		objsManager.PrintObjects();
	}

	void addObjectChoice();

	void groupObjectsChoice() {
		showGroupMenu();

		int groupChoice;
		std::cin >> groupChoice;
		switch (groupChoice) {
		case 1:
			objsManager.GroupByDistance();
			break;
		case 2:
			objsManager.GroupByTime();
			break;
		case 3:
			objsManager.GroupByName();
			break;
		case 4:
			objsManager.GroupByType();
			break;
		case 0:
			showStartMenu();
			break;
		default:
			std::cout << u8"некорректный выбор!" << groupChoice << "\n";
			break;
		}

		objsManager.PrintCurrentGroup();
	};

	void processCommand(int choice);
};
