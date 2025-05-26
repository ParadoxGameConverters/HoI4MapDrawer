#include "src/country_colors/country_tag_file_reader.h"

#include <external/commonItems/CommonRegexes.h>
#include <external/commonItems/ParserHelpers.h>



hoi4_map_drawer::CountryTagFileReader::CountryTagFileReader()
{
   parser_.registerRegex("([a-zA-Z0-9]){3}", [this](const std::string& tag, std::istream& the_stream) {
      tag_to_filename_map_.emplace(tag, commonItems::getString(the_stream));
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::map<std::string, std::filesystem::path> hoi4_map_drawer::CountryTagFileReader::ImportTags(
    const std::filesystem::path& filename)
{
   tag_to_filename_map_.clear();
   parser_.parseFile(filename);
   return tag_to_filename_map_;
}