#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include "rasterizer.hpp"
#include "stb_truetype.h"

extern unsigned char opensans_regular[];

namespace libplot{

void Rasterizer::DrawPoint(Image &image, const Pixel &color, float radius, size_t x, size_t y){
    auto circle = [radius](float x)->float{
        return std::sqrt(float(radius * radius - x*x));
    };

    for(float i = -radius; i <= radius; ++i){
        float res = circle(i);
        for(float j = -res; j <= res; j+=1){
            size_t f_x = i+x;
            size_t f_y = j+y;
            if(f_x < image.Width() && f_y < image.Height())
                image.BlendPixel(color, f_x, f_y);
        }
    }
}

void Rasterizer::DrawLine(Image &image, const Pixel &pixel, size_t width, size_t x0, size_t y0, size_t x1, size_t y1){
    if(y1 < y0){
        std::swap(y0, y1);
        std::swap(x0, x1);
    }

    long long dx = (long long)x1 - (long long)x0;
    long long dy = y1-y0; // swap quarantees no negative numbers

    float k = (dx != 0) ? float(dy)/float(llabs(dx)) : dy;

    int side = dx > 0 ? 1 : -1;

    auto line = [k](size_t x) -> size_t{
        return k*x;
    };

    for(long x = 0;x <= llabs(dx); x += 1){
        size_t y = line(x);
        size_t y_max = line(x + 1);
        for(;y < y_max || y == y_max; ++y)
            DrawPoint(image, pixel, width, x0 + x*side, y0 + y);
    }
}

void Rasterizer::DrawRect(Image &image, const Pixel &pixel, size_t x0, size_t y0, size_t width, size_t height){
    for(size_t j = y0; j<=height + y0; ++j)
    for(size_t i = x0; i<=width + x0;  ++i)
        image.BlendPixel(pixel, i, j);
}

struct FontInfo{
    stbtt_fontinfo STBTTInfo;
    unsigned char *FontBuffer = opensans_regular;

    FontInfo(){
        if(!stbtt_InitFont(&STBTTInfo, FontBuffer, stbtt_GetFontOffsetForIndex(FontBuffer, 0)))puts("Oh shit, stbtt can't init font");
    }
};

FontInfo default_font;

void Rasterizer::DrawString(Image &image, const Pixel &color, const char *string, size_t font_size, size_t x0, size_t y0){    
    int offset = 0;
    for(size_t i = 0; i<strlen(string); ++i){
        if(string[i] == ' '){
            offset += font_size * 0.2;
            continue;
        }

        int width, height, xoffset, yoffset;
        unsigned char *bitmap = stbtt_GetCodepointBitmap(&default_font.STBTTInfo, 0, stbtt_ScaleForPixelHeight(&default_font.STBTTInfo, font_size), (int)string[i], &width, &height, &xoffset, &yoffset);

        for(int y = 0; y < height; y++)
        for(int x = 0; x < width;  x++)
            image.BlendPixel({color.Red, color.Green, color.Blue, (unsigned char)(color.Alpha * (bitmap[y * width + x]/255.f))}, x0 + offset + x, y0 + abs(yoffset) - y);
        offset += width + font_size * 0.03;
        stbtt_FreeBitmap(bitmap, nullptr);
    }
}

}//namespace libplot::