#include "src/save_reader/country_importer.h"

#include <external/commonItems/CommonRegexes.h>
#include <external/commonItems/ParserHelpers.h>



hoi4_map_drawer::CountryImporter::CountryImporter()
{
   parser_.registerKeyword("cosmetic_tag", [this](std::istream& the_stream) {
      cosmetic_tag_ = commonItems::getString(the_stream);
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


hoi4_map_drawer::Country hoi4_map_drawer::CountryImporter::ImportCountry(std::istream& the_stream)
{
   cosmetic_tag_.reset();
   parser_.parseStream(the_stream);
   return Country(cosmetic_tag_);
}