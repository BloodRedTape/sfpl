#ifndef SFPL_HPP
#define SFPL_HPP

#include <cstddef>

namespace sfpl{

struct DataSource{
    const double *X = nullptr;
    const double *Y = nullptr;
    size_t Count = 0;
    const char *Name = "";
};

struct ChartParameters{
    size_t Width  = 1280;
    size_t Height = 720;
    const char *Title      = "";
    const char *XAxisName  = "";
    const char *YAxisName  = "";
};

enum class LineStyle: int{
    Lines        = 0x01,
    Dots         = 0x02,
    LinesAndDots = 0x03
};

struct LineChartStyle{
    enum LineStyle LineStyle = LineStyle::Lines;
};

struct LineChartBuilder{
    static bool Build(const DataSource &source, const char *outfilepath, const ChartParameters &params = {}, LineChartStyle style = {}){
        return Build(&source, 1, outfilepath, params, style);
    }

    template<size_t N>
    static bool Build(const DataSource (&sources)[N], const char *outfilepath, const ChartParameters &params = {}, LineChartStyle style = {}){
        return Build(sources, N, outfilepath, params, style);
    }

    static bool Build(const DataSource sources[], size_t sources_count, const char *outfilepath, ChartParameters params = {}, LineChartStyle style = {});
};

}//namespace sfpl::

#endif//SFPL_HPP