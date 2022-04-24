#include "src/state_definitions/state_definitions_importer.h"

#include "external/commonItems/OSCompatibilityLayer.h"



hoi4_map_drawer::state_definitions::StateDefinitionsImporter::StateDefinitionsImporter()
{
   parser_.registerKeyword("state", [this](std::istream& the_stream) {
      const auto state_data = state_definition_importer_.ImportState(the_stream);
      if (state_data.has_value())
      {
         state_data_.insert(*state_data);
      }
   });
}


std::map<int, std::vector<int>> hoi4_map_drawer::state_definitions::StateDefinitionsImporter::ImportStateDefinitions(
    const std::string& states_history_folder)
{
   state_data_.clear();

   for (const auto& file: commonItems::GetAllFilesInFolder(std::string(states_history_folder + "/history/states/")))
   {
      parser_.parseFile(states_history_folder + "/history/states/" + file);
   }

   return state_data_;
}