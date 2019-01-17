#pragma once

#include "Patch.h"
#include "PlayerBoard.h"
#include "PatchList.h"

class GameModel
{
public:
	GameModel(int num_players);
	~GameModel();	
	
	std::shared_ptr<Patch> getNextPatch();

private:

	PatchList m_patchlist;
	std::vector<PlayerBoard> m_boards;
	int m_num_players;
};

