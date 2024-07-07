#include "src/country_colors/cosmetic_tags_importer.h"

#include <external/commonItems/Color.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/googletest/googletest/include/gtest/gtest.h>

#include <sstream>



TEST(CosmeticTagsImporterTest, CosmeticTagsCanBeImported)
{
   const commonItems::ModFilesystem mod_filesystem("test_data/country_colors/cosmetic_tags_importer/", {});

   hoi4_map_drawer::country_colors::CosmeticTagsImporter cosmetic_tags_importer;

   EXPECT_THAT(cosmetic_tags_importer.ImportCosmeticTags(mod_filesystem),
       testing::UnorderedElementsAre(testing::Pair("TAG_cosmetic_tag", commonItems::Color(std::array<int, 3>{1, 2, 3})),
           testing::Pair("TWO_cosmetic_tag", commonItems::Color(std::array<int, 3>{10, 11, 12}))));
}