#include "src/save_reader/countries_importer.h"

#include <external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/googletest/googletest/include/gtest/gtest.h>

#include <sstream>



TEST(CountriesImporterTest, CosmeticTagsMapDefaultsToEmpty)
{
   std::stringstream input;

   hoi4_map_drawer::save_reader::CountriesImporter importer;
   const auto countries = importer.ImportCountries(input);

   EXPECT_TRUE(countries.GetTagsToCosmeticTagsMap().empty());
}


TEST(CountriesImporterTest, CosmeticTagsCanBeMapped)
{
   std::stringstream input;
   input << "= {\n";
   input << "\tTAG={\n";
   input << "\t\tcosmetic_tag=\"TAG_cosmetic_tag\"\n";
   input << "\t}\n";
   input << "\tTWO={\n";
   input << "\t\tcosmetic_tag=\"TWO_cosmetic_tag\"\n";
   input << "\t}\n";
   input << "}";

   hoi4_map_drawer::save_reader::CountriesImporter importer;
   const auto countries = importer.ImportCountries(input);

   EXPECT_THAT(countries.GetTagsToCosmeticTagsMap(),
       testing::UnorderedElementsAre(testing::Pair("TAG", "TAG_cosmetic_tag"),
           testing::Pair("TWO", "TWO_cosmetic_tag")));
}


TEST(CountriesImporterTest, CountriesWithoutCosmeticTagsAreIgnored)
{
   std::stringstream input;
   input << "= {\n";
   input << "\tTAG={\n";
   input << "\t\tcosmetic_tag=\"TAG_cosmetic_tag\"\n";
   input << "\t}\n";
   input << "\tTWO={\n";
   input << "\t\tcosmetic_tag=\"TWO_cosmetic_tag\"\n";
   input << "\t}\n";
   input << "\tBAD={\n";
   input << "\t}\n";
   input << "}";

   hoi4_map_drawer::save_reader::CountriesImporter importer;
   const auto countries = importer.ImportCountries(input);

   EXPECT_THAT(countries.GetTagsToCosmeticTagsMap(),
       testing::UnorderedElementsAre(testing::Pair("TAG", "TAG_cosmetic_tag"),
           testing::Pair("TWO", "TWO_cosmetic_tag")));
}