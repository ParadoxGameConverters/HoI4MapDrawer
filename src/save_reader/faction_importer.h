#ifndef SRC_SAVE_READER_FACTION_IMPORTER_H_
#define SRC_SAVE_READER_FACTION_IMPORTER_H_



#include <external/commonItems/Parser.h>



namespace hoi4_map_drawer
{

class FactionImporter
{
  public:
   FactionImporter();

   std::map<std::string, std::string> ImportFaction(std::istream& the_stream);

  private:
   commonItems::parser parser_;

   std::map<std::string, std::string> tags_to_faction_leader_map_;
};

}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_FACTION_IMPORTER_H_