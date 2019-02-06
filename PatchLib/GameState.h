#pragma once
#include "PatchList.h"
#include "GameTrack.h"
#include "PlayerState.h"
#include <vector>


struct GameState
{
	GameState(std::string patch_res_path, int num_players, int first_player) :
		m_patchlist(patch_res_path),
		m_track(num_players, first_player),
		m_player_states(num_players) {}
	PatchList m_patchlist;
	GameTrack m_track;
	std::vector<PlayerState> m_player_states;
};

struct Action
{
	enum Choice { PASS, TAKE_PATCH };
	Choice m_choice;

	// Parameters for the TAKE_PATCH option
	// TODO Could hide these with derived classes, but I don't think its necessary
	size_t patch_index;
	size_t patch_row_offset;
	size_t patch_col_offset;
	int patch_rot;
};
