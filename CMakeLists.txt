cmake_minimum_required(VERSION 3.5)
project(gfs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

find_package(Protobuf REQUIRED)
if (PROTOBUF_FOUND)
    message("protobuf found")
else ()
    message(FATAL_ERROR "Cannot find Protobuf")
endif ()


find_package(gRPC REQUIRED)
if (gRPC_FOUND)
    message("grpc found")
else ()
    message(FATAL_ERROR "Cannot find grpc")
endif ()


# 设置 gRPC 和 Protocol Buffers 的头文件路径
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(src/util)

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS gfs.proto)
PROTOBUF_GENERATE_CPP(GRPC_SRCS GRPC_HDRS gfs.proto)


add_executable(client src/client/client.cc ${PROTO_SRCS} ${GRPC_SRCS})
add_executable(chunk_server src/chunkserver/chunkserver.cc ${PROTO_SRCS} ${GRPC_SRCS})
add_executable(master_server src/master/master_server.cc ${PROTO_SRCS} ${GRPC_SRCS})

target_link_libraries(client PRIVATE ${Protobuf_LIBRARIES} gRPC::grpc++)
target_link_libraries(chunk_server PRIVATE ${Protobuf_LIBRARIES} grpc++)
target_link_libraries(master_server PRIVATE ${Protobuf_LIBRARIES} grpc++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")