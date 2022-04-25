#include "src/save_reader/save_importer.h"

#include "external/commonItems/CommonRegexes.h"
#include "external/commonItems/ParserHelpers.h"



hoi4_map_drawer::save_reader::SaveImporter::SaveImporter()
{
   parser_.registerKeyword("states", [this](std::istream& the_stream) {
      states_ = states_importer_.ImportStates(the_stream);
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


hoi4_map_drawer::save_reader::Save hoi4_map_drawer::save_reader::SaveImporter::ImportSave(std::string_view filename)
{
   states_.clear();
   parser_.parseFile(filename);
   return Save(states_);
}