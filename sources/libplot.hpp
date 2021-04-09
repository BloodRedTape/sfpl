#ifndef LIBPLOT_HPP
#define LIBPLOT_HPP

#include <cstddef>

namespace libplot{

struct TraceData{
    double *x = nullptr;
    double *y = nullptr;
    size_t Count = 0;
    const char *TraceName = "";
};

struct PlotBuilder{
    static bool Trace(const char *outfilepath, const char *title, size_t image_width, size_t image_height, const TraceData traces[], size_t traces_count);

    template<size_t N>
    static bool Trace(const char *outfilepath, const char *title, size_t image_width, size_t image_height, const TraceData (&traces)[N]);

    static bool Trace(const char *outfilepath, const char *title, size_t image_width, size_t image_height, const TraceData &trace);

};

inline bool PlotBuilder::Trace(const char *outfilepath, const char *title, size_t image_width, size_t image_height, const TraceData &trace){
    return Trace(outfilepath, title, image_width, image_height, &trace, 1);
}

template<size_t N>
inline bool PlotBuilder::Trace(const char *outfilepath, const char *title, size_t image_width, size_t image_height, const TraceData (&traces)[N]){
    return Trace(outfilepath, title, image_width, image_height, traces, N);
}

}//namespace libplot::

#endif//LIBPLOT_PLOT_BUILDER_HPP