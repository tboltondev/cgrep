#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include "search_result.h"

// Todo: find a way to avoid pointless 2nd arg or stdout handlers

void to_stdout(SearchResult sr, const char *output_filepath);

void json_to_stdout(SearchResult sr, const char *output_filepath);

void to_file(SearchResult sr, const char *out_file);

void json_to_file(SearchResult sr, const char *out_file);

void csv_to_stdout(SearchResult sr, const char *output_filepath);

void csv_to_file(SearchResult sr, const char *out_file);

#endif
