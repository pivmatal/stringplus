#include "s21_string.h"

// 4 Еще одна функция для копирования n символов из src в dest.
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *temp_dest = (char *)dest;
  const char *temp_src = (char *)src;
  char *temp = (char *)malloc(sizeof(char) * n);

  if (temp) {
    s21_memcpy(temp, temp_src, n);
    s21_memcpy(temp_dest, temp, n);
    free(temp);
  }
  return temp_dest;
}
