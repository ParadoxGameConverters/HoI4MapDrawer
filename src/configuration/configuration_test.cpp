#include "src/configuration/configuration.h"

#include <sstream>

#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(ConfigurationTest, MissingFileThrowsException)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   hoi4_map_drawer::configuration::ImportConfiguration("./test_data/configuration/missing_config.txt");

   EXPECT_THAT(log.str(),
       testing::HasSubstr("[ERROR] Could not open ./test_data/configuration/missing_config.txt for parsing."));

   std::cout.rdbuf(cout_buffer);
}


TEST(ConfigurationTest, ItemsAreDefaulted)
{
   const auto configuration =
       hoi4_map_drawer::configuration::ImportConfiguration("./test_data/configuration/empty_config.txt");
   EXPECT_TRUE(configuration.hoi4_folder.empty());
   EXPECT_TRUE(configuration.documents_folder.empty());
   EXPECT_TRUE(configuration.save_location.empty());
}


TEST(ConfigurationTest, ItemsCanBeSet)
{
   const auto configuration =
       hoi4_map_drawer::configuration::ImportConfiguration("./test_data/configuration/test_config.txt");
   EXPECT_EQ(configuration.hoi4_folder, "test_hoi4_folder");
   EXPECT_EQ(configuration.documents_folder, "test_documents_folder");
   EXPECT_EQ(configuration.save_location, "test_save_location");
}