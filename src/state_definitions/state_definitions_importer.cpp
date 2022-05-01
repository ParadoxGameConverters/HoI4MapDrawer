#include "src/state_definitions/state_definitions_importer.h"

#include "external/commonItems/CommonRegexes.h"
#include "external/commonItems/ModLoader/ModFilesystem.h"
#include "external/commonItems/OSCompatibilityLayer.h"
#include "external/commonItems/ParserHelpers.h"



hoi4_map_drawer::state_definitions::StateDefinitionsImporter::StateDefinitionsImporter()
{
   parser_.registerKeyword("state", [this](std::istream& the_stream) {
      const auto state_data = state_definition_importer_.ImportState(the_stream);
      if (state_data.has_value())
      {
         state_data_.insert(*state_data);
      }
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::map<int, std::vector<int>> hoi4_map_drawer::state_definitions::StateDefinitionsImporter::ImportStateDefinitions(
    const commonItems::ModFilesystem& mod_filesystem)
{
   state_data_.clear();

   for (const auto& file: mod_filesystem.GetAllFilesInFolder("/history/states/"))
   {
      parser_.parseFile(file);
   }

   return state_data_;
}