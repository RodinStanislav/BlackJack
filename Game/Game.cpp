#include "Game.h"
#include "GameMap.h"
#include "../Player/PlayerAI.h"
#include "../Player/Player.h"
#include "../Player/Diller.h"
#include "../Utility/ConsoleManipulator.h"
#include "../Utility/MouseInputHandler.h"
#include "../Utility/Timer.h"

#include <iostream>

namespace {
	Card GetRandomCard() {
		Card::Nominal nominal = static_cast<Card::Nominal>((rand() % 13) + 2);
		Card::Suit suit;

		switch (rand() % 4)
		{
		case 0: suit = Card::Suit::Clubs; break;
		case 1: suit = Card::Suit::Diamonds; break;
		case 2: suit = Card::Suit::Hearts; break;
		case 3: suit = Card::Suit::Spades; break;
		}

		return Card(nominal, suit);
	}
}

void Game::start() {
	init(showStartScreen());
}

void Game::init(const std::string& playerName) {
	if (m_players.empty()) {
		GenericPlayer* juddy = new PlayerAI("Juddy");
		GenericPlayer* hue = new PlayerAI("Hue");
		GenericPlayer* player = new Player(playerName);
		GenericPlayer* diller = new Diller;

		m_players.push_back(std::pair<GenericPlayer*, PlayerAlignment>(juddy, PlayerAlignment::Left));
		m_players.push_back(std::pair<GenericPlayer*, PlayerAlignment>(hue, PlayerAlignment::Right));
		m_players.push_back(std::pair<GenericPlayer*, PlayerAlignment>(player, PlayerAlignment::Center));
		m_players.push_back(std::pair<GenericPlayer*, PlayerAlignment>(diller, PlayerAlignment::Diller));
	}
	else {
		for (auto& player : m_players) {
			player.first->reset();
		}
	}

	for (std::size_t i = 0; i < 3; i++) {
		m_players[i].first->addCard(GetRandomCard());
		m_players[i].first->addCard(GetRandomCard());
	}

	m_players[3].first->addCard(GetRandomCard());
	auto card = GetRandomCard();
	card.flip();
	m_players[3].first->addCard(card);
}

void Game::printMap(bool choose) const {
	ClearGameMap();
	for (auto& player : m_players) {
		PrintPlayer(*player.first, player.second);
	}

	PrintChoose(choose);
}

void Game::playerAITurn(std::size_t index) {
	static auto mouseInputHandle = MouseInputHandler::instance();
	Timer delay;

	printMap(false);

	delay.start();
	while (true) {
		if (delay.loop(0.8)) {
			mouseInputHandle.waitInputCursorPosition();

			if (m_players[index].first->isHitting()) {
				m_players[index].first->addCard(GetRandomCard());
			}
			else {
				printMap(false);
				break;
			}

			printMap(false);
		}
	}
}

void Game::playerTurn() {
	static auto mouseInputHandle = MouseInputHandler::instance();
	Timer delay;
	printMap(true);

	// hit me 
	// 90 480
	// 170 510

	// stop
	// 605 480
	// 685 510

	delay.start();
	while (true) {
		if (delay.loop(0.8)) {
			if (m_players[2].first->isBusted() == false) {
				mouseInputHandle.waitInputCursorPosition();
				auto cell = mouseInputHandle.getClickedCell();

				// hit me 
				if (cell.x >= 90 && cell.x <= 170) {
					if (cell.y >= 480 && cell.y <= 510) {
						m_players[2].first->addCard(GetRandomCard());
					}
				}

				// stop
				if (cell.x >= 605 && cell.x <= 685) {
					if (cell.y >= 480 && cell.y <= 510) {
						m_players[2].first->stop();
						printMap(true);
						break;
					}
				}
			}
			else {
				printMap(true);
				break;
			}

			printMap(true);
		}
	}
}

void Game::dillerTurn() {
	static auto mouseInputHandle = MouseInputHandler::instance();
	Timer delay;

	printMap(false);

	delay.start();
	while (true) {
		if (delay.loop(0.8)) {
			mouseInputHandle.waitInputCursorPosition();

			if (m_players[3].first->isHitting()) {
				m_players[3].first->addCard(GetRandomCard());
			}
			else {
				m_players[3].first->stop();
				printMap(false);
				break;
			}

			printMap(false);
		}
	}
}

void Game::run() {
	static auto mouseInputHandle = MouseInputHandler::instance();
	do {
		printMap(false);	

		playerAITurn(0);
		playerAITurn(1);
		playerTurn();
		dillerTurn();

		mouseInputHandle.waitInputCursorPosition();
		showResult();
		restart();

	} while (true);
}

void Game::restart() {
	init(m_players[2].first->getName());
}

void Game::showResult() const {
	static auto& consoleManipulator = ConsoleManipulator::instance();
	static auto mouseInputHandler = MouseInputHandler::instance();

	std::size_t countOfWinners = 0;
	std::string whoWin = "";
	std::size_t maxScore = 0;
	for (std::size_t i = 0; i < m_players.size(); i++) {
		auto player = m_players[i];
		if (player.first->getScore() > maxScore && 
			player.first->isBusted() == false) {
			whoWin = player.first->getName();
			maxScore = player.first->getScore();
			countOfWinners = 1;
			continue;
		}

		if (player.first->getScore() == maxScore && i != 3) {
			if (countOfWinners == 1) {
				whoWin = whoWin + " and " + player.first->getName();
				countOfWinners++;
			}
			else if (countOfWinners == 2) {
				whoWin = player.first->getName() + ", " + whoWin;
				countOfWinners = 1;
			}
		}
	}

	consoleManipulator.clear();
	int x = 40 - whoWin.length() / 2;
	consoleManipulator.setCursorPosition({ x, 20 });
	consoleManipulator.putString(whoWin + " win");

	Timer timer;
	timer.start();
	while (timer.getElapsedSeconds() < 3) {
		int i = 0;
	}
}

std::string Game::showStartScreen() const {
	static ConsoleManipulator& consoleManipulator = ConsoleManipulator::instance();

	std::string name;

	consoleManipulator.clear();
	consoleManipulator.setCursorPosition({ 30, 20 });
	consoleManipulator.putString("Enter the name: ");
	while (name == "") {
		std::cin >> name;
	}

	return name;
}