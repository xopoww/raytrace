cmake_minimum_required(VERSION 3.10)

project(render LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE CPPS "*.cpp")

# find_package(OpenMP REQUIRED)
add_executable(${PROJECT_NAME} ${CPPS})
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

find_package( PNGwriter 0.7.0 REQUIRED )

target_link_libraries( ${PROJECT_NAME} PRIVATE PNGwriter::PNGwriter )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
