# libplot
## Simple and fast c++ plot library
### Examples
```c++
#include "plot_builder.hpp"

int main(){
    double ax[] = {0, 1, 2, 3};
    double ay[] = {0, 1, 4, 9};
    size_t size = sizeof(ax)/sizeof(double);

    libplot::PlotBuilder::Trace("graph.jpg", "Test Graph", {ax, ay, size}, 1280, 720);
}

```
Expected result:
![](https://github.com/E1Hephaestus/libplot/blob/master/examples/graph.jpg?raw=true)

### Or you can go even further
***

![](https://github.com/E1Hephaestus/libplot/blob/master/examples/example.png?raw=true)