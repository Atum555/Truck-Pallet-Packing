cmake_minimum_required(VERSION 3.26)

project(DA_Project)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(da_project
    src/main.cpp
    src/utils/utils.cpp
    src/parsers/dataset_parser.cpp
    src/algorithms/brute_force.cpp
    src/algorithms/greedy.cpp
    src/algorithms/genetic.cpp
)

target_include_directories(da_project PRIVATE
    ${CMAKE_SOURCE_DIR}/src/model
    ${CMAKE_SOURCE_DIR}/src/utils
    ${CMAKE_SOURCE_DIR}/src/parsers
    ${CMAKE_SOURCE_DIR}/src/algorithms
)

# Copy datasets folder next to the built executable
add_custom_target(copy_datasets ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory "$<TARGET_FILE_DIR:da_project>/datasets"
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:da_project>/datasets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/datasets"
            "$<TARGET_FILE_DIR:da_project>/datasets"
    COMMENT "Copying datasets to output directory"
)

add_dependencies(da_project copy_datasets)
