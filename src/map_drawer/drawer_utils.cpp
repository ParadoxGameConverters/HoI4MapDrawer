#include "src/map_drawer/drawer_utils.h"



cimg_library::CImg<uint8_t> hoi4_map_drawer::CreateBaseMap(int width, int height)
{
   cimg_library::CImg<uint8_t> map(width, height, 1, 3);
   map.fill(255);
   return map;
}

#pragma warning(push)
#pragma warning(disable : 4242)
#pragma warning(disable : 4244)
// This is the way CImg wants to work, even if it makes modern compilers unhappy
void hoi4_map_drawer::ColorProvince(int province,
    const std::map<int, std::set<hoi4_map_drawer::Pixel>>& map_definitions,
    const commonItems::Color& color,
    cimg_library::CImg<uint8_t>& map)
{
   const auto& definition = map_definitions.find(province);
   if (definition == map_definitions.end())
   {
      return;
   }

   for (auto& pixel: definition->second)
   {
      auto& r = map(pixel.x, pixel.y, 0, 0);
      r = color.r();
      auto& g = map(pixel.x, pixel.y, 0, 1);
      g = color.g();
      auto& b = map(pixel.x, pixel.y, 0, 2);
      b = color.b();
   }
}
#pragma warning(pop)