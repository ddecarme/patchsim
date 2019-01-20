#pragma once

#include <utility>
#include <vector>
#include <memory>
#include "Grid.h"


struct Patch
{
public:
	explicit Patch(const Grid &grid, int cost_buttons, int cost_time, int revenue);
	~Patch();

	friend std::ostream& operator<<(std::ostream& os, Patch const& p);
	const Grid& getGrid() const { return m_grid; };
	int getCostButtons();
	int getCostTime();
	int getDividend();
	
private:
	Grid m_grid;
	int m_cost_buttons;
	int m_cost_time;
	int m_dividend;
	
};

struct PatchPlacement
{
	std::shared_ptr<Patch> patch_p;
	int row_offset;
	int col_offset;
	int rot;	
};
