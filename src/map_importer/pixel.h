#ifndef SRC_MAP_IMPORTER_PIXEL_H
#define SRC_MAP_IMPORTER_PIXEL_H



namespace hoi4_map_drawer
{
namespace map_importer
{

struct Pixel
{
   int x;
   int y;
};


inline bool operator<(const Pixel& lhs, const Pixel& rhs)
{
   return lhs.y < rhs.y || lhs.x < rhs.x;
}


inline bool operator==(const Pixel& lhs, const Pixel& rhs)
{
   return lhs.y == rhs.y && lhs.x == rhs.x;
}

}  // namespace map_importer
}  // namespace hoi4_map_drawer



#endif  // SRC_MAP_IMPORTER_PIXEL_H