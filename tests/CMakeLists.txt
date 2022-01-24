cmake_minimum_required(VERSION 3.10)

project(sfpl-tests)


set(SFPL_TESTS_SOURCES
    ../sources/font.cpp
    ../sources/sfpl.cpp

    function_range.cpp
    line_chart_builder.cpp
    math_chart_builder.cpp

    main.cpp
)

set(SFPL_TESTS_INCLUDE
    ../sources
)

add_executable(sfpl-tests
    ${SFPL_TESTS_SOURCES}
)
target_include_directories(sfpl-tests
    PUBLIC ${SFPL_TESTS_INCLUDE}
)