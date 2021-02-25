#ifndef LIBPLOT_RASTERIZER_HPP
#define LIBPLOT_RASTERIZER_HPP

#include "image.hpp"

namespace libplot{

struct Rasterizer{
    static void DrawPoint(Image &image, const Pixel &color, float radius, size_t x, size_t y);

    static void DrawLine(Image &image, const Pixel &pixel, size_t width, size_t x0, size_t y0, size_t x1, size_t y1);

    static void DrawRect(Image &image, const Pixel &pixel, size_t x, size_t y, size_t width, size_t height);

    static void DrawString(Image &image, const Pixel &color, const char *string, size_t font_size, size_t x, size_t y);
};

}//namespace libplot::

#endif//LIBPLOT_RASTERIZER_HPP