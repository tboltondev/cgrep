#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char *get_filename() {
  char *filename = malloc(255);
  if (!filename)
    return NULL;

  printf("File: ");
  scanf("%s", filename);

  return filename;
}

char *get_searchterm() {
  char *searchterm = malloc(100);
  if (!searchterm)
    return NULL;

  printf("Search for: ");
  scanf("%s", searchterm);

  return searchterm;
}

void search_file(char searchterm[], char filename[]) {
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

int main() {
  char *fname = get_filename();
  char *searchterm = get_searchterm();

  if (fname && searchterm) {
    search_file(searchterm, fname);
  }

  free(fname);
  free(searchterm);
}
