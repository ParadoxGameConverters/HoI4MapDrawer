#include "src/save_reader/save_importer.h"

#include <sstream>

#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(SaveImporterTest, MissingFileIsLogged)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   std::stringstream input;
   input << "= {\n";
   input << "\tunhandled_input = 42\n";
   input << "}";

   hoi4_map_drawer::save_reader::SaveImporter importer;
   auto save = importer.ImportSave("./test_data/save_reader/missing_save.hoi4");
   auto states = save.GetStates();  // make the annoying warning go away
   states.clear();                  // make the annoying warning go away

   EXPECT_THAT(log.str(),
       testing::HasSubstr("[ERROR] Could not open ./test_data/save_reader/missing_save.hoi4 for parsing."));

   std::cout.rdbuf(cout_buffer);
}


TEST(SaveImporterTest, NoStatesFromEmptySave)
{
   hoi4_map_drawer::save_reader::SaveImporter importer;
   const auto save = importer.ImportSave("./test_data/save_reader/empty_save.hoi4");

   EXPECT_TRUE(save.GetStates().empty());
}


TEST(SaveImporterTest, StatesAreImported)
{
   hoi4_map_drawer::save_reader::SaveImporter importer;
   const auto save = importer.ImportSave("./test_data/save_reader/good_save.hoi4");

   EXPECT_THAT(save.GetStates(),
       testing::UnorderedElementsAre(testing::Pair(1, hoi4_map_drawer::save_reader::State(1, "TAG")),
           testing::Pair(2, hoi4_map_drawer::save_reader::State(2, "TWO"))));
}


TEST(SaveImporterTest, ExtraDataInSaveIsIgnored)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   hoi4_map_drawer::save_reader::SaveImporter importer;
   auto save = importer.ImportSave("./test_data/save_reader/extra_data_save.hoi4");
   auto states = save.GetStates();  // make the annoying warning go away
   states.clear();                  // make the annoying warning go away

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}