#ifndef CSV_UTILS_H
#define CSV_UTILS_H

int csv_count_quotes(char *str);

void csv_str_escape(char *str, char *out_str);

int needs_quotes(const char *str);

#endif
