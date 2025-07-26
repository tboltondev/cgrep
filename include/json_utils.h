#ifndef JSON_H
#define JSON_H

int json_count_escape_chars(const char *str);

void json_str_escape(const char *str, char *out_str);

#endif
