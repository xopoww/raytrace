cmake_minimum_required(VERSION 3.10)

project(render LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../)


# === Main library

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/body.cpp"
    "${PROJECT_SOURCE_DIR}/material.cpp"
    "${PROJECT_SOURCE_DIR}/scene.cpp"
    
    "${PROJECT_SOURCE_DIR}/imagery/color.cpp"
    "${PROJECT_SOURCE_DIR}/imagery/image.cpp"
    "${PROJECT_SOURCE_DIR}/imagery/png.cpp"
    "${PROJECT_SOURCE_DIR}/imagery/ppm.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/imagery"
)


# === Dependencies

add_subdirectory("${PROJECT_SOURCE_DIR}/linalg")
target_link_libraries(${PROJECT_NAME} PUBLIC linalg)

find_package(OpenMP)

if (OpenMP_FOUND)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE RAYTRACE_USE_OMP)
    message(STATUS "Found OpenMP which will be used for multicore rendering")
endif()

find_package( PNG )

if ( PNG_FOUND )
    target_link_libraries( ${PROJECT_NAME} PRIVATE ${PNG_LIBRARY} )
    target_include_directories( ${PROJECT_NAME} PRIVATE ${PNG_INCLUDES} )
    target_compile_definitions( ${PROJECT_NAME} PRIVATE ${PNG_DEFINITIONS} )
else()
    target_compile_definitions( ${PROJECT_NAME} PRIVATE LIBPNG_NOT_FOUND )
    message( WARNING "libpng not found - png backends will be unavailable")
endif()


# === Testing (including manual)

add_executable(${PROJECT_NAME}_mantest "${PROJECT_SOURCE_DIR}/test.cpp")

target_link_libraries(${PROJECT_NAME}_mantest PRIVATE ${PROJECT_NAME})


# === After-build stuff

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
