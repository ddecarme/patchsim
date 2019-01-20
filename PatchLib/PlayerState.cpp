#include "PlayerState.h"
#include <iostream>
#include <cassert>

#define PLAYER_BOARD_DIM 9

PlayerState::PlayerState() :
	m_grid(PLAYER_BOARD_DIM, PLAYER_BOARD_DIM),
	m_buttons(5),
	m_has_bonus(false)
{
}

PlayerState::~PlayerState()
{
}

bool PlayerState::CheckPlacement(struct PatchPlacement& p)
{
	return false;
}

void PlayerState::AddPlacement(struct PatchPlacement& p)
{
	assert(m_grid.checkIntersect(p.patch_p->getGrid(), p.row_offset, p.col_offset) == false);
	m_grid.merge(p.patch_p->getGrid(), p.row_offset, p.col_offset);
	m_buttons -= p.patch_p->getCostButtons();
}
