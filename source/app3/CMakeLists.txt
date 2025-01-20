set(TARGET app3)
set(SRC main.c)

add_executable(${TARGET} ${SRC})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_SOURCE_DIR}/source
)
target_link_libraries(${TARGET} PRIVATE
    App
    System
)
if(NOT CMAKE_BUILD_TYPE STREQ "Debug")
    set_target_properties(${TARGET} PROPERTIES LINK_FLAGS_RELEASE -s) 
endif()