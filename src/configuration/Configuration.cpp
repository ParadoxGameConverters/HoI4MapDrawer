#include "src/configuration/configuration.h"



hoi4_map_drawer::configuration::Configuration hoi4_map_drawer::configuration::ImportConfiguration()
{
   Configuration configuration;

   configuration.hoi4_folder = "C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV";
   configuration.mod_folder = "C:/Users/idhre/OneDrive/Documents/Paradox Interactive/Hearts of Iron IV";
   configuration.save_location = "../../data/saves/RME_1936_01_01_12.hoi4";

   return configuration;
}