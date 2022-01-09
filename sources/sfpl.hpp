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

struct OutputParameters{
    size_t ImageWidth = 1280;
    size_t ImageHeight = 720;
    const char *PlotTitle = "";
    const char *XAxisName = "";
    const char *YAxisName = "";
};

struct PlotBuilder{
    static bool Build(const DataSource &source, const char *outfilepath, const OutputParameters &params = {});

    template<size_t N>
    static bool Build(const DataSource (&sources)[N], const char *outfilepath, const OutputParameters &params = {});

    static bool Build(const DataSource sources[], size_t sources_count, const char *outfilepath, const OutputParameters &params = {});
};

inline bool PlotBuilder::Build(const DataSource &source, const char *outfilepath, const OutputParameters &params){
    return Build(&source, 1, outfilepath, params);
}

template<size_t N>
inline bool PlotBuilder::Build(const DataSource (&sources)[N], const char *outfilepath, const OutputParameters &params){
    return Build(sources, N, outfilepath, params);
}

}//namespace sfpl::

#endif//SFPL_HPP