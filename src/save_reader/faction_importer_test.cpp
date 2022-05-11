#include "src/save_reader/faction_importer.h"

#include <sstream>

#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(FactionImporterTest, EmptyMapWhenNoMembers)
{
   hoi4_map_drawer::save_reader::FactionImporter faction_importer;

   std::stringstream input;

   EXPECT_TRUE(faction_importer.ImportFaction(input).empty());
}


TEST(FactionImporterTest, MembersCanBeInput)
{
   hoi4_map_drawer::save_reader::FactionImporter faction_importer;

   std::stringstream input;
   input << "= {\n";
   input << "\tmembers = { \n";
   input << "\t\t\"UTA\"\n";
   input << "\t\t\"CAN\"\n";
   input << "\t}\n";
   input << "}";

   EXPECT_THAT(faction_importer.ImportFaction(input),
       testing::UnorderedElementsAre(testing::Pair("UTA", "UTA"), testing::Pair("CAN", "UTA")));
}


TEST(FactionImporterTest, ExtraDataIsIgnored)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   hoi4_map_drawer::save_reader::FactionImporter faction_importer;

   std::stringstream input;
   input << "= {\n";
   input << "\tideology=democratic\n";
   input << "\tmembers = {\n";
   input << "\t\t\"UTA\"\n";
   input << "\t\t\"CAN\"\n";
   input << "\t}\n";
   input << "}";

   auto mappings = faction_importer.ImportFaction(input);
   mappings.clear();  // make the annoying warning go away

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}