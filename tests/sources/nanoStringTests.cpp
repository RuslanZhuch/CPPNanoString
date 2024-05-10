#include "pch.h"

#include <array>
#include <thread>
#include <string>
#include <numeric>
#include <thread>
#include <latch>

#include "CPPNanoString.h"

nnstrINIT_TABLES(_nn8, std::mutex, mutex, std::vector, runtimeStringsTable, 8, 
	std::array, predefinedStringsTable,
	"1234",
	"Str 2"
);

TEST(NanoString, creationConstant)
{

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "1234", predefinedStringsTable>() };
		EXPECT_EQ(*ns, static_cast<size_t>(1));
		EXPECT_EQ(std::strcmp(nnstr::NanoString::get<predefinedStringsTable>(ns), "1234"), 0);
	}

	{
		constexpr nnstr::NanoString nsFailed{ nnstr::NanoString::make<8, "12345", predefinedStringsTable>() };
		EXPECT_EQ(*nsFailed, static_cast<size_t>(0));
		EXPECT_EQ(std::strcmp(nnstr::NanoString::get<predefinedStringsTable>(nsFailed), ""), 0);
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "Str 2", predefinedStringsTable>() };
		EXPECT_EQ(*ns, static_cast<size_t>(2));
		EXPECT_EQ(std::strcmp(nnstr::NanoString::get<predefinedStringsTable>(ns), "Str 2"), 0);
	}

}

TEST(NanoString, creationRuntime)
{

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex", predefinedStringsTable>(runtimeStringsTable, mutex_nn8) };
		EXPECT_EQ(*ns, static_cast<size_t>(3));
		EXPECT_EQ(std::strcmp(nnstr::NanoString::get<predefinedStringsTable>(ns, runtimeStringsTable), "Not ex"), 0);
		EXPECT_EQ(std::strcmp(get_nn8(ns), "Not ex"), 0);
	}

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex2", predefinedStringsTable>(runtimeStringsTable, mutex_nn8) };
		EXPECT_EQ(*ns, static_cast<size_t>(4));
		EXPECT_EQ(std::strcmp(nnstr::NanoString::get<predefinedStringsTable>(ns, runtimeStringsTable), "Not ex2"), 0);
		EXPECT_EQ(std::strcmp(get_nn8(ns), "Not ex2"), 0);
	}

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex", predefinedStringsTable>(runtimeStringsTable, mutex_nn8) };
		EXPECT_EQ(*ns, static_cast<size_t>(3));
		EXPECT_EQ(std::strcmp(nnstr::NanoString::get<predefinedStringsTable>(ns, runtimeStringsTable), "Not ex"), 0);
		EXPECT_EQ(std::strcmp(get_nn8(ns), "Not ex"), 0);
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "1234", predefinedStringsTable>(runtimeStringsTable, mutex_nn8) };
		EXPECT_EQ(*ns, static_cast<size_t>(1));
		EXPECT_EQ(std::strcmp(nnstr::NanoString::get<predefinedStringsTable>(ns, runtimeStringsTable), "1234"), 0);
		EXPECT_EQ(std::strcmp(get_nn8(ns), "1234"), 0);
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "Str 2", predefinedStringsTable>(runtimeStringsTable, mutex_nn8) };
		EXPECT_EQ(*ns, static_cast<size_t>(2));
		EXPECT_EQ(std::strcmp(nnstr::NanoString::get<predefinedStringsTable>(ns, runtimeStringsTable), "Str 2"), 0);
		EXPECT_EQ(std::strcmp(get_nn8(ns), "Str 2"), 0);
	}

	{
		EXPECT_EQ(std::strcmp(nnstr::NanoString::get<predefinedStringsTable>(nnstr::NanoString{}, runtimeStringsTable), ""), 0);
	}

}

TEST(NanoString, comparison)
{

	{
		const auto str1{ nnstr::NanoString::make<8, "1234", predefinedStringsTable>(runtimeStringsTable, mutex_nn8) };
		const auto str2{ nnstr::NanoString::make<8, "1234", predefinedStringsTable>(runtimeStringsTable, mutex_nn8) };
		EXPECT_EQ(str1, str2);
	}

	{
		const auto str1{ nnstr::NanoString::make<8, "1234", predefinedStringsTable>(runtimeStringsTable, mutex_nn8) };
		const auto str2{ nnstr::NanoString::make<8, "Str 2", predefinedStringsTable>(runtimeStringsTable, mutex_nn8) };
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

		strings1.push_back("str0"_nn8);
		strings1.push_back("str1"_nn8);
		strings1.push_back("str2"_nn8);
		strings1.push_back("str3"_nn8);
		strings1.push_back("str4"_nn8);
		strings1.push_back("str5"_nn8);
		strings1.push_back("str6"_nn8);
		strings1.push_back("str7"_nn8);
		strings1.push_back("str8"_nn8);
		strings1.push_back("str9"_nn8);
		strings1.push_back("str10"_nn8);
		strings1.push_back("str11"_nn8);
		strings1.push_back("str12"_nn8);
		strings1.push_back("str13"_nn8);
		strings1.push_back("str14"_nn8);
		strings1.push_back("str15"_nn8);
		strings1.push_back("str16"_nn8);
		strings1.push_back("str17"_nn8);
		strings1.push_back("str18"_nn8);
		strings1.push_back("str19"_nn8);
		strings1.push_back("str20"_nn8);
		strings1.push_back("str21"_nn8);
		strings1.push_back("str22"_nn8);
		strings1.push_back("str23"_nn8);
		strings1.push_back("str24"_nn8);
		strings1.push_back("str25"_nn8);
		strings1.push_back("str26"_nn8);
		strings1.push_back("str27"_nn8);
		strings1.push_back("str28"_nn8);
		strings1.push_back("str29"_nn8);

	}) };

	std::vector<nnstr::NanoString> strings2;
	strings2.reserve(numOfStrings);

	auto thread2{ std::jthread([&]()
	{
		latch.arrive_and_wait();

		strings2.push_back("str0"_nn8);
		strings2.push_back("str1"_nn8);
		strings2.push_back("str2"_nn8);
		strings2.push_back("str3"_nn8);
		strings2.push_back("str4"_nn8);
		strings2.push_back("str5"_nn8);
		strings2.push_back("str6"_nn8);
		strings2.push_back("str7"_nn8);
		strings2.push_back("str8"_nn8);
		strings2.push_back("str9"_nn8);
		strings2.push_back("str10"_nn8);
		strings2.push_back("str11"_nn8);
		strings2.push_back("str12"_nn8);
		strings2.push_back("str13"_nn8);
		strings2.push_back("str14"_nn8);
		strings2.push_back("str15"_nn8);
		strings2.push_back("str16"_nn8);
		strings2.push_back("str17"_nn8);
		strings2.push_back("str18"_nn8);
		strings2.push_back("str19"_nn8);
		strings2.push_back("str20"_nn8);
		strings2.push_back("str21"_nn8);
		strings2.push_back("str22"_nn8);
		strings2.push_back("str23"_nn8);
		strings2.push_back("str24"_nn8);
		strings2.push_back("str25"_nn8);
		strings2.push_back("str26"_nn8);
		strings2.push_back("str27"_nn8);
		strings2.push_back("str28"_nn8);
		strings2.push_back("str29"_nn8);

	}) };

	thread1.join();
	thread2.join();

	for (size_t stringId{ 0 }; stringId < numOfStrings; ++stringId)
	{
		EXPECT_EQ(strings1[stringId], strings2[stringId]);
	}

}