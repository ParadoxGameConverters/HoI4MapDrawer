#include "src/map_importer/pixel.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <sstream>

#include "external/googletest/googlemock/include/gmock/gmock.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



using hoi4_map_drawer::map_importer::Pixel;
using testing::UnorderedElementsAre;



TEST(PixelTest, EqualityIfBothCoordsAreSame)
{
   constexpr Pixel one{1, 2};
   constexpr Pixel two{1, 2};
   EXPECT_EQ(one, two);
}


TEST(PixelTest, InequalityIfXIsDifferent)
{
   constexpr Pixel one{1, 2};
   constexpr Pixel two{3, 2};
   EXPECT_NE(one, two);
}


TEST(PixelTest, InequalityIfYIsDifferent)
{
   constexpr Pixel one{1, 2};
   constexpr Pixel two{1, 3};
   EXPECT_NE(one, two);
}


TEST(PixelTest, LessIfYIsSmaller)
{
   constexpr Pixel smaller_y{1, 0};
   constexpr Pixel bigger_y_smaller_x{0, 1};
   constexpr Pixel bigger_y_equal_x{1, 1};
   constexpr Pixel bigger_y_larger_x{2, 1};
   EXPECT_LT(smaller_y, bigger_y_smaller_x);
   EXPECT_LT(smaller_y, bigger_y_equal_x);
   EXPECT_LT(smaller_y, bigger_y_larger_x);
}


TEST(PixelTest, LessIfYIsEqualButXIsSmaller)
{
   constexpr Pixel smaller_x{0, 0};
   constexpr Pixel equal_y_larger_x{1, 0};
   EXPECT_LT(smaller_x, equal_y_larger_x);
}