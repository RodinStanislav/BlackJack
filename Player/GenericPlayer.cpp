#include "GenericPlayer.h"

GenericPlayer::GenericPlayer(const std::string& name) : m_name(name), m_isActivePlayer(true) {}

std::string GenericPlayer::getName() const {
	return m_name;
}

void GenericPlayer::addCard(const Card& card) {
	m_hand.add(card);
}

bool GenericPlayer::isBusted() const {
	return (m_hand.getScore() > 21);
}

std::size_t GenericPlayer::getScore() const {
	return m_hand.getScore();
}

bool GenericPlayer::isStopped() const {
	return !m_isActivePlayer;
}

void GenericPlayer::reset() {
	m_hand.clear();
	m_isActivePlayer = true;
}

const Hand& GenericPlayer::getHand() const {
	return m_hand;
}

void GenericPlayer::stop() {
	m_isActivePlayer = false;
}