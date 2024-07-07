#include "src/country_colors/country_tags_reader.h"

#include <external/commonItems/Color.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/googletest/googletest/include/gtest/gtest.h>

#include <sstream>



TEST(CountryTagsReaderTest, DefaultColorWhenNoColorSpecified)
{
   const commonItems::ModFilesystem mod_filesystem("test_data/country_colors/empty_tags_directory", {});

   hoi4_map_drawer::country_colors::CountryTagsReader reader;
   EXPECT_TRUE(reader.ImportTags(mod_filesystem).empty());
}


TEST(CountryTagsReaderTest, ColorCanBeSpecified)
{
   const commonItems::ModFilesystem mod_filesystem("test_data/country_colors/tags_directory", {});

   hoi4_map_drawer::country_colors::CountryTagsReader reader;
   EXPECT_THAT(reader.ImportTags(mod_filesystem),
       testing::UnorderedElementsAre(testing::Pair("ONE", "common/country/country_tag_one.txt"),
           testing::Pair("TWO", "common/country/tag_two.txt"),
           testing::Pair("TAG", "common/country/country_tag.txt")));
}