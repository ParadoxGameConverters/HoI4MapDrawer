#include "src/save_reader/states_importer.h"

#include <external/commonItems/CommonRegexes.h>
#include <external/commonItems/ParserHelpers.h>



hoi4_map_drawer::save_reader::StatesImporter::StatesImporter()
{
   parser_.registerRegex(commonItems::integerRegex, [this](const std::string& id_string, std::istream& the_stream) {
      const auto id = std::stoi(id_string);
      states_.emplace(id, state_importer_.ImportState(id, the_stream));
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::map<int, hoi4_map_drawer::save_reader::State> hoi4_map_drawer::save_reader::StatesImporter::ImportStates(
    std::istream& the_stream)
{
   states_.clear();
   parser_.parseStream(the_stream);
   return states_;
}