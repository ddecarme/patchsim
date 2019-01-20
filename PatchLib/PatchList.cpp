#include "PatchList.h"
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>

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
	shuffleList();

	// Initialize the head pointer
	m_head_iter = m_patches.begin();
}

void PatchList::shuffleList()
{
	// Create an RNG for shuffle
	random_device rng;
	mt19937 urng(rng());

	// Save the first patch so we can start with it
	shared_ptr<Patch> first_patch = *m_patches.begin();
	m_patches.pop_front();

	// Need a temporary vector since we can't shuffle a list. 
	vector<shared_ptr<Patch>> v(m_patches.begin(), m_patches.end());
	std::shuffle(v.begin(), v.end(), urng);
	m_patches.assign(v.begin(), v.end());
	m_patches.push_front(first_patch);
}

void PatchList::AddPatch(json& j)
{
	// Read the simple elements 
	int width = j["width"].get<int>();
	int height = j["height"].get<int>();
	int cost_b = j["cost_buttons"].get<int>();
	int cost_t = j["cost_time"].get<int>();
	int div = j["dividend"].get<int>();

	// Read in the bitmap and convert to boolean for creating the grid
	vector<bool> bmap(height*width);
	transform(j["map"].begin(), j["map"].end(), bmap.begin(), [](int i) {return i > 0 ? true : false; });

	Grid g(height, width, bmap);

	// Construct the patch, and add to queue
	auto patch_p = std::make_shared<Patch>(g, cost_b, cost_t, div);
	m_patches.push_back(patch_p);
}

size_t PatchList::numRemaining(void) const
{
	return m_patches.size();
}

// Returns a pointer to the patch object at the given offset.
// Does not change the head pointer
// Returns null if the offset is greater than the number of 
// patches remaining.
shared_ptr<Patch> PatchList::getPatch(size_t offset) const
{
	// Return null if there aren't that many patches
	if (offset >= numRemaining()) {
		return nullptr;
	}

	// Local iterator so we don't change the head. Wrap if needed
	list<std::shared_ptr<Patch>>::const_iterator local_iter = m_head_iter;
	while (offset--) {
		if (++local_iter == m_patches.end()) {
			local_iter = m_patches.begin();
		}
	}

	return *local_iter;	
}

// Remove the patch specified at the offset and advance the head pointer
// to the element after it
void PatchList::removePatch(size_t offset)
{
	// No valid reason to have the offset wrap around multiple times when removing
	assert(offset < numRemaining());

	// Move up the head pointer to point at the patch to erase
	advance(offset);

	m_head_iter = m_patches.erase(m_head_iter);

	// Wrap to the beginning of the list if we removed the last patch
	if (m_head_iter == m_patches.end()) {
		m_head_iter = m_patches.begin();
	}		
}

void PatchList::advance(int offset)
{
	// Advance the head pointer by the number of elements specified in offset. Wrap around
	// to the front of the list if needed
	while (offset--) {
		if (++m_head_iter == m_patches.end()) {
			m_head_iter = m_patches.begin();
		}
	}	
}

void PatchList::reset(void)
{
	m_patches.clear();
	LoadPatches(m_res_path);
}
