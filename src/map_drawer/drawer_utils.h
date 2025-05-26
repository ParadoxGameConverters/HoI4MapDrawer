#ifndef SRC_MAP_DRAWER_DRAWER_UTILS_H_
#define SRC_MAP_DRAWER_DRAWER_UTILS_H_

#define cimg_verbosity 0
#define cimg_display 0


#include <external/CImg/CImg.h>
#include <external/commonItems/Color.h>

#include <map>
#include <set>

#include "src/map_importer/pixel.h"



namespace hoi4_map_drawer
{

cimg_library::CImg<uint8_t> CreateBaseMap(int width, int height);

void ColorProvince(int province,
    const std::map<int, std::set<hoi4_map_drawer::Pixel>>& map_definitions,
    const commonItems::Color& color,
    cimg_library::CImg<uint8_t>& map);

}  // namespace hoi4_map_drawer



#endif  // SRC_MAP_DRAWER_DRAWER_UTILS_H_