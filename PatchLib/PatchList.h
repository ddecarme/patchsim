#pragma once

#include <queue>
#include "Patch.h"
#include "json.hpp"

class PatchList
{
public:
	PatchList(std::string path);
	~PatchList();

	std::shared_ptr<Patch> getPatch(int offset);
	void removePatch(int offset);
	void advance(int offset);
	void reset(void);
	size_t numRemaining(void);

private:
	std::deque<std::shared_ptr<Patch>> m_patches;
	std::deque<std::shared_ptr<Patch>>::iterator m_head_iter;
	std::string m_res_path;

	void LoadPatches(std::string path);
	void AddPatch(nlohmann::json& j);
};

