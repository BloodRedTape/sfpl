#include <limits>
#include <algorithm>
#include <cmath>
#include "rasterizer.hpp"
#include "plot_builder.hpp"
#include "utils.hpp"
#include "image.hpp"

namespace libplot{

struct TracePoint{
    double x;
    double y;
};

struct PlotLimits{
    double MinX, MinY, MaxX, MaxY;
};

struct PlotConfig{
    PlotLimits Limits;
    Pixel TintColor;
    Pixel BackgroundColor;
    Pixel TextColor;
    size_t LineWidth;
    float MarkerRadius;
    size_t MarginX;
    size_t MarginY;
    size_t PlotSizeX;
    size_t PlotSizeY; 
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
        config.PlotSizeX * ((point.x - config.Limits.MinX)/(config.Limits.MaxX - config.Limits.MinX)),
        config.PlotSizeY * ((point.y - config.Limits.MinY)/(config.Limits.MaxY - config.Limits.MinY))
    };
}

PlotLimits FindArrayLimits(TraceData traces[], size_t traces_count){
    PlotLimits result = {
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::min(),
        std::numeric_limits<double>::min()
    };
    for(size_t i = 0; i<traces_count; ++i){
        for(size_t j = 0; j<traces[i].Count; j++){
            if(traces[i].x[j] < result.MinX)
                result.MinX = traces[i].x[j];
            if(traces[i].y[j] < result.MinY)
                result.MinY = traces[i].y[j];    
            if(traces[i].x[j] > result.MaxX)
                result.MaxX = traces[i].x[j];    
            if(traces[i].y[j] > result.MaxY)
                result.MaxY = traces[i].y[j];    
        }
    }
    return result;
}

void PlotBuilder::Trace(const char *outfilename, const char *graph_name, size_t image_width, size_t image_height, TraceData traces[], size_t traces_count){
#ifndef NDEBUG
    assert(traces);
    assert(traces_count);
    for(size_t i = 0; i<traces_count; ++i)
        assert(traces[i].Count > 1);
#endif

    PlotConfig config;
    config.Limits          = FindArrayLimits(traces, traces_count);
    config.TintColor       = {245, 252, 237, 255};
    config.BackgroundColor = Color::White;
    config.TextColor       = {80, 80, 80, 255};
    config.LineWidth       = 1;
    config.MarkerRadius    = 6;
    config.MarginX         = image_width * 0.1;
    config.MarginY         = image_height * 0.1;
    config.PlotSizeX       = image_width - config.MarginX * 2;
    config.PlotSizeY       = image_height - config.MarginY * 2;

    float title_font_size = std::min(config.MarginX, config.MarginY) * 0.6;
    float axis_font_size  = title_font_size/2;
    float x_font_margin   = axis_font_size * 2;
    float y_font_margin   = axis_font_size * 1.05;

    Image background(image_width, image_height, config.BackgroundColor);

    Rasterizer::DrawRect(background, config.TintColor, config.MarginX, config.MarginY, config.PlotSizeX, config.PlotSizeY);
    Rasterizer::DrawString(background, config.TextColor, graph_name, title_font_size, config.MarginX, background.Height() - config.MarginY*0.7);

    float dx = (config.Limits.MaxX - config.Limits.MinX) / 5;
    float x = config.Limits.MinX; 

    size_t counter = 0;
    while(x < std::floor(config.Limits.MaxX)){
        size_t i = counter++ % traces_count;

        for(size_t j = 0; j<traces[i].Count; ++j){
            if(traces[i].x[j] >= x){
                TracePoint cross = ClampToPlotSize(config, {traces[i].x[j], traces[i].y[j]});
                Rasterizer::DrawLine(background, config.BackgroundColor, 1, config.MarginX + cross.x, config.MarginY, config.MarginX + cross.x, image_height - config.MarginY);
                Rasterizer::DrawString(background, config.TextColor, Utils::Shorten(traces[i].x[j]).c_str(), axis_font_size, config.MarginX + cross.x - axis_font_size/2, config.MarginY - y_font_margin);

                Rasterizer::DrawLine(background, config.BackgroundColor, 1, config.MarginX, config.MarginY + cross.y, image_width - config.MarginX, config.MarginY + cross.y);
                Rasterizer::DrawString(background, config.TextColor, Utils::Shorten(traces[i].y[j]).c_str(), axis_font_size, config.MarginX - x_font_margin, config.MarginY + cross.y - axis_font_size / 4);
                x += dx;
            }
        }
    }


    PaletteGenerator colors;    
    Image trace(config.PlotSizeX, config.PlotSizeY, {255, 255, 255, 0});

    for(size_t i = 0; i<traces_count; ++i){
        Pixel color = colors.NextColor();
        for(size_t j = 0; j < traces[i].Count - 1;++j){
            TracePoint p0 = ClampToPlotSize(config, {traces[i].x[j], traces[i].y[j]});
            TracePoint p1 = ClampToPlotSize(config, {traces[i].x[j + 1], traces[i].y[j + 1]});

            Rasterizer::DrawLine(trace, color, config.LineWidth, p0.x, p0.y, p1.x, p1.y);
        }
    }

    background.DrawImage(trace, config.MarginX, config.MarginY);

    background.Write(outfilename);
}


}//namespace libplot::