#ifndef SRC_SAVE_READER_STATES_IMPORTER_H_
#define SRC_SAVE_READER_STATES_IMPORTER_H_



#include <external/commonItems/Parser.h>

#include "src/save_reader/state_importer.h"



namespace hoi4_map_drawer
{
namespace save_reader
{

class StatesImporter
{
  public:
   StatesImporter();
   std::map<int, State> ImportStates(std::istream& the_stream);

  private:
   std::map<int, State> states_;
   commonItems::parser parser_;
   StateImporter state_importer_;
};

}  // namespace save_reader
}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_STATES_IMPORTER_H_