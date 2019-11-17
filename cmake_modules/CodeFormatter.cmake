find_program(CLANG_FORMAT NAMES clang-format clang-format-6.0)

file(GLOB_RECURSE SOURCES_AND_HEADERS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.h
)

if(CLANG_FORMAT)
    add_custom_target(format
        COMMAND
        ${CLANG_FORMAT}
        -i
        ${SOURCES_AND_HEADERS}
        COMMENT "Auto formatting of all source and header files"
    )
else()
    message(STATUS "clang-format tool wasn't found. Can't format code. Check if installation enabled in Dockerfile.")
endif()
