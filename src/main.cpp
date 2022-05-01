#include <filesystem>
#include <fstream>
#include <ranges>

#define cimg_verbosity 0
#define cimg_display 0
#include "external/CImg/CImg.h"
#include "external/commonItems/Log.h"
#include "external/commonItems/ModLoader/ModFilesystem.h"
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
      const std::string hoi4_folder = "C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV";
      Mod rsb_mod("Converted - Rome_Strikes_Back",
          "C:/Users/idhre/OneDrive/Documents/Paradox Interactive/Hearts of Iron IV/mod/Rome_Strikes_Back",
          {},
          {"common/ideologies",
              "history/countries",
              "history/states",
              "history/units",
              "common/national_focus",
              "common/countries",
              "common/ideas",
              "map/supplyareas",
              "map/strategicregions",
              "events"});

      commonItems::ModFilesystem mod_filesystem(hoi4_folder, {rsb_mod});

      Log(LogLevel::Info) << "Importing HoI4 map.";
      const auto provinces_bmp_location = mod_filesystem.GetActualFileLocation("/map/provinces.bmp");
      if (!provinces_bmp_location)
      {
         throw std::runtime_error("/map/provinces.bmp couldn't be found!");
      }
      const cimg_library::CImg<uint8_t> provinces_image(provinces_bmp_location->c_str());
      const auto map_definitions =
          hoi4_map_drawer::map_importer::GetProvinceDefinitions(mod_filesystem, provinces_image);

      Log(LogLevel::Info) << "Importing state definitions";
      const auto state_definitions =
          hoi4_map_drawer::state_definitions::StateDefinitionsImporter{}.ImportStateDefinitions(mod_filesystem);

      Log(LogLevel::Info) << "Importing save";
      hoi4_map_drawer::save_reader::SaveImporter save_importer;
      const auto save = save_importer.ImportSave("../../data/saves/RME_1936_01_01_12.hoi4");

      Log(LogLevel::Info) << "Importing country colors";
      const auto tags_to_colors_map = hoi4_map_drawer::country_colors::ImportCountryColors(mod_filesystem);

      Log(LogLevel::Info) << "Drawing ownership map";
      hoi4_map_drawer::map_importer::DrawOwnershipMap(provinces_image.width(),
          provinces_image.height(),
          state_definitions,
          save.GetStates(),
          tags_to_colors_map,
          map_definitions);

      Log(LogLevel::Info) << "All done!";
   }
   catch (const std::exception& e)
   {
      LOG(LogLevel::Error) << e.what();
      return -1;
   }

   return 0;
}