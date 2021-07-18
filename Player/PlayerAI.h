#pragma once

#include "GenericPlayer.h"

class PlayerAI : public GenericPlayer {
public:
	PlayerAI(const std::string& name);
	bool isHitting()override;
};