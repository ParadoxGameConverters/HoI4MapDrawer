#ifndef SRC_CONFIGURATION_CONFIGURATION_H_
#define SRC_CONFIGURATION_CONFIGURATION_H_



#include <filesystem>
#include <string>



namespace hoi4_map_drawer
{

struct Configuration
{
   std::filesystem::path hoi4_folder;
   std::filesystem::path documents_folder;
   std::filesystem::path save_location;
};


Configuration ImportConfiguration(const std::filesystem::path& filename);

}  // namespace hoi4_map_drawer



#endif  // SRC_CONFIGURATION_CONFIGURATION_H_