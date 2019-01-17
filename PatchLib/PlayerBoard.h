#pragma once
#include <array>
#include <vector>
#include "Patch.h"

#define PLAYER_BOARD_DIM 9

class PlayerBoard
{
public:
	PlayerBoard();
	~PlayerBoard();

	bool CheckPlacement(struct PatchPlacement& p);
	void AddPlacement(struct PatchPlacement& p);

private:
	std::array<std::array<bool, 9>, 9> m_bitmap;
	std::vector<struct PatchPlacement> m_placements;
};

