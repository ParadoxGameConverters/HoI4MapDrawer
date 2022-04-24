#ifndef SRC_STATE_DEFINITIONS_STATE_DEFINITION_IMPORTER_H_
#define SRC_STATE_DEFINITIONS_STATE_DEFINITION_IMPORTER_H_


#include <istream>
#include <optional>
#include <vector>

#include "external/commonItems/Parser.h"



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
   std::optional<int> id;
   std::vector<int> provinces;

   commonItems::parser parser;
};


}  // namespace state_definitions
}  // namespace hoi4_map_drawer



#endif  // SRC_STATE_DEFINITIONS_STATE_DEFINITION_IMPORTER_H_