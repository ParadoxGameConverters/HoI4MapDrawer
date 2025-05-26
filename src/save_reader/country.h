#ifndef SRC_SAVE_READER_COUNTRY_H
#define SRC_SAVE_READER_COUNTRY_H



#include <optional>
#include <string>



namespace hoi4_map_drawer
{

class Country
{
  public:
   explicit Country(std::optional<std::string> cosmetic_tag): cosmetic_tag_(std::move(cosmetic_tag)) {}

   [[nodiscard]] const auto& GetCosmeticTag() const { return cosmetic_tag_; }

  private:
   std::optional<std::string> cosmetic_tag_;
};

}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_COUNTRY_H