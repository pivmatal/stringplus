#include "s21_string.h"

// 1 Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *temp = s21_NULL;
  const char *temp_str = str;
  for (s21_size_t i = 0; temp_str[i] && i < n; i++) {
    if (temp_str[i] == c) {
      temp = (char *)&temp_str[i];
      i = n;
    }
  }
  return temp;
}
