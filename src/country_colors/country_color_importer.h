#ifndef SRC_COUNTRY_COLORS_COUNTRY_COLOR_IMPORTER_H_
#define SRC_COUNTRY_COLORS_COUNTRY_COLOR_IMPORTER_H_



#include <external/commonItems/Color.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>

#include <map>
#include <string>



namespace hoi4_map_drawer
{
namespace country_colors
{

std::map<std::string, commonItems::Color> ImportCountryColors(const commonItems::ModFilesystem& mod_filesystem,
    const std::map<std::string, std::string>& tags_to_cosmetic_tags_map);

}  // namespace country_colors
}  // namespace hoi4_map_drawer



#endif  // SRC_COUNTRY_COLORS_COUNTRY_COLOR_IMPORTER_H_