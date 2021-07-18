#pragma once

#include <vector>
#include <utility>
#include <string>

class GenericPlayer;
enum class PlayerAlignment;

class Game {
public:
	void start();
	void run();

private:
	void init(const std::string& playerName);
	void printMap(bool choose) const;
	void playerAITurn(std::size_t index);
	void playerTurn();
	void dillerTurn();
	void restart();
	void showResult() const;
	std::string showStartScreen() const;

	std::vector<std::pair<GenericPlayer*, PlayerAlignment>> m_players;
};