#ifndef SRC_STATE_DEFINITIONS_STATE_DEFINITIONS_IMPORTER_H_
#define SRC_STATE_DEFINITIONS_STATE_DEFINITIONS_IMPORTER_H_



#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <external/commonItems/Parser.h>

#include <map>
#include <string_view>
#include <vector>

#include "src/state_definitions/state_definition_importer.h"



namespace hoi4_map_drawer
{

class StateDefinitionsImporter
{
  public:
   StateDefinitionsImporter();
   std::map<int, std::vector<int>> ImportStateDefinitions(const commonItems::ModFilesystem& mod_filesystem);

  private:
   commonItems::parser parser_;
   StateDefinitionImporter state_definition_importer_;
   std::map<int, std::vector<int>> state_data_;
};

}  // namespace hoi4_map_drawer



#endif  // SRC_STATE_DEFINITIONS_STATE_DEFINITIONS_IMPORTER_H_