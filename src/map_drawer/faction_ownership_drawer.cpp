#define cimg_verbosity 0
#define cimg_display 0

#include "src/map_drawer/faction_ownership_drawer.h"

#include <external/CImg/CImg.h>
#include <external/commonItems/Color.h>

#include "src/map_drawer/drawer_utils.h"



namespace
{

commonItems::Color DetermineColor(int state_number,
    const std::map<int, hoi4_map_drawer::State>& save_states,
    const std::map<std::string, commonItems::Color>& tags_to_colors_map,
    const std::map<std::string, std::string>& tags_to_faction_leader_map)
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

   const auto& faction_leader = tags_to_faction_leader_map.find(*owner);
   if (faction_leader == tags_to_faction_leader_map.end())
   {
      return commonItems::Color(std::array<int, 3>{0, 0, 0});
   }

   const auto color_mapping = tags_to_colors_map.find(faction_leader->second);
   if (color_mapping == tags_to_colors_map.end())
   {
      return commonItems::Color(std::array<int, 3>{0, 0, 0});
   }
   return color_mapping->second;
}

}  // namespace


void hoi4_map_drawer::DrawFactionOwnershipMap(int width,
    int height,
    const std::map<int, std::vector<int>>& state_definitions,
    const std::map<int, State>& save_states,
    const std::map<std::string, commonItems::Color>& tags_to_colors_map,
    const std::map<std::string, std::string>& tags_to_faction_leader_map,
    const std::map<int, std::set<Pixel>>& map_definitions)
{
   auto ownership_map = CreateBaseMap(width, height);

   for (const auto& [state_number, state_provinces]: state_definitions)
   {
      const auto state_color =
          DetermineColor(state_number, save_states, tags_to_colors_map, tags_to_faction_leader_map);
      for (const auto& province: state_provinces)
      {
         ColorProvince(province, map_definitions, state_color, ownership_map);
      }
   }

   ownership_map.save_bmp("faction_ownership_map.bmp");
}