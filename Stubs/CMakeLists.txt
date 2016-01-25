################################################################
# CMakefile for the stubs lib
# Author: Jens Nelke
# Company: Brunel Communications
# Date: 25.01.2016
################################################################

include(${PROJECT_SOURCE_DIR}/stub_sources.cmake) 

add_definitions(-DMODULE_TEST)

add_library(Stubs STATIC ${STUB_SOURCES})
