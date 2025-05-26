#define cimg_verbosity 0
#define cimg_display 0

#include "src/map_drawer/controller_drawer.h"

#include <external/CImg/CImg.h>
#include <external/commonItems/Color.h>

#include "src/map_drawer/drawer_utils.h"



namespace
{

commonItems::Color DetermineColor(const std::string& tag,
    const std::map<std::string, commonItems::Color>& tags_to_colors_map)
{
   const auto color_mapping = tags_to_colors_map.find(tag);
   if (color_mapping == tags_to_colors_map.end())
   {
      return commonItems::Color(std::array<int, 3>{0, 0, 0});
   }
   return color_mapping->second;
}


commonItems::Color DetermineStateColor(int state_number,
    const std::map<int, hoi4_map_drawer::State>& save_states,
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

   return DetermineColor(*owner, tags_to_colors_map);
}

}  // namespace


void hoi4_map_drawer::DrawControllerMap(int width,
    int height,
    const std::map<int, std::vector<int>>& state_definitions,
    const std::map<int, State>& save_states,
    const std::map<int, std::string>& controlled_provinces,
    const std::map<std::string, commonItems::Color>& tags_to_colors_map,
    const std::map<int, std::set<Pixel>>& map_definitions)
{
   auto controller_map = CreateBaseMap(width, height);

   for (const auto& [state_number, state_provinces]: state_definitions)
   {
      const auto state_color = DetermineStateColor(state_number, save_states, tags_to_colors_map);
      for (const auto& province: state_provinces)
      {
         ColorProvince(province, map_definitions, state_color, controller_map);
      }
   }

   for (const auto& [province_number, owner]: controlled_provinces)
   {
      const auto province_color = DetermineColor(owner, tags_to_colors_map);
      ColorProvince(province_number, map_definitions, province_color, controller_map);
   }

   controller_map.save_bmp("controller_map.bmp");
}