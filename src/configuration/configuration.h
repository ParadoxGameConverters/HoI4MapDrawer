#ifndef SRC_CONFIGURATION_CONFIGURATION_H_
#define SRC_CONFIGURATION_CONFIGURATION_H_



#include <string>



namespace hoi4_map_drawer
{
namespace configuration
{

class Configuration
{
  public:
   [[nodiscard]] const auto& GetHoi4Folder() const { return hoi4_folder; }
   [[nodiscard]] const auto& GetModFolder() const { return mod_folder; }
   [[nodiscard]] const auto& GetSaveLocation() const { return save_location; }

  private:
   std::string hoi4_folder = "C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV";
   std::string mod_folder = "C:/Users/idhre/OneDrive/Documents/Paradox Interactive/Hearts of Iron IV";
   std::string save_location = "../../data/saves/RME_1936_01_01_12.hoi4";
};

}  // namespace configuration
}  // namespace hoi4_map_drawer



#endif  // SRC_CONFIGURATION_CONFIGURATION_H_