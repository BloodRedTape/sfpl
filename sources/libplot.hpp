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
    static bool Trace(const char *outfilepath, const char *graph_name, size_t image_width, size_t image_height, const TraceData traces[], size_t traces_count);
};

}//namespace libplot::

#endif//LIBPLOT_PLOT_BUILDER_HPP