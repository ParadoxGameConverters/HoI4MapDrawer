#include "src/map_importer.h"

#include <string>

#include "external/CImg/CImg.h"



namespace hoi4_map_drawer
{
namespace map_importer
{


namespace
{

std::map<int32_t, std::set<Pixel>> GetColorToPixelDefinitions(const std::string& map_folder)
{
   std::map<int32_t, std::set<Pixel>> definitions;
   cimg_library::CImg<int32_t> provinces_image((map_folder + "/provinces.bmp").c_str());

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

}  // namespace


std::map<int, std::set<Pixel>> GetProvinceDefinitions()
{
   return GetColorToPixelDefinitions("C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV/map");
}


}  // namespace map_importer
}  // namespace hoi4_map_drawer
