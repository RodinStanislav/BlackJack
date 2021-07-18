#include "Hand.h"

Hand::Hand() {}

std::size_t Hand::getScore() const {
	if (m_cards.size() == 2) {
		bool isBlackJack = (m_cards[0].getNominal() == Card::Nominal::A) &&
						   (m_cards[1].getNominal() == Card::Nominal::A);
		if (isBlackJack) {
			return 21;
		}
	}

	std::size_t score = 0;

	for (auto& card : m_cards) {
		if (!card.isFilpped()) {
			continue;
		}

		auto nom = static_cast<std::size_t>(card.getNominal());
		if (nom < 11) {
			score += nom;
			continue;
		}

		if (nom < 14) {
			score += 10;
			continue;
		}

		if (score < 21) {
			score += 11;
			continue;
		}

		score += 1;
	}

	return score;
}

void Hand::add(const Card& card) {
	m_cards.push_back(std::move(card));
}

void Hand::clear() {
	m_cards.clear();
}

Card& Hand::operator[](std::size_t index) {
	return m_cards[index];
}

std::size_t Hand::size() const {
	return m_cards.size();
}

const Card& Hand::operator[](std::size_t index) const {
	return m_cards[index];
}