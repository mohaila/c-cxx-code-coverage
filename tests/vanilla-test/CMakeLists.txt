set(TARGET vanilla-test)
set(SRC main.cpp)

add_executable(${TARGET} ${SRC})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(${TARGET} PRIVATE
    gtest_main
    gtest
)
add_test(NAME ${TARGET} 
    COMMAND ${TARGET}
)