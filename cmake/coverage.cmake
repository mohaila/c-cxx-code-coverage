find_program(LCOV lcov REQUIRED)
find_program(GENHTML genhtml REQUIRED)

function(addCodeCoverage target)
    add_custom_target(${target}-coverage
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
        COMMAND ${GENHTML} --demangle-cpp -o ${target}-coverage coverage.info
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})   
endfunction()


