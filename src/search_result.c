#include "search_result.h"
#include "exit_status.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MatchedLine create_matched_line(const char *line, const size_t match_start, const size_t match_end,
                                const size_t line_num) {
  const size_t line_len = strlen(line) + 1;

  const MatchedLine matched_line = {.line = malloc(line_len),
                              .line_num = line_num,
                              .line_len = line_len,
                              .match_position = match_start,
                              .match_len = match_end - match_start};

  strncpy(matched_line.line, line, matched_line.line_len);

  return matched_line;
}

void free_matched_line(const MatchedLine *matched_line) { free(matched_line->line); }

SearchResult create_search_result(const size_t initial_capacity, const char *path) {
  MatchedLine *lines = malloc(initial_capacity * sizeof(MatchedLine));
  if (lines == NULL) {
    fprintf(stderr, "Malloc failed creating search result.\n");
    exit(MEM_ALLOC_ERR);
  }
  SearchResult search_result = {
      .lines = lines,
      .count = 0,
      .capacity = initial_capacity};

  strncpy(search_result.path, path, strlen(path));

  return search_result;
}

void add_to_search_result(SearchResult *sr, const MatchedLine line) {
  if (sr->count == sr->capacity) {
    sr->capacity *= 2;
    MatchedLine *temp = realloc(sr->lines, sr->capacity * sizeof(MatchedLine));
    if (temp == NULL) {
      fprintf(stderr, "Realloc failed adding to search result.\n");
      exit(MEM_ALLOC_ERR);
    }
    sr->lines = temp;
  }
  sr->lines[sr->count] = line;
  sr->count++;
}

void free_search_result(const SearchResult *sr) {
  for (int i = 0; i < sr->count; i++) {
    free_matched_line(&sr->lines[i]);
  }
  free(sr->lines);
}
