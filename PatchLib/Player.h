#pragma once
#include "GameState.h"

class Player
{
public:
	Player() {};
	virtual ~Player() {};
	virtual void Init(int player_index) { m_player_index = player_index; };
	virtual void TakeTurn(const GameState &state, Action& out_action) = 0;

public:
	int m_player_index;
};

