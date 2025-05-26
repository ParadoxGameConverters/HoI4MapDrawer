#ifndef SRC_COUNTRY_COLORS_COUNTRY_DEFINITION_READER_H_
#define SRC_COUNTRY_COLORS_COUNTRY_DEFINITION_READER_H_



#include <external/commonItems/Color.h>
#include <external/commonItems/Parser.h>

#include <string_view>



namespace hoi4_map_drawer
{

class CountryDefinitionReader
{
  public:
   CountryDefinitionReader();
   commonItems::Color ImportCountryDefinition(const std::filesystem::path& filename);
   commonItems::Color ImportCountryDefinition(std::istream& the_stream);

  private:
   commonItems::parser parser_;
   commonItems::Color the_color_;
};

}  // namespace hoi4_map_drawer



#endif  // SRC_COUNTRY_COLORS_COUNTRY_DEFINITION_READER_H_