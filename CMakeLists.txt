cmake_minimum_required(VERSION 3.21)
project(CodeCoverage LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if(ENABLE_COVERAGE)
    find_program(LCOV lcov REQUIRED)
    find_program(GENHTML genhtml REQUIRED)

    add_custom_target(coverage
        COMMAND ${LCOV} --directory . 
            --ignore-errors unused
            --exclude usr 
            --exclude gtest 
            --exclude gmock 
            --exclude System 
            --exclude Mock 
            --exclude Wrapper 
            --exclude tests 
            --capture 
            --output-file coverage.info              
        COMMAND ${GENHTML} --demangle-cpp -o coverage coverage.info
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    ) 
endif()

add_subdirectory(extern)
add_subdirectory(source)

if(ENABLE_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()