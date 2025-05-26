#ifndef SRC_SAVE_READER_PROVINCES_IMPORTER_H_
#define SRC_SAVE_READER_PROVINCES_IMPORTER_H_


#include <external/commonItems/Parser.h>

#include <map>
#include <set>
#include <string>

#include "src/save_reader/province_importer.h"



namespace hoi4_map_drawer
{

class ProvincesImporter
{
  public:
   ProvincesImporter();
   std::map<int, std::string> ImportProvinces(std::istream& the_stream);

  private:
   std::map<int, std::string> controlled_provinces_;

   commonItems::parser parser_;
   ProvinceImporter province_importer_;
};

}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_PROVINCES_IMPORTER_H_