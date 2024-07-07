#include "src/map_importer/map_importer.h"

#include <sstream>

// clang-format off
// gtest must be before CImg, else we get compile errors
#define cimg_display 0
#include <external/googletest/googletest/include/gtest/gtest.h>
#include <external/googletest/googlemock/include/gmock/gmock.h>
#include <external/CImg/CImg.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>
// clang-format on



using hoi4_map_drawer::map_importer::GetProvinceDefinitions;
using hoi4_map_drawer::map_importer::Pixel;
using testing::UnorderedElementsAre;



TEST(MapImporterTest, MissingDefinitionDotCsvThrowsException)
{
   const commonItems::ModFilesystem mod_filesystem("./test_data/map_importer_test/missing_definition.csv", {});

   const cimg_library::CImg<uint8_t> provinces_image(
       "./test_data/map_importer_test/missing_definition.csv/map/provinces.bmp");
   EXPECT_THROW(GetProvinceDefinitions(mod_filesystem, provinces_image), std::runtime_error);
}


TEST(MapImporterTest, ProvinceDefinitionsAreImported)
{
   const commonItems::ModFilesystem mod_filesystem("./test_data/map_importer_test/valid_map_data", {});

   const cimg_library::CImg<uint8_t> provinces_image("./test_data/map_importer_test/valid_map_data/map/provinces.bmp");
   const auto province_definitions = GetProvinceDefinitions(mod_filesystem, provinces_image);

   EXPECT_EQ(province_definitions.size(), 3);
   ASSERT_TRUE(province_definitions.contains(1));
   EXPECT_THAT(province_definitions.at(1),
       UnorderedElementsAre(Pixel{0, 0},
           Pixel{0, 1},
           Pixel{0, 2},
           Pixel{0, 3},
           Pixel{0, 4},
           Pixel{0, 5},
           Pixel{0, 6},
           Pixel{0, 7},
           Pixel{1, 0},
           Pixel{1, 1},
           Pixel{1, 2},
           Pixel{1, 3},
           Pixel{1, 4},
           Pixel{1, 5},
           Pixel{1, 6},
           Pixel{1, 7},
           Pixel{2, 0},
           Pixel{2, 1},
           Pixel{2, 2},
           Pixel{2, 3},
           Pixel{2, 4},
           Pixel{2, 5},
           Pixel{2, 6},
           Pixel{2, 7},
           Pixel{3, 0},
           Pixel{3, 1},
           Pixel{3, 2},
           Pixel{3, 3},
           Pixel{3, 4},
           Pixel{3, 5},
           Pixel{3, 6},
           Pixel{3, 7}));
   ASSERT_TRUE(province_definitions.contains(2));
   EXPECT_THAT(province_definitions.at(2),
       UnorderedElementsAre(Pixel{4, 0},
           Pixel{4, 1},
           Pixel{4, 2},
           Pixel{4, 3},
           Pixel{5, 0},
           Pixel{5, 1},
           Pixel{5, 2},
           Pixel{5, 3},
           Pixel{6, 0},
           Pixel{6, 1},
           Pixel{6, 2},
           Pixel{6, 3},
           Pixel{7, 0},
           Pixel{7, 1},
           Pixel{7, 2},
           Pixel{7, 3}));
   ASSERT_TRUE(province_definitions.contains(3));
   EXPECT_THAT(province_definitions.at(3),
       UnorderedElementsAre(Pixel{4, 4},
           Pixel{4, 5},
           Pixel{4, 6},
           Pixel{4, 7},
           Pixel{5, 4},
           Pixel{5, 5},
           Pixel{5, 6},
           Pixel{5, 7},
           Pixel{6, 4},
           Pixel{6, 5},
           Pixel{6, 6},
           Pixel{6, 7},
           Pixel{7, 4},
           Pixel{7, 5},
           Pixel{7, 6},
           Pixel{7, 7}));
}


TEST(MapImporterTest, BadDefinitionLinesAreLogged)
{
   std::stringstream log;
   std::streambuf* cout_buffer = std::cout.rdbuf();
   std::cout.rdbuf(log.rdbuf());

   const commonItems::ModFilesystem mod_filesystem("./test_data/map_importer_test/valid_map_data", {});

   const cimg_library::CImg<uint8_t> provinces_image("./test_data/map_importer_test/valid_map_data/map/provinces.bmp");
   auto province_definitions = GetProvinceDefinitions(mod_filesystem, provinces_image);
   province_definitions.clear();  // make the annoying warning go away

   EXPECT_THAT(log.str(), testing::HasSubstr("[WARNING] Broken Definition Line: 10;broken_line; - "));

   std::cout.rdbuf(cout_buffer);
}