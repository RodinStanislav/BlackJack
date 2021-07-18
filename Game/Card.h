#pragma once

#include <string>

class Card {
public:
	enum class Nominal {
		_2 = 2, 
		_3,
		_4,
		_5,
		_6, 
		_7,
		_8,
		_9,
		_10,

		J,
		D,
		K,
		A
	};

	enum class Suit {
		Spades = 's',
		Hearts = 'h',
		Clubs = 'c',
		Diamonds = 'd'
	};

	Card(Nominal, Suit, bool = true);

	Nominal getNominal() const;
	Suit getSuit() const;
	void flip();
	bool isFilpped() const;

private:
	Nominal m_nominal;
	Suit m_suit;
	bool m_isFlipped;
};

std::string GetCardNominalString(Card::Nominal);
std::string GetCardSuitString(Card::Suit);