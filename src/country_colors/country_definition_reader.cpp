#include "src/country_colors/country_definition_reader.h"

#include "external/commonItems/CommonRegexes.h"
#include "external/commonItems/ParserHelpers.h"



hoi4_map_drawer::country_colors::CountryDefinitionReader::CountryDefinitionReader()
{
   parser_.registerKeyword("color", [this](std::istream& the_stream) {
      the_color_ = commonItems::Color::Factory{}.getColor(the_stream);
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


commonItems::Color hoi4_map_drawer::country_colors::CountryDefinitionReader::ImportCountryDefinition(
    std::string_view filename)
{
   the_color_ = commonItems::Color(std::array{0, 0, 0});
   parser_.parseFile(filename);
   return the_color_;
}


commonItems::Color hoi4_map_drawer::country_colors::CountryDefinitionReader::ImportCountryDefinition(
    std::istream& the_stream)
{
   the_color_ = commonItems::Color(std::array{0, 0, 0});
   parser_.parseStream(the_stream);
   return the_color_;
}