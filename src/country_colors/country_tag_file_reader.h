#ifndef SRC_COUNTRY_COLORS_COUNTRY_TAG_FILE_READER_H_
#define SRC_COUNTRY_COLORS_COUNTRY_TAG_FILE_READER_H_



#include <external/commonItems/Parser.h>

#include <map>
#include <string>
#include <string_view>



namespace hoi4_map_drawer
{
namespace country_colors
{

class CountryTagFileReader
{
  public:
   CountryTagFileReader();
   std::map<std::string, std::string> ImportTags(std::string_view filename);

  private:
   commonItems::parser parser_;
   std::map<std::string, std::string> tag_to_filename_map_;
};

}  // namespace country_colors
}  // namespace hoi4_map_drawer



#endif  // SRC_COUNTRY_COLORS_COUNTRY_TAG_FILE_READER_H_