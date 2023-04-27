#include "s21_string.h"

// Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src). В
// случае какой-либо ошибки следует вернуть значение NULL
void *s21_trim(const char *src, const char *trim_chars) {
  char *temp_str = s21_NULL;

  if (src != s21_NULL) {
    if (trim_chars && *trim_chars) {
      s21_size_t len = s21_strlen(src);
      s21_size_t len_ch = s21_strlen(trim_chars);
      s21_start_trim(&src, trim_chars, &len, len_ch);

      if (len) {
        s21_end_trim(&src, trim_chars, &len, len_ch);
        temp_str = (char *)malloc((len + 1) * sizeof(char));
      }

      if (temp_str != s21_NULL) {
        for (s21_size_t i = 0; i < len + 1; i++) {
          if (i < len) {
            temp_str[i] = src[i];
          } else {
            temp_str[i] = '\0';
          }
        }
      }
    } else {
      temp_str = s21_trim(src, " \t\n");
    }
  }
  return temp_str;
}

void s21_start_trim(const char **src, const char *trim_chars,
                    s21_size_t *len_src, const s21_size_t trim_len_ch) {
  s21_size_t x = 0;

  while (src && x != trim_len_ch) {
    if ((**src) == trim_chars[x]) {
      (*src)++;
      (*len_src) -= 1;
      x = 0;
      break;
    }
    x++;
  }
}

void s21_end_trim(const char **src, const char *trim_chars, s21_size_t *len_src,
                  const s21_size_t trim_len_ch) {
  s21_size_t x = 0;
  s21_size_t y = (*len_src) - 1;

  while (src && x != trim_len_ch) {
    if ((*src)[y] == trim_chars[x]) {
      y--;
      (*len_src)--;
      x = 0;
      break;
    }
    x++;
  }
}
