cmake_minimum_required(VERSION 3.30)

project(glaze_vs_protobuf)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)

# add cmake search path
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/generators)

find_package(glaze CONFIG REQUIRED)
find_package(protobuf CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(cppbenchmark CONFIG REQUIRED)

set(TARGET glaze_vs_protobuf)

set(PROTO_FILES
    proto/message.proto
)

set(SOURCE_FILES
    main.cpp
)

set(HEADER_FILES
)

add_executable(
    ${TARGET}
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${PROTO_FILES}
)

target_include_directories(
    ${TARGET} 
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(
    ${TARGET}
    PRIVATE
        spdlog::spdlog
        protobuf::libprotobuf
        glaze::glaze
        cppbenchmark::cppbenchmark
)

protobuf_generate(
    TARGET 
        ${TARGET} 
    LANGUAGE 
        cpp
)