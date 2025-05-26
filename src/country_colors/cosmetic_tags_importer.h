#ifndef SRC_COUNTRY_COLORS_COSMETIC_TAGS_IMPORTER_H_
#define SRC_COUNTRY_COLORS_COSMETIC_TAGS_IMPORTER_H_



#include <external/commonItems/Color.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <external/commonItems/Parser.h>

#include <map>
#include <string>

#include "src/country_colors/country_definition_reader.h"



namespace hoi4_map_drawer
{

class CosmeticTagsImporter
{
  public:
   CosmeticTagsImporter();

   std::map<std::string, commonItems::Color> ImportCosmeticTags(const commonItems::ModFilesystem& mod_filesystem);

  private:
   std::map<std::string, commonItems::Color> cosmetic_tag_to_color_map_;

   commonItems::parser parser_;
   CountryDefinitionReader country_definition_reader_;
};

}  // namespace hoi4_map_drawer



#endif  // SRC_COUNTRY_COLORS_COSMETIC_TAGS_IMPORTER_H_