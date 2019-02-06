#pragma once
#include <vector>

typedef unsigned PlayerID;

class GameTrack
{
public:
	GameTrack(size_t num_players, PlayerID first_player);
	~GameTrack();

	int getPlayerPosition(PlayerID player_idx) const;
	PlayerID getActivePlayer() const;
	void advancePlayer(PlayerID player_idx, int steps);
	bool isGameOver() const;	
	bool buttonInRange(PlayerID player_idx, int steps) const;
	bool spareInRange(PlayerID player_idx, int steps) const;
	int getDistToNextPlayer(PlayerID player_idx) const;

	friend std::ostream& operator<<(std::ostream& os, GameTrack const& gt);
	
private:
	std::vector<int> m_player_loc;
	PlayerID m_cur_player;

	static bool checkRange(int start_loc, int end_loc, std::vector<int>::const_iterator iter_begin, std::vector<int>::const_iterator iter_end);
	void formatPlayerLine(PlayerID player_idx, std::string & str) const;
	bool checkSpace(int space_idx, std::vector<int> const & indexes) const;
	bool findNextPlayer(int start_loc, int end_loc, PlayerID *out_player) const;
	PlayerID getOtherPlayer(PlayerID player) const;
};

