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
