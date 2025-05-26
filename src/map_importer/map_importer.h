#ifndef SRC_MAP_IMPORTER_MAP_IMPORTER_H_
#define SRC_MAP_IMPORTER_MAP_IMPORTER_H_

#define cimg_verbosity 0
#define cimg_display 0


#include <external/CImg/CImg.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>

#include <map>
#include <set>

#include "src/map_importer/pixel.h"



namespace hoi4_map_drawer
{

std::map<int, std::set<Pixel>> GetProvinceDefinitions(const commonItems::ModFilesystem& mod_filesystem,
    const cimg_library::CImg<uint8_t>& provinces_image);

}  // namespace hoi4_map_drawer



#endif  // SRC_MAP_IMPORTER_MAP_IMPORTER_H_