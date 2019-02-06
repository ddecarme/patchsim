#include "GameModel.h"
#include <iostream>
#include <string>


GameModel::GameModel(int num_players) :
	m_num_players(num_players),
	m_players(num_players),
	m_state("res\\patches.txt", num_players, 0)	
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

void GameModel::advancePlayer(PlayerID player, int spaces)
{
	if (m_state.m_track.spareInRange(player, spaces)) {
		assert(0);
	}
	else if (m_state.m_track.buttonInRange(player, spaces)) {
		// Add the player's dividend to their number of buttons
		int dividend = m_state.m_player_states[player].getDividend();
		m_state.m_player_states[player].addButtons(dividend);		
	}

	m_state.m_track.advancePlayer(player, spaces);
}

void GameModel::startGame()
{
	using namespace std;
	log("Starting game now");

	while (!m_state.m_track.isGameOver()) {
		// Print player states
		for (int p = 0; p < m_num_players; p++) {
			cout << "Player " << p + 1 << " board:" << endl;
			cout << m_state.m_player_states[p] << endl;
		}

		// Print available patches
		cout << m_state.m_patchlist;

		// Print tracker state to console
		cout << m_state.m_track;

		// Determine which players' turn it is
		PlayerID cur_player = m_state.m_track.getActivePlayer();

		// Tell the player to take its turn and give us a resulting action
		Action player_action;
		m_players[cur_player]->TakeTurn(m_state, player_action);

		// Implement the player's action
		if (player_action.m_choice == Action::PASS) {
			cout << "Player PASSED" << endl;
			int steps = m_state.m_track.getDistToNextPlayer(cur_player) + 1;
			advancePlayer(cur_player, steps);
			m_state.m_player_states[cur_player].addButtons(steps);
		}
		else if (player_action.m_choice == Action::TAKE_PATCH) {
			cout << "Player took patch " << player_action.patch_index;

			// Pull the selected patch off the list, and advance the head pointer
			shared_ptr<Patch> p_patch = m_state.m_patchlist.getPatch(player_action.patch_index);
			m_state.m_patchlist.removePatch(player_action.patch_index);
#if 0
			// Add the patch to the player's grid, and subtract the cost
			m_state.m_player_states[cur_player].AddPlacement(player_action.m_placement);


			// Subtract the cost from the player's button count
			int cost = p_patch->getCostButtons();
			assert(m_state.m_player_states[cur_player].getButtons() >= cost);
			m_state.m_player_states[cur_player].addButtons(cost);
#endif

			// Advance on the game track
			advancePlayer(cur_player, p_patch->getCostTime());
			// TODO Add patch to player board
		}
		else {
			assert(0);
		}


	}

	// TODO Calculate scores and declare winner
}




