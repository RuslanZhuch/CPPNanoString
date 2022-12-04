#pragma once
#include <cassert>
#include <string_view>
#include <type_traits>

namespace nnstr
{
	constexpr void captureError(bool expr, std::string_view errorDesc)
	{
		assert(expr);
	}
	constexpr void throwError(std::string_view errorDesc)
	{
		assert(false);
	}
};