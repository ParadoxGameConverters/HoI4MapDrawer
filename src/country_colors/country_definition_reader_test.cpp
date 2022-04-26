#include "src/country_colors/country_definition_reader.h"

#include <sstream>

#include "external/commonItems/Color.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(CountryDefinitionReaderTest, DefaultColorWhenNoColorSpecified)
{
   std::stringstream input;

   hoi4_map_drawer::country_colors::CountryDefinitionReader reader;
   EXPECT_EQ(reader.ImportCountryDefinition(input), commonItems::Color());
}


TEST(CountryDefinitionReaderTest, ColorCanBeSpecified)
{
   std::stringstream input;
   input << "color = { 51 204 51 }";

   hoi4_map_drawer::country_colors::CountryDefinitionReader reader;
   EXPECT_EQ(reader.ImportCountryDefinition(input), commonItems::Color(std::array{51, 204, 51}));
}


TEST(CountryDefinitionReaderTest, ExtraInputIsIgnored)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   std::stringstream input;
   input << "color = { 51 204 51 }\n";
   input << "unhandled_input = 42";

   hoi4_map_drawer::country_colors::CountryDefinitionReader reader;
   auto color = reader.ImportCountryDefinition(input);
   color.RandomlyFluctuate(42);  // make the annoying warning go away

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}