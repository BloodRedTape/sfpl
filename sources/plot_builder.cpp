#include <limits>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include "rasterizer.hpp"
#include "plot_builder.hpp"
#include "image.hpp"

namespace libplot{

struct Point{
    size_t x = 0;
    size_t y = 0;
};

struct TracePoint{
    double x;
    double y;
};

struct PlotLimits{
    double MinX, MinY, MaxX, MaxY;
};

struct PlotConfig{
    PlotLimits Limits;
    Pixel Color;
    Pixel TintColor;
    Pixel BackgroundColor;
    Pixel TextColor;
    size_t LineWidth;
    float MarkerRadius;
    Point Margins;
    Point PlotSize; 
};

PlotLimits FindLimits(TraceData array){
    PlotLimits result = {
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::min(),
        std::numeric_limits<double>::min()
    };
    for(size_t i = 0; i<array.Count; i++){
        if(array.x[i] < result.MinX)
            result.MinX = array.x[i];
        if(array.y[i] < result.MinY)
            result.MinY = array.y[i];    
        if(array.x[i] > result.MaxX)
            result.MaxX = array.x[i];    
        if(array.y[i] > result.MaxY)
            result.MaxY = array.y[i];    
    }
    return result;
}

inline TracePoint ClampToPlotSize(const PlotConfig &config, TracePoint point){
    return {
        config.PlotSize.x * ((point.x - config.Limits.MinX)/(config.Limits.MaxX - config.Limits.MinX)),
        config.PlotSize.y * ((point.y - config.Limits.MinY)/(config.Limits.MaxY - config.Limits.MinY))
    };
}

char PostfixTable[] = {
    'k',
    'm',
    'b',
    't'
};

float PowerTable[] = {
    1000.f,
    1000000.f,
    1000000000.f,
    1000000000000.f
};

std::string Format(double n){
    char postfix = 0;
    for(size_t i = sizeof(PostfixTable); i>0; --i){
        if(fabs(n) > PowerTable[i - 1]){
            n/=PowerTable[i - 1];
            postfix = PostfixTable[i - 1];
            break;
        }
    }
    std::stringstream ss;
    ss << std::setw(3 + (postfix == 0)) << std::ceil(n) << postfix;
    return ss.str();
}

void PlotBuilder::Trace(const char *outfilename, const char *trace_name, TraceData array, size_t image_width, size_t image_height){
    if(array.Count < 2){
        std::cerr << "Plot " << trace_name << " should have more than 2 points" << std::endl;
        return;
    }

    PlotConfig config;
    config.Limits           = FindLimits(array);
    config.Color            = Color::Green;
    config.TintColor        = {245, 252, 237, 255};
    config.BackgroundColor  = Color::White;
    config.TextColor        = {80, 80, 80, 255};
    config.LineWidth        = 1;
    config.MarkerRadius     = 6;
    config.Margins.x        = image_width * 0.1;
    config.Margins.y        = image_height * 0.1;
    config.PlotSize.x       = image_width - config.Margins.x * 2;
    config.PlotSize.y       = image_height - config.Margins.y * 2;

    float title_font_size   = std::min(config.Margins.x, config.Margins.y) * 0.6;
    float axis_font_size    = title_font_size/2;
    float x_font_margin = axis_font_size * 2;
    float y_font_margin = axis_font_size * 1.05;

    Image background(image_width, image_height, config.BackgroundColor);

    Rasterizer::DrawRect(background, config.TintColor, config.Margins.x, config.Margins.y, config.PlotSize.x, config.PlotSize.y);
    Rasterizer::DrawString(background, config.TextColor, trace_name, title_font_size, config.Margins.x, background.Height() - config.Margins.y*0.7);

    float dx = (config.Limits.MaxX - config.Limits.MinX) / std::min(array.Count, (size_t)5);
    float x = config.Limits.MinX; 

    for(size_t i = 0; i<array.Count; ++i){
        if(array.x[i] >= x){
            TracePoint cross = ClampToPlotSize(config, {array.x[i], array.y[i]});
            Rasterizer::DrawLine(background, config.BackgroundColor, 1, config.Margins.x + cross.x, config.Margins.y, config.Margins.x + cross.x, image_height - config.Margins.y);
            Rasterizer::DrawString(background, config.TextColor, Format(array.x[i]).c_str(), axis_font_size, config.Margins.x + cross.x - axis_font_size/2, config.Margins.y - y_font_margin);

            Rasterizer::DrawLine(background, config.BackgroundColor, 1, config.Margins.x, config.Margins.y + cross.y, image_width - config.Margins.x, config.Margins.y + cross.y);
            Rasterizer::DrawString(background, config.TextColor, Format(array.y[i]).c_str(), axis_font_size, config.Margins.x - x_font_margin, config.Margins.y + cross.y - axis_font_size / 4);
            x += dx;
        }
    }

    Image trace(config.PlotSize.x, config.PlotSize.y, {255, 255, 255, 0});

    for(size_t i = 0; i < array.Count - 1;++i){
        TracePoint p0 = ClampToPlotSize(config, {array.x[i], array.y[i]});
        TracePoint p1 = ClampToPlotSize(config, {array.x[i + 1], array.y[i + 1]});

        Rasterizer::DrawLine(trace, config.Color, config.LineWidth, p0.x, p0.y, p1.x, p1.y);
    }

    background.DrawImage(trace, config.Margins.x, config.Margins.y);

    background.Write(outfilename);
}

}//namespace libplot::