#include "pch.h"

#include <array>

#include "../CPPNanoString/CPPNanoString.h"

nnstrINIT_TABLES(8, 
	"1234", 
	"Str 2"
);

//constexpr auto predefinedStringsTable = std::to_array<nnstr::FixedString<8>>({
//		"1234",
//		"Str 2"
//	});
//
//static std::vector<nnstr::FixedString<8>> runtimeStringsTable;

#include "../CPPNanoString/NanoString.h"

TEST(NanoString, creationConstant)
{

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "1234">() };
		EXPECT_EQ(*ns, 1);
	}

	{
		constexpr nnstr::NanoString nsFailed{ nnstr::NanoString::make<8, "12345">() };
		EXPECT_EQ(*nsFailed, 0);
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "Str 2">() };
		EXPECT_EQ(*ns, 2);
	}

}

TEST(NanoString, creationRuntime)
{

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex">() };
		EXPECT_EQ(*ns, 3);
	}

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex2">() };
		EXPECT_EQ(*ns, 4);
	}

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex">() };
		EXPECT_EQ(*ns, 3);
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "1234">() };
		EXPECT_EQ(*ns, 1);
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "Str 2">() };
		EXPECT_EQ(*ns, 2);
	}

}

TEST(NanoString, comparison)
{

	{
		const auto str1{ nnstr::NanoString::make<8, "1234">() };
		const auto str2{ nnstr::NanoString::make<8, "1234">() };
		EXPECT_EQ(str1, str2);
	}

	{
		const auto str1{ nnstr::NanoString::make<8, "1234">() };
		const auto str2{ nnstr::NanoString::make<8, "Str 2">() };
		EXPECT_NE(str1, str2);
	}

}