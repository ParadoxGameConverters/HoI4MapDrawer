#ifndef SRC_COUNTRY_COLORS_COUNTRY_TAG_FILE_READER_H_
#define SRC_COUNTRY_COLORS_COUNTRY_TAG_FILE_READER_H_



#include <external/commonItems/Parser.h>

#include <filesystem>
#include <map>
#include <string>
#include <string_view>



namespace hoi4_map_drawer
{

class CountryTagFileReader
{
  public:
   CountryTagFileReader();
   std::map<std::string, std::filesystem::path> ImportTags(const std::filesystem::path& filename);

  private:
   commonItems::parser parser_;
   std::map<std::string, std::filesystem::path> tag_to_filename_map_;
};

}  // namespace hoi4_map_drawer



#endif  // SRC_COUNTRY_COLORS_COUNTRY_TAG_FILE_READER_H_