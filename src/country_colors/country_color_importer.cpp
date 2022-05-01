#include "src/country_colors/country_color_importer.h"

#include "country_definition_reader.h"
#include "country_tags_reader.h"
#include "external/commonItems/Log.h"



std::map<std::string, commonItems::Color> hoi4_map_drawer::country_colors::ImportCountryColors(
    const commonItems::ModFilesystem& mod_filesystem)
{
   std::map<std::string, commonItems::Color> tag_to_colors_map;

   hoi4_map_drawer::country_colors::CountryTagsReader tags_reader;
   hoi4_map_drawer::country_colors::CountryDefinitionReader definition_reader;
   for (const auto& [tag, definition_file]: tags_reader.ImportTags(mod_filesystem))
   {
      const auto actual_definition_file = mod_filesystem.GetActualFileLocation(definition_file);
      if (!actual_definition_file)
      {
         Log(LogLevel::Warning) << definition_file << " could not be found";
         continue;
      }
      tag_to_colors_map.emplace(tag, definition_reader.ImportCountryDefinition(*actual_definition_file));
   }

   return tag_to_colors_map;
}