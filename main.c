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

void search_file(const char searchterm[], char filename[]) {
  FILE *file = fopen(filename, "r");
  char line[255];

  assert(file != NULL);

  int line_num = 1;
  while (fgets(line, sizeof(line), file) != NULL) {

    // TODO: handle multiple matches in same line
    char *pfound = strstr(line, searchterm); // pointer to first character of first match in line
    
    if (pfound != NULL) {
      int found_position = pfound - line;
      int match_length = strlen(searchterm);
      int line_length = strlen(line);

      printf(ANSI_COLOR_GREEN);
      printf("%i:", line_num);
      printf(ANSI_COLOR_RESET);
      printf("%.*s", found_position, line); // print line up to first match
      printf(ANSI_COLOR_RED);
      printf("%.*s", match_length, &line[found_position]); // print match
      printf(ANSI_COLOR_RESET);
      printf("%s", &line[found_position + match_length]); // print remainder of line
    }
    line_num++;
  }
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
      printf(ANSI_COLOR_MAGENTA "\n%s\n" ANSI_COLOR_RESET, path); // TODO: prints for files with no match
      search_file(pattern, path);
    }
  }

  closedir(dir);
}
int main(int argc, char *argv[]) {
  char *pattern = argv[1];
  char *path = argv[2] == NULL ? "." : argv[2];

  const int MAX_DEPTH = 100;

  if (pattern) { // TODO: change to return early
    search_subdirs(pattern, path, 0, MAX_DEPTH);
  }
}
