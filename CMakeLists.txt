cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# 设置 gRPC 和 Protocol Buffers 的头文件路径
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS gfs.proto)
protobuf_generate_grpc_cpp(GRPC_SRCS GRPC_HDRS gfs.proto)


add_executable(client client.cc ${PROTO_SRCS} ${GRPC_SRCS})
add_executable(chunk_server chunk_server.cc ${PROTO_SRCS} ${GRPC_SRCS})
add_executable(master_server master_server.cc ${PROTO_SRCS} ${GRPC_SRCS})

target_link_libraries(client PRIVATE ${Protobuf_LIBRARIES} gRPC::gRPC)
target_link_libraries(chunk_server PRIVATE ${Protobuf_LIBRARIES} gRPC::gRPC)
target_link_libraries(master_server PRIVATE ${Protobuf_LIBRARIES} gRPC::gRPC)

