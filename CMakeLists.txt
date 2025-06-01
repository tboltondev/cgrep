cmake_minimum_required(VERSION 3.15)
project(cgrep VERSION 0.0.1 LANGUAGES C)

set(SOURCES
  src/main.c
  src/searcher.c
  src/search_result.c
  src/output_handler.c
  src/file_utils.c
  src/json_utils.c
)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(cgrep ${SOURCES})
