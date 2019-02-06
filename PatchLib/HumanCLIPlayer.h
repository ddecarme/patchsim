#pragma once
#include "Player.h"

class HumanCLIPlayer :
	public Player
{
public:
	HumanCLIPlayer();
	~HumanCLIPlayer();

	void TakeTurn(const GameState& state, Action& out_action);
	void PlaceSparePatch(const GameState &state, Action& out_action);
};

