#include "src/country_colors/country_color_importer.h"

#include "country_definition_reader.h"
#include "country_tags_reader.h"



std::map<std::string, commonItems::Color> hoi4_map_drawer::country_colors::ImportCountryColors(
    const std::string& hoi4_install_folder)
{
   std::map<std::string, commonItems::Color> tag_to_colors_map;

   hoi4_map_drawer::country_colors::CountryTagsReader tags_reader;
   hoi4_map_drawer::country_colors::CountryDefinitionReader definition_reader;
   for (const auto& [tag, definition_file]: tags_reader.ImportTags(hoi4_install_folder))
   {
      tag_to_colors_map.emplace(tag,
          definition_reader.ImportCountryDefinition(hoi4_install_folder + "/common/" + definition_file));
   }

   return tag_to_colors_map;
}