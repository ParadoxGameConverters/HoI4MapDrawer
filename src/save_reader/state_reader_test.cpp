#include <gmock/gmock-matchers.h>

#include <sstream>

#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/save_reader/state_importer.h"



TEST(StateImporterTest, ReturnsNulloptIfMissingOwner)
{
   std::stringstream input;

   hoi4_map_drawer::save_reader::StateImporter importer;
   const auto state = importer.ImportState(input);

   EXPECT_EQ(state.GetOwner(), std::nullopt);
}


TEST(StateImporterTest, OwnerCanBeImported)
{
   std::stringstream input;
   input << "= {\n";
   input << "\towner=TAG\n";
   input << "}";

   hoi4_map_drawer::save_reader::StateImporter importer;
   const auto state = importer.ImportState(input);

   ASSERT_TRUE(state.GetOwner());
   EXPECT_EQ(state.GetOwner(), "TAG");
}


TEST(StateImporterTest, ExtraInputIsIgnored)
{
	std::stringstream log;
	std::streambuf* cout_buffer = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	std::stringstream input;
	input << "= {\n";
	input << "\tunhandled_input = 42\n";
	input << "}";

	hoi4_map_drawer::save_reader::StateImporter importer;
	auto state_data = importer.ImportState(input);
	auto owner = state_data.GetOwner();  // make the annoying warning go away
	owner.reset();

	EXPECT_TRUE(log.str().empty());

	std::cout.rdbuf(cout_buffer);
}