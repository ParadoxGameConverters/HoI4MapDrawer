#include "src/save_reader/state_importer.h"

#include "external/commonItems/CommonRegexes.h"
#include "external/commonItems/ParserHelpers.h"



hoi4_map_drawer::save_reader::StateImporter::StateImporter()
{
   parser_.registerKeyword("owner", [this](std::istream& the_stream) {
      owner_ = commonItems::getString(the_stream);
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


hoi4_map_drawer::save_reader::State hoi4_map_drawer::save_reader::StateImporter::ImportState(std::istream& the_stream)
{
   owner_.reset();

   parser_.parseStream(the_stream);

   return State(owner_);
}