#include "src/map_drawer/ownership_drawer.h"

#define cimg_verbosity 0
#define cimg_display 0
#include "external/CImg/CImg.h"
#include "external/commonItems/Color.h"


void hoi4_map_drawer::map_importer::DrawOwnershipMap(int width,
    int height,
    const std::map<int, std::vector<int>>& state_definitions,
    const std::map<int, save_reader::State>& save_states,
    const std::map<std::string, commonItems::Color>& tags_to_colors_map,
    const std::map<int, std::set<Pixel>>& map_definitions)
{
   cimg_library::CImg<uint8_t> ownership_map(width, height, 1, 3);
   ownership_map.fill(255);
   for (const auto& [state_number, state_provinces]: state_definitions)
   {
      commonItems::Color state_color(std::array<int, 3>{0, 0, 0});
      const auto save_state = save_states.find(state_number);
      if (save_state != save_states.end())
      {
         const auto& owner = save_state->second.GetOwner();
         if (owner)
         {
            const auto color_mapping = tags_to_colors_map.find(*owner);
            if (color_mapping != tags_to_colors_map.end())
            {
               state_color = color_mapping->second;
            }
         }
      }
      for (const auto& province: state_provinces)
      {
         const auto& definition = map_definitions.find(province);
         if (definition == map_definitions.end())
         {
            continue;
         }

         for (const auto& pixel: definition->second)
         {
            ownership_map(pixel.x, pixel.y, 0, 0) = state_color.r();
            ownership_map(pixel.x, pixel.y, 0, 1) = state_color.g();
            ownership_map(pixel.x, pixel.y, 0, 2) = state_color.b();
         }
      }
   }

   ownership_map.save_bmp("ownership_map.bmp");
}