#include "s21_string.h"

// 5 Копирует символ c (беззнаковый char)
// в первые n символов строки, на которую указывает аргумент str.
void *s21_memset(void *str, int c, s21_size_t n) {
  char *temp_str = (char *)str;

  for (s21_size_t i = 0; i < n; i++) {
    temp_str[i] = c;
  }
  return temp_str;
}
