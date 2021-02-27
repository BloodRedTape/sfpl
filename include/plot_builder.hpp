#ifndef LIBPLOT_PLOT_BUILDER_HPP
#define LIBPLOT_PLOT_BUILDER_HPP

#include <cstddef>

namespace libplot{

struct TraceData{
    double *x    = nullptr;
    double *y    = nullptr;
    size_t Count = 0;
};

struct PlotBuilder{
    static void Trace(const char *outfilepath, const char *graph_name, size_t image_width, size_t image_height, TraceData traces[], size_t traces_count);
};

}//namespace libplot::

#endif//LIBPLOT_PLOT_BUILDER_HPP