#include "pch.h"
#include "Patch.h"
#include "GameModel.h"

using namespace std;

TEST(Patch, Create) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);

	std::vector<std::vector<bool>> bmap = { { 1,0 },{ 1,1 } };

	Patch p(bmap, 0, 0, 0);
	EXPECT_EQ(p.m_size.first, 2);
	EXPECT_EQ(p.m_size.second, 2);

	cout << p;
}



TEST(Patch, Equality) {
	PatchBitmap bmap_ref = { { 1,1,1 },{ 0,1,0 } };
	Patch p_orig(bmap_ref, 0, 0, 0);
	EXPECT_TRUE(p_orig.IsBitmapEqual(bmap_ref));

	PatchBitmap bmap_diff_size = { { 1,1,1 },{ 0,1,0 },{ 0,0,0 } };
	EXPECT_FALSE(p_orig.IsBitmapEqual(bmap_diff_size));

	PatchBitmap bmap_diff_val = { {1,1,1} , { 0,1,1 } };
	EXPECT_FALSE(p_orig.IsBitmapEqual(bmap_diff_val));
}


TEST(Patch, Rotation) {
	PatchBitmap bmap_orig = { { 1,1,1 },{ 0,1,0 } };
	Patch p_orig(bmap_orig, 0, 0, 0);
	PatchBitmap bmap_expected;

	auto bmap_rot = p_orig.GetBitmap(0);
	EXPECT_TRUE(p_orig.IsBitmapEqual(*bmap_rot));

	bmap_rot = p_orig.GetBitmap(1);
	Patch p_rot = Patch(*bmap_rot, 0, 0, 0);
	bmap_expected = { { 0,1 },{ 1,1 },{ 0,1 } };
	EXPECT_TRUE(p_rot.IsBitmapEqual(bmap_expected));

	bmap_rot = p_orig.GetBitmap(2);
	p_rot = Patch(*bmap_rot, 0, 0, 0);
	bmap_expected = { { 0,1,0 },{ 1,1,1 } };
	EXPECT_TRUE(p_rot.IsBitmapEqual(bmap_expected));

	bmap_rot = p_orig.GetBitmap(3);
	p_rot = Patch(*bmap_rot, 0, 0, 0);
	bmap_expected = { { 1,0 },{ 1,1 },{ 1,0 } };
	EXPECT_TRUE(p_rot.IsBitmapEqual(bmap_expected));
};

TEST(PatchList, Load) {
	PatchList pl("..\\res\\patches.txt");
}