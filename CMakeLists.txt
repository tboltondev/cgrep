cmake_minimum_required(VERSION 3.15)
project(cgrep VERSION 0.0.1 LANGUAGES C)

add_executable(cgrep
  main.c
  searcher.c
  search_result.c
  output_handler.c
  file_utils.c)

include_directories(${PROJECT_SOURCE_DIR}) 
