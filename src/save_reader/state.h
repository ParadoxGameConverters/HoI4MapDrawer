#ifndef SRC_SAVE_READER_STATE_H_
#define SRC_SAVE_READER_STATE_H_



#include <optional>
#include <string>



namespace hoi4_map_drawer
{
namespace save_reader
{

class State
{
  public:
   explicit State(std::optional<std::string> owner): owner_(std::move(owner)) {}

   [[nodiscard]] const auto& GetOwner() const { return owner_; }

  private:
   std::optional<std::string> owner_;
};

}  // namespace save_reader
}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_STATE_H_