#ifndef SRC_SAVE_READER_COUNTRIES_H_
#define SRC_SAVE_READER_COUNTRIES_H_



#include <map>
#include <string>



namespace hoi4_map_drawer
{
namespace save_reader
{

class Countries
{
  public:
   explicit Countries(std::map<std::string, std::string> tags_to_cosmetic_tags_map):
       tags_to_cosmetic_tags_map_(std::move(tags_to_cosmetic_tags_map))
   {
   }

   [[nodiscard]] const auto& GetTagsToCosmeticTagsMap() const { return tags_to_cosmetic_tags_map_; }

  private:
   std::map<std::string, std::string> tags_to_cosmetic_tags_map_;
};

}  // namespace save_reader
}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_COUNTRIES_H_