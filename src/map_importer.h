#ifndef SRC_MAP_IMPORTER_H_
#define SRC_MAP_IMPORTER_H_



#include <map>
#include <set>
#include <string>



namespace hoi4_map_drawer
{
namespace map_importer
{


struct Pixel
{
   int x;
   int y;
   bool operator<(const Pixel& rhs) const { return y < rhs.y || x < rhs.x; }
};

std::map<int, std::set<Pixel>> GetProvinceDefinitions(const std::string& hoi4_folder);


}  // namespace map_importer
}  // namespace hoi4_map_drawer



#endif  // SRC_MAP_IMPORTER_H_