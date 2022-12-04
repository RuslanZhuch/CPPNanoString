#include "pch.h"

#include "../CPPNanoString/FixedString.h"

TEST(FixedString, constructionFromStringView) 
{

	nnstr::FixedString<4> fs("123");
	EXPECT_EQ(*fs, "123");

	nnstr::FixedString<16> fs2("1234");
	EXPECT_EQ(*fs2, "1234");

}

TEST(FixedString, implicitConstruction)
{

	nnstr::FixedString<4> fs = "123";
	EXPECT_EQ(*fs, "123");


	nnstr::FixedString<16> fs2 = "1234";
	EXPECT_EQ(*fs2, "1234");

}