#ifndef SRC_STATE_DEFINITIONS_STATE_DEFINITION_IMPORTER_H_
#define SRC_STATE_DEFINITIONS_STATE_DEFINITION_IMPORTER_H_


#include <external/commonItems/Parser.h>

#include <istream>
#include <optional>
#include <vector>



namespace hoi4_map_drawer
{
namespace state_definitions
{


class StateDefinitionImporter
{
  public:
   StateDefinitionImporter();

   std::optional<std::pair<int, std::vector<int>>> ImportState(std::istream& the_stream);

  private:
   std::optional<int> id_;
   std::vector<int> provinces_;

   commonItems::parser parser_;
};


}  // namespace state_definitions
}  // namespace hoi4_map_drawer



#endif  // SRC_STATE_DEFINITIONS_STATE_DEFINITION_IMPORTER_H_