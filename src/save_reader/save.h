#ifndef SRC_SAVE_READER_SAVE_H_
#define SRC_SAVE_READER_SAVE_H_



#include <map>

#include "external/commonItems/ModLoader/Mod.h"
#include "src/save_reader/state.h"



namespace hoi4_map_drawer
{
namespace save_reader
{

class Save
{
  public:
   explicit Save(std::map<int, State> states, std::vector<Mod> mods, std::map<int, std::string> controlled_provinces):
       states_(std::move(states)),
       mods_(std::move(mods)),
       controlled_provinces_(std::move(controlled_provinces))
   {
   }

   [[nodiscard]] const auto& GetStates() const { return states_; }
   [[nodiscard]] const auto& GetMods() const { return mods_; }
   [[nodiscard]] const auto& GetControlledProvinces() const { return controlled_provinces_; }
   [[nodiscard]] const auto& GetTagsToFactionLeaderMap() const { return tags_to_faction_leader_map_; }

  private:
   std::map<int, State> states_;
   std::vector<Mod> mods_;
   std::map<int, std::string> controlled_provinces_;
   std::map<std::string, std::string> tags_to_faction_leader_map_ = {{"UTA", "UTA"}, {"CAN", "UTA"}};
};

}  // namespace save_reader
}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_SAVE_H_