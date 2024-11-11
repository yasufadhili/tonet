cmake_minimum_required(VERSION 3.10)
project(tonet VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API YES)

find_package(Boost REQUIRED COMPONENTS system)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_SOURCE_DIR}/src/*.cpp 
    ${CMAKE_SOURCE_DIR}/src/*.ixx 
    ${CMAKE_SOURCE_DIR}/src/*.cppm 
    ${CMAKE_SOURCE_DIR}/src/*.mpp
)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS 
    ${CMAKE_SOURCE_DIR}/include/*.h 
    ${CMAKE_SOURCE_DIR}/include/*.hpp 
    ${CMAKE_SOURCE_DIR}/include/*.hxx
)

add_executable(tonet ${SOURCE_FILES})
target_include_directories(tonet PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(tonet Boost::system)

#find_package(Filesystem REQUIRED) 
#   target_link_libraries(tonet PRIVATE std::filesystem)

#target_compile_features(tonet PRIVATE cxx_modules)

target_compile_options(tonet PRIVATE -Wall -Wextra -Wpedantic)

