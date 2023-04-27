#include "s21_string.h"

// 2 Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  s21_size_t temp = 0;
  const char *temp_str1 = str1;
  const char *temp_str2 = str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (temp_str1[i] != temp_str2[i]) {
      temp = (int)temp_str1[i] - (int)temp_str2[i];
      i = n - 1;
    }
  }
  return temp;
}
