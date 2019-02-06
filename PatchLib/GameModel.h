#pragma once

#include "Patch.h"
#include "GameState.h"
#include "Player.h"


class GameModel
{
public:
	GameModel(int num_players);
	~GameModel();

	void addPlayer(int player_index, std::unique_ptr<Player> p);
	void startGame();

private:
	GameState m_state;
	int m_num_players;
	std::vector<std::unique_ptr<Player>> m_players;

	static void log(const std::string &&str);
	void advancePlayer(PlayerID player, int spaces);
};
