#ifndef gfs
#define gfs

#include <iostream>

enum state_code {
  state_ok = 0,
  state_err = 1,
  state_file_not_found = 2,
  state_file_chunk_index_err = 3,
  state_length_err = 4,
};

std::string debug_string(state_code c);
std::string debug_string(int32_t c);

#endif