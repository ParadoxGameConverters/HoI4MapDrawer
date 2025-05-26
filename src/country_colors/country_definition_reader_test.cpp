#include "src/country_colors/country_definition_reader.h"

#include <external/commonItems/Color.h>
#include <external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/googletest/googletest/include/gtest/gtest.h>

#include <sstream>



TEST(CountryDefinitionReaderTest, DefaultColorWhenNoColorSpecified)
{
   hoi4_map_drawer::CountryDefinitionReader reader;
   EXPECT_EQ(reader.ImportCountryDefinition("test_data/country_colors/empty_country_definition.txt"),
       commonItems::Color());
}


TEST(CountryDefinitionReaderTest, ColorCanBeSpecified)
{
   hoi4_map_drawer::CountryDefinitionReader reader;
   EXPECT_EQ(reader.ImportCountryDefinition("test_data/country_colors/definition_with_color.txt"),
       commonItems::Color(std::array{51, 204, 51}));
}


TEST(CountryDefinitionReaderTest, ExtraInputIsIgnored)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   std::stringstream input;
   input << "color = { 51 204 51 }\n";
   input << "unhandled_input = 42";

   hoi4_map_drawer::CountryDefinitionReader reader;
   auto color = reader.ImportCountryDefinition("test_data/country_colors/definition_with_extra_data.txt");
   color.RandomlyFluctuate(42);  // make the annoying warning go away

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}