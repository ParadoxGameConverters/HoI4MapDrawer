#include "src/map_drawer/ownership_drawer.h"

#define cimg_verbosity 0
#define cimg_display 0
#include "external/CImg/CImg.h"
#include "external/commonItems/Color.h"



namespace
{

cimg_library::CImg<uint8_t> CreateBaseMap(int width, int height)
{
   cimg_library::CImg<uint8_t> map(width, height, 1, 3);
   map.fill(255);
   return map;
}


commonItems::Color DetermineColor(int state_number,
    const std::map<int, hoi4_map_drawer::save_reader::State>& save_states,
    const std::map<std::string, commonItems::Color>& tags_to_colors_map)
{
   const auto save_state = save_states.find(state_number);
   if (save_state == save_states.end())
   {
      return commonItems::Color(std::array<int, 3>{0, 0, 0});
   }

   const auto& owner = save_state->second.GetOwner();
   if (!owner)
   {
      return commonItems::Color(std::array<int, 3>{0, 0, 0});
   }

   const auto color_mapping = tags_to_colors_map.find(*owner);
   if (color_mapping == tags_to_colors_map.end())
   {
      return commonItems::Color(std::array<int, 3>{0, 0, 0});
   }
   return color_mapping->second;
}


void ColorProvince(int province,
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

}  // namespace


void hoi4_map_drawer::map_importer::DrawOwnershipMap(int width,
    int height,
    const std::map<int, std::vector<int>>& state_definitions,
    const std::map<int, save_reader::State>& save_states,
    const std::map<std::string, commonItems::Color>& tags_to_colors_map,
    const std::map<int, std::set<Pixel>>& map_definitions)
{
   auto ownership_map = CreateBaseMap(width, height);

   for (const auto& [state_number, state_provinces]: state_definitions)
   {
      const auto state_color = DetermineColor(state_number, save_states, tags_to_colors_map);
      for (const auto& province: state_provinces)
      {
         ColorProvince(province, map_definitions, state_color, ownership_map);
      }
   }

   ownership_map.save_bmp("ownership_map.bmp");
}