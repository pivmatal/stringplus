#include "s21_string.h"

// Возвращает копию строки (str), преобразованной в верхний регистр. В случае
// какой-либо ошибки следует вернуть значение NULL
void *s21_to_upper(const char *str) {
  char *temp_str = s21_NULL;
  if (str) {
    temp_str = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (temp_str != s21_NULL) {
      s21_strcpy(temp_str, str);
      for (int i = 0; temp_str[i] != '\0'; i++) {
        if (temp_str[i] >= 97 && temp_str[i] <= 122) {
          temp_str[i] = temp_str[i] - 32;
        }
      }
    }
  }
  return temp_str;
}
