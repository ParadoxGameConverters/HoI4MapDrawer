#include "src/map_drawer/faction_controller_drawer.h"

#define cimg_verbosity 0
#define cimg_display 0
#include "external/CImg/CImg.h"
#include "external/commonItems/Color.h"
#include "src/map_drawer/drawer_utils.h"



namespace
{

commonItems::Color DetermineColor(const std::string& tag,
    const std::map<std::string, std::string>& tags_to_faction_leader_map,
    const std::map<std::string, commonItems::Color>& tags_to_colors_map)
{
   const auto& faction_leader = tags_to_faction_leader_map.find(tag);
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


commonItems::Color DetermineStateColor(int state_number,
    const std::map<int, hoi4_map_drawer::save_reader::State>& save_states,
    const std::map<std::string, std::string>& tags_to_faction_leader_map,
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

   return DetermineColor(*owner, tags_to_faction_leader_map, tags_to_colors_map);
}

}  // namespace


void hoi4_map_drawer::map_drawer::DrawFactionControllerMap(int width,
    int height,
    const std::map<int, std::vector<int>>& state_definitions,
    const std::map<int, save_reader::State>& save_states,
    const std::map<int, std::string>& controlled_provinces,
    const std::map<std::string, commonItems::Color>& tags_to_colors_map,
    const std::map<std::string, std::string>& tags_to_faction_leader_map,
    const std::map<int, std::set<map_importer::Pixel>>& map_definitions)
{
   auto controller_map = CreateBaseMap(width, height);

   for (const auto& [state_number, state_provinces]: state_definitions)
   {
      const auto state_color =
          DetermineStateColor(state_number, save_states, tags_to_faction_leader_map, tags_to_colors_map);
      for (const auto& province: state_provinces)
      {
         ColorProvince(province, map_definitions, state_color, controller_map);
      }
   }

   for (const auto& [province_number, owner]: controlled_provinces)
   {
      const auto province_color = DetermineColor(owner, tags_to_faction_leader_map, tags_to_colors_map);
      ColorProvince(province_number, map_definitions, province_color, controller_map);
   }

   controller_map.save_bmp("faction_controller_map.bmp");
}