#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include "arg_parser.h"
#include "search_result.h"

typedef struct {
  const char *output_filepath;
  void (*handler)(SearchResult, const char*);
} OutputHandler;

int assign_oh(Args args, OutputHandler *oh);

#endif
