#include "Card.h"

Card::Card(Nominal nominal, Suit suit, bool isFlipped) 
	: m_nominal(nominal), m_suit(suit), m_isFlipped(isFlipped) {}

Card::Nominal Card::getNominal() const {
	return m_nominal;
}

Card::Suit Card::getSuit() const {
	return m_suit;
}

void Card::flip() {
	m_isFlipped = !m_isFlipped;
}

bool Card::isFilpped() const {
	return m_isFlipped;
}

std::string GetCardNominalString(Card::Nominal nominal) {
	std::string outputString;
	auto nom = static_cast<std::size_t>(nominal);

	// 2 - 10
	if (nom < 11) {
		if (nom == 10) {
			return "10";
		}

		char c('0' + nom);
		outputString = c;
		return outputString;
	}

	// J - K
	switch (nominal)
	{
	case Card::Nominal::J: return "J";
	case Card::Nominal::D: return "D";
	case Card::Nominal::K: return "K";
	case Card::Nominal::A: return "A";
	}

	return "WTF?!";
}

std::string GetCardSuitString(Card::Suit suit) {
	std::string outputString;
	auto s = static_cast<char>(suit);
	outputString = s;
	return outputString;
}