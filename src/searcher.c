#include "searcher.h"
#include "file_utils.h"
#include "search_result.h"
#include "exit_status.h"
#include <dirent.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE (300 * sizeof(char))

ExitStatus search_file(SearchResult *sr, const char *pattern,
                         const char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file %s\n", path);
    return FILE_READ_ERR;
  }

  char line[300]; // TODO: make dynamic

  int line_num = 1;
  while (fgets(line, sizeof(line), file) != NULL) {
    regex_t regex_buffer;

    // TODO: use extended regex
    // TODO: use regerror
    if ((regcomp(&regex_buffer, pattern, 0)) != 0) {
      fprintf(stderr, "Regex compilation failed\n");
      return REGEX_COMPILATION_ERR;
    }

    regmatch_t pmatch;

    if ((regexec(&regex_buffer, line, 1, &pmatch, 0)) == 0) {
      const MatchedLine matched_line =
          create_matched_line(line, pmatch.rm_so, pmatch.rm_eo, line_num);
      add_to_search_result(sr, matched_line);
    }
    line_num++;
  }
  return SEARCH_SUCCESS;
}

ExitStatus handle_search_file(const char *pattern, const char *path, const OutputHandler output_handler) {
  SearchResult sr = create_search_result(10, path);

  const ExitStatus status = search_file(&sr, pattern, path);

  if (sr.count > 0)
    output_handler.handler(sr, output_handler.output_filepath);

  free_search_result(&sr);
  return status;
}

ExitStatus search_dir_recursively(const char *pattern, const char *base_path,
                                    const OutputHandler output_handler,
                                    const int current_depth, const int max_depth) {
  if (current_depth > max_depth) {
    fprintf(stderr,
            "Reached max directory depth\n"); // TODO: flag for user to set this
    return MAX_DIR_DEPTH_ERR;
  }

  DIR *dir = opendir(base_path);
  if (dir == NULL) {
    fprintf(stderr, "Error opening directory %s\n", base_path);
    return FILE_READ_ERR;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    // TODO: exclude .gitignore files / dirs, binaries etc
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

    if (is_dir(path)) {
      // TODO: avoid recursion
      search_dir_recursively(pattern, path, output_handler,
                             current_depth + 1, max_depth);
    } else if (is_file(path)) {
      handle_search_file(pattern, path, output_handler);
    }
  }
  closedir(dir);
  return SEARCH_SUCCESS;
}

ExitStatus search(const char *pattern, const char *path, const OutputHandler output_handler) {
  // TODO: user flag to override this
  const int MAX_DEPTH = 1000;

  if (is_dir(path)) {
    return search_dir_recursively(pattern, path, output_handler, 0, MAX_DEPTH);
  } else if (is_file(path)) {
    return handle_search_file(pattern, path, output_handler);
  }

  return SEARCH_SUCCESS;
}
