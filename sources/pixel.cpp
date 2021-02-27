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
    Color::Green,
    Color::Blue,
    Color::Red,
    Color::Orange,
    Color::Black,
    Color::Magenta,
    Color::Cyan
};

Pixel PaletteGenerator::NextColor(){
    return Colors[m_Counter++ % (sizeof(Colors)/sizeof(Pixel))];
}

}//namespace libplot
