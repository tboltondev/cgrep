#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/syslimits.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"

#define MAX_LINE_SIZE 300 * sizeof(char)

char **search_file(const char searchterm[], char filename[]) {
  char **found_lines;
  found_lines = (char**)calloc(1000, MAX_LINE_SIZE); // TODO: don't allocate unless anything is found

  FILE *file = fopen(filename, "r");
  char line[255];

  assert(file != NULL);

  int line_num = 1;
  int found_lines_index = 0;
  while (fgets(line, sizeof(line), file) != NULL) {

    // TODO: handle multiple matches in same line
    char *pfound = strstr(line, searchterm); // pointer to first character of first match in line
    
    if (pfound != NULL) {

      int found_position = pfound - line;
      int match_length = strlen(searchterm);
      int line_length = strlen(line);

      if (found_lines == NULL) {
        printf("Memory not allocated.\n");
      } else {
        char found_line[MAX_LINE_SIZE];
        int buffer_size = sizeof(found_line);
        int offset = 0;

        offset += snprintf(found_line + offset, buffer_size - offset, ANSI_COLOR_GREEN);
        offset += snprintf(found_line + offset, buffer_size - offset, "%i:", line_num);
        offset += snprintf(found_line + offset, buffer_size - offset, ANSI_COLOR_RESET);
        offset += snprintf(found_line + offset, buffer_size - offset, "%.*s", found_position, line); // part of line before first match
        offset += snprintf(found_line + offset, buffer_size - offset, ANSI_COLOR_RED);
        offset += snprintf(found_line + offset, buffer_size - offset, "%.*s", match_length, &line[found_position]); // first match
        offset += snprintf(found_line + offset, buffer_size - offset, ANSI_COLOR_RESET);
        offset += snprintf(found_line + offset, buffer_size - offset, "%s", &line[found_position + match_length]); // remainder of line

        found_lines[found_lines_index] = strdup(found_line);
        found_lines_index++;
      }
    }
    line_num++;
  }
  found_lines[found_lines_index] = NULL;
  return found_lines;
}

int is_dir(const char *path) {
  struct stat statbuf;
  if (stat(path, &statbuf) != 0) {
    perror("stat failed");
    return 0;
  }
  return S_ISDIR(statbuf.st_mode);
}

int is_file(const char *path) {
  struct stat statbuf;
  if (stat(path, &statbuf) != 0)
    return 0;
  return S_ISREG(statbuf.st_mode);
}

void print_results(char **lines, char *path) {
      if (lines[0] != NULL)
        printf(ANSI_COLOR_MAGENTA "\n%s\n" ANSI_COLOR_RESET, path);

      int i = 0;
      while (lines[i] != NULL) {
        printf("%s", lines[i]);
        i++;
      }
      free(lines);
}

void search_subdirs(const char *pattern, const char *base_path, int current_depth, int max_depth) {
  if (current_depth > max_depth)
    return;

  DIR *dir = opendir(base_path);
  if (dir == NULL) {
    perror("opendir");
    return;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);

    if (is_dir(path)) {
      search_subdirs(pattern, path, current_depth + 1, max_depth);
    } else if (is_file(path)) {
      char **found_lines = search_file(pattern, path);
      print_results(found_lines, path);
    }
  }

  closedir(dir);
}

int main(int argc, char *argv[]) {
  char *pattern = argv[1];
  if (pattern == NULL)
    printf("No pattern provided\n");

  char *path = argv[2] == NULL ? "." : argv[2];

  const int MAX_DEPTH = 100;

  if (is_dir(path)) {
    search_subdirs(pattern, path, 0, MAX_DEPTH);
  } else if (is_file(path)) {
    char **lines = search_file(pattern, path);
    print_results(lines, path);
  }
}
