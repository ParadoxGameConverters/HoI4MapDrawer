#include "src/map_importer/map_importer.h"

#include <fstream>
#include <optional>
#include <ranges>
#include <string>

#define cimg_verbosity 0
#include "external/CImg/CImg.h"
#include "external/commonItems/Log.h"
#include "external/commonItems/OSCompatibilityLayer.h"



namespace hoi4_map_drawer
{
namespace map_importer
{


namespace
{


uint32_t PixelPack(const uint8_t r, const uint8_t g, const uint8_t b)
{
   return r << 0xFU | g << 0x8U | b;
}


std::map<int32_t, std::set<Pixel>> GetColorToPixelDefinitions(const std::string& filename)
{
   std::map<int32_t, std::set<Pixel>> definitions;
   cimg_library::CImg<uint8_t> provinces_image(filename.c_str());

   Log(LogLevel::Info) << "provinces.bmp is " << provinces_image.width() << " x " << provinces_image.height() << ".";
   for (int x = 0; x < provinces_image.width(); ++x)
   {
      for (int y = 0; y < provinces_image.height(); ++y)
      {
         const auto r = *provinces_image.data(x, y, 0, 0);
         const auto g = *provinces_image.data(x, y, 0, 1);
         const auto b = *provinces_image.data(x, y, 0, 2);
         const Pixel coords{.x = x, .y = y};
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
      auto sections = std::views::split(line, ';');

      auto section = sections.begin();
      if (section == sections.end())
      {
         return std::nullopt;
      }
      const std::string id_string(*section);
      auto id = std::stoi(id_string);

      ++section;
      if (section == sections.end())
      {
         return std::nullopt;
      }
      const std::string red_string(*section);
      auto red = std::stoi(red_string);

      ++section;
      if (section == sections.end())
      {
         return std::nullopt;
      }
      const std::string green_string(*section);
      auto green = std::stoi(green_string);

      ++section;
      if (section == sections.end())
      {
         return std::nullopt;
      }
      const std::string blue_string(*section);
      auto blue = std::stoi(blue_string);

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


std::map<int, int> LoadDefinitions(const std::string& filename)
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


std::map<int, std::set<Pixel>> GetProvinceDefinitions(const std::string& hoi4_folder)
{
   const auto color_to_pixel_definitions = GetColorToPixelDefinitions(hoi4_folder + "/map/provinces.bmp");
   const auto color_to_province_definitions = LoadDefinitions(hoi4_folder + "/map/definition.csv");

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

}  // namespace map_importer
}  // namespace hoi4_map_drawer
