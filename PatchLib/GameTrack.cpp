#include "GameTrack.h"
#include <cassert>
#include <string>
#include <algorithm>

// Constants from the game board
static const std::vector<int> BUTTON_LOCS = { 4,10,16,22,28,34,40,46,52 };
static const std::vector<int> SPARE_LOCS = { 19,25,31,43,49 };
static const int NUM_SPACES = 53;

GameTrack::GameTrack(size_t num_players, PlayerID first_player) :
	m_player_loc(num_players, 0),
	m_cur_player(first_player)
{
}


GameTrack::~GameTrack()
{
}

int GameTrack::getPlayerPosition(PlayerID player_idx) const
{
	return m_player_loc[player_idx];
}

PlayerID GameTrack::getActivePlayer() const
{
	return m_cur_player;
}

PlayerID GameTrack::getOtherPlayer(PlayerID player) const
{
	// Only works for 2 players
	assert(m_player_loc.size() == 2);
	return player ^ 1;
}

int GameTrack::getDistToNextPlayer(PlayerID player_idx) const
{
	PlayerID other_player = getOtherPlayer(player_idx);
	return m_player_loc[other_player] - m_player_loc[player_idx];
}

// Get the first player on the board in the interval [start_loc, end_loc) scanning towards the end
// Returns true if a player is found, false otherwise
bool GameTrack::findNextPlayer(int start_loc, int end_loc, PlayerID *out_player) const
{
	// TODO Only one user, is this the best interface?
	int min_player_loc = end_loc;
	bool found = false;
	for (PlayerID i = 0; i < m_player_loc.size(); i++) {

		// Find min location
		int loc = m_player_loc[i];
		if (loc >= start_loc && loc < end_loc && loc < min_player_loc) {
			*out_player = i;
			min_player_loc = m_player_loc[i];
			found = true;
		}
	}
	return found;
}

void GameTrack::advancePlayer(PlayerID adv_player, int steps)
{
	// We should only ever advance who the tracker thinks is the current player,
	// otherwise there's a logic bug somewhere
	assert(adv_player == m_cur_player);

	// Advance the location
	int new_loc = m_player_loc[adv_player] + steps;

	// Cap the location at the end of the board
	m_player_loc[adv_player] = std::min(new_loc, NUM_SPACES);

	(void)findNextPlayer(0, m_player_loc[adv_player], &m_cur_player);

	// TODO Cleanup
#if 0
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
#endif
}

bool GameTrack::isGameOver() const
{	
	for (int location : m_player_loc) {
		if (location < NUM_SPACES) {
			return false;
		}
	}

	// All players are over the end space, so game is over
	return true;
}

bool GameTrack::checkRange(int start_loc, int end_loc,
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

bool GameTrack::checkSpace(int space_idx, std::vector<int> const &indexes) const {	
	auto iter = std::find(indexes.cbegin(), indexes.cend(), space_idx);
	return iter != indexes.cend();
}

bool GameTrack::buttonInRange(PlayerID player_idx, int steps) const
{
	return checkRange(player_idx, player_idx + steps, BUTTON_LOCS.cbegin(), BUTTON_LOCS.cend());
}

bool GameTrack::spareInRange(PlayerID player_idx, int steps) const
{
	return checkRange(player_idx, player_idx + steps, SPARE_LOCS.cbegin(), SPARE_LOCS.cend());
}

void GameTrack::formatPlayerLine(PlayerID player_idx, std::string &str) const
{
	str.insert(str.end(), m_player_loc[player_idx], ' ');
	str.push_back('0' + player_idx + 1);	
}

std::ostream& operator<<(std::ostream& os, GameTrack const& gt)
{
	// First line is the first player marker
	std::string line = ">";
	gt.formatPlayerLine(0, line);
	os << line << std::endl;

	// Second line is the game path, with @ for buttons and X for spare patches
	line.clear();
	line.push_back('>');
	for (int i = 0; i < NUM_SPACES; i++) {
		if (gt.checkSpace(i, BUTTON_LOCS)) {
			line.push_back('@');
		}
		else if (gt.checkSpace(i, SPARE_LOCS)) {
			line.push_back('X');
		}
		else {
			line.push_back('-');
		}
	}
	line.push_back('|');
	os << line << std::endl;

	// Third line is the second player marker (and any further players)
	line.clear();
	line.push_back('>');
	gt.formatPlayerLine(1, line);
	os << line << std::endl;

	// Print whose turn it is
	os << "Player " << gt.getActivePlayer() + 1 << "'s turn" << std::endl;

	return os;
}