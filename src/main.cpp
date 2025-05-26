#define cimg_verbosity 0
#define cimg_display 0

#include <external/CImg/CImg.h>
#include <external/commonItems/Log.h>
#include <external/commonItems/ModLoader/Mod.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <external/commonItems/ModLoader/ModLoader.h>

#include <filesystem>
#include <fstream>
#include <ranges>

#include "map_drawer/controller_drawer.h"
#include "src/configuration/configuration.h"
#include "src/country_colors/country_color_importer.h"
#include "src/map_drawer/faction_controller_drawer.h"
#include "src/map_drawer/faction_ownership_drawer.h"
#include "src/map_drawer/ownership_drawer.h"
#include "src/map_importer/map_importer.h"
#include "src/save_reader/save_importer.h"
#include "src/state_definitions/state_definitions_importer.h"



int main()
{
   try
   {
      Log(LogLevel::Info) << "Loading configuration";
      const auto configuration = hoi4_map_drawer::ImportConfiguration("configuration.txt");
      Log(LogLevel::Progress) << "5";

      Log(LogLevel::Info) << "Importing save";
      hoi4_map_drawer::SaveImporter save_importer;
      const auto save = save_importer.ImportSave(configuration.save_location);
      Log(LogLevel::Progress) << "15";

      Log(LogLevel::Info) << "Reading mods";
      commonItems::ModLoader mod_loader;
      mod_loader.loadMods(configuration.documents_folder, save.GetMods());
      mod_loader.sortMods();
      commonItems::ModFilesystem mod_filesystem(configuration.hoi4_folder, mod_loader.getMods());
      Log(LogLevel::Progress) << "20";

      Log(LogLevel::Info) << "Importing HoI4 map.";
      const auto provinces_bmp_location = mod_filesystem.GetActualFileLocation("map/provinces.bmp");
      if (!provinces_bmp_location)
      {
         throw std::runtime_error("map/provinces.bmp couldn't be found!");
      }
      const cimg_library::CImg<uint8_t> provinces_image(provinces_bmp_location->string().c_str());
      const auto map_definitions = hoi4_map_drawer::GetProvinceDefinitions(mod_filesystem, provinces_image);
      Log(LogLevel::Progress) << "50";

      Log(LogLevel::Info) << "Importing state definitions";
      const auto state_definitions = hoi4_map_drawer::StateDefinitionsImporter{}.ImportStateDefinitions(mod_filesystem);
      Log(LogLevel::Progress) << "60";

      Log(LogLevel::Info) << "Importing country colors";
      const auto tags_to_colors_map =
          hoi4_map_drawer::ImportCountryColors(mod_filesystem, save.GetTagsToCosmeticTagsMap());
      Log(LogLevel::Progress) << "65";

      Log(LogLevel::Info) << "Drawing ownership map";
      hoi4_map_drawer::DrawOwnershipMap(provinces_image.width(),
          provinces_image.height(),
          state_definitions,
          save.GetStates(),
          tags_to_colors_map,
          map_definitions);
      Log(LogLevel::Progress) << "70";

      Log(LogLevel::Info) << "Drawing controller map";
      hoi4_map_drawer::DrawControllerMap(provinces_image.width(),
          provinces_image.height(),
          state_definitions,
          save.GetStates(),
          save.GetControlledProvinces(),
          tags_to_colors_map,
          map_definitions);
      Log(LogLevel::Progress) << "80";

      Log(LogLevel::Info) << "Drawing faction ownership map";
      hoi4_map_drawer::DrawFactionOwnershipMap(provinces_image.width(),
          provinces_image.height(),
          state_definitions,
          save.GetStates(),
          tags_to_colors_map,
          save.GetTagsToFactionLeaderMap(),
          map_definitions);
      Log(LogLevel::Progress) << "90";

      Log(LogLevel::Info) << "Drawing faction controller map";
      hoi4_map_drawer::DrawFactionControllerMap(provinces_image.width(),
          provinces_image.height(),
          state_definitions,
          save.GetStates(),
          save.GetControlledProvinces(),
          tags_to_colors_map,
          save.GetTagsToFactionLeaderMap(),
          map_definitions);
      Log(LogLevel::Progress) << "100";

      Log(LogLevel::Info) << "All done! Maps are in the MapDrawer folder.";
   }
   catch (const std::exception& e)
   {
      LOG(LogLevel::Error) << e.what();
      return -1;
   }

   return 0;
}