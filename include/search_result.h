#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

#include <stddef.h>
#include <limits.h>

typedef struct {
  char *line;
  size_t line_num;
  size_t line_len;
  size_t match_position;
  size_t match_len;
} MatchedLine;

MatchedLine create_matched_line(const char *line, size_t match_start,
                                size_t match_end, size_t line_num);

typedef struct {
  char path[PATH_MAX];
  MatchedLine *lines;
  size_t count;
  size_t capacity;
} SearchResult;

SearchResult create_search_result(size_t initial_capacity, const char *path);

void add_to_search_result(SearchResult *sr, MatchedLine line);

void free_search_result(const SearchResult *sr);

#endif
