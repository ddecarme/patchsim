#pragma once
#include "Patch.h"
#include "Grid.h"


class PlayerState
{
public:
	PlayerState();
	~PlayerState();

	bool CheckPlacement(struct PatchPlacement& p);
	void AddPlacement(struct PatchPlacement& p);

private:
	Grid m_grid;
	int m_buttons;
	bool m_has_bonus;
};

