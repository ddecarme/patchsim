#include "GameModel.h"
#include <iostream>
#include <string>


GameModel::GameModel(int num_players) :
	m_num_players(num_players),
	m_state("..\\res\\patches.txt", num_players, 0)	
{

}

GameModel::~GameModel()
{
}

void GameModel::addPlayer(int player_index, std::unique_ptr<Player> p)
{
	// Don't add multiple players with the same index
	assert(!m_players[player_index]);
	m_players[player_index] = std::move(p);
	m_players[player_index]->Init(player_index);
}

void GameModel::log(const std::string&& str)
{
	using namespace std;
	cout << str << endl;
}

void GameModel::startGame()
{
	using namespace std;
	log("Starting game now");

	while (!m_state.m_track.isGameOver()) {
		// Determine which players' turn it is
		int cur_player = m_state.m_track.getNextPlayer();

		// Tell the player to take its turn and give us a resulting action
		cout << "Player " << cur_player << "'s turn" << endl;
		Action player_action;
		m_players[cur_player]->TakeTurn(m_state, player_action);

		// Implement the player's action
		switch (player_action.m_choice) {
		case Action::PASS:
			cout << "Player PASSED" << endl;

			break;

		case Action::TAKE_PATCH:
			cout << "Player took patch " << player_action.patch_index;
			break;
		}
	}
}




