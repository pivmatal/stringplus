#include "s21_string.h"

// 8 Ищет первое вхождение символа
// c (unsigned char) в строке, на которую указывает аргумент str.

char *s21_strchr(const char *str, int c) {
  for (; *str != '\0' && *str != c; ++str) {
  }
  return *str == c ? (char *)str : s21_NULL;
}
