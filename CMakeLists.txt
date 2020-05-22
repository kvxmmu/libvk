cmake_minimum_required(VERSION 3.16)
project(libvk VERSION 1.0 DESCRIPTION "Vk api wrapper")

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

add_library(vk SHARED libvk/libvk.cpp libvk/libvk.hpp)

include_directories(${CURL_INCLUDE_DIRS})

target_link_libraries(vk ${CURL_LIBRARIES})