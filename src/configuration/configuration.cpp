#include "src/configuration/configuration.h"

#include "external/commonItems/Parser.h"
#include "external/commonItems/ParserHelpers.h"



hoi4_map_drawer::configuration::Configuration hoi4_map_drawer::configuration::ImportConfiguration(
    std::string_view filename)
{
   Configuration configuration;

   commonItems::parser configuration_parser;
   configuration_parser.registerKeyword("hoi4_folder", [&configuration](std::istream& the_stream) {
      configuration.hoi4_folder = commonItems::getString(the_stream);
   });
   configuration_parser.registerKeyword("documents_folder", [&configuration](std::istream& the_stream) {
      configuration.documents_folder = commonItems::getString(the_stream);
   });
   configuration_parser.registerKeyword("save_location", [&configuration](std::istream& the_stream) {
      configuration.save_location = commonItems::getString(the_stream);
   });
   configuration_parser.parseFile(filename);

   return configuration;
}