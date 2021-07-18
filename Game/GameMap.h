#pragma once

enum class PlayerAlignment {
	Left,
	Right,
	Center,
	Diller
};

class GenericPlayer;

void PrintPlayer(const GenericPlayer&, PlayerAlignment);
void PrintChoose(bool isActive);
void ClearGameMap();