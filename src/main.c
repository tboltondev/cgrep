#include "../include/output_handler.h" // TODO: find out why absolute includes are not working
#include "../include/searcher.h"
#include "../include/arg_parser.h"

int main(int argc, char *argv[]) {
  Args args = {0};
  if (!parse_args(argc, argv, &args))
     return 1;

  ResultHandler result_handler = args.json ? json_stdout : to_stdout;
  search(args.pattern, args.path, result_handler);
}
