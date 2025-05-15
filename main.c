#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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

int main(int argc, char *argv[]) {
  char *pattern = argv[1];
  char *file = argv[2];

  if (file && pattern) {
    // TODO: handle directories
    search_file(pattern, file);
  }
}
