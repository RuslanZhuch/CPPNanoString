#pragma once
#pragma warning (push)
#include "warningsBlacklist.h"
#include <cassert>
#include <string_view>
#include <type_traits>
#pragma warning (pop)

namespace nnstr
{
	inline void captureError(bool expr, [[maybe_unused]] std::string_view errorDesc)
	{
	    assert(expr && "NanoString error");
	}
	inline void throwError([[maybe_unused]] std::string_view errorDesc)
	{
	    assert(false && "NanoString fatal error");
	}
};
