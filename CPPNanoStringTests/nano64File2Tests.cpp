#include "pch.h"

#include "nano64Bytes.h"

TEST(nano64BytesFile2, creationWithLiterals)
{
	{
		const auto ns{ "orange"_nn64 };
		EXPECT_EQ(*ns, 2);
	}
	{
		//This file included after "nano64File1Tests", therefore "kivi" has an index 5
		const auto ns{ "kiwi"_nn64 };
		EXPECT_EQ(*ns, 5);
	}
	{
		constexpr auto ns{ "orange"_nn64 };
		EXPECT_EQ(*ns, 2);
	}
}