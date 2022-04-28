#include "src/country_colors/country_tags_reader.h"

#include <sstream>

#include "external/commonItems/Color.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(CountryTagsReaderTest, DefaultColorWhenNoColorSpecified)
{
   hoi4_map_drawer::country_colors::CountryTagsReader reader;
   EXPECT_TRUE(reader.ImportTags("test_data/country_colors/empty_tags_directory").empty());
}


TEST(CountryTagsReaderTest, ColorCanBeSpecified)
{
   hoi4_map_drawer::country_colors::CountryTagsReader reader;
   EXPECT_THAT(reader.ImportTags("test_data/country_colors/tags_directory"),
       testing::UnorderedElementsAre(testing::Pair("ONE", "country/country_tag_one.txt"),
           testing::Pair("TWO", "country/tag_two.txt"),
           testing::Pair("TAG", "country/country_tag.txt")));
}