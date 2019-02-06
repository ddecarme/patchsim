#include "PlayerState.h"
#include <iostream>
#include <cassert>

#define PLAYER_BOARD_DIM 9

PlayerState::PlayerState() :
	m_grid(PLAYER_BOARD_DIM, PLAYER_BOARD_DIM),
	m_buttons(5),
	m_dividend(0),
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
	m_grid.merge(p.patch_p->getGrid(), p.row_offset, p.col_offset); // TODO rotations?

	assert(m_buttons >= p.patch_p->getCostButtons());
	m_buttons -= p.patch_p->getCostButtons();
	m_dividend += p.patch_p->getDividend();
}

int PlayerState::getButtons() const
{
	return m_buttons;
}

int PlayerState::getDividend() const
{
	return m_dividend;
}

void PlayerState::addButtons(int num)
{
	// TODO Probably not good to expose this in the public interface that is sent outside the library
	assert(m_buttons + num >= 0);
	m_buttons += num;
}

std::ostream& operator<<(std::ostream& os, PlayerState const& ps) {
	os << ps.m_grid << "Player has " << ps.m_buttons << " buttons in hand";
	if (ps.m_has_bonus) {
		os << ", and has the 7x7 bonus";
	}
	os << std::endl;
	return os;
}