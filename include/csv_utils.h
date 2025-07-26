#ifndef CSV_UTILS_H
#define CSV_UTILS_H

int csv_count_quotes(const char *str);

void csv_str_escape(const char *str, char *out_str);

int needs_quotes(const char *str);

#endif
