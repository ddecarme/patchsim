#include "pch.h"
#include "Patch.h"
#include "GameModel.h"
#include "GameTrack.h"

using namespace std;

TEST(Grid, Basic) {
	Grid g(2, 3);
	std::vector<bool> bmap = { 1,0,1,0,1,0 };
	g.setData(bmap);
	EXPECT_EQ(g.at(0, 0), true);
	EXPECT_EQ(g.at(1, 2), false);

	g.set(1, 2, 1);
	EXPECT_EQ(g.at(1, 2), true);

	g.clear();
	EXPECT_EQ(g.at(1, 2), false);
}

TEST(Grid, Equality) {
	std::vector<bool> bmap1 = { 1,1,0,1};
	Grid g1(2, 2, bmap1);

	std::vector<bool> bmap2 = { 1,0,0,1 };
	Grid g2(2, 2, bmap2);
	EXPECT_FALSE(g1 == g2);

	std::vector<bool> bmap3 = { 1,1,0,1 };
	Grid g3(2, 2, bmap3);
	EXPECT_TRUE(g1 == g3);

	std::vector<bool> bmap4 = { 1,1,0,1,0,0 };
	Grid g4(2, 3, bmap4);	
	EXPECT_FALSE(g1 == g4);
}

TEST(Grid, Merge) {
	std::vector<bool> bmap_big = { 1,1,0,1,1,0,0,0,0 };
	Grid g_big(3, 3, bmap_big);

	std::vector<bool> bmap_small = { 0,1,1,1 };
	Grid g_small(2, 2, bmap_small);

	g_big.merge(g_small, 1, 1);

	std::vector<bool> bmap_expected = { 1,1,0,1,1,1,0,1,1 };
	Grid g_expected(3, 3, bmap_expected);

	EXPECT_TRUE(g_big == g_expected);
};

TEST(Grid, Intersect) {
	std::vector<bool> bmap_big = { 1,1,0,1,1,0,0,0,0 };
	Grid g_big(3, 3, bmap_big);

	std::vector<bool> bmap_small = { 0,1,1,1 };
	Grid g_small(2, 2, bmap_small);

	EXPECT_FALSE(g_big.checkIntersect(g_small, 1, 1));
	EXPECT_TRUE(g_big.checkIntersect(g_small, 1, 0));
}

TEST(Grid, Rotate) {
	Grid g_orig(2, 3, { 1,1,1,0,1,0 });	
	Grid g_expected(2, 3, { 1,1,1,0,1,0 });

	std::unique_ptr<Grid> g_rot;
	
	g_rot = g_orig.getRotation(0);
	EXPECT_TRUE(*g_rot == g_expected);

	Grid g_expected1(3, 2, { 0,1,1,1,0,1 });
	g_rot = g_orig.getRotation(1);
	EXPECT_TRUE(*g_rot == g_expected1);

	Grid g_expected2(2, 3, { 0,1,0,1,1,1 }); 
	g_rot = g_orig.getRotation(2);
	EXPECT_TRUE(*g_rot == g_expected2);

	Grid g_expected3(3, 2, { 1,0,1,1,1,0 });
	g_rot = g_orig.getRotation(3);
	EXPECT_TRUE(*g_rot == g_expected3);

}

TEST(Patch, Create) {
	Grid g(2, 2, { 1, 0, 1, 1 });

	Patch p(g, 0, 0, 0);
	EXPECT_TRUE(p.getGrid() == g);
	cout << p;
}

unique_ptr<PatchList> LoadPatchList(void)
{
	return make_unique<PatchList>("..\\res\\patches.txt");
}

TEST(PatchList, Load) {
	unique_ptr<PatchList> pl = LoadPatchList();
}

TEST(PatchList, Remaining) {
	unique_ptr<PatchList> pl = LoadPatchList();
	EXPECT_EQ(pl->numRemaining(), 4);
}

TEST(PatchList, Get) {
	unique_ptr<PatchList> pl = LoadPatchList();

	// The first patch doesn't get shuffled, so we can be sure of its properties
	shared_ptr<Patch> patch = pl->getPatch(0);
	EXPECT_EQ(patch->getCostButtons(), 1);
	EXPECT_EQ(patch->getCostTime(), 1);
	EXPECT_EQ(patch->getDividend(), 1);

	// Other patches are shuffled, so can't confirm much
	patch = pl->getPatch(1);
	EXPECT_TRUE(patch != nullptr);

	patch = pl->getPatch(20);
	EXPECT_TRUE(patch == nullptr);
}


TEST(PatchList, Advance) {
	unique_ptr<PatchList> pl = LoadPatchList();
	shared_ptr<Patch> patch0 = pl->getPatch(0);
	const Grid &g0 = patch0->getGrid();

	shared_ptr<Patch> patch1 = pl->getPatch(1);
	const Grid &g1 = patch1->getGrid();

	// Verify that advance by 0 does nothing
	pl->advance(0);
	EXPECT_TRUE(pl->getPatch(0)->getGrid() == g0);

	// Verify that advancing does work
	pl->advance(1);
	EXPECT_TRUE(pl->getPatch(0)->getGrid() == g1);
}


TEST(PatchList, Remove) {
	unique_ptr<PatchList> pl = LoadPatchList();
	EXPECT_EQ(pl->numRemaining(), 4);

	shared_ptr<Patch> patch1 = pl->getPatch(1);

	pl->removePatch(0);
	EXPECT_EQ(pl->numRemaining(), 3);

	// Verify that the head has advanced
	shared_ptr<Patch> patch2 = pl->getPatch(0);
	EXPECT_TRUE(patch2->getGrid() == patch1->getGrid());
}

TEST(PatchList, Wraparound) {
	unique_ptr<PatchList> pl = LoadPatchList();
	shared_ptr<Patch> patch_before = pl->getPatch(0);
	pl->advance(pl->numRemaining());
	shared_ptr<Patch> patch_after = pl->getPatch(0);
	EXPECT_TRUE(patch_before->getGrid() == patch_after->getGrid());
}

TEST(GameTrack, TurnOrder) {
	GameTrack gt(2, 0);
	EXPECT_EQ(gt.getActivePlayer(), 0);
	EXPECT_EQ(gt.getPlayerPosition(0), 0);
	EXPECT_EQ(gt.getPlayerPosition(1), 0);
	
	gt.advancePlayer(0, 1);
	EXPECT_EQ(gt.getActivePlayer(), 1);
	
	// Advance p1 to be even, still p1's turn
	gt.advancePlayer(1, 1);
	EXPECT_EQ(gt.getActivePlayer(), 1);

	gt.advancePlayer(1, 1);
	EXPECT_EQ(gt.getActivePlayer(), 0);

	gt.advancePlayer(0, 10);
	EXPECT_EQ(gt.getActivePlayer(), 1);
	EXPECT_EQ(gt.getPlayerPosition(0), 11);
	EXPECT_EQ(gt.getPlayerPosition(1), 2);
}

TEST(GameTrack, GameOver) {
	GameTrack gt(2, 0);
	EXPECT_FALSE(gt.isGameOver());

	gt.advancePlayer(0, 52);
	EXPECT_FALSE(gt.isGameOver());
	gt.advancePlayer(1, 52);
	EXPECT_FALSE(gt.isGameOver());
	gt.advancePlayer(1, 2);
	EXPECT_FALSE(gt.isGameOver());
	gt.advancePlayer(0, 1);
	EXPECT_TRUE(gt.isGameOver());
}

TEST(GameTrack, NextPlayer) {
	GameTrack gt(2, 0);

	gt.advancePlayer(0, 5);
	EXPECT_EQ(gt.getDistToNextPlayer(1), 5);
	gt.advancePlayer(1, 10);
	EXPECT_EQ(gt.getDistToNextPlayer(0), 5);
}

TEST(GameTrack, Milestones) {
	GameTrack gt(2, 0);
	EXPECT_FALSE(gt.buttonInRange(0, 4));
	EXPECT_FALSE(gt.spareInRange(0, 19));
	EXPECT_TRUE(gt.buttonInRange(0, 5));
	EXPECT_TRUE(gt.spareInRange(0, 20));

	gt.advancePlayer(0, 6);
	EXPECT_FALSE(gt.buttonInRange(0, 4));
	EXPECT_TRUE(gt.buttonInRange(0, 5));

	gt.advancePlayer(1, 3);
	EXPECT_FALSE(gt.buttonInRange(1, 1));
	EXPECT_FALSE(gt.buttonInRange(1, 2));
}
