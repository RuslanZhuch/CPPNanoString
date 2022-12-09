#include "pch.h"

#include <array>
#include <thread>
#include <string>
#include <numeric>
#include <thread>
#include <latch>

#include "CPPNanoString.h"

nnstrINIT_TABLES(__nn8, std::mutex, mutex, std::vector, runtimeStringsTable, 8, 
	std::array, predefinedStringsTable,
	"1234",
	"Str 2"
);

TEST(NanoString, creationConstant)
{

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "1234", predefinedStringsTable>() };
		EXPECT_EQ(*ns, static_cast<size_t>(1));
	}

	{
		constexpr nnstr::NanoString nsFailed{ nnstr::NanoString::make<8, "12345", predefinedStringsTable>() };
		EXPECT_EQ(*nsFailed, static_cast<size_t>(0));
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "Str 2", predefinedStringsTable>() };
		EXPECT_EQ(*ns, static_cast<size_t>(2));
	}

}

TEST(NanoString, creationRuntime)
{

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex", predefinedStringsTable>(runtimeStringsTable, mutex) };
		EXPECT_EQ(*ns, static_cast<size_t>(3));
	}

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex2", predefinedStringsTable>(runtimeStringsTable, mutex) };
		EXPECT_EQ(*ns, static_cast<size_t>(4));
	}

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex", predefinedStringsTable>(runtimeStringsTable, mutex) };
		EXPECT_EQ(*ns, static_cast<size_t>(3));
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "1234", predefinedStringsTable>(runtimeStringsTable, mutex) };
		EXPECT_EQ(*ns, static_cast<size_t>(1));
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "Str 2", predefinedStringsTable>(runtimeStringsTable, mutex) };
		EXPECT_EQ(*ns, static_cast<size_t>(2));
	}

}

TEST(NanoString, comparison)
{

	{
		const auto str1{ nnstr::NanoString::make<8, "1234", predefinedStringsTable>(runtimeStringsTable, mutex) };
		const auto str2{ nnstr::NanoString::make<8, "1234", predefinedStringsTable>(runtimeStringsTable, mutex) };
		EXPECT_EQ(str1, str2);
	}

	{
		const auto str1{ nnstr::NanoString::make<8, "1234", predefinedStringsTable>(runtimeStringsTable, mutex) };
		const auto str2{ nnstr::NanoString::make<8, "Str 2", predefinedStringsTable>(runtimeStringsTable, mutex) };
		EXPECT_NE(str1, str2);
	}

}

TEST(NanoString, mutlithreading)
{

	constexpr size_t numOfStrings{ 30 };

	std::vector<nnstr::NanoString> strings1;
	strings1.reserve(numOfStrings);

	std::latch latch(2);
	auto thread1{ std::jthread([&]()
	{
		latch.arrive_and_wait();

		strings1.push_back("str0"__nn8);
		strings1.push_back("str1"__nn8);
		strings1.push_back("str2"__nn8);
		strings1.push_back("str3"__nn8);
		strings1.push_back("str4"__nn8);
		strings1.push_back("str5"__nn8);
		strings1.push_back("str6"__nn8);
		strings1.push_back("str7"__nn8);
		strings1.push_back("str8"__nn8);
		strings1.push_back("str9"__nn8);
		strings1.push_back("str10"__nn8);
		strings1.push_back("str11"__nn8);
		strings1.push_back("str12"__nn8);
		strings1.push_back("str13"__nn8);
		strings1.push_back("str14"__nn8);
		strings1.push_back("str15"__nn8);
		strings1.push_back("str16"__nn8);
		strings1.push_back("str17"__nn8);
		strings1.push_back("str18"__nn8);
		strings1.push_back("str19"__nn8);
		strings1.push_back("str20"__nn8);
		strings1.push_back("str21"__nn8);
		strings1.push_back("str22"__nn8);
		strings1.push_back("str23"__nn8);
		strings1.push_back("str24"__nn8);
		strings1.push_back("str25"__nn8);
		strings1.push_back("str26"__nn8);
		strings1.push_back("str27"__nn8);
		strings1.push_back("str28"__nn8);
		strings1.push_back("str29"__nn8);

	}) };

	std::vector<nnstr::NanoString> strings2;
	strings2.reserve(numOfStrings);

	auto thread2{ std::jthread([&]()
	{
		latch.arrive_and_wait();

		strings2.push_back("str0"__nn8);
		strings2.push_back("str1"__nn8);
		strings2.push_back("str2"__nn8);
		strings2.push_back("str3"__nn8);
		strings2.push_back("str4"__nn8);
		strings2.push_back("str5"__nn8);
		strings2.push_back("str6"__nn8);
		strings2.push_back("str7"__nn8);
		strings2.push_back("str8"__nn8);
		strings2.push_back("str9"__nn8);
		strings2.push_back("str10"__nn8);
		strings2.push_back("str11"__nn8);
		strings2.push_back("str12"__nn8);
		strings2.push_back("str13"__nn8);
		strings2.push_back("str14"__nn8);
		strings2.push_back("str15"__nn8);
		strings2.push_back("str16"__nn8);
		strings2.push_back("str17"__nn8);
		strings2.push_back("str18"__nn8);
		strings2.push_back("str19"__nn8);
		strings2.push_back("str20"__nn8);
		strings2.push_back("str21"__nn8);
		strings2.push_back("str22"__nn8);
		strings2.push_back("str23"__nn8);
		strings2.push_back("str24"__nn8);
		strings2.push_back("str25"__nn8);
		strings2.push_back("str26"__nn8);
		strings2.push_back("str27"__nn8);
		strings2.push_back("str28"__nn8);
		strings2.push_back("str29"__nn8);

	}) };

	thread1.join();
	thread2.join();

	for (size_t stringId{ 0 }; stringId < numOfStrings; ++stringId)
	{
		EXPECT_EQ(strings1[stringId], strings2[stringId]);
	}

}