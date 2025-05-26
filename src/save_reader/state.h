#ifndef SRC_SAVE_READER_STATE_H_
#define SRC_SAVE_READER_STATE_H_



#include <optional>
#include <string>



namespace hoi4_map_drawer
{

class State
{
  public:
   explicit State(int id, std::optional<std::string> owner): id_(id), owner_(std::move(owner)) {}

   [[nodiscard]] const auto& GetId() const { return id_; }
   [[nodiscard]] const auto& GetOwner() const { return owner_; }

   auto operator<=>(const State&) const = default;

  private:
   int id_;
   std::optional<std::string> owner_;
};


}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_STATE_H_