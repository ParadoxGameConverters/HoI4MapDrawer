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
   explicit Save(std::map<int, State> states, std::vector<Mod> mods): states_(std::move(states)), mods_(std::move(mods))
   {
   }

   [[nodiscard]] const auto& GetStates() const { return states_; }
   [[nodiscard]] const auto& GetMods() const { return mods_; }

  private:
   std::map<int, State> states_;
   std::vector<Mod> mods_;
};

}  // namespace save_reader
}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_SAVE_H_