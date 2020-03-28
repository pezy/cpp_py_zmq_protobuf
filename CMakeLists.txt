cmake_minimum_required(VERSION 3.5.1)
project(zmq_cpp)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set (CMAKE_CXX_STANDARD 11)

find_package(ZeroMQ REQUIRED)
find_package(Protobuf)

message(status ${ZeroMQ_INCLUDE_DIR})
message(status ${ZeroMQ_STATIC_LIBRARY})
message(status ${Protobuf_INCLUDE_DIRS})
message(status ${Protobuf_LIBRARIES})
message(status ${Protobuf_PROTOC_LIBRARIES})
message(status ${Protobuf_LITE_LIBRARIES})

include_directories(${ZEROMQ_INCLUDE_DIR})
include_directories(${Protobuf_INCLUDE_DIR})
include_directories("${PROJECT_SOURCE_DIR}")

PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER msg.proto)
ADD_LIBRARY(proto ${PROTO_HEADER} ${PROTO_SRC})

PROTOBUF_GENERATE_PYTHON(PROTO_PY msg.proto)
add_custom_target(myTarget ALL DEPENDS ${PROTO_PY})

add_executable(pub "wuserver.cpp")
target_link_libraries(pub proto
                          ${Protobuf_LIBRARIES}
                          ${ZeroMQ_STATIC_LIBRARY})
