#include "src/save_reader/country_importer.h"

#include <external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/googletest/googletest/include/gtest/gtest.h>

#include <sstream>



TEST(CountryImporterTest, CosmeticTagDefaultsToNullopt)
{
   std::stringstream input;

   hoi4_map_drawer::CountryImporter importer;
   const auto country = importer.ImportCountry(input);

   EXPECT_FALSE(country.GetCosmeticTag().has_value());
}


TEST(CountryImporterTest, CosmeticTagCanBeInput)
{
   std::stringstream input;
   input << "= {\n";
   input << "\tcosmetic_tag=\"TAG_cosmetic_tag\"\n";
   input << "}";

   hoi4_map_drawer::CountryImporter importer;
   const auto country = importer.ImportCountry(input);

   ASSERT_TRUE(country.GetCosmeticTag().has_value());
   EXPECT_EQ(country.GetCosmeticTag(), "TAG_cosmetic_tag");
}


TEST(CountryImporterTest, ExtraInputIsIgnored)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   std::stringstream input;
   input << "= {\n";
   input << "\tcosmetic_tag=\"TAG_cosmetic_tag\"\n";
   input << "\tunhandled_input = 42\n";
   input << "}";

   hoi4_map_drawer::CountryImporter importer;
   auto country = importer.ImportCountry(input);
   auto cosmetic_tag = country.GetCosmeticTag();  // make the annoying warning go away
   cosmetic_tag.reset();

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}