#ifndef SRC_CONFIGURATION_CONFIGURATION_H_
#define SRC_CONFIGURATION_CONFIGURATION_H_



#include <string>



namespace hoi4_map_drawer
{
namespace configuration
{

struct Configuration
{
   std::string hoi4_folder;
   std::string documents_folder;
   std::string save_location;
};


Configuration ImportConfiguration(std::string_view filename);

}  // namespace configuration
}  // namespace hoi4_map_drawer



#endif  // SRC_CONFIGURATION_CONFIGURATION_H_