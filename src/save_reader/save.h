#ifndef SRC_SAVE_READER_SAVE_H_
#define SRC_SAVE_READER_SAVE_H_



#include <map>

#include "src/save_reader/state.h"



namespace hoi4_map_drawer
{
namespace save_reader
{

class Save
{
  public:
   explicit Save(std::map<int, State> states): states_(std::move(states)) {}

   [[nodiscard]] const auto& GetStates() const { return states_; }

  private:
   std::map<int, State> states_;
};

}  // namespace save_reader
}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_SAVE_H_