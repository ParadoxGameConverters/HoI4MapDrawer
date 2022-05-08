#ifndef SRC_COUNTRY_COLORS_COUNTRY_COLOR_IMPORTER_H_
#define SRC_COUNTRY_COLORS_COUNTRY_COLOR_IMPORTER_H_



#include <map>
#include <string>

#include "external/commonItems/Color.h"
#include "external/commonItems/ModLoader/ModFilesystem.h"



namespace hoi4_map_drawer
{
namespace country_colors
{

std::map<std::string, commonItems::Color> ImportCountryColors(const commonItems::ModFilesystem& mod_filesystem);

}  // namespace country_colors
}  // namespace hoi4_map_drawer



#endif  // SRC_COUNTRY_COLORS_COUNTRY_COLOR_IMPORTER_H_