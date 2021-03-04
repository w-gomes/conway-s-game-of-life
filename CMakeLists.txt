cmake_minimum_required(VERSION 3.16)

############################ project setup ############################

project(game-of-life LANGUAGES CXX)
include(cmake/standard_project_settings.cmake)
include(cmake/prevent_in_source_builds.cmake)


############################ external libraries ############################

# add installed libraries
find_package(fmt REQUIRED)


############################ Options ############################

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)
target_include_directories(project_options INTERFACE ${CMAKE_SOURCE_DIR}/external)

# time trace if clang
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

set_target_properties(project_options 
  PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON
             CMAKE_CXX_EXTENSIONS OFF
             CMAKE_BUILD_TYPE "Debug"
)


############################ warnings, sanitizers ############################

# Link this 'library' to use the warnings specified in compiler_warnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/compiler_warnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/sanitizers.cmake)
enable_sanitizers(project_options)

# static analyzers
include(cmake/static_analyzers.cmake)


############################ project files ############################

add_executable(example src/main.cpp
                       src/parser.cpp)

target_link_libraries(
  example
  PRIVATE project_warnings
          project_options
          fmt::fmt-header-only
)
