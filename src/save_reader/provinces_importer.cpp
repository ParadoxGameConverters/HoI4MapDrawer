#include "src/save_reader/provinces_importer.h"

#include <external/commonItems/CommonRegexes.h>
#include <external/commonItems/Log.h>
#include <external/commonItems/ParserHelpers.h>

#include <charconv>



hoi4_map_drawer::ProvincesImporter::ProvincesImporter()
{
   parser_.registerRegex(commonItems::integerRegex, [this](const std::string& number_string, std::istream& the_stream) {
      const auto province_controller = province_importer_.ImportProvince(the_stream);
      if (!province_controller.has_value())
      {
         return;
      }

      int number = 0;
      const auto last = number_string.data() + number_string.size();
      const auto [ptr, ec] = std::from_chars(number_string.data(), last, number);
      if (ec != std::errc() ||
          ptr != last)  // conversion either failed or was successful but not all characters matched
      {
         Log(LogLevel::Warning) << "string to integer - invalid argument: " << number_string;
         return;
      }

      if (auto [itr, success] = controlled_provinces_.emplace(number, *province_controller); !success)
      {
         itr->second = *province_controller;
      }
   });
}


std::map<int, std::string> hoi4_map_drawer::ProvincesImporter::ImportProvinces(std::istream& the_stream)
{
   controlled_provinces_.clear();

   parser_.parseStream(the_stream);

   return controlled_provinces_;
}