#pragma once

#include <queue>
#include "Patch.h"
#include "json.hpp"

class PatchList
{
public:
	PatchList(std::string path);
	~PatchList();

	std::shared_ptr<Patch> getPatch(size_t offset) const;
	void removePatch(size_t offset);
	void advance(int offset);
	void reset(void);
	size_t numRemaining(void) const;

private:
	// TODO: This should be a list, and needs to be circular
	std::list<std::shared_ptr<Patch>> m_patches;
	std::list<std::shared_ptr<Patch>>::iterator m_head_iter;
	std::string m_res_path;

	void LoadPatches(std::string path);
	void AddPatch(nlohmann::json& j);
	void shuffleList();
};

