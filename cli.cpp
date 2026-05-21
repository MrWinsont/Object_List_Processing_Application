#include "cli.h"

void Cli::Run() {
	while (work) {
		showStartMenu();
		int choice;
		std::cin >> choice;
		processCommand(choice);
	}
};

void Cli::showStartMenu() {
	std::cout << "\tObject List Processing Application\n";
	std::cout << u8"1. Прочитать список объектов из файла\n";
	std::cout << u8"2. Добавить объект в список\n";
	std::cout << u8"3. Группировать объекты\n";
	std::cout << u8"4. Сохранить результаты в файл\n";
	std::cout << u8"0. Выход\n";
	std::cout << u8"Выберите пункт из меню: ";
}

void Cli::processCommand(int choice) {
	switch (choice) {
	case 1:
		readObjectsChoice();
		break;
	case 2:
		addObjectChoice();
		break;
	case 3:
	case 4:
		std::cout << "entered: " << choice << "\n";
		break;

	case 0:
		work = false;
		break;
	default:
		std::cout << u8"некорректный выбор!" << choice << "\n";
		break;
	}
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

	std::cout << u8"Объект добавлен!\n";
}
