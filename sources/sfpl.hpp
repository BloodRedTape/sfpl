#ifndef SFPL_HPP
#define SFPL_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <cfloat>

namespace sfpl{

struct DataSource{
    const double *X = nullptr;
    const double *Y = nullptr;
    std::size_t Count = 0;
    const char *Name = "";
};

struct ChartParameters{
    std::size_t Width  = 1280;
    std::size_t Height = 720;
    const char *Title      = "";
    const char *XAxisName  = "";
    const char *YAxisName  = "";
    std::function<std::string(double)> XStringify = &DefaultStringify;
    std::function<std::string(double)> YStringify = &DefaultStringify;
    double EpsX = std::numeric_limits<double>::epsilon();
    double EpsY = std::numeric_limits<double>::epsilon();

    static std::string DefaultStringify(double value);
};

enum class LineStyle: int{
    Lines        = 0x01,
    Dots         = 0x02,
    LinesAndDots = 0x03
};

struct LineChartStyle{
    enum LineStyle LineStyle = LineStyle::Lines;
};

enum class ImageFormat {
    Png,
    Jpg
};

struct LineChartBuilder{
    static bool Build(const DataSource &source, const char *outfilepath, const ChartParameters &params = {}, LineChartStyle style = {}){
        return Build(&source, 1, outfilepath, params, style);
    }

    template<std::size_t N>
    static bool Build(const DataSource (&sources)[N], const char *outfilepath, const ChartParameters &params = {}, LineChartStyle style = {}){
        return Build(sources, N, outfilepath, params, style);
    }

    static bool Build(const DataSource sources[], std::size_t sources_count, const char *outfilepath, ChartParameters params = {}, LineChartStyle style = {});

    static std::string BuildToMemory(const DataSource &source, ImageFormat format, const ChartParameters &params = {}, LineChartStyle style = {}){
        return BuildToMemory(&source, 1, format, params, style);
    }

    template<std::size_t N>
    static std::string BuildToMemory(const DataSource (&sources)[N], ImageFormat format, const ChartParameters &params = {}, LineChartStyle style = {}){
        return BuildToMemory(sources, N, format, params, style);
    }

    static std::string BuildToMemory(const DataSource sources[], std::size_t sources_count, ImageFormat format, ChartParameters params = {}, LineChartStyle style = {});
};

struct MathChartStyle{
    enum LineStyle LineStyle = LineStyle::Lines;
};

struct MathChartBuilder{
    static bool Build(const DataSource &source, const char *outfilepath, const ChartParameters &params = {}, MathChartStyle style = {}){
        return Build(&source, 1, outfilepath, params, style);
    }

    template<std::size_t N>
    static bool Build(const DataSource (&sources)[N], const char *outfilepath, const ChartParameters &params = {}, MathChartStyle style = {}){
        return Build(sources, N, outfilepath, params, style);
    }

    static bool Build(const DataSource sources[], std::size_t sources_count, const char *outfilepath, ChartParameters params = {}, MathChartStyle style = {});
};


}//namespace sfpl::

#endif//SFPL_HPP