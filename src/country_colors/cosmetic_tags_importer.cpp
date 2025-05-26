#include "src/country_colors/cosmetic_tags_importer.h"

#include <external/commonItems/CommonRegexes.h>



hoi4_map_drawer::CosmeticTagsImporter::CosmeticTagsImporter()
{
   parser_.registerRegex(commonItems::catchallRegex, [this](const std::string& cosmetic_tag, std::istream& the_stream) {
      cosmetic_tag_to_color_map_.emplace(cosmetic_tag, country_definition_reader_.ImportCountryDefinition(the_stream));
   });
}


std::map<std::string, commonItems::Color> hoi4_map_drawer::CosmeticTagsImporter::ImportCosmeticTags(
    const commonItems::ModFilesystem& mod_filesystem)
{
   cosmetic_tag_to_color_map_.clear();
   if (const auto& cosmetic_tags_file = mod_filesystem.GetActualFileLocation("/common/countries/cosmetic.txt");
       cosmetic_tags_file.has_value())
   {
      parser_.parseFile(*cosmetic_tags_file);
   }
   return cosmetic_tag_to_color_map_;
}