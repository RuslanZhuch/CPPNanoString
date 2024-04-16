#pragma once

#pragma warning (push)
#include "warningsBlacklist.h"
#include <vector>
#include <array>
#include <atomic>
#include <mutex>
#include <tuple>
#include <type_traits>
#pragma warning (pop)

#include "FixedString.h"
#include "NanoString.h"

#define nnstrNUM_ARGS(...) (std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value)

#define nnstrINIT_TABLES(lit, mutexType, mutexName, runtimeType, runtimeName, maxSizePerString, compiletimeType, compiletimeName, ...) \
inline constexpr compiletimeType<nnstr::FixedString<maxSizePerString>, nnstrNUM_ARGS(__VA_ARGS__)> compiletimeName{{__VA_ARGS__}}; \
inline runtimeType<nnstr::FixedString<maxSizePerString>> runtimeName;	\
inline mutexType mutexName##lit;\
\
namespace nnstr::literals	\
{	\
	template<FixedString<maxSizePerString> FS>	\
	constexpr auto operator"" lit()	\
	{	\
		if (std::is_constant_evaluated())	\
			return NanoString::make<maxSizePerString, FS, compiletimeName>();	\
		else	\
			return NanoString::make<maxSizePerString, FS, compiletimeName>(runtimeName, mutexName##lit);	\
	}	\
};	\
\
[[nodiscard]] static constexpr auto make##lit(std::string_view str) noexcept \
{\
	return nnstr::NanoString::make<maxSizePerString, compiletimeName>(str, runtimeName, mutexName##lit);	\
}	\
using namespace nnstr::literals;	