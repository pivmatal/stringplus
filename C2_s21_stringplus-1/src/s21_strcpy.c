#include "s21_string.h"

// 11 Копирует строку, на которую указывает src, в dest.

char* s21_strcpy(char* dest, const char* src) {
  if (dest == s21_NULL) {
    return s21_NULL;
  }
  char* ptr = dest;
  while (*src != '\0') {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';
  return ptr;
}
