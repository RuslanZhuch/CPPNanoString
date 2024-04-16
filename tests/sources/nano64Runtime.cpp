#include "pch.h"
#include <string>
#include <thread>
#include <latch>

#include "CPPNanoString.h"

nnstrINIT_TABLES(_nn64run, std::mutex, mut64run, std::vector, runtime64run, 64, std::array, compiletime64run,
	"plane",
	"boat",
	"train"
);

static std::string trainStr{ "train" };
static std::string tankStr{ "tank" };
static std::string shipStr{ "ship" };

TEST(nano64Runtime, creation)
{

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<64, compiletime64run>(trainStr, runtime64run, mut64run_nn64run) };
		EXPECT_EQ(*ns, static_cast<size_t>(3));
	}
	{
		nnstr::NanoString ns{ nnstr::NanoString::make<64, compiletime64run>(tankStr, runtime64run, mut64run_nn64run) };
		EXPECT_EQ(*ns, static_cast<size_t>(4));
	}
	{
		nnstr::NanoString ns{ make_nn64run(shipStr) };
		EXPECT_EQ(*ns, static_cast<size_t>(5));
	}

}

TEST(nano64Runtime, creationMultithread)
{

	constexpr size_t numOfStrings(1000);
	const auto stringsToCreate = [numOfStrings]()
	{
		std::vector<std::string> out;
		out.reserve(numOfStrings);
		for (size_t stringId{ 0 }; stringId < numOfStrings; ++stringId)
		{
			out.push_back(std::to_string(stringId + 1));
		}
		return out;
	} ();

	std::vector<nnstr::NanoString> strings1;
	strings1.reserve(numOfStrings);

	std::latch latch(2);
	auto thread1{ std::jthread([&]()
	{
		latch.arrive_and_wait();
		for (size_t stringId{ 0 }; stringId < numOfStrings; ++stringId)
		{
			strings1.push_back(make_nn64run(stringsToCreate[stringId]));
		}
		
	}) };

	std::vector<nnstr::NanoString> strings2;
	strings2.reserve(numOfStrings);

	auto thread2{ std::jthread([&]()
	{
		latch.arrive_and_wait();
		for (size_t stringId{ 0 }; stringId < numOfStrings; ++stringId)
		{
			strings2.push_back(make_nn64run(stringsToCreate[stringId]));
		}

	}) };

	thread1.join();
	thread2.join();

	for (size_t stringId{ 0 }; stringId < numOfStrings; ++stringId)
	{
		EXPECT_EQ(strings1[stringId], strings2[stringId]);
	}

}