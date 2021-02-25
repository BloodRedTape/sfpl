#ifndef LIBPLOT_IMAGE_HPP
#define LIBPLOT_IMAGE_HPP

#include <assert.h>
#include <cstddef>
#include "error.hpp"
#include "pixel.hpp"

namespace libplot{

class Image{
private:
    Pixel *m_Pixels;
    size_t m_Width;
    size_t m_Height;
public:
    Image(size_t width, size_t height, const Pixel &fill_color = {0, 0, 0, 255});

    Image(const Image &other) = delete;

    ~Image();

    inline size_t Width()const{ return m_Width; }

    inline size_t Height()const{ return m_Height; }

    inline Pixel &Get(size_t x, size_t y){
        assert(x < m_Width);
        assert(y < m_Height);
        y = m_Height - 1 - y;
        return *(m_Pixels + m_Width * y + x);
    }

    inline const Pixel &Get(size_t x, size_t y)const{
        return const_cast<Image*>(this)->Get(x, y);
    }

    inline void DrawPixel(const Pixel &pixel, size_t x, size_t y){
        Get(x, y) = pixel;
    }

    inline void BlendPixel(const Pixel &src, size_t x, size_t y){
        auto& dst = Get(x, y);
        dst.Red   = dst.Red   * (1 - src.Alpha/255.f) + src.Red   * (src.Alpha/255.f);
        dst.Green = dst.Green * (1 - src.Alpha/255.f) + src.Green * (src.Alpha/255.f);
        dst.Blue  = dst.Blue  * (1 - src.Alpha/255.f) + src.Blue  * (src.Alpha/255.f);
        dst.Alpha = dst.Alpha * (1 - src.Alpha/255.f) + src.Alpha;
    }

    void Fill(const Pixel &pixel);

    void DrawImage(const Image &other, size_t x, size_t y);

    Error Write(const char *filepath);
};

}//namespace libplot

#endif//LIBPLOT_IMAGE_HPP