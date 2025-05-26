#include "src/country_colors/country_color_importer.h"

#include <external/commonItems/Color.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/googletest/googletest/include/gtest/gtest.h>

#include <sstream>



TEST(CountryColorImporterTest, CountryColorsCanBeImported)
{
   const commonItems::ModFilesystem mod_filesystem(
       std::filesystem::path("test_data/country_colors/country_color_importer/"),
       {});

   const auto colors = hoi4_map_drawer::ImportCountryColors(mod_filesystem, {{"TST", "TST_cosmetic_tag"}});
   EXPECT_THAT(colors,
       testing::UnorderedElementsAre(testing::Pair("ONE", commonItems::Color(std::array{1, 2, 3})),
           testing::Pair("TWO", commonItems::Color(std::array{2, 4, 6})),
           testing::Pair("TST", commonItems::Color(std::array{3, 6, 9}))));
}