include(${PROJECT_SOURCE_DIR}/stub_sources.cmake) 

add_definitions(-DMODULE_TEST)

add_library(Stubs STATIC ${STUB_SOURCES})
