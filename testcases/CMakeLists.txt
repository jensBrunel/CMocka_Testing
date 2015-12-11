include(${PROJECT_SOURCE_DIR}/testcases_sources.cmake) 

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/DUT ${CMAKE_SOURCE_DIR}/Stubs)

add_definitions(-DMODULE_TEST)

add_library(testcases STATIC ${TEST_SOURCES} )
target_link_libraries(testcases DUT)
