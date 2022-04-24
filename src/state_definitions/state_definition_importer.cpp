#include "src/state_definitions/state_definition_importer.h"

#include "external/commonItems/ParserHelpers.h"



hoi4_map_drawer::state_definitions::StateDefinitionImporter::StateDefinitionImporter()
{
   parser.registerKeyword("id", [this](std::istream& the_stream) {
      id = commonItems::getInt(the_stream);
   });
   parser.registerKeyword("provinces", [this](std::istream& the_stream) {
      provinces = commonItems::getInts(the_stream);
   });
}


std::optional<std::pair<int, std::vector<int>>>
hoi4_map_drawer::state_definitions::StateDefinitionImporter::ImportState(std::istream& the_stream)
{
   id.reset();
   provinces.clear();
   parser.parseStream(the_stream);
   if (id.has_value())
   {
      return make_pair(*id, provinces);
   }
   else
   {
      return std::nullopt;
   }
}