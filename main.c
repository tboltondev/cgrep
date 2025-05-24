#include "search_result.h"
#include "searcher.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  // TODO: arg parser
  char *pattern = argv[1];
  if (pattern == NULL)
    printf("No pattern provided\n");

  char *path = argv[2] == NULL ? "." : argv[2];

  search(pattern, path, print_search_result);
}
