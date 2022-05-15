#include "src/save_reader/countries_importer.h"



hoi4_map_drawer::save_reader::CountriesImporter::CountriesImporter()
{
   parser_.registerRegex("[A-Z][A-Z0-9]{2}", [this](const std::string& tag, std::istream& the_stream) {
      const auto country = country_importer_.ImportCountry(the_stream);
      if (const auto& cosmetic_tag = country.GetCosmeticTag(); cosmetic_tag.has_value())
      {
         tag_to_cosmetic_tags_map_.emplace(tag, *cosmetic_tag);
      }
   });
}


hoi4_map_drawer::save_reader::Countries hoi4_map_drawer::save_reader::CountriesImporter::ImportCountries(
    std::istream& the_stream)
{
   tag_to_cosmetic_tags_map_.clear();
   parser_.parseStream(the_stream);
   return Countries(tag_to_cosmetic_tags_map_);
}