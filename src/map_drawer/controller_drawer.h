#ifndef SRC_MAP_DRAWER_CONTROLLER_DRAWER_H_
#define SRC_MAP_DRAWER_CONTROLLER_DRAWER_H_



#include <map>
#include <set>
#include <vector>

#include "external/commonItems/Color.h"
#include "src/map_importer/pixel.h"
#include "src/save_reader/state.h"



namespace hoi4_map_drawer
{
namespace map_drawer
{

void DrawControllerMap(int width,
    int height,
    const std::map<int, std::vector<int>>& state_definitions,
    const std::map<int, save_reader::State>& save_states,
    const std::map<int, std::string>& controlled_provinces,
    const std::map<std::string, commonItems::Color>& tags_to_colors_map,
    const std::map<int, std::set<map_importer::Pixel>>& map_definitions);

}  // namespace map_drawer
}  // namespace hoi4_map_drawer



#endif  // SRC_MAP_DRAWER_CONTROLLER_DRAWER_H_