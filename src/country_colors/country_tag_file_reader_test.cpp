#include "src/country_colors/country_tag_file_reader.h"

#include <external/commonItems/Color.h>
#include <external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/googletest/googletest/include/gtest/gtest.h>

#include <sstream>



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


TEST(CountryTagFileReaderTest, ExtraDataIsIgnored)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   std::stringstream input;
   input << "color = { 51 204 51 }\n";
   input << "unhandled_input = 42";

   hoi4_map_drawer::country_colors::CountryTagFileReader reader;
   auto tags_to_definitions_map = reader.ImportTags("test_data/country_colors/tag_file_with_extra_data.txt");
   tags_to_definitions_map.clear();  // make the annoying warning go away

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}