#include "GameTracker.h"
#include <cassert>

// Constants from the game board
static const std::vector<int> BUTTON_LOCS = { 4,10,16,22,28,34,40,46,52 };
static const std::vector<int> SPARE_LOCS = { 19,25,31,43,49 };
static const int NUM_SPACES = 53;

GameTracker::GameTracker(int num_players, int first_player) :
	m_player_loc(num_players, 0),
	m_cur_player(first_player)
{
}


GameTracker::~GameTracker()
{
}

int GameTracker::getPlayerPosition(int player_idx) const
{
	return m_player_loc[player_idx];
}

int GameTracker::getNextPlayer() const
{
	return m_cur_player;
}

void GameTracker::advancePlayer(int adv_player, int steps)
{
	// We should only ever advance who the tracker thinks is the current player,
	// otherwise there's a logic bug somewhere
	assert(adv_player == m_cur_player);

	// Advance the location
	m_player_loc[adv_player] += steps;

	// Check if the current player has changed by iterating through
	// the other players and checking if their position is now lower
	int min_player_loc = m_player_loc[adv_player];
	for (size_t i = 0; i < m_player_loc.size(); i++) {
		// Skip the current player, we are looking at the other players
		if (i == m_cur_player) {
			continue;
		}

		// Find min location
		if (m_player_loc[i] < min_player_loc) {
			m_cur_player = i;
			min_player_loc = m_player_loc[i];
		}
	}

}

bool GameTracker::isGameOver() const
{	
	for (int location : m_player_loc) {
		if (location < NUM_SPACES) {
			return false;
		}
	}

	// All players are over the end space, so game is over
	return true;
}

bool GameTracker::checkRange(int start_loc, int end_loc,
	std::vector<int>::const_iterator iter_begin, std::vector<int>::const_iterator iter_end)
{
	// Not possible to get multiple patches/spares in one move, so this just returns a bool
	std::vector<int>::const_iterator iter;
	for (iter = iter_begin; iter != iter_end; iter++) {
		int loc = *iter;
		if (loc >= start_loc && loc < end_loc) {
			return true;
		}
	}

	return false;
}

bool GameTracker::buttonInRange(int player_idx, int steps) const
{
	return checkRange(player_idx, player_idx + steps, BUTTON_LOCS.cbegin(), BUTTON_LOCS.cend());
}

bool GameTracker::spareInRange(int player_idx, int steps) const
{
	return checkRange(player_idx, player_idx + steps, SPARE_LOCS.cbegin(), SPARE_LOCS.cend());
}
