#include "Player.h"

Player::Player(const std::string& name) : GenericPlayer(name) {}

bool Player::isHitting() {
	if (isBusted()) {
		m_isActivePlayer = false;
	}

	return m_isActivePlayer;
}