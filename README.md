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
    // Instead of regular array you can use any array-like data structures 
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

### You can pass array of TraceData in order to plot multiple traces
```c++

    TraceData traces[SIZE];
    //... code to fill traces array
    PlotBuilder::Trace(traces, "parabola.jpg");

```
### You can provide each trace with name

```c++
    TraceData trace; 
    //... code to fill trace structure
    trace.Name = "Trace Name";

```

### You can pass output image width and height, plot title and axis names
By default they are empty.

```c++
    //...
    PlotBuilder::Trace(traces, "parabola.jpg", ImageWidth, ImageHeight, "PlotTitle", "XAxisName", "YAxisName");

```

### In the end you can get something like this
***

![](https://github.com/E1Hephaestus/libplot/blob/master/examples/operations.png?raw=true)
