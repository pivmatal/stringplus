#include "s21_string.h"

// 15 вычисляет длину строки (не включая 0)
s21_size_t s21_strlen(const char *str) {
  int i = 0;
  while (str[i] != '\0' && str[i] != '\n') {
    i++;
  }
  return i;
}
