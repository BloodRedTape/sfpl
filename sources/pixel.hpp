#ifndef LIBPLOT_PIXEL_HPP
#define LIBPLOT_PIXEL_HPP

#include <cstddef>

namespace libplot{

struct Pixel{
    unsigned char Red   = 0;
    unsigned char Green = 0;
    unsigned char Blue  = 0;
    unsigned char Alpha = 255;

};

struct Color{
    static constexpr Pixel White   = {255, 255, 255, 255};
    static constexpr Pixel Black   = {0,   0,   0,   255};
    static constexpr Pixel Red     = {255, 0,   0,   255};
    static constexpr Pixel Green   = {0,   255, 0,   255};
    static constexpr Pixel Blue    = {0,   0,   255, 255};
    static constexpr Pixel Yellow  = {255, 255, 0,   255};
    static constexpr Pixel Cyan    = {0,   255, 255, 255};
    static constexpr Pixel Magenta = {255, 0,   255, 255};
    static constexpr Pixel Orange  = {255, 128, 0,   255};
};

class PaletteGenerator{
private:
    size_t m_Counter = 0;
public:
    Pixel NextColor();
};

}//namespace libplot

#endif//LIBPLOT_PIXEL_HPP