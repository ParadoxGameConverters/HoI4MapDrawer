#include "src/state_definitions/state_definition_importer.h"

#include <external/commonItems/external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/commonItems/external/googletest/googletest/include/gtest/gtest.h>

#include <sstream>



TEST(StateDefinitionImporterTest, ReturnsNulloptIfMissingId)
{
   std::stringstream input;

   hoi4_map_drawer::StateDefinitionImporter importer;

   EXPECT_EQ(importer.ImportState(input), std::nullopt);
}


TEST(StateDefinitionImporterTest, IdCanBeImported)
{
   std::stringstream input;
   input << "= {\n";
   input << "\tid = 42\n";
   input << "}";

   hoi4_map_drawer::StateDefinitionImporter importer;
   const auto state_data = importer.ImportState(input);

   EXPECT_TRUE(state_data.has_value());
   EXPECT_EQ(state_data.value_or({0, {}}).first, 42);
}


TEST(StateDefinitionImporterTest, ReturnsEmptyVectorIfMissingProvinces)
{
   std::stringstream input;
   input << "= {\n";
   input << "\tid = 42\n";
   input << "}";

   hoi4_map_drawer::StateDefinitionImporter importer;
   const auto state_data = importer.ImportState(input);

   EXPECT_TRUE(state_data.has_value());
   EXPECT_TRUE(state_data.value_or({0, {}}).second.empty());
}


TEST(StateDefinitionImporterTest, ProvincesCanBeImported)
{
   std::stringstream input;
   input << "= {\n";
   input << "\tid = 42\n";
   input << "\tprovinces={\n";
   input << "\t\t1 4 9 16";
   input << "\t}";
   input << "}";

   hoi4_map_drawer::StateDefinitionImporter importer;
   const auto state_data = importer.ImportState(input);

   EXPECT_TRUE(state_data.has_value());
   EXPECT_THAT(state_data.value_or({0, {}}).second, testing::ElementsAre(1, 4, 9, 16));
}


TEST(StateDefinitionImporterTest, ExtraInputIsIgnored)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   std::stringstream input;
   input << "= {\n";
   input << "\tunhandled_input = 42\n";
   input << "}";

   hoi4_map_drawer::StateDefinitionImporter importer;
   auto state_data = importer.ImportState(input);
   state_data.reset();  // make the annoying warning go away

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}