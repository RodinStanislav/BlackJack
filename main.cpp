#include "Utility/ConsoleManipulator.h"
#include "Game/GameMap.h"
#include "Utility/ConsoleManipulator.h"
#include "Game/Game.h"

#include <iostream>

int main() {
	srand(time(nullptr));
	auto console = ConsoleManipulator::instance();
	console.setTextColor(ConsoleColor::White);
	console.setBackgroundColor(ConsoleColor::Black);

	auto game = Game();
	game.start();

	game.run();

	return EXIT_SUCCESS;
}