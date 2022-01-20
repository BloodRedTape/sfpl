#ifndef SFPL_HPP
#define SFPL_HPP

#include <cstddef>

namespace sfpl{

struct ImageOutputParams{
    size_t Width = 1280;
    size_t Height = 720;
};

struct DataSource{
    const double *X = nullptr;
    const double *Y = nullptr;
    size_t Count = 0;
    const char *Name = "";
};

enum class LineStyle: int{
    Lines        = 0x01,
    Dots         = 0x02,
    LinesAndDots = 0x03
};

struct LineChartStyle{
    enum LineStyle LineStyle = LineStyle::Lines;
    const char *ChartTitle = "";
    const char *XAxisName = "";
    const char *YAxisName = "";
};

struct LineChartBuilder{
    static bool Build(const DataSource &source, const char *outfilepath, const LineChartStyle &style = {}, const ImageOutputParams &params = {});

    template<size_t N>
    static bool Build(const DataSource (&sources)[N], const char *outfilepath, const LineChartStyle &style = {}, const ImageOutputParams &params = {});

    static bool Build(const DataSource sources[], size_t sources_count, const char *outfilepath, LineChartStyle style = {}, ImageOutputParams params = {});
};

inline bool LineChartBuilder::Build(const DataSource &source, const char *outfilepath, const LineChartStyle &style, const ImageOutputParams &params){
    return Build(&source, 1, outfilepath, style, params);
}

template<size_t N>
inline bool LineChartBuilder::Build(const DataSource (&sources)[N], const char *outfilepath, const LineChartStyle &style, const ImageOutputParams &params){
    return Build(sources, N, outfilepath, style, params);
}

}//namespace sfpl::

#endif//SFPL_HPP