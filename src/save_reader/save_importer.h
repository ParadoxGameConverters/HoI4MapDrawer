#ifndef SRC_SAVE_IMPORTER_H_
#define SRC_SAVE_IMPORTER_H_



#include "external/commonItems/ModLoader/Mod.h"
#include "external/commonItems/Parser.h"
#include "src/save_reader/save.h"
#include "src/save_reader/states_importer.h"



namespace hoi4_map_drawer
{
namespace save_reader
{

class SaveImporter
{
  public:
   SaveImporter();

   Save ImportSave(std::string_view filename);

  private:
   std::map<int, State> states_;
   std::vector<Mod> mods_;
   commonItems::parser parser_;
   StatesImporter states_importer_;
};

}  // namespace save_reader
}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_IMPORTER_H_