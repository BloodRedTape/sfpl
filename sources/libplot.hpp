#ifndef LIBPLOT_HPP
#define LIBPLOT_HPP

#include <cstddef>

namespace libplot{

struct TraceData{
    const double *x = nullptr;
    const double *y = nullptr;
    size_t Count = 0;
    const char *TraceName = "";
};

struct PlotBuilder{
    static bool Trace(const TraceData &trace, const char *outfilepath, size_t width = 1280, size_t height = 720, const char *title = "", const char *x_axis_name = "", const char *y_axis_name = "");

    template<size_t N>
    static bool Trace(const TraceData (&traces)[N], const char *outfilepath, size_t width = 1280, size_t height = 720, const char *title = "", const char *x_axis_name = "", const char *y_axis_name = "");

    static bool Trace(const TraceData traces[], size_t traces_count, const char *outfilepath, size_t width, size_t height, const char *title, const char *x_axis_name, const char *y_axis_name);

};

inline bool PlotBuilder::Trace(const TraceData &trace, const char *outfilepath, size_t width, size_t height, const char *title, const char *x_axis_name, const char *y_axis_name){
    return Trace(&trace, 1, outfilepath, width, height, title, x_axis_name, y_axis_name);
}

template<size_t N>
inline bool PlotBuilder::Trace(const TraceData (&traces)[N], const char *outfilepath, size_t width, size_t height, const char *title, const char *x_axis_name, const char *y_axis_name){
    return Trace(traces, N, outfilepath, width, height, title, x_axis_name, y_axis_name);
}

}//namespace libplot::

#endif//LIBPLOT_PLOT_BUILDER_HPP