cmake_minimum_required(VERSION 3.10)

project(render LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE CPPS "*.cpp")

# find_package(OpenMP REQUIRED)
add_executable(${PROJECT_NAME} ${CPPS})
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

find_package( PNG )

if ( PNG_FOUND )
    target_link_libraries( ${PROJECT_NAME} PRIVATE ${PNG_LIBRARY} )
    target_include_directories( ${PROJECT_NAME} PRIVATE ${PNG_INCLUDES} )
    target_compile_definitions( ${PROJECT_NAME} PRIVATE ${PNG_DEFINITIONS} )
else()
    target_compile_definitions( ${PROJECT_NAME} PRIVATE LIBPNG_NOT_FOUND )
    message( STATUS "libpng not found - png backends will be unavailable")
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
