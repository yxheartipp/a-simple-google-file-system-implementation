#ifndef gfs
#define gfs

#include <cstdint>
#include <string>
#include <vector>

#include "iostream"
#include "string.h"

struct status_code {
  int value;
  std::string exception;
};

struct gfs_config {
  int chunk_size = 64;
  std::vector<std::string> chunk_server_locations = {"50052", "50053", "50054",
                                                     "50055", "50056"};
  std::string chunk_server_root = "root_chunkserver";
};

struct PathInfo {
  std::string Name;

  bool IsDir;

  uint64_t Length;
  uint64_t Chunks;
};

#endif