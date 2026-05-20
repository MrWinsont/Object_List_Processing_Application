#pragma once

#include <iostream>

class Cli
{
public:
	void Run();

private:
	bool work = true;

	void showStartMenu();

	void processCommand(int choice);
};
