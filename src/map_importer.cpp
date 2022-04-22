#include "src/map_importer.h"



namespace hoi4_map_drawer
{
namespace map_importer
{


namespace
{


}


std::map<int, std::set<Pixel>> GetProvinceDefinitions()
{
   std::map<int, std::set<Pixel>> definitions;

   std::set<Pixel> pixels_one{{16, 25}, {196, 225}};
   definitions.emplace(4, pixels_one);

   std::set<Pixel> pixels_two{{36, 49}, {256, 289}};
   definitions.emplace(6, pixels_two);
   return definitions;
}


}  // namespace map_importer
}  // namespace hoi4_map_drawer
