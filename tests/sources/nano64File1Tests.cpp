#include "pch.h"

#include "nano64Bytes.h"

TEST(nano64BytesFile1, creation)
{
	{
		const auto ns{ nnstr::NanoString::make<size_t(64), "orange", compiletime64>(runtime64, mut64) };
		EXPECT_EQ(*ns, static_cast<size_t>(2));
	}
	{
		const auto ns{ nnstr::NanoString::make<size_t(64), "potato", compiletime64>(runtime64, mut64) };
		EXPECT_EQ(*ns, static_cast<size_t>(4));
	}
}