#pragma once

#pragma warning (push)
#include "warningsBlacklist.h"
#include <string_view>
#include <mutex>
#pragma warning (pop)

#include "FixedString.h"

namespace nnstr
{

    using type_t = uint64_t;

	class NanoString
	{
	public:
        template <size_t maxSize, FixedString<maxSize> str, auto predefinedStringsTable>
        [[nodiscard]] static consteval auto make() noexcept
        {

            return makeCompiletime<maxSize, str, predefinedStringsTable>();

        }

        template <size_t maxSize, FixedString<maxSize> str, auto predefinedStringsTable>
        [[nodiscard]] static constexpr auto make(auto&& runtimeStringsTable, auto&& mutex) noexcept
        {
            
            if (std::is_constant_evaluated())
                return makeCompiletime<maxSize, str, predefinedStringsTable>();
            else
                return makeRuntime<maxSize, str, predefinedStringsTable>(runtimeStringsTable, mutex);

        }

        template <size_t maxSize, auto predefinedStringsTable>
        [[nodiscard]] static constexpr auto make(std::string_view str, auto&& runtimeStringsTable, auto&& mutex) noexcept
        {

            const auto compareFnc = [&](auto&& el) -> bool
            {
                return std::string_view(el.data) == str;
            };

            auto fStr{ std::find_if(predefinedStringsTable.begin(), predefinedStringsTable.end(), compareFnc) };

            NanoString fs{};
            if (fStr != predefinedStringsTable.end())
            {
                fs.index = static_cast<type_t>(std::distance(predefinedStringsTable.begin(), fStr)) + 1;
                return fs;
            }

            std::scoped_lock lck(mutex);
            const auto fStrRuntime{ std::find_if(runtimeStringsTable.begin(), runtimeStringsTable.end(), compareFnc) };
            if (fStrRuntime != runtimeStringsTable.end())
            {
                fs.index = static_cast<type_t>(std::distance(runtimeStringsTable.begin(), fStrRuntime)) + predefinedStringsTable.size() + 1;
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
        template <size_t maxSize, FixedString<maxSize> str, auto predefinedStringsTable>
        [[nodiscard]] static consteval auto makeCompiletime() noexcept
        {
            constexpr auto compareFnc = [&](auto&& el) -> bool
            {
                return std::string_view(el.data) == std::string_view(str.data);
            };

            constexpr auto fStr{ std::find_if(predefinedStringsTable.begin(), predefinedStringsTable.end(), compareFnc) };

            NanoString fs{};
            if (fStr != predefinedStringsTable.end())
            {
                fs.index = static_cast<type_t>(std::distance(predefinedStringsTable.begin(), fStr)) + 1;
                return fs;
            }
            return fs;
        }

        template <size_t maxSize, FixedString<maxSize> str, auto predefinedStringsTable>
        [[nodiscard]] static auto makeRuntime(auto&& runtimeStringsTable, auto&& mutex) noexcept
        {

            constexpr auto compareFnc = [&](auto&& el) -> bool
            {
                return std::string_view(el.data) == std::string_view(str.data);
            };

            constexpr auto fStr{ std::find_if(predefinedStringsTable.begin(), predefinedStringsTable.end(), compareFnc) };

            NanoString fs{};
            if (fStr != predefinedStringsTable.end())
            {
                fs.index = static_cast<type_t>(std::distance(predefinedStringsTable.begin(), fStr)) + 1;
                return fs;
            }

            std::scoped_lock lck(mutex);
            const auto fStrRuntime{ std::find_if(runtimeStringsTable.begin(), runtimeStringsTable.end(), compareFnc) };
            if (fStrRuntime != runtimeStringsTable.end())
            {
                fs.index = static_cast<type_t>(std::distance(runtimeStringsTable.begin(), fStrRuntime)) + predefinedStringsTable.size() + 1;
                return fs;
            }
            runtimeStringsTable.push_back(str);
            fs.index = runtimeStringsTable.size() + predefinedStringsTable.size();
            return fs;

        }

    private:
        type_t index;
	};

};