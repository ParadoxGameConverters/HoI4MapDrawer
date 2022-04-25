#include "src/save_reader/save_importer.h"

#include <filesystem>
#include <fstream>

#include "external/commonItems/CommonRegexes.h"
#include "external/commonItems/Log.h"
#include "external/commonItems/ParserHelpers.h"
#include "src/rakaly_wrapper.h"


namespace
{

std::string UnmeltSaveIfNeeded(const std::string& save_data)
{
   if (save_data.starts_with("HOI4bin"))
   {
      return rakaly::meltHoi4(save_data);
   }

   return save_data;
}

}  // namespace



hoi4_map_drawer::save_reader::SaveImporter::SaveImporter()
{
   parser_.registerKeyword("states", [this](std::istream& the_stream) {
      states_ = states_importer_.ImportStates(the_stream);
   });
   parser_.registerKeyword("HOI4txt", [](std::istream& the_stream) {
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


hoi4_map_drawer::save_reader::Save hoi4_map_drawer::save_reader::SaveImporter::ImportSave(std::string_view filename)
{
   states_.clear();

   std::ifstream in_binary(std::filesystem::path(filename), std::ios::binary);
   if (!in_binary.is_open())
   {
      throw std::runtime_error("Could not open input.hoi4 for parsing.");
   }
   std::stringstream inStream;
   inStream << in_binary.rdbuf();
   in_binary.close();

   const auto unmelted_save = UnmeltSaveIfNeeded(inStream.str());
   auto game_state = std::istringstream(unmelted_save);

   parser_.parseStream(game_state);
   return Save(states_);
}