#include "src/save_reader/provinces_importer.h"

#include <external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/googletest/googletest/include/gtest/gtest.h>

#include <sstream>



TEST(ProvincesImporterTest, EmptyMapWhenNoProvinces)
{
   hoi4_map_drawer::save_reader::ProvincesImporter importer;

   std::stringstream input;
   input << "= {\n";
   input << "}";

   const auto province_controllers = importer.ImportProvinces(input);
   EXPECT_TRUE(province_controllers.empty());
}


TEST(ProvincesImporterTest, EmptyMapWhenNoControllers)
{
   hoi4_map_drawer::save_reader::ProvincesImporter importer;

   std::stringstream input;
   input << "= {\n";
   input << "\t1={\n";
   input << "\t}\n";
   input << "}";

   const auto province_controllers = importer.ImportProvinces(input);
   EXPECT_TRUE(province_controllers.empty());
}


TEST(ProvincesImporterTest, ControllersCanBeImported)
{
   hoi4_map_drawer::save_reader::ProvincesImporter importer;

   std::stringstream input;
   input << "= {\n";
   input << "\t1={\n";
   input << "\t\tcontroller=\"TAG\"\n";
   input << "\t}\n";
   input << "\t2={\n";
   input << "\t\tcontroller=\"TAG\"\n";
   input << "\t}\n";
   input << "\t3={\n";
   input << "\t\tcontroller=\"TWO\"\n";
   input << "\t}\n";
   input << "\t4={\n";
   input << "\t\tcontroller=\"TWO\"\n";
   input << "\t}\n";
   input << "}";

   const auto province_controllers = importer.ImportProvinces(input);
   EXPECT_THAT(province_controllers,
       testing::UnorderedElementsAre(testing::Pair(1, "TAG"),
           testing::Pair(2, "TAG"),
           testing::Pair(3, "TWO"),
           testing::Pair(4, "TWO")));
}