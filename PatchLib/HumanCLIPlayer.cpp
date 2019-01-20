#include "HumanCLIPlayer.h"



HumanCLIPlayer::HumanCLIPlayer()
{
}


HumanCLIPlayer::~HumanCLIPlayer()
{
}

void HumanCLIPlayer::TakeTurn(const GameState & state, Action& out_action)
{
	out_action.m_choice = Action::PASS;
}
