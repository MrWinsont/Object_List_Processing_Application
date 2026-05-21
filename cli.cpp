#include "cli.h"
#include <chrono>
#include <thread>
#include <Windows.h>
#include <io.h> 
#include <fcntl.h>

void Cli::Run() {
	while (work) {
		try {
			showStartMenu();
			int choice;
			std::cin >> choice;
			processCommand(choice);
		}
		catch (const std::exception& ex) {
			std::cerr << ex.what() << "n";
		}
	}
};

void Cli::showStartMenu() {
	std::cout << u8"1. Прочитать список объектов из файла\n";
	std::cout << u8"2. Добавить объект в список\n";
	std::cout << u8"3. Группировать объекты\n";
	std::cout << u8"4. Сохранить результаты в файл\n";
	std::cout << u8"0. Выход\n";
	std::cout << u8"Выберите пункт из меню: ";
}

void Cli::showGroupMenu() {
	std::cout << u8"1. Сгруппировать по расстоянию\n";
	std::cout << u8"2. Сгруппировать по времнеи\n";
	std::cout << u8"3. Сгруппировать по имени\n";
	std::cout << u8"4. Сгруппироьвать по типу\n";
	std::cout << u8"0. Назад\n";
	std::cout << u8"Выберите пункт из меню: ";
};

void Cli::processCommand(int choice) {
	switch (choice) {
	case 1:
		clearConsole();
		readObjectsChoice();
		break;
	case 2:
		clearConsole();
		addObjectChoice();
		break;
	case 3:
		clearConsole();
		groupObjectsChoice();
		break;
	case 4:
		clearConsole();
		saveGroupChoice();
		break;

	case 0:
		work = false;
		break;
	default:
		std::cout << choice << u8" - некорректный выбор!" << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		clearConsole();
		break;
	}
}

void Cli::readObjectsChoice() {
	objsManager.LoadFromFile("objects.txt");
	if (objsManager.IsObjectListEmpty()) {
		std::cout << u8"Список объектов пуст!\n";
		return;
	}
	objsManager.PrintObjects();
}

void Cli::addObjectChoice() {
	ListObject obj;

	std::cout << u8"Добавление нового объекта\n";
	std::cout << u8"Имя: ";
	std::cin >> obj.name;

	std::cout << u8"Координата X: ";
	std::cin >> obj.x;

	std::cout << u8"Координата Y: ";
	std::cin >> obj.y;

	std::cout << u8"Тип объекта: ";
	std::cin >> obj.type;

	std::cout << u8"Время создания (timestamp): ";
	std::cin >> obj.timestamp;

	objsManager.Add(obj);

	clearConsole();
	std::cout << u8"Объект добавлен!\n";
}

void Cli::groupObjectsChoice() {
	if (objsManager.IsObjectListEmpty()) {
		std::cout << u8"Список объектов пуст!\n";
		return;
	}
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
		clearConsole();
		break;
	default:
		std::cout << groupChoice << u8" - некорректный выбор!" << "\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		clearConsole();
		groupObjectsChoice();
		break;
	}

	clearConsole();
	objsManager.PrintCurrentGroup();
};

void Cli::saveGroupChoice() {
	if (objsManager.IsGroupsEmpty()){
		std::cout << u8"Список групп пуст!\n";
		return;
	}	
	objsManager.Save("test_save.txt");
	std::cout << u8"Группировка успешно сохранена!\n";

}

void Cli::clearConsole() {
	std::system("cls");
}