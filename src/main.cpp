#include <filesystem>
#include <fstream>

#include "external/commonItems/Log.h"
#include "src/rakaly_wrapper.h"



namespace
{


std::string UnmeltSaveIfNeeded(const std::string& save_data)
{
   if (save_data.starts_with("HOI4bin"))
   {
      return rakaly::meltHoi4(save_data);
   }

   return save_data;
}


}  // namespace



int main()
{
   try
   {
      LOG(LogLevel::Info) << "-> Importing HoI4 save.";
      std::ifstream inBinary(std::filesystem::path(u8"input.hoi4"), std::ios::binary);
      if (!inBinary.is_open())
      {
         throw std::runtime_error("Could not open input.hoi4 for parsing.");
      }
      std::stringstream inStream;
      inStream << inBinary.rdbuf();
      Log(LogLevel::Progress) << "8 %";

      const auto unmelted_save = UnmeltSaveIfNeeded(inStream.str());
      Log(LogLevel::Progress) << "9 %";

      auto game_state = std::istringstream(unmelted_save);
      std::string line;
      std::getline(game_state, line);
      Log(LogLevel::Info) << line;
      Log(LogLevel::Progress) << "15 %";
   }
   catch (const std::exception& e)
   {
      LOG(LogLevel::Error) << e.what();
      return -1;
   }

   return 0;
}