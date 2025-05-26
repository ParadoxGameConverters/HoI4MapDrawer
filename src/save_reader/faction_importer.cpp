#include "src/save_reader/faction_importer.h"

#include <external/commonItems/CommonRegexes.h>
#include <external/commonItems/ParserHelpers.h>



hoi4_map_drawer::FactionImporter::FactionImporter()
{
   parser_.registerKeyword("members", [this](std::istream& the_stream) {
      const auto members = commonItems::getStrings(the_stream);
      for (const auto& member: members)
      {
         tags_to_faction_leader_map_.emplace(member, members[0]);
      }
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::map<std::string, std::string> hoi4_map_drawer::FactionImporter::ImportFaction(std::istream& the_stream)
{
   tags_to_faction_leader_map_.clear();
   parser_.parseStream(the_stream);
   return tags_to_faction_leader_map_;
}