#ifndef SRC_SAVE_READER_STATE_IMPORTER_H
#define SRC_SAVE_READER_STATE_IMPORTER_H



#include <istream>
#include <optional>
#include <string>

#include "external/commonItems/Parser.h"
#include "src/save_reader/state.h"



namespace hoi4_map_drawer
{
namespace save_reader
{


class StateImporter
{
  public:
   StateImporter();

   State ImportState(std::istream& the_stream);

  private:
   std::optional<std::string> owner_;
   commonItems::parser parser_;
};


}  // namespace save_reader
}  // namespace hoi4_map_drawer


#endif  // SRC_SAVE_READER_STATE_IMPORTER_H