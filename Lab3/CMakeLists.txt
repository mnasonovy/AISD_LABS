cmake_minimum_required(VERSION 3.11)

project(sorting CXX)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

add_library(sorting
    "include/stats.h"
    "include/selectionSort.h"
)

set_target_properties(sorting PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(sorting PUBLIC cxx_std_23)

