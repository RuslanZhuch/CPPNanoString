#pragma once

#pragma warning (push)
#include "warningsBlacklist.h"
#include <string_view>
#include <mutex>
#pragma warning (pop)

#include "FixedString.h"

namespace nnstr
{

	class NanoString
	{
	public:
        template <size_t maxSize, FixedString<maxSize> str>
        [[nodiscard]] static constexpr auto make() noexcept
        {
            
            if (std::is_constant_evaluated())
                return makeCompiletime<maxSize, str>();
            else
                return makeRuntime<maxSize, str>();

        }
        [[nodiscard]] constexpr auto operator*() const noexcept
        {
            return this->index;
        }
        [[nodiscard]] constexpr friend auto operator<=>(const NanoString&, const NanoString&) noexcept = default;

    private:
        template <size_t maxSize, FixedString<maxSize> str>
        [[nodiscard]] static consteval auto makeCompiletime() noexcept
        {
            constexpr auto compareFnc = [&](auto&& el) -> bool
            {
                return std::string_view(el.data) == std::string_view(str.data);
            };

            constexpr auto fStr{ std::find_if(predefinedStringsTable.begin(), predefinedStringsTable.end(), compareFnc) };

            NanoString fs;
            if (fStr != predefinedStringsTable.end())
            {
                fs.index = static_cast<uint64_t>(std::distance(predefinedStringsTable.begin(), fStr)) + 1;
                return fs;
            }
            return fs;
        }

        template <size_t maxSize, FixedString<maxSize> str>
        [[nodiscard]] static auto makeRuntime() noexcept
        {

            constexpr auto compareFnc = [&](auto&& el) -> bool
            {
                return std::string_view(el.data) == std::string_view(str.data);
            };

            constexpr auto fStr{ std::find_if(predefinedStringsTable.begin(), predefinedStringsTable.end(), compareFnc) };

            NanoString fs;
            if (fStr != predefinedStringsTable.end())
            {
                fs.index = static_cast<uint64_t>(std::distance(predefinedStringsTable.begin(), fStr)) + 1;
                return fs;
            }

            std::scoped_lock lck(nnstr::mutex);
            const auto fStrRuntime{ std::find_if(runtimeStringsTable.begin(), runtimeStringsTable.end(), compareFnc) };
            if (fStrRuntime != runtimeStringsTable.end())
            {
                fs.index = static_cast<uint64_t>(std::distance(runtimeStringsTable.begin(), fStrRuntime)) + predefinedStringsTable.size() + 1;
                return fs;
            }
            runtimeStringsTable.push_back(str);
            fs.index = runtimeStringsTable.size() + predefinedStringsTable.size();
            return fs;

        }

    private:
        uint64_t index{};
	};

};