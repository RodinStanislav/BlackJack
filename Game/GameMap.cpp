#include "GameMap.h"
#include "Card.h"
#include "Hand.h"
#include "../Player/GenericPlayer.h"
#include "../Utility/ConsoleManipulator.h"

namespace {
	const std::size_t cardSize = 7;
	const std::size_t maxWidth = 86;
	const std::size_t maxHeight = 25;

	Point2 GetPlayerHandPosition(const GenericPlayer& player, PlayerAlignment alignment) {
		auto cardsSize = player.getHand().size() * cardSize;

		switch (alignment)
		{
		case PlayerAlignment::Center: {	
			return Point2((maxWidth / 2) - cardsSize / 2, maxHeight);
		}
		case PlayerAlignment::Diller: {
			return Point2((maxWidth / 2) - cardsSize / 2, 4);
		}
		case PlayerAlignment::Left: {
			return Point2(4, 14);
		}
		case PlayerAlignment::Right: {
			return Point2(maxWidth - cardsSize - 4, 14);
		}
		}

		return Point2(0, 0);
	}

	Point2 GetPlayerInfoPosition(const GenericPlayer& player, PlayerAlignment alignment) {
		auto cardsSize = player.getHand().size() * cardSize;
		auto handPosition = GetPlayerHandPosition(player, alignment);
		switch (alignment)
		{
		case PlayerAlignment::Center: {
			std::size_t offset = (maxWidth / 2) - player.getName().length() /2 - 3;
			return Point2(offset, maxHeight + cardSize + 1);
		}
		case PlayerAlignment::Diller: {
			std::size_t offset = (maxWidth / 2) - player.getName().length() / 2 - 3;
			return Point2(offset, 1);
		}
		case PlayerAlignment::Left: {
			return Point2(handPosition.x, handPosition.y + cardSize + 1);
		}
		case PlayerAlignment::Right: {
			size_t offset = maxWidth - player.getName().length() - 9;
			return Point2(offset, handPosition.y + cardSize + 1);
		}
		}

		return Point2(0, 0);
	}

	void PrintCardInfo(const Card& card) {
		auto consoleManipulator = ConsoleManipulator::instance();
		auto currentTextColor = consoleManipulator.getTextColor();

		bool isRed = (card.getSuit() == Card::Suit::Hearts ||
					  card.getSuit() == Card::Suit::Diamonds);

		ConsoleColor color = isRed ? color = ConsoleColor::Red : 
									 color = ConsoleColor::Black;

		consoleManipulator.setTextColor(color);
		consoleManipulator.setBackgroundColor(ConsoleColor::White);

		if (card.isFilpped() == true) {
			consoleManipulator.putString(GetCardNominalString(card.getNominal()) + GetCardSuitString(card.getSuit()));
		}
		else {
			consoleManipulator.putString("XX");
		}

		consoleManipulator.setTextColor(currentTextColor);
	}


	void PrintCard(const Card& card, Point2 position) {
		auto consoleManipulator = ConsoleManipulator::instance();
		auto currentTextColor = consoleManipulator.getTextColor();
		auto currentBackground = consoleManipulator.getBackgroundColor();
	
		consoleManipulator.setBackgroundColor(ConsoleColor::White);
		consoleManipulator.setTextColor(ConsoleColor::Black);

		int y = position.y;

		std::string border;
		for (std::size_t i = 0; i < cardSize; i++) {
			border += "*";
		}

		consoleManipulator.setCursorPosition(position);
		consoleManipulator.putString(border);
		consoleManipulator.setCursorPosition({ position.x, y + 1 });
		consoleManipulator.putString("* ");

		PrintCardInfo(card);

		bool offset = card.getNominal() == Card::Nominal::_10;

		std::string topString;
		for (std::size_t i = 0; i < cardSize - 5 - offset; i++) {
			topString += " ";
		}

		consoleManipulator.setTextColor(ConsoleColor::Black);

		topString += "*";
		consoleManipulator.putString(topString);
		consoleManipulator.setCursorPosition({ position.x, y + 2 });
		y += 2;
		for (int i = 0; i < cardSize - 4; i++) {
			std::string space = "*";

			for (std::size_t i = 0; i < cardSize - 2; i++) {
				space += " ";
			}

			space += "*";

			consoleManipulator.putString(space);
			consoleManipulator.setCursorPosition({ position.x, y + i + 1 });
		}
		y += cardSize - 4;
		std::string bottomString = "*";

		for (std::size_t i = 0; i < cardSize - 5 - offset; i++) {
			bottomString += " ";
		}

		consoleManipulator.putString(bottomString);

		PrintCardInfo(card);

		consoleManipulator.setTextColor(ConsoleColor::Black);

		consoleManipulator.putString(" *");
		consoleManipulator.setCursorPosition({ position.x, y + 1 });
		consoleManipulator.putString(border);

		consoleManipulator.setTextColor(currentTextColor);
		consoleManipulator.setBackgroundColor(currentBackground);
	}

	void PrintHand(const Hand& hand, Point2 position) {
		auto consoleManipulator = ConsoleManipulator::instance();
		int x = position.x;

		for (std::size_t i = 0; i < hand.size(); i++) {
			PrintCard(hand[i], { x, position.y });
			x += cardSize;
		}
	}

	void PrintPlayerInfo(const GenericPlayer& player, Point2 position) {
		auto cardsSize = player.getHand().size() * cardSize;
		auto name = player.getName();
		auto score = player.getScore();

		auto consoleManipulator = ConsoleManipulator::instance();
		std::string playerInfoString = name + "(" + std::to_string(score) + ")";
		consoleManipulator.setCursorPosition(position);
		consoleManipulator.putString(playerInfoString);

		bool isBusted = player.isBusted();
		bool isBlackJack = (player.getScore() == 21);

		auto currentTextColor = consoleManipulator.getTextColor();
		consoleManipulator.setCursorPosition({ position.x + 1, position.y + 1 });

		if (isBusted) {
			consoleManipulator.setTextColor(ConsoleColor::LightRed);
			consoleManipulator.putString("BUSTED");
		}
		else if (isBlackJack) {
			consoleManipulator.setTextColor(ConsoleColor::LightGreen);
			consoleManipulator.putString("BlackJack!");
		}
		else if (player.isStopped()) {
			consoleManipulator.setTextColor(ConsoleColor::LightGray);
			consoleManipulator.putString("Stopped");
		}
		else {
			consoleManipulator.setTextColor(ConsoleColor::LightBlue);
			consoleManipulator.putString("Active");
		}
		consoleManipulator.setTextColor(currentTextColor);
	}
}


void PrintPlayer(const GenericPlayer& player, PlayerAlignment alignment) {
	auto consoleManipulator = ConsoleManipulator::instance();
	consoleManipulator.updateConsole();

	PrintHand(player.getHand(), GetPlayerHandPosition(player, alignment));
	PrintPlayerInfo(player, GetPlayerInfoPosition(player, alignment));
}

void PrintChoose(bool isActive) {
	auto consoleManipulator = ConsoleManipulator::instance();
	consoleManipulator.updateConsole();

	auto currentTextColor = consoleManipulator.getTextColor();
	
	ConsoleColor newColor;
	isActive ? newColor = ConsoleColor::White : newColor = ConsoleColor::DarkGray;
	consoleManipulator.setTextColor(newColor);

	consoleManipulator.setCursorPosition({ 12, 34 });
	consoleManipulator.putString("Hit me");

	std::string stopString = "Stop";
	int x = maxWidth - stopString.length() - 12;

	consoleManipulator.setCursorPosition({ x, 34 });
	consoleManipulator.putString(stopString);

	consoleManipulator.setTextColor(currentTextColor);
}

void ClearGameMap() {
	auto consoleManipulator = ConsoleManipulator::instance();
	consoleManipulator.clear();
}