#include "src/map_importer.h"

#include <fstream>
#include <optional>
#include <string>

#include "external/CImg/CImg.h"
#include "external/commonItems/Log.h"
#include "external/commonItems/OSCompatibilityLayer.h"



namespace hoi4_map_drawer
{
namespace map_importer
{


namespace
{


unsigned int pixelPack(const unsigned char r, const unsigned char g, const unsigned char b)
{
   return r << 16 | g << 8 | b;
}


std::map<int32_t, std::set<Pixel>> GetColorToPixelDefinitions(const std::string& map_folder)
{
   std::map<int32_t, std::set<Pixel>> definitions;
   cimg_library::CImg<int32_t> provinces_image((map_folder + "/provinces.bmp").c_str());

   Log(LogLevel::Info) << "provinces.bmp is " << provinces_image.width() << " x " << provinces_image.height() << ".";
   for (int x = 0; x < provinces_image.width(); ++x)
   {
      for (int y = 0; y < provinces_image.height(); ++y)
      {
         const auto r = *provinces_image.data(x, y, 0, 0);
         const auto g = *provinces_image.data(x, y, 0, 1);
         const auto b = *provinces_image.data(x, y, 0, 2);
         const Pixel coords{.x = x, .y = y};
         if (auto [existing, success] = definitions.emplace(pixelPack(r, g, b), std::set{coords}); !success)
         {
            existing->second.insert({x, y});
         }
      }
   }

   return definitions;
}


std::optional<std::tuple<int, unsigned char, unsigned char, unsigned char>> ParseLine(const std::string& line)
{
   try
   {
      auto sepLoc = line.find(';');
      if (sepLoc == std::string::npos)
         return std::nullopt;
      auto sepLocSave = sepLoc;
      auto ID = std::stoi(line.substr(0, sepLoc));
      sepLoc = line.find(';', sepLocSave + 1);
      if (sepLoc == std::string::npos)
         return std::nullopt;
      auto r = static_cast<unsigned char>(std::stoi(line.substr(sepLocSave + 1, sepLoc - sepLocSave - 1)));
      sepLocSave = sepLoc;
      sepLoc = line.find(';', sepLocSave + 1);
      if (sepLoc == std::string::npos)
         return std::nullopt;
      auto g = static_cast<unsigned char>(std::stoi(line.substr(sepLocSave + 1, sepLoc - sepLocSave - 1)));
      sepLocSave = sepLoc;
      sepLoc = line.find(';', sepLocSave + 1);
      if (sepLoc == std::string::npos)
         return std::nullopt;
      auto b = static_cast<unsigned char>(std::stoi(line.substr(sepLocSave + 1, sepLoc - sepLocSave - 1)));
      sepLocSave = sepLoc;
      sepLoc = line.find(';', sepLocSave + 1);
      if (sepLoc == std::string::npos)
         return std::nullopt;
      return std::make_tuple(ID, r, g, b);
   }
   catch (std::exception& e)
   {
      Log(LogLevel::Warning) << "Broken Definition Line: " << line << " - " << e.what();
      return std::nullopt;
   }
}


std::map<int, int> ParseStream(std::istream& theStream)
{
   std::map<int, int> color_to_province_map;

   std::string line;
   getline(theStream, line);  // discard first line.

   while (!theStream.eof())
   {
      getline(theStream, line);
      if (!isdigit(line[0]) || line.length() < 4)
         continue;

      try
      {
         const auto& parsedLine = ParseLine(line);
         if (parsedLine)
         {
            const auto [id, r, g, b] = *parsedLine;
            color_to_province_map.emplace(pixelPack(r, g, b), id);
         }
      }
      catch (std::exception& e)
      {
         throw std::runtime_error("Line: |" + line + "| is unparseable! Breaking. (" + e.what() + ")");
      }
   }

   return color_to_province_map;
}


std::map<int, int> LoadDefinitions(const std::string& fileName)
{
   if (!commonItems::DoesFileExist(fileName))
      throw std::runtime_error("Definitions file cannot be found!");

   std::ifstream definitionsFile(fileName);
   const auto definitions = ParseStream(definitionsFile);
   definitionsFile.close();
   return definitions;
}

}  // namespace


std::map<int, std::set<Pixel>> GetProvinceDefinitions()
{
   const auto color_to_pixel_definitions =
       GetColorToPixelDefinitions("C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV/map");
   const auto color_to_province_definitions =
       LoadDefinitions("C:/Program Files (x86)/Steam/steamapps/common/Hearts of Iron IV/map/definition.csv");

   int pixel_count = 0;
   std::map<int, std::set<Pixel>> province_to_pixel_map;
   for (const auto& [color, pixels]: color_to_pixel_definitions)
   {
      if (const auto color_to_province_itr = color_to_province_definitions.find(color);
          color_to_province_itr != color_to_province_definitions.end())
      {
         province_to_pixel_map.emplace(color_to_province_itr->second, pixels);
         pixel_count += pixels.size();
      }
      else
      {
         Log(LogLevel::Warning) << "Could not find province definitions for color " << color;
      }
   }

   Log(LogLevel::Info) << "Assigned " << pixel_count << " pixels to provinces.";

   return province_to_pixel_map;
}


}  // namespace map_importer
}  // namespace hoi4_map_drawer
