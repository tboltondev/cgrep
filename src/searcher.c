#include "../include/searcher.h"
#include "../include/file_utils.h"
#include "../include/search_result.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/syslimits.h>

#define MAX_LINE_SIZE 300 * sizeof(char)

void search_file(SearchResult *sr, const char *pattern, const char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL)
    fprintf(stderr, "Error opening file %s\n", path);

  char line[300]; // Max chars in line, maybe make dynamic

  int line_num = 1;

  while (fgets(line, sizeof(line), file) != NULL) {
    char *match = strstr(line, pattern);

    if (match != NULL) {
      MatchedLine matched_line =
          create_matched_line(line, match, strlen(pattern), line_num);
      add_to_search_result(sr, matched_line);
    }
    line_num++;
  }
}

SearchStatus handle_search_file(const char *pattern, const char *path,
                        ResultHandler result_handler) {
  SearchResult sr = create_search_result(10, path);

  search_file(&sr, pattern, path);

  if (sr.count > 0)
    result_handler(sr);

  free_search_result(&sr);
  return SEARCH_SUCCESS;
}

SearchStatus search_dir_recursively(const char *pattern, const char *base_path,
                            ResultHandler result_handler, int current_depth,
                            int max_depth) {
  if (current_depth > max_depth) {
    fprintf(stderr, "Reached max directory depth\n"); // TODO: flag for user to set this
    return SEARCH_ERR_MAX_DIR_DEPTH;
  }

  DIR *dir = opendir(base_path);
  if (dir == NULL) {
    fprintf(stderr, "Error opening directory %s\n",
           base_path);
    return SEARCH_ERR_FILE_READ;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

    if (is_dir(path)) {
      search_dir_recursively(pattern, path, result_handler, current_depth + 1,
                             max_depth);
    } else if (is_file(path)) {
      handle_search_file(pattern, path, result_handler);
    }
  }
  closedir(dir);
  return SEARCH_SUCCESS;
}

SearchStatus search(const char *pattern, const char *path,
            ResultHandler result_handler) {
  const int MAX_DEPTH = 1000;

  if (is_dir(path)) {
    return search_dir_recursively(pattern, path, result_handler, 0, MAX_DEPTH);
  } else if (is_file(path)) {
    return handle_search_file(pattern, path, result_handler);
  }
  return SEARCH_SUCCESS;
}
