#include "HumanCLIPlayer.h"
#include <iostream>


HumanCLIPlayer::HumanCLIPlayer()
{
}


HumanCLIPlayer::~HumanCLIPlayer()
{
}

void HumanCLIPlayer::TakeTurn(const GameState & state, Action& out_action)
{
	out_action.m_choice = Action::PASS;
	std::cout << "human passing" << std::endl;
}

void HumanCLIPlayer::PlaceSparePatch(const GameState & state, Action & out_action)
{
}
