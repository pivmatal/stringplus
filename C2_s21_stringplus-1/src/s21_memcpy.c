#include "s21_string.h"

// 3 Копирует n символов из src в dest.
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *temp_dest = (char *)dest;
  const char *temp_src = (char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    temp_dest[i] = temp_src[i];
  }
  return temp_dest;
}
