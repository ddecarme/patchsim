#pragma once
#include <vector>

class GameTracker
{
public:
	GameTracker(int num_players, int first_player);
	~GameTracker();

	int getPlayerPosition(int player_idx) const;
	int getNextPlayer() const;
	void advancePlayer(int player_idx, int steps);
	bool isGameOver() const;	
	bool buttonInRange(int player_idx, int steps) const;
	bool spareInRange(int player_idx, int steps) const;
	
private:
	std::vector<int> m_player_loc;
	int m_cur_player;

	static bool checkRange(int start_loc, int end_loc, std::vector<int>::const_iterator iter_begin, std::vector<int>::const_iterator iter_end);
};

