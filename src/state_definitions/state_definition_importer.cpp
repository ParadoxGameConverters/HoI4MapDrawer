#include "src/state_definitions/state_definition_importer.h"

#include <external/commonItems/CommonRegexes.h>
#include <external/commonItems/ParserHelpers.h>



hoi4_map_drawer::state_definitions::StateDefinitionImporter::StateDefinitionImporter()
{
   parser_.registerKeyword("id", [this](std::istream& the_stream) {
      id_ = commonItems::getInt(the_stream);
   });
   parser_.registerKeyword("provinces", [this](std::istream& the_stream) {
      provinces_ = commonItems::getInts(the_stream);
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::optional<std::pair<int, std::vector<int>>>
hoi4_map_drawer::state_definitions::StateDefinitionImporter::ImportState(std::istream& the_stream)
{
   id_.reset();
   provinces_.clear();
   parser_.parseStream(the_stream);
   if (id_.has_value())
   {
      return make_pair(*id_, provinces_);
   }
   else
   {
      return std::nullopt;
   }
}