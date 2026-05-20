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
	case 2:
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
