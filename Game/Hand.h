#pragma once

#include <vector>
#include "Card.h"

class Hand {
public:
	Hand();

	std::size_t getScore() const;
	void add(const Card&);
	void clear();
	Card& operator[](std::size_t);
	const Card& operator[](std::size_t) const;
	std::size_t size() const;

private:
	std::vector<Card> m_cards;
};