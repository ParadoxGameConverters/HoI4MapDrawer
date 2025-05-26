#include "src/country_colors/country_tags_reader.h"

#include <external/commonItems/OSCompatibilityLayer.h>



std::map<std::string, std::filesystem::path> hoi4_map_drawer::CountryTagsReader::ImportTags(
    const commonItems::ModFilesystem& mod_filesystem)
{
   tag_to_filename_map_.clear();
   for (const auto& filename: mod_filesystem.GetAllFilesInFolder("/common/country_tags/"))
   {
      for (const auto& [tag, tag_filename]: reader_.ImportTags(filename))
      {
         if (auto [iterator, success] = tag_to_filename_map_.emplace(tag, "common" / tag_filename); !success)
         {
            iterator->second = "common" / tag_filename;
         }
      }
   }

   return tag_to_filename_map_;
}