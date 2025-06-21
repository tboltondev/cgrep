cmake_minimum_required(VERSION 3.15)
project(cgrep VERSION 0.0.1 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS On)

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
)

target_include_directories(cgrep PRIVATE include)
