#include "PlayerAI.h" 

PlayerAI::PlayerAI(const std::string& name) : GenericPlayer(name) {}

bool PlayerAI::isHitting() {
	if (m_hand.getScore() >= 20) {
		m_isActivePlayer = false;
		return false;
	}

	if (m_hand.getScore() <= (21 - 11)) {
		return true;
	}

	auto valueToBlackJack = 21 - m_hand.getScore();
	double chance = 0;

	if (valueToBlackJack == 10) {
		chance = (12.0 / 13.0) * 1000;
		
	}

	if (valueToBlackJack == 9) {
		chance = (8.0 / 13.0) * 1000;
	}
	else {
		chance = (valueToBlackJack - 1) / 13;
	}

	m_isActivePlayer = !((rand() % 1000) > chance * 1000);

	return m_isActivePlayer;
}