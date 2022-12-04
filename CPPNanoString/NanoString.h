#pragma once

#include "FixedString.h"
#include <string_view>

namespace nnstr
{

	class NanoString
	{
	public:
        template <size_t maxSize, FixedString<maxSize> str>
        [[nodiscard]] static constexpr auto make() noexcept
        {
            constexpr auto fStr{ std::find_if(predefinedStringsTable.begin(), predefinedStringsTable.end(), [&](auto&& el)
            {
                return std::string_view(el.data) == std::string_view(str.data);
            }) };

            NanoString fs;
            if (fStr != predefinedStringsTable.end())
            {
                fs.index = std::distance(predefinedStringsTable.begin(), fStr) + 1;
                return fs;
            }
            if (std::is_constant_evaluated())
            {
                return fs;
            }
            const auto fStrRuntime{ std::find_if(runtimeStringsTable.begin(), runtimeStringsTable.end(), [&](auto&& el)
            {
                return std::string_view(el.data) == std::string_view(str.data);
            }) };
            if (fStrRuntime != runtimeStringsTable.end())
            {
                fs.index = std::distance(runtimeStringsTable.begin(), fStrRuntime) + predefinedStringsTable.size() + 1;
                return fs;
            }
            runtimeStringsTable.push_back(str);
            fs.index = runtimeStringsTable.size() + predefinedStringsTable.size();
            return fs;
        }
        [[nodiscard]] constexpr auto operator*() const noexcept
        {
            return this->index;
        }
        [[nodiscard]] constexpr friend auto operator<=>(const NanoString&, const NanoString&) noexcept = default;

    private:
        int32_t index{};
	};

};