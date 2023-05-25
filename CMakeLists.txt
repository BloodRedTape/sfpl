cmake_minimum_required(VERSION 3.10)

project(sfpl)

add_library(sfpl STATIC 
	"sources/font.cpp"
	"sources/sfpl.cpp"
)

target_include_directories(sfpl PUBLIC "sources/")



add_executable(sfpl-tests
    "tests/function_range.cpp"
    "tests/line_chart_builder.cpp"
    "tests/math_chart_builder.cpp"

    "tests/main.cpp"
)

target_link_libraries(sfpl-tests PRIVATE sfpl)