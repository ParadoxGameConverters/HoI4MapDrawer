#include <filesystem>
#include <fstream>
#include <ranges>

#define cimg_verbosity 0
#define cimg_display 0
#include "external/CImg/CImg.h"
#include "external/commonItems/Log.h"
#include "rakaly_wrapper.h"
#include "src/country_colors/country_color_importer.h"
#include "src/map_importer/map_importer.h"
#include "src/save_reader/save_importer.h"
#include "src/state_definitions/state_definitions_importer.h"



int main()
{
   try
   {
      Log(LogLevel::Info) << "-> Importing HoI4 map.";
      Log(LogLevel::Progress) << "20 %";
      const auto map_definitions = hoi4_map_drawer::map_importer::GetProvinceDefinitions(
          "C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV");

      std::stringstream pixel_log;
      pixel_log << "Pixels of province ";
      for (const auto& province: map_definitions | std::views::keys | std::views::take(1))
      {
         pixel_log << province;
      }
      pixel_log << ": ";
      for (const auto& province_pixels: map_definitions | std::views::values | std::views::take(1))
      {
         for (const auto& pixel: province_pixels)
         {
            pixel_log << "(" << pixel.x << ", " << pixel.y << "), ";
         }
      }
      Log(LogLevel::Info) << pixel_log.str();

      const auto state_definitions =
          hoi4_map_drawer::state_definitions::StateDefinitionsImporter{}.ImportStateDefinitions(
              "C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV");
      std::stringstream state_log;
      state_log << "Provinces of state ";
      for (const auto& state: state_definitions | std::views::keys | std::views::take(1))
      {
         state_log << state;
      }
      state_log << ": ";
      for (const auto& provinces: state_definitions | std::views::values | std::views::take(1))
      {
         for (const auto& province: provinces)
         {
            state_log << province << " ";
         }
      }
      Log(LogLevel::Info) << state_log.str();

      hoi4_map_drawer::save_reader::SaveImporter save_importer;
      const auto save = save_importer.ImportSave("../../data/saves/input.hoi4");
      const auto& save_states = save.GetStates();
      std::stringstream save_log;
      save_log << "Owner of state ";
      for (const auto& state: save_states | std::views::keys | std::views::take(1))
      {
         save_log << state;
      }
      save_log << ": ";
      for (const auto& state: save_states | std::views::values | std::views::take(1))
      {
         if (const auto& owner = state.GetOwner(); owner)
         {
            save_log << *owner << " ";
         }
         else
         {
            save_log << "none ";
         }
      }
      Log(LogLevel::Info) << save_log.str();

      const auto tags_to_colors_map = hoi4_map_drawer::country_colors::ImportCountryColors(
          "C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV");
      std::stringstream colors_log;
      colors_log << "Tag ";
      for (const auto& tag: tags_to_colors_map | std::views::keys | std::views::take(1))
      {
         colors_log << tag;
      }
      colors_log << " is color ";
      for (const auto& color: tags_to_colors_map | std::views::values | std::views::take(1))
      {
         colors_log << color;
      }
      Log(LogLevel::Info) << colors_log.str();

      cimg_library::CImg<uint8_t> ownership_map(5632, 2048, 1, 3);
      ownership_map.fill(255);
      for (const auto& [state_number, state_provinces]: state_definitions)
      {
         commonItems::Color state_color(std::array{0, 0, 0});
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
   catch (const std::exception& e)
   {
      LOG(LogLevel::Error) << e.what();
      return -1;
   }

   return 0;
}