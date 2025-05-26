#include "src/state_definitions/state_definitions_importer.h"

#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/googletest/googletest/include/gtest/gtest.h>



TEST(StateDefinitionsImporterTest, ReturnsNulloptIfMissingId)
{
   const commonItems::ModFilesystem mod_filesystem(std::filesystem::path("./test_data/state_definitions/empty_folder"),
       {});
   hoi4_map_drawer::StateDefinitionsImporter importer;

   EXPECT_TRUE(importer.ImportStateDefinitions(mod_filesystem).empty());
}


TEST(StateDefinitionsImporterTest, ReturnsStateDefinitions)
{
   const commonItems::ModFilesystem mod_filesystem(
       std::filesystem::path("./test_data/state_definitions/state_definitions"),
       {});
   hoi4_map_drawer::StateDefinitionsImporter importer;

   EXPECT_THAT(importer.ImportStateDefinitions(mod_filesystem),
       testing::UnorderedElementsAre(testing::Pair(2, std::vector{2, 4, 8, 16}),
           testing::Pair(3, std::vector{3, 9, 27, 81})));
}


TEST(StateDefinitionsImporterTest, ExtraInputIsIgnored)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   const commonItems::ModFilesystem mod_filesystem(
       std::filesystem::path("./test_data/state_definitions/state_definitions"),
       {});
   hoi4_map_drawer::StateDefinitionsImporter importer;
   auto state_data = importer.ImportStateDefinitions(mod_filesystem);
   state_data.clear();  // make the annoying warning go away

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}