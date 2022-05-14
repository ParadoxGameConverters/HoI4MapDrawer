#ifndef SRC_SAVE_READER_COUNTRY_IMPORTER_H
#define SRC_SAVE_READER_COUNTRY_IMPORTER_H



#include "external/commonItems/Parser.h"
#include "src/save_reader/country.h"



namespace hoi4_map_drawer
{
namespace save_reader
{

class CountryImporter
{
  public:
   CountryImporter();

   [[nodiscard]] Country ImportCountry(std::istream& the_stream);

  private:
   commonItems::parser parser_;

   std::optional<std::string> cosmetic_tag_;
};

}  // namespace save_reader
}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_COUNTRY_IMPORTER_H