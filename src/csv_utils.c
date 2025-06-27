#include <string.h>

int csv_count_quotes(char *str) {
  int escape_chars_count = 0;
  for (int i = 0; i < strlen(str); ++i) {
    switch (str[i]) {
    case '"':
      escape_chars_count++;
      break;
    }
  }
  return escape_chars_count;
}

// TODO: add bounds check
void csv_str_escape(char *str, char *out_str) {
  int k = 0;
  for (int j = 0; j < strlen(str); ++j) {
    switch (str[j]) {
    case '\"':
      out_str[k++] = '\"';
      out_str[k++] = '\"';
      break;
    default:
      out_str[k++] = str[j];
      break;
    }
  }

  out_str[k] = '\0';
}

int needs_quotes(const char *str) {
  for (int i = 0; i < strlen(str); ++i) {
    if (',' == str[i] || '"' == str[i])
      return 1;
  }
  return 0;
}
