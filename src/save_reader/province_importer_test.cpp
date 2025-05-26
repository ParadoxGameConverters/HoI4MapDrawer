#include "src/save_reader/province_importer.h"

#include <external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/googletest/googletest/include/gtest/gtest.h>

#include <sstream>



TEST(ProvinceImporterTest, NulloptReturnedWhenNoController)
{
   hoi4_map_drawer::ProvinceImporter importer;

   std::stringstream input;
   input << "= {\n";
   input << "}";

   const auto province_controller = importer.ImportProvince(input);
   EXPECT_FALSE(province_controller.has_value());
}


TEST(ProvinceImporterTest, ControllerCanBeImported)
{
   hoi4_map_drawer::ProvinceImporter importer;

   std::stringstream input;
   input << "= {\n";
   input << "\tcontroller=\"TAG\"\n";
   input << "}";

   const auto province_controller = importer.ImportProvince(input);
   ASSERT_TRUE(province_controller.has_value());
   EXPECT_EQ(province_controller.value(), "TAG");
}


TEST(ProvinceImporterTest, ExtraDataInProvinceIsIgnored)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   hoi4_map_drawer::ProvinceImporter importer;

   std::stringstream input;
   input << "= {\n";
   input << "\tcontroller=\"TAG\"\n";
   input << "\tjunk=whatever\n";
   input << "}";

   auto province_controller = importer.ImportProvince(input);
   auto controller = province_controller.value();  // make the annoying warning go away
   controller.clear();                             // make the annoying warning go away

   EXPECT_TRUE(log.str().empty());

   std::cout.rdbuf(cout_buffer);
}