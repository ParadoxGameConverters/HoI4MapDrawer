#include "src/map_drawer/drawer_utils.h"



cimg_library::CImg<uint8_t> hoi4_map_drawer::map_drawer::CreateBaseMap(int width, int height)
{
   cimg_library::CImg<uint8_t> map(width, height, 1, 3);
   map.fill(255);
   return map;
}


void hoi4_map_drawer::map_drawer::ColorProvince(int province,
    const std::map<int, std::set<hoi4_map_drawer::map_importer::Pixel>>& map_definitions,
    const commonItems::Color& color,
    cimg_library::CImg<uint8_t>& map)
{
   const auto& definition = map_definitions.find(province);
   if (definition == map_definitions.end())
   {
      return;
   }

   for (const auto& pixel: definition->second)
   {
      map(pixel.x, pixel.y, 0, 0) = color.r();
      map(pixel.x, pixel.y, 0, 1) = color.g();
      map(pixel.x, pixel.y, 0, 2) = color.b();
   }
}