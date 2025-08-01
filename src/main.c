#include "arg_parser.h"
#include "output_handler.h"
#include "searcher.h"
#include <stdio.h>

int main(const int argc, char *argv[]) {
  Args args = {0};
  if (!parse_args(argc, argv, &args))
    return ARG_PARSE_ERR;

  OutputHandler output_handler = {0};
  if (!assign_oh(args, &output_handler))
    fprintf(stderr, "Error assigning output handler.\n"); // Todo: should be debug only

   return search(args.pattern, args.path, output_handler);
}
