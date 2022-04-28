#ifndef SRC_COUNTRY_COLORS_COUNTRY_DEFINITION_READER_H_
#define SRC_COUNTRY_COLORS_COUNTRY_DEFINITION_READER_H_



#include <string_view>

#include "external/commonItems/Color.h"
#include "external/commonItems/Parser.h"



namespace hoi4_map_drawer
{
namespace country_colors
{

class CountryDefinitionReader
{
  public:
   CountryDefinitionReader();
   commonItems::Color ImportCountryDefinition(std::string_view filename);

  private:
   commonItems::parser parser_;
   commonItems::Color the_color_;
};

}  // namespace country_colors
}  // namespace hoi4_map_drawer



#endif  // SRC_COUNTRY_COLORS_COUNTRY_DEFINITION_READER_H_