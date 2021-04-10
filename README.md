# libplot
## Simple and fast c++ plot library
### Png, jpg and tga output image formats are supported
***
## Usage

To use library copy libplot.cpp, libplot.hpp and font.cpp inside your project and feed them to the compiler. 

P.S. It is better not to open font.cpp :-)

## Examples

### Minimum amount of code to create a simple plot:
```c++
#include "libplot.hpp"

using namespace libplot;

int main(){
    // Instead of regular array any array-like data structure can be used
    // including std::vector, std::array and others
    double x[] = {0, 1, 2, 3, 4,  5};
    double y[] = {0, 1, 4, 9, 16, 25};

    TraceData trace; 
    trace.x = &x[0]; // pointer to the first element of X array
    trace.y = &y[0]; // pointer to the first element of Y array
    trace.Count = 6; // elements count of X and Y arrays

    PlotBuilder::Trace(trace, "parabola.jpg");
}

```
Expected result:
![](https://github.com/E1Hephaestus/libplot/blob/master/examples/parabola.jpg?raw=true)

### Array of TraceData can be passed in order to plot multiple traces
```c++

    TraceData traces[SIZE];
    //... code to fill traces array
    PlotBuilder::Trace(traces, "parabola.jpg");

```
### Each trace can be provided with a name

```c++
    TraceData trace; 
    //... code to fill trace structure
    trace.Name = "Trace Name";

```

### Output image width and height, plot title and axis names can be passed as function parameters
By default they are empty.

```c++
    //...
    PlotBuilder::Trace(traces, "parabola.jpg", ImageWidth, ImageHeight, "PlotTitle", "XAxisName", "YAxisName");

```

### Combining this techniques can lead to something like this
***

![](https://github.com/E1Hephaestus/libplot/blob/master/examples/operations.png?raw=true)

## Original library intention was to plot operation benchmarks

It can be done somehow like this

```c++
#include "libplot.hpp"
// https://github.com/E1Hephaestus/clock
#include "clock.hpp"

using namespace libplot;

void HeavyOperation(int n){
    ++n;
    for(int i = 0; i<n; i++){
        char *array = new char[n*20];
        for(int j = 0; j<n*20; j++)
            array[j] = 0;
        delete[] array;
    }
}

int main(){
    const int BenchmarkSize = 1000;

    double x[BenchmarkSize];
    double y[BenchmarkSize];

    for(int j = 0; j<BenchmarkSize; ++j){
        Clock clock;

        HeavyOperation(j);

        auto time = clock.GetElapsedTime().AsNanoseconds();

        x[j] = j;
        y[j] = time;
    }

    TraceData trace;
    trace.x = &x[0];
    trace.y = &y[0];
    trace.Count = BenchmarkSize;

    PlotBuilder::Trace(trace, "heavy_test.jpg",1280, 720, "Heavy Operation Test", "Heavy operation size", "Time [ns]");
}

```

Or in case you are a big STL fan
```c++
#include <vector>
#include "libplot.hpp"
// https://github.com/E1Hephaestus/clock
#include "clock.hpp"

using namespace libplot;

void HeavyOperation(int n){
    for(int i = 0; i<n; i++){
        char *array = new char[n*20];
        for(int j = 0; j<n*20; j++)
            array[j] = 0;
        delete[] array;
    }
}

int main(){
    std::vector<double> x;
    std::vector<double> y;

    for(int j = 0; j<1000; ++j){
        Clock clock;

        HeavyOperation(j);

        auto time = clock.GetElapsedTime().AsNanoseconds();

        x.push_back(j);
        y.push_back(time);
    }

    TraceData trace;
    trace.x = &x[0];
    trace.y = &y[0];
    trace.Count = x.size();

    PlotBuilder::Trace(trace, "heavy_test.jpg",1280, 720, "Heavy Operation Test", "Heavy operation size", "Time [ns]");
}
```

Possible Result:
![](https://github.com/E1Hephaestus/libplot/blob/master/examples/heavy_test.jpg?raw=true)
