cmake_minimum_required(VERSION 3.10)

project(libplot)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)

set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sources)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(THIRDPARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

set(SOURCES
    ${SOURCES_DIR}/image.cpp
    ${SOURCES_DIR}/pixel.cpp
    ${SOURCES_DIR}/rasterizer.cpp
    ${SOURCES_DIR}/plot_builder.cpp
    ${SOURCES_DIR}/opensans_regular.cpp
    ${THIRDPARTY_DIR}/stb_truetype.c
    ${THIRDPARTY_DIR}/stb_image_write.c
)
add_library(libplot STATIC ${SOURCES})
target_include_directories(libplot PUBLIC ${INCLUDE_DIR} ${THIRDPARTY_DIR} ${SOURCES_DIR})