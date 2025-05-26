#include "src/save_reader/save_importer.h"

#include <external/commonItems/CommonRegexes.h>
#include <external/commonItems/Log.h>
#include <external/commonItems/ParserHelpers.h>
#include <external/rakaly/rakaly.h>

#include <filesystem>
#include <fstream>


namespace
{

std::string UnmeltSaveIfNeeded(const std::string& save_data)
{
   if (save_data.starts_with("HOI4bin"))
   {
      const rakaly::GameFile game_file = rakaly::parseHoi4(save_data);
      const rakaly::MeltedOutput melted_output = game_file.melt();

      std::string data;
      melted_output.writeData(data);
      return data;
   }

   return save_data;
}

}  // namespace



hoi4_map_drawer::SaveImporter::SaveImporter()
{
   parser_.registerKeyword("HOI4txt", []([[maybe_unused]] std::istream& the_stream) {
   });
   parser_.registerKeyword("mods", [this](std::istream& the_stream) {
      for (const auto& mod_name: commonItems::getStrings(the_stream))
      {
         mods_.emplace_back(mod_name, "");
      }
   });
   parser_.registerKeyword("provinces", [this](std::istream& the_stream) {
      controlled_provinces_ = provinces_importer_.ImportProvinces(the_stream);
   });
   parser_.registerKeyword("states", [this](std::istream& the_stream) {
      states_ = states_importer_.ImportStates(the_stream);
   });
   parser_.registerKeyword("countries", [this](std::istream& the_stream) {
      tags_to_cosmetic_tags_map_ = countries_importer_.ImportCountries(the_stream).GetTagsToCosmeticTagsMap();
   });
   parser_.registerKeyword("faction", [this](std::istream& the_stream) {
      for (const auto& new_tags_to_faction_leader_mapping: faction_importer_.ImportFaction(the_stream))
      {
         tags_to_faction_leader_map_.emplace(new_tags_to_faction_leader_mapping);
      }
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


hoi4_map_drawer::Save hoi4_map_drawer::SaveImporter::ImportSave(const std::filesystem::path& filename)
{
   mods_.clear();
   controlled_provinces_.clear();
   states_.clear();
   tags_to_cosmetic_tags_map_.clear();
   tags_to_faction_leader_map_.clear();

   std::ifstream in_binary(std::filesystem::path(filename), std::ios::binary);
   if (!in_binary.is_open())
   {
      throw std::runtime_error("Could not open " + filename.string() + " for parsing.");
   }
   std::stringstream inStream;
   inStream << in_binary.rdbuf();
   in_binary.close();

   const auto unmelted_save = UnmeltSaveIfNeeded(inStream.str());
   auto game_state = std::istringstream(unmelted_save);

   parser_.parseStream(game_state);
   return Save(states_, mods_, controlled_provinces_, tags_to_faction_leader_map_, tags_to_cosmetic_tags_map_);
}