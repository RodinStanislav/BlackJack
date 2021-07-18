#pragma once

#include "../Game/Hand.h"

class GenericPlayer {
public:
	GenericPlayer(const std::string& name);
	std::string getName() const;
	void addCard(const Card& card);
	bool isBusted() const;

	virtual std::size_t getScore() const;
	void reset();

	virtual bool isHitting() = 0;
	bool isStopped() const;
	const Hand& getHand() const;
	void stop();

protected:
	Hand m_hand;
	std::string m_name;

	bool m_isActivePlayer;
};