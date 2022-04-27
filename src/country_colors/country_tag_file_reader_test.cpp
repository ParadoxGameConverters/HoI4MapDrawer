#include "src/country_colors/country_tag_file_reader.h"

#include <sstream>

#include "external/commonItems/Color.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(CountryTagFileReaderTest, DefaultColorWhenNoColorSpecified)
{
   hoi4_map_drawer::country_colors::CountryTagFileReader reader;
   EXPECT_TRUE(reader.ImportTags("test_data/country_colors/empty_tag_file.txt").empty());
}


TEST(CountryTagFileReaderTest, ColorCanBeSpecified)
{
   hoi4_map_drawer::country_colors::CountryTagFileReader reader;
   EXPECT_THAT(reader.ImportTags("test_data/country_colors/definition_with_tags.txt"),
       testing::UnorderedElementsAre(testing::Pair("TAG", "country/country_tag.txt"),
           testing::Pair("TWO", "country/tag_two.txt")));
}