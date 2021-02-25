#ifndef LIBPLOT_PLOT_BUILDER_HPP
#define LIBPLOT_PLOT_BUILDER_HPP

#include <cstddef>

namespace libplot{

struct TraceData{
    double *x    = nullptr;
    double *y    = nullptr;
    size_t Count = 0;
};

class PlotBuilder{
public:
    static void Trace(const char *outfilename, const char *graph_name, TraceData trace, size_t image_width, size_t image_height);
};

}//namespace libplot::

#endif//LIBPLOT_PLOT_BUILDER_HPP