cmake_minimum_required(VERSION 3.20)
project(lhs)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_SOURCE_DIR "src")

file(GLOB lhs_soures "src/*.cpp")

add_library(lhs SHARED ${lhs_soures})

# Find the R executable
find_program(R_EXECUTABLE NAMES R R.exe)
find_program(R_SCRIPT_EXECUTABLE NAMES Rscript Rscript.exe)

message(STATUS "R_SCRIPT_EXECUTABLE: ${R_SCRIPT_EXECUTABLE}")

# Execute R to find the Rcpp include directory
execute_process(
    COMMAND ${R_SCRIPT_EXECUTABLE} -e "cat(system.file('include', package='Rcpp'))"
    OUTPUT_VARIABLE RCPP_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${R_SCRIPT_EXECUTABLE} -e "cat(R.home('include'))"
    OUTPUT_VARIABLE R_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${R_SCRIPT_EXECUTABLE} -e "cat(file.path(R.home('bin'), 'R.dll'))"
    OUTPUT_VARIABLE R_LIB_WIN
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${R_SCRIPT_EXECUTABLE} -e "cat(file.path(R.home('lib'), 'libR.so'))"
    OUTPUT_VARIABLE R_LIB_LINUX
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "RCPP_INCLUDE_DIR: ${RCPP_INCLUDE_DIR}")
message(STATUS "R_INCLUDE_DIR: ${R_INCLUDE_DIR}")
message(STATUS "R_LIB_WIN: ${R_LIB_WIN}")
message(STATUS "R_LIB_LINUX: ${R_LIB_LINUX}")

# Add to your project
target_include_directories(lhs PUBLIC ${RCPP_INCLUDE_DIR} ${R_INCLUDE_DIR})

if (MSVC)
  target_link_libraries(lhs PUBLIC ${R_LIB_WIN}) 
  # disable unreferenced formal parameters (4100) and constant conditional expression (4127) and special noexcept from asserterror (26439) and not initialized variables (26495)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /W4 /WX /wd4100 /wd4127 /wd26439 /wd26495")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} /Od /Zi")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /Ox")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} /O2 /Zi")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_SYSTEM_NAME MATCHES "Linux")
  target_link_libraries(lhs PUBLIC ${R_LIB_LINUX}) 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -m64 -Wall -pedantic -mtune=native -Werror -Wno-unknown-pragmas -Wno-long-long")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} -O2 -g")
else ()
  target_link_libraries(lhs PUBLIC ${R_LIBRARY}) 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -m64 -Wall -pedantic -mtune=native -Werror -Wno-unknown-pragmas -Wno-long-long")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} -O2 -g")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov")
  message(STATUS "CXXFLAGS: ${CMAKE_CXX_FLAGS}")
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
  message(STATUS "Debug CXXFLAGS: ${CMAKE_CXX_FLAGS_DEBUG}")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "Release CXXFLAGS: ${CMAKE_CXX_FLAGS_RELEASE}")
else()
  message(STATUS "CXXFLAGS: ${CMAKE_CXX_FLAGS}")
endif()

message(STATUS "Linker FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
