#pragma once

#include <utility>
#include <vector>
#include <memory>


typedef std::vector<std::vector<bool>> PatchBitmap;

class Patch
{
public:
	Patch(PatchBitmap &bitmap, int cost_buttons, int cost_time, int revenue);
	~Patch();

	friend std::ostream& operator<<(std::ostream& os, Patch const& p);
	std::unique_ptr<PatchBitmap> GetBitmap(int rot);
	bool IsBitmapEqual(PatchBitmap const& bmap);

	std::pair<int,int> m_size;	

private:
	PatchBitmap m_bitmap;
	int m_cost_buttons;
	int m_cost_time;
	int m_revenue;
	
};

struct PatchPlacement
{
	std::shared_ptr<Patch> patch_p;
	int pos_x;
	int pos_y;
	int rot;	
};
