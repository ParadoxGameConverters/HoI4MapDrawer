#include "src/map_importer/pixel.h"

#include <external/commonItems/external/googletest/googlemock/include/gmock/gmock-matchers.h>
#include <external/commonItems/external/googletest/googletest/include/gtest/gtest.h>



namespace hoi4_map_drawer
{

TEST(PixelTest, EqualityIfBothCoordsAreSame)
{
   const Pixel one{.x = 1, .y = 2};
   const Pixel two{.x = 1, .y = 2};
   EXPECT_EQ(one, two);
}


TEST(PixelTest, InequalityIfXIsDifferent)
{
   const Pixel one{.x = 1, .y = 2};
   const Pixel two{.x = 3, .y = 2};
   EXPECT_NE(one, two);
}


TEST(PixelTest, InequalityIfYIsDifferent)
{
   const Pixel one{.x = 1, .y = 2};
   const Pixel two{.x = 1, .y = 3};
   EXPECT_NE(one, two);
}


TEST(PixelTest, LessIfYIsSmaller)
{
   const Pixel smaller_y{.x = 1, .y = 0};
   const Pixel bigger_y_smaller_x{.x = 0, .y = 1};
   const Pixel bigger_y_equal_x{.x = 1, .y = 1};
   const Pixel bigger_y_larger_x{.x = 2, .y = 1};
   EXPECT_LT(smaller_y, bigger_y_smaller_x);
   EXPECT_LT(smaller_y, bigger_y_equal_x);
   EXPECT_LT(smaller_y, bigger_y_larger_x);
}


TEST(PixelTest, LessIfYIsEqualButXIsSmaller)
{
   const Pixel smaller_x{.x = 0, .y = 0};
   const Pixel equal_y_larger_x{.x = 1, .y = 0};
   EXPECT_LT(smaller_x, equal_y_larger_x);
}

}  // namespace hoi4_map_drawer