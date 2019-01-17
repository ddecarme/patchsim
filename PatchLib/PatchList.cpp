#include "PatchList.h"
#include <fstream>
#include <iostream>

using namespace nlohmann;
using namespace std;

PatchList::PatchList(std::string path):
	m_res_path(path)
{
	LoadPatches(m_res_path);
}

PatchList::~PatchList()
{
}

void PatchList::LoadPatches(std::string path)
{
	// Open input file with patch definitions
	ifstream pfile;
	pfile.open(path);
	if (!pfile.good())
	{
		cout << "Error: Could not find patch file\n";
		exit(-1);
	}

	// Read in the file and parse to JSON
	json j;
	pfile >> j;
	pfile.close();

	// JSON is one big array of patch objects. Parse each patch element, and add to the deque
	for (json::iterator iter = j["patches"].begin(); iter != j["patches"].end(); iter++)
	{
		AddPatch(*iter);
	}

	// Shuffle the patches in the list. Leave the first patch (2x1 starter) in place
	random_shuffle(m_patches.begin() + 1, m_patches.end());

	m_head_iter = m_patches.begin();
}

void PatchList::AddPatch(json& j)
{
	// Read the simple elements 
	int width = j["width"].get<int>();
	int height = j["height"].get<int>();
	int cost_b = j["cost_buttons"].get<int>();
	int cost_t = j["cost_time"].get<int>();
	int div = j["dividend"].get<int>();

	// Read the 1-D JSON bit array into the 2-D vector
	vector<vector<bool>> bmap;
	int w = 0, h = 0;
	for (auto iter = j["map"].begin(); iter != j["map"].end(); iter++)
	{
		vector<bool> row;
		row.push_back((*iter > 0) ? true : false);
		w++;
		if (w == width)
		{
			bmap.push_back(row);
			w = 0;
			h++;
		}
	}

	// Construct the patch, and add to queue
	auto patch_p = std::make_shared<Patch>(bmap, cost_b, cost_t, div);
	m_patches.push_back(patch_p);
}

size_t PatchList::numRemaining(void)
{
	return m_patches.size();
}

shared_ptr<Patch> PatchList::getPatch(int offset)
{
	if (offset >= numRemaining())
	{
		return nullptr;
	}

	shared_ptr<Patch> patch_p = *(m_head_iter + offset);
	return patch_p;
}

void PatchList::removePatch(int offset)
{
	assert(offset < numRemaining());
	m_patches.erase(m_head_iter + offset);
	m_head_iter += offset;
}

void PatchList::advance(int offset)
{
	assert(offset < numRemaining());
	m_head_iter += offset;
}

void PatchList::reset(void)
{
	m_patches.clear();
	LoadPatches(m_res_path);
}
