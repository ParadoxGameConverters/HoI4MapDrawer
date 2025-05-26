#ifndef SRC_COUNTRY_COLORS_COUNTRY_TAGS_READER_H_
#define SRC_COUNTRY_COLORS_COUNTRY_TAGS_READER_H_



#include <external/commonItems/ModLoader/ModFilesystem.h>

#include <filesystem>
#include <map>
#include <string>

#include "src/country_colors/country_tag_file_reader.h"



namespace hoi4_map_drawer
{

class CountryTagsReader
{
  public:
   CountryTagsReader() = default;
   std::map<std::string, std::filesystem::path> ImportTags(const commonItems::ModFilesystem& mod_filesystem);

  private:
   std::map<std::string, std::filesystem::path> tag_to_filename_map_;

   CountryTagFileReader reader_;
};

}  // namespace hoi4_map_drawer



#endif  // SRC_COUNTRY_COLORS_COUNTRY_TAGS_READER_H_