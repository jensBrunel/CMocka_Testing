cmake_minimum_required(VERSION 2.8.7)
project(UnitTesting C)

set(CMAKE_COLOR_MAKEFILE ON)
enable_testing()

# Added for CTest
include(CTest)
# Added for External Projects
include(ExternalProject)

add_definitions(-DMODULE_TEST)

SET(CMAKE_C_FLAGS "-g -Wall -W -pedantic --coverage")
SET(CMAKE_CXX_FLAGS "-g --coverage"
    CACHE STRING "Flags used by the C++ compiler during coverage builds."
    FORCE )
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

################################################################
# Set Module Path
################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include(CodeCoverage)
include(CorrectWindowsPaths)

SETUP_TARGET_FOR_COVERAGE(coverage UnitTesting coverage)

SETUP_TARGET_FOR_COVERAGE_COBERTURA(cobertura UnitTesting cobertura)

find_library(CUNIT_PATH NAMES libcunit.a PATHS /usr/lib /usr/local/lib)
find_path(CUNIT_INCLUDE_PATH NAMES CUnit.h PATHS /usr/include/CUnit /usr/local/include/CUnit)

if(CUNIT_PATH)
set(CUNIT_LIBRARY_PATH $CUNIT_PATH)
else(CUNIT_PATH)
################################################################
# External: CUNIT
################################################################
set(CUNIT_LIBRARY_PATH /usr/local/lib/)
ExternalProject_Add(cunit
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CUnit
    CONFIGURE_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/ && autoreconf --install && ./configure --prefix=${CUNIT_LIBRARY_PATH}
    BUILD_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/ && make #Build command
    INSTALL_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/ && make install 
)

endif(CUNIT_PATH)

find_program(LCOV_PATH NAMES lcov PATHS /usr/bin /usr/local/bin)

if(LCOV_PATH)

else(LCOV_PATH)
################################################################
# External: lcov
################################################################
ExternalProject_Add(lcov
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lcov
    CONFIGURE_COMMAND cd .
    BUILD_COMMAND cd .
    INSTALL_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/lcov/ && make install
)
endif(LCOV_PATH)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CUNIT_INCLUDE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/DUT ${CMAKE_CURRENT_SOURCE_DIR}/testcases ${CMAKE_SOURCE_DIR}/Stubs)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CUNIT_LIBRARY_PATH})

add_subdirectory(Stubs)
add_subdirectory(DUT)
add_subdirectory(testcases)

add_test(UnitTesting ${EXECUTABLE_OUTPUT_PATH}/UnitTesting)

add_executable(UnitTesting main.c)
add_dependencies(UnitTesting locv cunit Stubs DUT testcases lint)

target_link_libraries(UnitTesting Stubs DUT testcases libcunit.a gcov)
