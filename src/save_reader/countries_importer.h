#ifndef SRC_SAVE_READER_COUNTRIES_IMPORTER_H_
#define SRC_SAVE_READER_COUNTRIES_IMPORTER_H_



#include <map>
#include <string>

#include "external/commonItems/Parser.h"
#include "src/save_reader/countries.h"
#include "src/save_reader/country_importer.h"



namespace hoi4_map_drawer
{
namespace save_reader
{

class CountriesImporter
{
  public:
   CountriesImporter();
   Countries ImportCountries(std::istream& the_stream);

  private:
   std::map<std::string, std::string> tag_to_cosmetic_tags_map_;

   commonItems::parser parser_;
   CountryImporter country_importer_;
};

}  // namespace save_reader
}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_COUNTRIES_IMPORTER_H_