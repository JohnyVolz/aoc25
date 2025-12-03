cmake_minimum_required(VERSION 3.28)
project(MyProject)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-14")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")

## Find FFTW3 library (system-wide or /usr/local)
#find_path(FFTW3_INCLUDE_DIR fftw3.h /usr/include /usr/local/include)
#find_library(FFTW3_LIBRARY NAMES fftw3 fftw3f PATHS /usr/lib /usr/local/lib)

#if(NOT FFTW3_INCLUDE_DIR)
#	message(FATAL_ERROR "FFTW3 include not found. Install FFTW3 or set FFTW3_INCLUDE_DIR.")
#endif()
#if(NOT FFTW3_LIBRARY)
#	message(FATAL_ERROR "FFTW3 library not found. Install FFTW3 or set FFTW3_LIBRARY.")
#endif()

add_executable(tag2.out tag2/main.cpp)

# target_include_directories(main PRIVATE ${FFTW3_INCLUDE_DIR})
# target_link_libraries(main PRIVATE ${FFTW3_LIBRARY} m)


