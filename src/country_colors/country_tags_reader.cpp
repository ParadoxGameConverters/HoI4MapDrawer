#include "src/country_colors/country_tags_reader.h"

#include "external/commonItems/OSCompatibilityLayer.h"



std::map<std::string, std::string> hoi4_map_drawer::country_colors::CountryTagsReader::ImportTags(
    const std::string& hoi4_install_folder)
{
   tag_to_filename_map_.clear();
   for (const auto& filename: commonItems::GetAllFilesInFolder(hoi4_install_folder + "/common/country_tags/"))
   {
      for (const auto& [tag, filename]: reader_.ImportTags(hoi4_install_folder + "/common/country_tags/" + filename))
      {
         if (auto [iterator, success] = tag_to_filename_map_.emplace(tag, filename); !success)
         {
            iterator->second = filename;
         }
      }
   }

   return tag_to_filename_map_;
}