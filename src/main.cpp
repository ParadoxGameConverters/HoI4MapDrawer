#include <filesystem>
#include <fstream>
#include <ranges>

#include "external/commonItems/Log.h"
#include "src/map_importer/map_importer.h"
#include "src/rakaly_wrapper.h"
#include "src/save_reader/save_importer.h"
#include "src/state_definitions/state_definitions_importer.h"



namespace
{


std::string UnmeltSaveIfNeeded(const std::string& save_data)
{
   if (save_data.starts_with("HOI4bin"))
   {
      return rakaly::meltHoi4(save_data);
   }

   return save_data;
}


}  // namespace



int main()
{
   try
   {
      Log(LogLevel::Info) << "-> Importing HoI4 save.";
      std::ifstream inBinary(std::filesystem::path(u8"input.hoi4"), std::ios::binary);
      if (!inBinary.is_open())
      {
         throw std::runtime_error("Could not open input.hoi4 for parsing.");
      }
      std::stringstream inStream;
      inStream << inBinary.rdbuf();
      Log(LogLevel::Progress) << "8 %";

      const auto unmelted_save = UnmeltSaveIfNeeded(inStream.str());
      Log(LogLevel::Progress) << "9 %";

      auto game_state = std::istringstream(unmelted_save);
      std::string line;
      std::getline(game_state, line);
      Log(LogLevel::Info) << line;
      Log(LogLevel::Progress) << "15 %";

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
      const auto save = save_importer.ImportSave("../../data/saves/USA_1936_01_01_12.hoi4");
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
   }
   catch (const std::exception& e)
   {
      LOG(LogLevel::Error) << e.what();
      return -1;
   }

   return 0;
}