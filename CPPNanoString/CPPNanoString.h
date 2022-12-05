#pragma once

#include <vector>
#include <array>
#include <atomic>
#include "FixedString.h"

#define nnstrINIT_TABLES(maxSize, ...) \
namespace nnstr {	\
	inline constexpr auto predefinedStringsTable = std::to_array<nnstr::FixedString<maxSize>>({__VA_ARGS__}); \
	inline std::vector<nnstr::FixedString<maxSize>> runtimeStringsTable;	\
};	\

#define nnstrINIT_LITERALS(maxSize, lit)	\
namespace nnstr::literals	\
{	\
	template<FixedString<64> FS>	\
	constexpr auto operator"" lit()	\
	{	\
		return NanoString::make<64, FS>();	\
	}	\
};	\
\
using namespace nnstr::literals;	