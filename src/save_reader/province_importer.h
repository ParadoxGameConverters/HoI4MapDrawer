#ifndef SRC_SAVE_READER_PROVINCE_IMPORTER_H_
#define SRC_SAVE_READER_PROVINCE_IMPORTER_H_



#include <external/commonItems/Parser.h>



namespace hoi4_map_drawer
{

class ProvinceImporter
{
  public:
   ProvinceImporter();
   [[nodiscard]] std::optional<std::string> ImportProvince(std::istream& the_stream);

  private:
   commonItems::parser parser_;

   std::optional<std::string> controller;
};

}  // namespace hoi4_map_drawer



#endif  // SRC_SAVE_READER_PROVINCE_IMPORTER_H_