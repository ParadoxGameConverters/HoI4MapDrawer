#include "src/state_definitions/state_definitions_importer.h"

#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(StateDefinitionsImporterTest, ReturnsNulloptIfMissingId)
{
   hoi4_map_drawer::state_definitions::StateDefinitionsImporter importer;

   EXPECT_TRUE(importer.ImportStateDefinitions("./test_data/state_definitions/empty_folder").empty());
}


TEST(StateDefinitionsImporterTest, ReturnsStateDefinitions)
{
   hoi4_map_drawer::state_definitions::StateDefinitionsImporter importer;

   EXPECT_THAT(importer.ImportStateDefinitions("./test_data/state_definitions/state_definitions"),
       testing::UnorderedElementsAre(testing::Pair(2, std::vector{2, 4, 8, 16}),
           testing::Pair(3, std::vector{3, 9, 27, 81})));
}