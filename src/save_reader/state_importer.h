#ifndef SRC_SAVE_READER_STATE_IMPORTER_H
#define SRC_SAVE_READER_STATE_IMPORTER_H



#include <external/commonItems/Parser.h>

#include <istream>
#include <optional>
#include <string>

#include "src/save_reader/state.h"



namespace hoi4_map_drawer
{

class StateImporter
{
  public:
   StateImporter();

   State ImportState(int id, std::istream& the_stream);

  private:
   int id_ = 0;
   std::optional<std::string> owner_;
   commonItems::parser parser_;
};

}  // namespace hoi4_map_drawer


#endif  // SRC_SAVE_READER_STATE_IMPORTER_H