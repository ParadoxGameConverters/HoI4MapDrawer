#include "src/map_importer.h"

#include "external/CImg/CImg.h"



namespace hoi4_map_drawer
{
namespace map_importer
{


namespace
{


}


std::map<int, std::set<Pixel>> GetProvinceDefinitions()
{
   std::map<int, std::set<Pixel>> definitions;
   cimg_library::CImg<int32_t> provinces_image(
       "C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV/map/provinces.bmp");
   for (int x = 0; x < provinces_image.width(); ++x)
   {
      for (int y = 0; y < provinces_image.height(); ++y)
      {
         const auto pixel = *provinces_image.data(x, y);
         const Pixel coords{.x = x, .y = y};
         if (auto [existing, success] = definitions.emplace(pixel, std::set{coords}); !success)
         {
            existing->second.insert({x, y});
         }
      }
   }

   return definitions;
}


}  // namespace map_importer
}  // namespace hoi4_map_drawer
