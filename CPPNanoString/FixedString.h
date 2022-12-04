#pragma once
#include <string_view>

#include "ErrorsCapture.h"

namespace nnstr
{

	template <size_t maxSize>
	struct FixedString
	{
		constexpr FixedString(std::string_view str) noexcept
		{
			this->init(str);
		}
		constexpr FixedString(const char* str) noexcept
		{
			this->init(str);
		}
		constexpr auto operator*() noexcept
		{
			return std::string_view(this->data);
		}
		constexpr void init(std::string_view str) noexcept
		{

			if (str.size() > maxSize - 1)
			{
				throwError("Out of bound");
				return;
			}

			for (size_t id{ 0 }; id < str.size(); ++id)
			{
				this->data[id] = str[id];
			}
			this->data[str.size()] = '\0';

		}
		char data[maxSize]{};
	};

};