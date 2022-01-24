#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>
#include "function_range.hpp"
#include "sfpl.hpp"


using namespace sfpl;

void LineChartBuilderTest(){
    std::vector<double> x, y;
    x.reserve(2000000);
    y.reserve(2000000);

    float all_gen_time = 0;
    float all_build_time = 0;

    int i = 0;
    for(auto range: s_TestFunctionRanges){
        const auto gen_begin = std::chrono::steady_clock::now();

        for(double j = range.Begin; j<=range.End; j+=range.Step){
            x.push_back(j);
            y.push_back(range.Proc(j));
        }

        const auto gen_end = std::chrono::steady_clock::now();
        const float gen_time = std::chrono::duration_cast<std::chrono::nanoseconds>(gen_end - gen_begin).count() / 1000000.f;

        DataSource source;
        source.X = x.data();
        source.Y = y.data();
        source.Count = x.size();

        ChartParameters params;
        params.Width = 1280;
        params.Height = 720;
        params.Title = range.Name;

        LineChartStyle style;
        style.LineStyle = LineStyle::Lines;

        const auto build_begin = std::chrono::steady_clock::now();

        LineChartBuilder::Build(source, ("tests/line_chart_builder/" + std::to_string(i) + "_" + std::string(range.Name) + ".jpg").c_str(), params, style);

        const auto build_end = std::chrono::steady_clock::now();
        const float build_time = std::chrono::duration_cast<std::chrono::nanoseconds>(build_end - build_begin).count() / 1000000.f;

        std::cout<<std::setw(14) << std::left << range.Name << " With "<<std::setw(10) << std::right << source.Count <<std::setw(5) << std::right << " Elements Took " << build_time << " microseconds\n";
        x.clear();
        y.clear();
        i++;
        all_build_time += build_time;
        all_gen_time += gen_time;
    }

    std::cout << "Plotting took " << all_build_time << " microseconds " << " Generating took " << all_gen_time << " microseconds" << std::endl;
}
