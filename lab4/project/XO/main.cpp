// XO.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "utils.h"
#include <iostream>


int main()
{
	setlocale(LC_ALL, "Russian");
	char c;
	std::cout << "Введите ваш символ (X или O или любой другой символ): " << std::endl;
	std::cin >> c;
	Game game = initGame(c);
	updateDisplay(game);
	while (!updateGame(&game)) {
		updateDisplay(game);
	}

	return 0;
}
