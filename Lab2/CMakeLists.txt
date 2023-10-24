cmake_minimum_required(VERSION 3.11)

project(linked_list CXX)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/6b63c98ac43efc992122f1da12aaf0a0e0658206.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(linked_list
   "linked_list.cc")
set_target_properties(linked_list PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(linked_list PUBLIC cxx_std_23)


add_executable(linked_list_test
    "tests.cc")
target_link_libraries(linked_list_test gtest gtest_main linked_list)
target_include_directories(linked_list_test PRIVATE "${CMAKE_SOURCE_DIR}")