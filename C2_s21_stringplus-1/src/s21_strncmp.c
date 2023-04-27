#include "s21_string.h"

// 10 Сравнивает не более первых n байтов str1 и str2.

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  for (s21_size_t i = 0; i < n && res == 0 && (*str1 != '\0' || *str2 != '\0');
       i++, str1++, str2++)
    res = (int)*str1 - (int)*str2;
  return res;
}
