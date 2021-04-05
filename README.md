# libplot
## Simple and fast c++ plot library
### Png, jpg and tga output image formats are supported
***
## Usage

To use library copy libplot.cpp, libplot.hpp and font.cpp inside your project and feed them to the compiler. 

P.S. It is better not to open font.cpp :-)

## Examples

### Small parabola
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



    PlotBuilder::Trace("parabola.jpg", "Test Graph", 1280, 720, &trace, 1);
}

```
Expected result:
![](https://github.com/E1Hephaestus/libplot/blob/master/examples/parabola.jpg?raw=true)

### Or you can go even further
***

![](https://github.com/E1Hephaestus/libplot/blob/master/examples/example.png?raw=true)
