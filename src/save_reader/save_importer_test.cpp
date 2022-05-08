#include "src/save_reader/save_importer.h"

#include <sstream>

#include "external/commonItems/ModLoader/Mod.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(SaveImporterTest, MissingFileThrowsException)
{
   hoi4_map_drawer::save_reader::SaveImporter importer;
   EXPECT_THROW(importer.ImportSave("./test_data/save_reader/missing_save.hoi4"), std::runtime_error);
}


TEST(SaveImporterTest, DefaultsAreSet)
{
   hoi4_map_drawer::save_reader::SaveImporter importer;
   const auto save = importer.ImportSave("./test_data/save_reader/empty_save.hoi4");

   EXPECT_TRUE(save.GetStates().empty());
   EXPECT_TRUE(save.GetMods().empty());
   EXPECT_TRUE(save.GetControlledProvinces().empty());
}


TEST(SaveImporterTest, ItemsAreImported)
{
   hoi4_map_drawer::save_reader::SaveImporter importer;
   const auto save = importer.ImportSave("./test_data/save_reader/good_save.hoi4");

   EXPECT_THAT(save.GetStates(),
       testing::UnorderedElementsAre(testing::Pair(1, hoi4_map_drawer::save_reader::State(1, "TAG")),
           testing::Pair(2, hoi4_map_drawer::save_reader::State(2, "TWO"))));
   EXPECT_THAT(save.GetMods(), testing::ElementsAre(Mod("Mod One", ""), Mod("Mod Two", "")));
   EXPECT_THAT(save.GetControlledProvinces(),
       testing::ElementsAre(testing::Pair(1, "TAG"),
           testing::Pair(2, "TAG"),
           testing::Pair(3, "TWO"),
           testing::Pair(4, "TWO")));
}


TEST(SaveImporterTest, ExtraDataInSaveIsIgnored)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   hoi4_map_drawer::save_reader::SaveImporter importer;
   const auto save = importer.ImportSave("./test_data/save_reader/extra_data_save.hoi4");
   auto states = save.GetStates();  // make the annoying warning go away
   states.clear();                  // make the annoying warning go away

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}