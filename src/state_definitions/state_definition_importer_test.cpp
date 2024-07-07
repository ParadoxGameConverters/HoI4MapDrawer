#include "src/state_definitions/state_definition_importer.h"

#include <external/googletest/googletest/include/gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <sstream>



TEST(StateDefinitionImporterTest, ReturnsNulloptIfMissingId)
{
   std::stringstream input;

   hoi4_map_drawer::state_definitions::StateDefinitionImporter importer;

   EXPECT_EQ(importer.ImportState(input), std::nullopt);
}


TEST(StateDefinitionImporterTest, IdCanBeImported)
{
   std::stringstream input;
   input << "= {\n";
   input << "\tid = 42\n";
   input << "}";

   hoi4_map_drawer::state_definitions::StateDefinitionImporter importer;
   const auto state_data = importer.ImportState(input);

   ASSERT_TRUE(state_data.has_value());
   EXPECT_EQ(state_data->first, 42);
}


TEST(StateDefinitionImporterTest, ReturnsEmptyVectorIfMissingProvinces)
{
   std::stringstream input;
   input << "= {\n";
   input << "\tid = 42\n";
   input << "}";

   hoi4_map_drawer::state_definitions::StateDefinitionImporter importer;
   const auto state_data = importer.ImportState(input);

   ASSERT_TRUE(state_data.has_value());
   EXPECT_TRUE(state_data->second.empty());
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

   hoi4_map_drawer::state_definitions::StateDefinitionImporter importer;
   const auto state_data = importer.ImportState(input);

   ASSERT_TRUE(state_data.has_value());
   EXPECT_THAT(state_data->second, testing::ElementsAre(1, 4, 9, 16));
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

   hoi4_map_drawer::state_definitions::StateDefinitionImporter importer;
   auto state_data = importer.ImportState(input);
   state_data.reset();  // make the annoying warning go away

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}