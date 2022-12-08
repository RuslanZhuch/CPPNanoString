#include "pch.h"
#include <string>

#include "CPPNanoString.h"

nnstrINIT_TABLES(_nn64run, std::mutex, mut64run, std::vector, runtime64run, 64, std::array, compiletime64run,
	"plane",
	"boat",
	"train"
);

static std::string trainStr{ "train" };
static std::string tankStr{ "tank" };
static std::string shipStr{ "ship" };

TEST(nano64Runtime, creation)
{

	{
		nnstr::NanoString ns{ nnstr::NanoString::make<64, compiletime64run>(trainStr, runtime64run, mut64run) };
		EXPECT_EQ(*ns, static_cast<size_t>(3));
	}
	{
		nnstr::NanoString ns{ nnstr::NanoString::make<64, compiletime64run>(tankStr, runtime64run, mut64run) };
		EXPECT_EQ(*ns, static_cast<size_t>(4));
	}
	{
		nnstr::NanoString ns{ make_nn64run(shipStr) };
		EXPECT_EQ(*ns, static_cast<size_t>(5));
	}

}