#include "src/save_reader/province_importer.h"

#include <external/commonItems/CommonRegexes.h>
#include <external/commonItems/ParserHelpers.h>



hoi4_map_drawer::ProvinceImporter::ProvinceImporter()
{
   parser_.registerKeyword("controller", [this](std::istream& the_stream) {
      controller = commonItems::getString(the_stream);
   });
   parser_.registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::optional<std::string> hoi4_map_drawer::ProvinceImporter::ImportProvince(std::istream& the_stream)
{
   controller.reset();

   parser_.parseStream(the_stream);

   return controller;
}