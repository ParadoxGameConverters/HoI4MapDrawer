#include "src/country_colors/country_tag_file_reader.h"

#include "external/commonItems/CommonRegexes.h"
#include "external/commonItems/ParserHelpers.h"



hoi4_map_drawer::country_colors::CountryTagFileReader::CountryTagFileReader()
{
   parser_.registerRegex("([a-zA-Z0-9]){3}", [this](const std::string& tag, std::istream& the_stream) {
      tag_to_filename_map_.emplace(tag, commonItems::getString(the_stream));
   });
}


std::map<std::string, std::string> hoi4_map_drawer::country_colors::CountryTagFileReader::ImportTags(
    std::string_view filename)
{
   tag_to_filename_map_.clear();
   parser_.parseFile(filename);
   return tag_to_filename_map_;
}