cmake_minimum_required(VERSION 3.7)
set (CMAKE_CXX_STANDARD 14)
project(proto_xpt)

set (GCC_COVERAGE_COMPILE_FLAGS "-coverage -fprofile-arcs -ftest-coverage")
set (GCC_COVERAGE_LINK_FLAGS    "-coverage -lgcov")
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
set (CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

include(FindProtobuf)
find_package(Protobuf REQUIRED)
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS
#   "${CMAKE_SOURCE_DIR}/msh/mesh2dcartesian.proto")

file(GLOB_RECURSE sources "src/*.cpp" "src/*.cc")
#list(APPEND sources ${PROTO_SRCS} ${PROTO_HDRS})
set(testing_sources ${sources})
list(FILTER sources EXCLUDE REGEX ".(/tests/).")

include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/inc
                    ${Protobuf_INCLUDE_DIRS})

add_executable(proto_xpt ${sources})
add_executable(proto_xpt_test ${testing_sources})

target_compile_definitions(proto_xpt_test PUBLIC -DTEST)

target_link_libraries(proto_xpt ${Protobuf_LIBRARIES})

target_link_libraries(proto_xpt_test ${GTEST_BOTH_LIBRARIES}
                               ${GMOCK_BOTH_LIBRARIES}
                               ${Protobuf_LIBRARIES})

