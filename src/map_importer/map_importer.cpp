#include "src/map_importer/map_importer.h"

#include <external/commonItems/Log.h>
#include <external/commonItems/ModLoader/ModFilesystem.h>
#include <external/commonItems/OSCompatibilityLayer.h>

#include <fstream>
#include <optional>
#include <string>



namespace
{


uint32_t PixelPack(const uint8_t r, const uint8_t g, const uint8_t b)
{
   return r << 0x10U | g << 0x8U | b;
}


std::map<int32_t, std::set<hoi4_map_drawer::Pixel>> GetColorToPixelDefinitions(
    const cimg_library::CImg<uint8_t>& provinces_image)
{
   std::map<int32_t, std::set<hoi4_map_drawer::Pixel>> definitions;

   for (int x = 0; x < provinces_image.width(); ++x)
   {
      for (int y = 0; y < provinces_image.height(); ++y)
      {
         const auto r = *provinces_image.data(x, y, 0, 0);
         const auto g = *provinces_image.data(x, y, 0, 1);
         const auto b = *provinces_image.data(x, y, 0, 2);
         const hoi4_map_drawer::Pixel coords{.x = x, .y = y};
         if (auto [existing, success] = definitions.emplace(PixelPack(r, g, b), std::set{coords}); !success)
         {
            existing->second.insert({x, y});
         }
      }
   }

   return definitions;
}


std::optional<std::tuple<int, uint8_t, uint8_t, uint8_t>> ParseLine(const std::string& line)
{
   try
   {
      auto separator_location = line.find(';');
      if (separator_location == std::string::npos)
      {
         return std::nullopt;
      }
      auto id = std::stoi(line.substr(0, separator_location));

      auto separator_location_save = separator_location;
      separator_location = line.find(';', separator_location_save + 1);
      if (separator_location == std::string::npos)
      {
         return std::nullopt;
      }
      auto red = static_cast<unsigned char>(
          std::stoi(line.substr(separator_location_save + 1, separator_location - separator_location_save - 1)));

      separator_location_save = separator_location;
      separator_location = line.find(';', separator_location_save + 1);
      if (separator_location == std::string::npos)
      {
         return std::nullopt;
      }
      auto green = static_cast<unsigned char>(
          std::stoi(line.substr(separator_location_save + 1, separator_location - separator_location_save - 1)));

      separator_location_save = separator_location;
      separator_location = line.find(';', separator_location_save + 1);
      if (separator_location == std::string::npos)
      {
         return std::nullopt;
      }
      auto blue = static_cast<unsigned char>(
          std::stoi(line.substr(separator_location_save + 1, separator_location - separator_location_save - 1)));

      return std::make_tuple(id, red, green, blue);
   }
   catch (std::exception& e)
   {
      Log(LogLevel::Warning) << "Broken Definition Line: " << line << " - " << e.what();
      return std::nullopt;
   }
}


std::map<int, int> ParseStream(std::istream& the_stream)
{
   std::map<int, int> color_to_province_map;

   std::string line;
   getline(the_stream, line);  // discard first line.

   while (!the_stream.eof())
   {
      getline(the_stream, line);
      if (!isdigit(line[0]) || line.length() < 4)
      {
         continue;
      }

      try
      {
         if (const auto& parsed_line = ParseLine(line); parsed_line)
         {
            const auto& [id, r, g, b] = *parsed_line;
            color_to_province_map.emplace(PixelPack(r, g, b), id);
         }
      }
      catch (std::exception& e)
      {
         throw std::runtime_error("Line: |" + line + "| is unparseable! Breaking. (" + e.what() + ")");
      }
   }

   return color_to_province_map;
}


std::map<int, int> LoadDefinitions(const std::filesystem::path& filename)
{
   if (!commonItems::DoesFileExist(filename))
   {
      throw std::runtime_error("Definitions file cannot be found!");
   }

   std::ifstream definitionsFile(filename);
   auto definitions = ParseStream(definitionsFile);
   definitionsFile.close();

   return definitions;
}

}  // namespace


namespace hoi4_map_drawer
{

std::map<int, std::set<Pixel>> GetProvinceDefinitions(const commonItems::ModFilesystem& mod_filesystem,
    const cimg_library::CImg<uint8_t>& provinces_image)
{
   const auto color_to_pixel_definitions = GetColorToPixelDefinitions(provinces_image);

   const auto definition_csv_location = mod_filesystem.GetActualFileLocation("map/definition.csv");
   if (!definition_csv_location)
   {
      throw std::runtime_error("/map/definition.csv couldn't be found!");
   }
   const auto color_to_province_definitions = LoadDefinitions(*definition_csv_location);

   std::map<int, std::set<Pixel>> province_to_pixel_map;
   for (const auto& [color, pixels]: color_to_pixel_definitions)
   {
      if (const auto color_to_province_itr = color_to_province_definitions.find(color);
          color_to_province_itr != color_to_province_definitions.end())
      {
         province_to_pixel_map.emplace(color_to_province_itr->second, pixels);
      }
      else
      {
         Log(LogLevel::Warning) << "Could not find province definitions for color " << color;
      }
   }

   return province_to_pixel_map;
}

}  // namespace hoi4_map_drawer
