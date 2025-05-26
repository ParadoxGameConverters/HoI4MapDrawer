#include "src/save_reader/states_importer.h"

#include <external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/googletest/googletest/include/gtest/gtest.h>

#include <sstream>



TEST(StatesImporterTest, ReturnsNothingIfNoStates)
{
   std::stringstream input;

   hoi4_map_drawer::StatesImporter importer;
   EXPECT_TRUE(importer.ImportStates(input).empty());
}


TEST(StatesImporterTest, StatesCanBeImported)
{
   std::stringstream input;
   input << "={\n";
   input << "\t1={\n";
   input << "\t\towner=\"TAG\"\n";
   input << "\t}\n";
   input << "\t2={\n";
   input << "\t\towner=\"TWO\"\n";
   input << "\t}\n";
   input << "}";

   hoi4_map_drawer::StatesImporter importer;
   EXPECT_THAT(importer.ImportStates(input),
       testing::UnorderedElementsAre(testing::Pair(1, hoi4_map_drawer::State(1, "TAG")),
           testing::Pair(2, hoi4_map_drawer::State(2, "TWO"))));
}


TEST(StatesImporterTest, ExtraInputIsIgnored)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   std::stringstream input;
   input << "= {\n";
   input << "\tunhandled_input = 42\n";
   input << "}";

   hoi4_map_drawer::StatesImporter importer;
   auto states = importer.ImportStates(input);
   states.clear();  // make the annoying warning go away

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}