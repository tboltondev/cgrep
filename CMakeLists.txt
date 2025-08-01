cmake_minimum_required(VERSION 3.15)
project(cgrep VERSION 0.0.1 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS On)

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

if(ENABLE_ASAN)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

add_executable(cgrep ${SOURCES})

target_sources(
  cgrep
  PRIVATE
  src/main.c
  src/searcher.c
  src/search_result.c
  src/output_handler.c
  src/file_utils.c
  src/json_utils.c
  src/arg_parser.c
  src/csv_utils.c
)

target_include_directories(cgrep PRIVATE include)
