#include <iostream>
#include <string>
#include "image.hpp"
#include "stb_image_write.h"

namespace libplot{
Image::Image(size_t width, size_t height, const Pixel &fill_color):
    m_Width(width),
    m_Height(height)
{
    m_Pixels = new Pixel[m_Height * m_Width];
    Fill(fill_color);
}

Image::~Image(){
    delete[] m_Pixels;
}

void Image::Fill(const Pixel &pixel){
    for(size_t j = 0; j<m_Height; ++j)
    for(size_t i = 0; i<m_Width; ++i){
        DrawPixel(pixel, i, j);
    }
}

void Image::DrawImage(const Image &other, size_t x, size_t y){
    for(size_t j = 0; j < other.Height(); ++j)
    for(size_t i = 0; i < other.Width();  ++i){
        BlendPixel(other.Get(i,j), x + i, y + j);
    }
}

Error Image::Write(const char *filepath){
    std::string str(filepath);
    std::string extension(&str[str.find_last_of('.') + 1]);

    if(extension == "png"){
        stbi_write_png(filepath, m_Width, m_Height, 4, m_Pixels, m_Width * 4);
    }else if(extension == "jpg" || extension == "jpeg"){
        stbi_write_jpg(filepath, m_Width, m_Height, 4, m_Pixels, m_Width * 4);
    }else if(extension == "tga"){
        stbi_write_tga(filepath, m_Width, m_Height, 4, m_Pixels);
    }else{
        std::cerr << "Error: Unknown image extension of '" << filepath << "'\n";
        return Error::Failure;
    }

    return Error::None;
}

}//namespace libplot