#include "pch.h"

#include <array>
#include <thread>
#include <string>
#include <numeric>

#include "CPPNanoString.h"

nnstrINIT_TABLES(8, 
	"1234", 
	"Str 2"
);

#include "NanoString.h"

TEST(NanoString, creationConstant)
{

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "1234">() };
		EXPECT_EQ(*ns, static_cast<size_t>(1));
	}

	{
		constexpr nnstr::NanoString nsFailed{ nnstr::NanoString::make<8, "12345">() };
		EXPECT_EQ(*nsFailed, static_cast<size_t>(0));
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "Str 2">() };
		EXPECT_EQ(*ns, static_cast<size_t>(2));
	}

}

TEST(NanoString, creationRuntime)
{

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex">() };
		EXPECT_EQ(*ns, static_cast<size_t>(3));
	}

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex2">() };
		EXPECT_EQ(*ns, static_cast<size_t>(4));
	}

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<8, "Not ex">() };
		EXPECT_EQ(*ns, static_cast<size_t>(3));
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "1234">() };
		EXPECT_EQ(*ns, static_cast<size_t>(1));
	}

	{
		constexpr nnstr::NanoString ns{ nnstr::NanoString::make<8, "Str 2">() };
		EXPECT_EQ(*ns, static_cast<size_t>(2));
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

template<typename T, T Val, char ... S>
[[nodiscard]] consteval auto toStringLiteral()
{
	
	if constexpr (Val == 0)
	{
		constexpr char data[sizeof...(S) + 1]{ S... };
		return nnstr::FixedString<8>(data);
	}
	else
		return toStringLiteral<T, Val / 10, (Val % 10) + '0', S...>();
}

template<size_t N, nnstr::FixedString<8> ... Strings>
[[nodiscard]] consteval auto generateArrayOfStrings()
{
	if constexpr (N == 0)
		return std::to_array<nnstr::FixedString<8>>({ Strings... });
	else
		return generateArrayOfStrings<N - 1, toStringLiteral<size_t, N>(), Strings...>();
}

//TEST(NanoString, mutlithreading)
//{
//
//	constexpr size_t numOfElements{ 100 };
////	constexpr auto v = toStringLiteral<size_t, 100>();
//	constexpr auto source{ generateArrayOfStrings<numOfElements>() };
////
////	std::vector<nnstr::NanoString> target1;
////	target1.reserve(numOfElements);
////	std::jthread thr1([&](std::stop_token token)
////	{
////		for(size_t id{0}; id < numOfElements; ++id)
////		{
////			target1.push_back(nnstr::NanoString::make<8, source[id]>());
////		}
////	});
//
//}