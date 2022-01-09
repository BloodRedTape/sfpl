# SFPL - Simple and Fast Plotting Library 
### Png, jpg and tga output image formats are supported
***
## Usage

To use library copy sfpl.cpp, sfpl.hpp and font.cpp inside your project and feed them to the compiler. 

P.S. It is better not to open font.cpp :-)

## Examples

### Minimum amount of code to create a simple plot:
```c++
#include <sfpl.hpp>

using namespace sfpl;

int main(){
    // Instead of regular array any array-like data structure can be used
    // including std::vector, std::array and others
    double x[] = {0, 1, 2, 3, 4,  5};
    double y[] = {0, 1, 4, 9, 16, 25};

    DataSource source; 
    source.X = &x[0]; // pointer to the first element of X array
    source.Y = &y[0]; // pointer to the first element of Y array
    source.Count = 6; // elements count of X and Y arrays

    PlotBuilder::Build(source, "parabola.jpg");
}

```
Expected result:
![](https://github.com/E1Hephaestus/sfpl/blob/master/examples/parabola.jpg?raw=true)

### Array of DataSource can be passed in order to plot multiple data sets
```c++

    DataSource sources[SIZE];
    //... code to fill traces array
    PlotBuilder::Build(sources, "parabola.jpg");

```
### Each trace can be provided with a name

```c++
    DataSource source; 
    //... code to fill trace structure
    source.Name = "Source Name";

```

### Output image width and height, plot title and axis names can be passed as function parameters
By default they are empty.

```c++
    //...
    OutputParameters params;
    params.ImageWidth = 1280;
    params.ImageHeight = 720;
    params.PlotTitle = "PlotTitle";
    params.XAxisName = "XAxisName";
    params.YAxisName = "YAxisName";

    PlotBuilder::Build(source, "parabola.jpg", params);

```

### Combining this techniques can lead to something like this
***

![](https://github.com/E1Hephaestus/sfpl/blob/master/examples/sort.jpg?raw=true)

## Original library intention was to plot operation benchmarks

It can be done somehow like this

```c++
#include <sfpl.hpp>
// https://github.com/E1Hephaestus/clock
#include "clock.hpp"

using namespace sfpl;

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

    OutputParameters params;
    params.ImageWidth = 1280;
    params.ImageHeight = 720;
    params.PlotTitle = "Heavy Operation Test";
    params.XAxisName = "Heavy operation size";
    params.YAxisName = "Time [ns]";

    DataSource source;
    source.X = &x[0];
    source.Y = &y[0];
    source.Count = BenchmarkSize;

    PlotBuilder::Build(source, "heavy_test.jpg", params);
}

```

Or in case you are a big STL fan
```c++
#include <vector>
#include <sfpl.hpp>
// https://github.com/E1Hephaestus/clock
#include "clock.hpp"

using namespace sfpl;

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
    std::vector<double> x;
    std::vector<double> y;

    for(int j = 0; j<1000; ++j){
        Clock clock;

        HeavyOperation(j);

        auto time = clock.GetElapsedTime().AsNanoseconds();

        x.push_back(j);
        y.push_back(time);
    }

    OutputParameters params;
    params.ImageWidth = 1280;
    params.ImageHeight = 720;
    params.PlotTitle = "Heavy Operation Test";
    params.XAxisName = "Heavy operation size";
    params.YAxisName = "Time [ns]";

    DataSource source;
    source.X = &x[0];
    source.Y = &y[0];
    source.Count = x.size();

    PlotBuilder::Build(source, "heavy_test.jpg", params);
}

```

Possible Result:
![](https://github.com/E1Hephaestus/sfpl/blob/master/examples/heavy_test.jpg?raw=true)
