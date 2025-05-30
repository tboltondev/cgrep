#include "../include/searcher.h"
#include "../include/file_utils.h"
#include "../include/search_result.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/syslimits.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define MAX_LINE_SIZE 300 * sizeof(char)

void search_file(SearchResult *sr, char *pattern, char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("Error opening file %s\n", path);
  }

  char line[300]; // Max chars in line, maybe make dynamic

  int line_num = 1;

  while (fgets(line, sizeof(line), file) != NULL) {
    char *match = strstr(line, pattern);

    if (match != NULL) {
      // int matched_position = match - line;
      // int match_length = strlen(pattern);
      // int line_len = strlen(line);

      // char matched_line[MAX_LINE_SIZE];
      // int buffer_size = sizeof(matched_line);
      // int offset = 0;

      // TODO: colors shouldnt be part of this
      // offset += snprintf(matched_line + offset, buffer_size - offset,
      //                    ANSI_COLOR_GREEN);
      // offset += snprintf(matched_line + offset, buffer_size - offset,
      //                    "%i:", line_num);
      // offset += snprintf(matched_line + offset, buffer_size - offset,
      //                    ANSI_COLOR_RESET);
      // offset +=
      //     snprintf(matched_line + offset, buffer_size - offset, "%.*s",
      //              matched_position, line); // part of line before first match
      // offset +=
      //     snprintf(matched_line + offset, buffer_size - offset, ANSI_COLOR_RED);
      // offset += snprintf(matched_line + offset, buffer_size - offset, "%.*s",
      //                    match_length, &line[matched_position]); // first match
      // offset += snprintf(matched_line + offset, buffer_size - offset,
      //                    ANSI_COLOR_RESET);
      // offset +=
      //     snprintf(matched_line + offset, buffer_size - offset, "%s",
      //              &line[matched_position + match_length]); // remainder of line

      MatchedLine ml = create_matched_line(line, match, line_num); // TODO: rename

      _add_to_search_result(sr, ml);

      // add_to_search_result(sr, matched_line);
    }
    line_num++;
  }
}

void handle_search_file(char *pattern, char *path, ResultHandler result_handler) {
    SearchResult sr = create_search_result(10, path);

    search_file(&sr, pattern, path);

    if (sr.count > 0)
      result_handler(sr);

    // free_search_result(&sr);
}

void search_dir_recursively(char *pattern, char *base_path, ResultHandler result_handler, int current_depth,
                            int max_depth) {
  if (current_depth > max_depth) {
    printf("Reached max directory depth\n");
    return;
  }

  DIR *dir = opendir(base_path);
  if (dir == NULL) {
    printf("Error opening directory %s\n", base_path);
    return;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

    if (is_dir(path)) {
      search_dir_recursively(pattern, path, result_handler, current_depth + 1, max_depth);
    } else if (is_file(path)) {
      handle_search_file(pattern, path, result_handler);
    }
  }
  closedir(dir);
}

void search(char *pattern, char *path, ResultHandler result_handler) {
  const int MAX_DEPTH = 1000;

  if (is_dir(path)) {
    search_dir_recursively(pattern, path, result_handler, 0, MAX_DEPTH);
  } else if (is_file(path)) {
    handle_search_file(pattern, path, result_handler);
  }
}
