#include "file_utils.h"
#include <stdio.h>
#include <sys/stat.h>

int is_dir(const char *path) {
  struct stat statbuf;
  if (stat(path, &statbuf) != 0) {
    printf("stat failed. File: %s\n", path);
    return 0;
  }
  return S_ISDIR(statbuf.st_mode);
}

int is_file(const char *path) {
  struct stat statbuf;
  if (stat(path, &statbuf) != 0) {
    printf("stat failed. File: %s\n", path);
    return 0;
  }
  return S_ISREG(statbuf.st_mode);
}

void remove_newline_chars(char *str) {
  while (*str) {
    if (*str == '\n')
      *str = '\0';
    str++;
  }
}

int truncate_file(const char *path) {
  FILE *fp = fopen(path, "w");
  if (fp == NULL) {
    fprintf(stderr, "Error opening file: %s\n", path);
    return 0;
  }
  fclose(fp);
  return 1;
}
