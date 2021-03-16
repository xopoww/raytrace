cmake_minimum_required( VERSION 3.14 )

project( linalg LANGUAGES CXX)


add_library( ${PROJECT_NAME} STATIC )

target_include_directories( ${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include" )

target_sources(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/src/math.cpp"
    "${PROJECT_SOURCE_DIR}/src/random.cpp"
    "${PROJECT_SOURCE_DIR}/src/ray.cpp"
    "${PROJECT_SOURCE_DIR}/src/vector.cpp"
    )
