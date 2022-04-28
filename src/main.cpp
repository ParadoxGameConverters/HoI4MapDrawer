#include <filesystem>
#include <fstream>
#include <ranges>

#include "external/commonItems/Log.h"
#include "rakaly_wrapper.h"
#include "src/country_colors/country_color_importer.h"
#include "src/map_drawer/ownership_drawer.h"
#include "src/map_importer/map_importer.h"
#include "src/save_reader/save_importer.h"
#include "src/state_definitions/state_definitions_importer.h"



int main()
{
   try
   {
      Log(LogLevel::Info) << "-> Importing HoI4 map.";
      const auto map_definitions = hoi4_map_drawer::map_importer::GetProvinceDefinitions(
          "C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV");

      Log(LogLevel::Info) << "Importing state definitions";
      const auto state_definitions =
          hoi4_map_drawer::state_definitions::StateDefinitionsImporter{}.ImportStateDefinitions(
              "C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV");

      Log(LogLevel::Info) << "Importing save";
      hoi4_map_drawer::save_reader::SaveImporter save_importer;
      const auto save = save_importer.ImportSave("../../data/saves/input.hoi4");

      Log(LogLevel::Info) << "Importing country colors";
      const auto tags_to_colors_map = hoi4_map_drawer::country_colors::ImportCountryColors(
          "C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV");

      Log(LogLevel::Info) << "Drawing ownership map";
      hoi4_map_drawer::map_importer::DrawOwnershipMap(state_definitions,
          save.GetStates(),
          tags_to_colors_map,
          map_definitions);
   }
   catch (const std::exception& e)
   {
      LOG(LogLevel::Error) << e.what();
      return -1;
   }

   return 0;
}