#include "Patch.h"
#include <ostream>
#include <iostream>

using namespace std;

Patch::Patch(PatchBitmap &bitmap, int cost_buttons, int cost_time, int revenue) :
	m_bitmap(bitmap),
	m_cost_buttons(cost_buttons),
	m_cost_time(cost_time),
	m_revenue(revenue)
{
	m_bitmap = bitmap;
	m_size = { m_bitmap.size(), m_bitmap[0].size() };	
}


Patch::~Patch()
{	
}

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

bool Patch::IsBitmapEqual(PatchBitmap const& bmap)
{
	if (m_bitmap.size() != bmap.size() || m_bitmap[0].size() != bmap[0].size())
		return false;

	for (size_t i = 0; i < m_bitmap.size(); i++)
	{
		for (size_t j = 0; j < m_bitmap[0].size(); j++)
		{
			if (bmap[i][j] != m_bitmap[i][j])
			{
				return false;
			}
		}
	}

	return true;
}

std::ostream& operator<<(std::ostream& os, Patch const& p)
{
	for (auto vect_patch : p.m_bitmap)
	{
		for (bool bit : vect_patch)
		{
			os << bit ? "-" : "X";
		}
		os << std::endl;
	}
	os << std::endl;
	return os;
}
