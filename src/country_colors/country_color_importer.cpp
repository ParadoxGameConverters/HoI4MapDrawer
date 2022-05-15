#include "src/country_colors/country_color_importer.h"

#include "external/commonItems/Log.h"
#include "src/country_colors/cosmetic_tags_importer.h"
#include "src/country_colors/country_definition_reader.h"
#include "src/country_colors/country_tags_reader.h"



std::map<std::string, commonItems::Color> hoi4_map_drawer::country_colors::ImportCountryColors(
    const commonItems::ModFilesystem& mod_filesystem,
    const std::map<std::string, std::string>& tags_to_cosmetic_tags_map)
{
   std::map<std::string, commonItems::Color> tag_to_colors_map;

   CosmeticTagsImporter cosmetic_tags_importer;
   const auto cosmetic_tags_to_colors_map = cosmetic_tags_importer.ImportCosmeticTags(mod_filesystem);

   hoi4_map_drawer::country_colors::CountryTagsReader tags_reader;
   hoi4_map_drawer::country_colors::CountryDefinitionReader definition_reader;
   for (const auto& [tag, definition_file]: tags_reader.ImportTags(mod_filesystem))
   {
      if (const auto cosmetic_tag = tags_to_cosmetic_tags_map.find(tag);
          cosmetic_tag != tags_to_cosmetic_tags_map.end())
      {
         if (const auto color = cosmetic_tags_to_colors_map.find(cosmetic_tag->second);
             color != cosmetic_tags_to_colors_map.end())
         {
            tag_to_colors_map.emplace(tag, color->second);
            continue;
         }
      }

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