cmake_minimum_required(VERSION 3.0.0)

set(VCPKG_TARGET_TRIPLET x86-windows)

project(H5x VERSION 0.1.0)

add_library(H5x SHARED H5x.cpp Main.cpp)

find_package(minhook REQUIRED)
find_package(libzippp REQUIRED)
find_package(pugixml REQUIRED)

target_link_libraries(H5x
    PRIVATE
        minhook::minhook
        libzippp::libzippp
        pugixml::pugixml
) 
