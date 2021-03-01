#include "pixel.hpp"

namespace libplot{

constexpr Pixel Color::White;
constexpr Pixel Color::Black;
constexpr Pixel Color::Red;
constexpr Pixel Color::Green;
constexpr Pixel Color::Blue;
constexpr Pixel Color::Yellow;
constexpr Pixel Color::Cyan;
constexpr Pixel Color::Magenta;
constexpr Pixel Color::Orange;


Pixel Colors[]={
    {51, 234, 66, 255},
    {51, 118, 234, 255},
    {234, 51, 51, 255},
    {234, 155, 51, 255},
    {0, 0, 0, 255},
    {234, 51, 143, 255},
    {51, 213, 234, 255}
};

Pixel PaletteGenerator::NextColor(){
    return Colors[m_Counter++ % (sizeof(Colors)/sizeof(Pixel))];
}

}//namespace libplot
