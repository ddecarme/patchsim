#include "Patch.h"
#include "Grid.h"
#include <ostream>
#include <iostream>

using namespace std;

Patch::Patch(const Grid &grid, int cost_buttons, int cost_time, int revenue) :
	m_grid(grid),
	m_cost_buttons(cost_buttons),
	m_cost_time(cost_time),
	m_dividend(revenue)
{
}


Patch::~Patch()
{	
}

#if 0
std::unique_ptr<PatchBitmap> Patch::GetBitmap(int rot)
{
	auto bitm_p = make_unique<PatchBitmap>();

	// Alias rotations greater than 3 
	rot = rot % 4;

	int x = 0, y = 0;

	bool mybool = m_bitmap[0][0];

	if (rot == 0)
	{	
		for (size_t i = 0; i < m_bitmap.size(); i++)
		{
			for (size_t j = 0; j < m_bitmap[0].size(); j++)
			{
				(*bitm_p)[i][j] = m_bitmap[i][j];
			}
		}
	}
	else if (rot == 1)
	{
		for (size_t i = 0; i < m_bitmap[0].size(); i++)
		{
			for (size_t j = 0; j < m_bitmap.size(); j++)
			{
				(*bitm_p)[i][j] = m_bitmap[i][j];
			}
		}
	}
	else if (rot == 2)
	{
		for (size_t i = 0; i < m_bitmap[0].size(); i++)
		{
			for (size_t j = 0; j < m_bitmap.size(); j++)
			{
				(*bitm_p)[i][j] = m_bitmap[i][j];
			}
		}
	}
	else if (rot == 3)
	{
		for (size_t i = 0; i < m_bitmap[0].size(); i++)
		{
			for (size_t j = 0; j < m_bitmap.size(); j++)
			{
				(*bitm_p)[i][j] = m_bitmap[i][j];
			}
		}
	}

	return bitm_p;	
}
#endif

int Patch::getCostButtons()
{
	return m_cost_buttons;
}

int Patch::getCostTime()
{
	return m_cost_time;
}

int Patch::getDividend()
{
	return m_dividend;
}

std::ostream& operator<<(std::ostream& os, Patch const& p)
{
	os << p.m_grid << std::endl;
	return os;
}
