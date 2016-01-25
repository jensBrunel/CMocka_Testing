cmake_minimum_required(VERSION 2.8.7)
project(UnitTesting C)

set(CMAKE_COLOR_MAKEFILE ON)
enable_testing()

# Added for CTest
include(CTest)
# Added for External Projects
include(ExternalProject)
include(wrap_functions.cmake)
include(dut_sources.cmake)

################################################################
# Compiler and linker
################################################################
#Flag can be used for defines
add_definitions(-DMODULE_TEST)

#Compiler flags for C and C++
SET(CMAKE_C_FLAGS "-g -Wall -W -pedantic --coverage")
SET(CMAKE_CXX_FLAGS "-g --coverage"
    CACHE STRING "Flags used by the C++ compiler during coverage builds."
    FORCE )
#Wrap string for linker command is build
STRING(REPLACE ";" ",-wrap," WRAP_FUNCTIONS_RAW "${WRAP_FUNCTIONS_RAW}")
SET(WRAP_FUNCTIONS "-Wl,-wrap,${WRAP_FUNCTIONS_RAW}")

#Linker flags
SET(CMAKE_EXE_LINKER_FLAGS "-O0 -fprofile-arcs -ftest-coverage ${WRAP_FUNCTIONS}")

################################################################
# Set Module Path
################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

################################################################
# Codecoverage with LCOV and GCOVR
################################################################
include(CodeCoverage)
include(CorrectWindowsPaths)

SETUP_TARGET_FOR_COVERAGE(coverage UnitTesting coverage)
SETUP_TARGET_FOR_COVERAGE_COBERTURA(cobertura UnitTesting cobertura)

find_library(CMOCKA_PATH NAMES libcmocka.so PATHS /usr/lib /usr/local/lib)
find_path(CMOCKA_INCLUDE_PATH NAMES cmocka.h PATHS /usr/include/ /usr/local/include/)

if(CMOCKA_PATH AND CMOCKA_INCLUDE_PATH)
get_filename_component(CMOCKA_LIBRARY_PATH ${CMOCKA_PATH} PATH)
else(CMOCKA_PATH AND CMOCKA_INCLUDE_PATH)
################################################################
# External: build and install CMocka
################################################################
ExternalProject_Add(cmocka
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmocka
    CONFIGURE_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/cmocka/build && cmake -DCMAKE_INSTALL_PREFIX=/usr/ -DCMAKE_BUILD_TYPE=Debug ..
    BUILD_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/cmocka/build && make #Build command
    INSTALL_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/cmocka/build && make install
)
set(CMOCKA_INCLUDE_PATH /usr/include/)
set(CMOCKA_LIBRARY_PATH /usr/lib/)
endif(CMOCKA_PATH AND CMOCKA_INCLUDE_PATH)

find_program(LCOV_PATH NAMES lcov PATHS /usr/bin /usr/local/bin)

if(LCOV_PATH)

else(LCOV_PATH)
################################################################
# External: build and install lcov
################################################################
ExternalProject_Add(lcov
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lcov
    CONFIGURE_COMMAND cd .
    BUILD_COMMAND cd .
    INSTALL_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/lcov/ && make install
)
endif(LCOV_PATH)

################################################################
# Include paths, libraries and subdirectories
################################################################
if(CMOCKA_INCLUDE_PATH)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMOCKA_INCLUDE_PATH} ${DUT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/testcases ${CMAKE_SOURCE_DIR}/Stubs)
else(CMOCKA_INCLUDE_PATH)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMOCKA_INCLUDE_PATH} ${DUT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/testcases ${CMAKE_SOURCE_DIR}/Stubs)
endif(CMOCKA_INCLUDE_PATH)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMOCKA_LIBRARY_PATH})

add_subdirectory(Stubs)
add_subdirectory(DUT)
add_subdirectory(testcases)

add_test(UnitTesting ${EXECUTABLE_OUTPUT_PATH}/UnitTesting)

add_executable(UnitTesting main.c)
add_dependencies(UnitTesting lcov mocka  Stubs DUT testcases )

if(CYGWIN)
target_link_libraries(UnitTesting  Stubs DUT testcases libcmocka.dll.a gcov)
else(CYGWIN)
target_link_libraries(UnitTesting  Stubs DUT testcases libcmocka.so gcov)
endif(CYGWIN)
