#include "pch.h"

#include "FixedString.h"

TEST(FixedString, constructionFromStringView) 
{

	nnstr::FixedString<4> fs("123");
	EXPECT_STREQ(fs.data, "123");

	nnstr::FixedString<16> fs2("1234");
	EXPECT_STREQ(fs2.data, "1234");

}

TEST(FixedString, implicitConstruction)
{

	nnstr::FixedString<4> fs = "123";
	EXPECT_STREQ(fs.data, "123");


	nnstr::FixedString<16> fs2 = "1234";
	EXPECT_STREQ(fs2.data, "1234");

}