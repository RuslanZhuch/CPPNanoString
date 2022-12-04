#pragma once

#include <vector>
#include <array>
#include "FixedString.h"

#define nnstrINIT_TABLES(maxSize, ...) \
namespace nnstr {	\
	inline constexpr auto predefinedStringsTable = std::to_array<nnstr::FixedString<maxSize>>({__VA_ARGS__}); \
	static inline std::vector<nnstr::FixedString<maxSize>> runtimeStringsTable;	\
};