#include "pch.h"

#include "nano64Bytes.h"

TEST(nano64BytesFile1, creation)
{
	{
		const auto ns{ nnstr::NanoString::make<64, "orange">() };
		EXPECT_EQ(*ns, 2);
	}
	{
		const auto ns{ nnstr::NanoString::make<64, "potato">() };
		EXPECT_EQ(*ns, 4);
	}
}