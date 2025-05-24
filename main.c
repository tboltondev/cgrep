#include "searcher.h"
#include <stdio.h>

void placeholder_handler() {};

int main(int argc, char *argv[]) {
  // TODO: arg parser
  char *pattern = argv[1];
  if (pattern == NULL)
    printf("No pattern provided\n");

  char *path = argv[2] == NULL ? "." : argv[2];

  search(pattern, path, placeholder_handler);
}
