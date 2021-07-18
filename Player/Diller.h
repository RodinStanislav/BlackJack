#pragma once

#include "GenericPlayer.h"

class Diller : public GenericPlayer {
public:
	Diller();

	bool isHitting() override;
};