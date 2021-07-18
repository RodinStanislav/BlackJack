#include "Diller.h"

Diller::Diller() : GenericPlayer("Diller") {}

bool Diller::isHitting() {
	if (!m_hand[1].isFilpped()) {
		m_hand[1].flip();
	}

	if (isBusted()) {
		m_isActivePlayer = false;
	}
    
	m_isActivePlayer = m_hand.getScore() < 17;

	return m_isActivePlayer;
}