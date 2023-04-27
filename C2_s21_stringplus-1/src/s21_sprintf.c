#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  int n = 0;
  opt options = {0};
  va_list list;
  va_start(list, format);
  options.lenght_format = s21_strlen(format);
  s21_options(str, &n, format, options, list);
  va_end(list);
  return n;
}

void s21_options(char *str, int *n, const char *format, opt options,
                 va_list list) {
  for (int i = 0; i < options.lenght_format; i++) {
    if (format[i] == '%') {
      options.accuracy = 0;
      options.accuracy_lenght = 0;
      options.lenght_h = 0;
      options.lenght_l = 0;
      options.minus = 0;
      options.plus = 0;
      options.space = 0;
      options.specifier = '\0';
      options.width = 0;
      options.zero = 0;
      int flag = 1;
      while (flag) {
        i++;
        if (format[i] == '+') {
          options.plus = 1;
        } else if (format[i] == '-') {
          options.minus = 1;
        } else if (format[i] == '0' && format[i - 1] != '-') {
          options.zero = 1;
        } else if (format[i] == ' ') {
          options.space = 1;
        } else if (format[i] == '.') {
          i++;
          options.accuracy = 1;
          options.accuracy_lenght = s21_from_string_to_number(format, &i);
        } else if (format[i] == 'h') {
          options.lenght_h = 1;
        } else if (format[i] == 'l') {
          options.lenght_l = 1;
        } else {
          if (format[i] >= '0' && format[i] <= '9') {
            options.width = s21_from_string_to_number(format, &i);
          } else {
            flag = 0;
          }
        }
      }
      options.specifier = format[i];
      s21_flag_hand(str, n, options, list);
    } else {
      str[*n] = format[i];
      (*n)++;
    }
  }
  str[*n] = '\0';
}

void s21_flag_hand(char *str, int *n, opt options, va_list list) {
  if (options.specifier == 'c') {
    s21_c_spec(str, n, options, list);
  } else if (options.specifier == 'd') {
    s21_d_spec(str, n, options, list);
  } else if (options.specifier == 'i') {
    s21_i_spec(str, n, options, list);
  } else if (options.specifier == 'f') {
    s21_f_spec(str, n, options, list);
  } else if (options.specifier == 's') {
    s21_s_spec(str, n, options, list);
  } else if (options.specifier == 'u') {
    s21_u_spec(str, n, options, list);
  } else if (options.specifier == '%') {
    s21_persent_spec(str, n, options);
  }
}

void s21_c_spec(char *str, int *n, opt options, va_list list) {
  if (options.lenght_l == 1) {
    int sd = 0;
    wchar_t w_char = va_arg(list, wchar_t);
    if (options.minus == 0 && options.width != 0) {
      for (int i; i < options.width; i++) {
        str[*n + i] = ' ';
        sd = i;
      }
      wcstombs(str + *n + sd, &w_char, BUFF_SIZE);

    } else if (options.width != 0) {
      wcstombs(str, &w_char, BUFF_SIZE);
      for (int i = s21_strlen(str); i < options.width; i++) {
        str[*n + i] = ' ';
        sd = i;
      }
    } else {
      wcstombs(str, &w_char, BUFF_SIZE);
    }
    *n = *n + sd + 1;
  } else {
    if (options.minus == 0 && options.width != 0) {
      s21_write_space(str, n, 1, options);
    }
    char arg_char = va_arg(list, int);
    str[*n] = arg_char;
    (*n)++;
    if (options.minus == 1 && options.width != 0) {
      s21_write_space(str, n, 1, options);
    }
    options.width = 0;
  }
}

void s21_d_spec(char *str, int *n, opt options, va_list list) {
  long long val = va_arg(list, long long int);
  if (options.lenght_l == 1) {
    val = (long int)val;
    s21_from_number_to_string(str, n, val, 10, options);
  } else if (options.lenght_h == 1) {
    val = (short)val;
    s21_from_number_to_string(str, n, val, 10, options);
  } else {
    val = (int)val;
    s21_from_number_to_string(str, n, val, 10, options);
  }
}

void s21_i_spec(char *str, int *n, opt options, va_list list) {
  if (options.lenght_l == 1) {
    long long int val = (long long int)va_arg(list, long int);
    s21_from_number_to_string(str, n, val, 10, options);
  } else if (options.lenght_h == 1) {
    long long int val = (long long int)(short int)va_arg(list, int);
    s21_from_number_to_string(str, n, val, 10, options);
  } else {
    long long int val = va_arg(list, int);
    s21_from_number_to_string(str, n, val, 10, options);
  }
}

void s21_f_spec(char *str, int *n, opt options, va_list list) {
  double val = va_arg(list, double);
  double temp = val;
  int len = s21_len_of_arg((int)round(val));
  if (temp < 0) {
    temp = -temp;
  }
  int len_int = s21_len_of_arg((int)val);

  if (!options.accuracy) {
    options.accuracy_lenght = 6;
  }
  int full_len;

  if (options.accuracy == 1 && options.accuracy_lenght == 0) {
    if (len > len_int) {
      len_int = len;
      full_len = len_int;
    }
  } else {
    full_len = len_int + 1 + options.accuracy_lenght;
  }
  char before_dot[BUFF_SIZE] = {'\0'};
  char after_dot[BUFF_SIZE] = {'\0'};
  int sign_len = s21_count_len(options, (int)val);

  if (options.minus == 1) {
    if (signbit(val)) {
      str[*n] = '-';
      (*n)++;
    }
    s21_write_float(str, n, options, val);
    s21_write_fl(str, n, before_dot, after_dot, options, temp);
    s21_write_space(str, n, full_len + sign_len, options);
  } else {
    s21_write_space(str, n, full_len + sign_len, options);
    if (signbit(val)) {
      str[*n] = '-';
      (*n)++;
    }
    s21_write_float(str, n, options, val);
    s21_write_fl(str, n, before_dot, after_dot, options, temp);
  }
}

void s21_s_spec(char *str, int *n, opt options, va_list list) {
  if (options.lenght_l == 1) {
    wchar_t *w_sl = va_arg(list, wchar_t *);
    char temp[BUFF_SIZE] = {'\0'};
    wcstombs(temp, w_sl, BUFF_SIZE);
    int len = s21_strlen(temp);
    if (options.accuracy_lenght != 0) {
      if (len > options.accuracy_lenght) {
        len = options.accuracy_lenght;
      }
    }

    if (options.minus == 1) {
      for (int i = 0; i < len; i++) {
        str[*n] = temp[i];
        (*n)++;
      }
      s21_write_space(str, n, len, options);
      str[*n] = '\0';
    } else {
      s21_write_space(str, n, len, options);
      for (int i = 0; i < len; i++) {
        str[*n] = temp[i];
        (*n)++;
      }
      str[*n] = '\0';
    }

  } else {
    char *w_s = va_arg(list, char *);
    if (w_s == s21_NULL) {
      w_s = "(null)";
    }
    int lenght = s21_strlen(w_s);
    if (options.accuracy_lenght != 0) {
      if (lenght > options.accuracy_lenght) {
        lenght = options.accuracy_lenght;
      }
    }

    if (options.minus == 1) {
      for (int i = 0; i < lenght; i++) {
        str[*n] = w_s[i];
        (*n)++;
      }
      s21_write_space(str, n, lenght, options);
    } else {
      s21_write_space(str, n, lenght, options);
      for (int i = 0; i < lenght; i++) {
        str[*n] = w_s[i];
        (*n)++;
      }
    }
  }
}

void s21_u_spec(char *str, int *n, opt options, va_list list) {
  unsigned long long val = va_arg(list, unsigned long long);
  if (options.lenght_l == 1) {
    val = (unsigned long int)val;
    s21_from_number_to_string(str, n, val, 10, options);
  } else if (options.lenght_h == 1) {
    val = (unsigned short)val;
    s21_from_number_to_string(str, n, val, 10, options);
  } else {
    val = (unsigned int)val;
    s21_from_number_to_string(str, n, val, 10, options);
  }
}

void s21_accuracy_format(char *str, opt options) {
  char temp[BUFF_SIZE] = {'\0'};
  int s = 0;
  int len = s21_strlen(str);
  if (str[0] == '-') {
    s = 1;
    temp[0] = '-';
    len--;
  }

  if (options.accuracy_lenght > len) {
    int index;
    for (index = s; index < options.accuracy_lenght - len + s; index++) {
      temp[index] = '0';
    }
    for (int i = s; str[i]; i++, index++) {
      temp[index] = str[i];
    }
    s21_strcpy(str, temp);
  }
}

void s21_work_with_flags(char *str, opt options) {
  char temp[BUFF_SIZE + 1] = {'\0'};
  if (options.plus == 1 && options.specifier != 'u') {  // знаки + или -
    if (str[0] == '-') {
      temp[0] = str[0];
    } else {
      temp[0] = '+';
    }
    if (str[0] == '-') {
      s21_strcpy(temp + 1, str + 1);
    } else {
      s21_strcpy(temp + 1, str);
    }
    s21_strcpy(str, temp);

  } else if (options.space && str[0] != '-' && options.specifier != 'u') {
    temp[0] = ' ';
    s21_strcpy(temp + 1, str);
    s21_strcpy(str, temp);
  }

  if (options.width > (int)s21_strlen(str)) {  // здесь ставятся нули и пробелы
    int size = options.width - s21_strlen(str);
    if (options.minus == 0) {
      if (options.zero == 1 && options.accuracy != 1) {
        s21_memset(temp, '0', size);
      } else {
        s21_memset(temp, ' ', size);
      }
      s21_strcpy(temp + size, str);

    } else {
      s21_strcpy(temp, str);
      s21_memset(temp + s21_strlen(temp), ' ', size);
    }
    s21_strcpy(str, temp);
  }
}

void s21_write_space(char *str, int *n, int length, opt options) {
  for (int i = 0; i < (options.width - length); i++) {
    str[*n] = ' ';
    (*n)++;
  }
}

// переводит строку в число и проверяет Точность
void s21_from_number_to_string(char *str, int *n, int64_t value, int base,
                               opt options) {
  char temp[BUFF_SIZE] = {'\0'};
  char temp2[BUFF_SIZE] = {'\0'};
  int index = BUFF_SIZE - 2;
  int neg = 0;
  int temp_ind;
  if (value < 0) {
    value = -value;
    neg = 1;
  }

  if (value == 0) {
    temp[index] = '0';
  }

  while (value > 0) {
    index--;
    temp[index] = "0123456789abcdef"[value % base];
    value = value / base;
    temp_ind = index;
  }

  for (int i = 0; temp[index]; index++, i++) {
    if (index == temp_ind && neg == 1) {
      temp2[i] = '-';
      i++;
    }
    temp2[i] = temp[index];
  }

  if (options.accuracy) {  // добавляет нули если нужно
    s21_accuracy_format(temp2, options);
  }

  s21_work_with_flags(temp2, options);
  int j = 0, len = s21_strlen(temp2);

  while (j < len) {
    str[*n] = temp2[j];
    j++;
    (*n)++;
  }
}

// перевод строки в число
int s21_from_string_to_number(const char *format, int *i) {
  int lenght = 0;

  for (int y = 0; format[*i] >= 48 && format[*i] <= 57; y++) {
    lenght = (lenght * 10) + format[*i] - 48;
    (*i)++;
  }
  (*i)--;
  return lenght;
}

int s21_len_of_arg(long long num) {
  int len = 1;
  if (num < 0) {
    num = -num;
  }
  while (num > 9) {
    len++;
    num = num / 10;
  }
  return len;
}

int s21_count_len(opt options, long long arg) {
  int sign_len = 0;
  if ((options.space == 1 && arg >= 0) || (options.plus == 1 && arg >= 0) ||
      arg < 0) {
    if (options.width != 0) {
      sign_len = 1;
    }
  }
  return sign_len;
}

void s21_write_float(char *str, int *n, opt options, long double arg) {
  if (options.plus == 1 && !signbit(arg)) {
    str[*n] = '+';
    (*n)++;
  }
}

void s21_write_fl(char *str, int *n, char *bef_dot, char *aft_dot, opt options,
                  double arg) {
  if (options.accuracy_lenght != 0) {
    arg = s21_round_arg(options, arg);
    double num_bef_dot = 0.0;
    long double num_aft_dot = 0.0;
    double num_c = 0.0;
    num_aft_dot = modf(arg, &num_bef_dot);
    s21_number_of_int(bef_dot, num_bef_dot);
    int l = s21_strlen(bef_dot) - 1;
    while (l >= 0) {
      str[*n] = bef_dot[l--];
      (*n)++;
    }
    str[*n] = '.';
    (*n)++;
    for (int i = 0; i < options.accuracy_lenght; i++) {
      num_aft_dot =
          (num_aft_dot * 10.) + (5 * pow(10, -options.accuracy_lenght));
      modf(num_aft_dot, &num_c);
      if (i > 20) {
        num_aft_dot = num_aft_dot + (0 * pow(10, -i));
      }
      if (i == options.accuracy_lenght - 1) {
        num_c = round(num_c);
        aft_dot[i] = num_c + '0';
      } else {
        aft_dot[i] = num_c + '0';
        num_aft_dot = num_aft_dot - num_c;
      }
    }
    for (int i = 0; i < options.accuracy_lenght; i++) {
      str[*n] = aft_dot[i];
      (*n)++;
    }
  } else {
    arg = round(arg);
    s21_number_of_int(bef_dot, (long long)arg);
    int y = s21_strlen(bef_dot) - 1;
    while (y >= 0) {
      str[*n] = bef_dot[y];
      y--;
      (*n)++;
    }
  }
}

void s21_number_of_int(char *mem_str, long long arg) {
  int i = 0;
  if (arg == LONG_MIN) {
    arg = 922337203685477580;
    mem_str[i] = '8';
    i++;
  }
  while (arg > 9) {
    mem_str[i] = (arg % 10) + 48;
    arg = arg / 10;
    i++;
  }
  mem_str[i] = (arg % 10) + 48;
}

double s21_round_arg(opt options, double num) {
  double all;
  double m = modf(num, &all) * pow(10.0, options.accuracy_lenght);
  double mod = fmod(m, pow(10.0, options.accuracy_lenght));
  if (mod == 50) {
    m = round(m + 1) / pow(10.0, options.accuracy_lenght);
  } else {
    m = round(m) / pow(10.0, options.accuracy_lenght);
  }
  num = all + m;
  return num;
}

void s21_persent_spec(char *str, int *n, opt options) {
  if (options.minus == 1) {
    str[*n] = '%';
    (*n)++;
    s21_write_space(str, n, 1, options);
  } else {
    s21_write_space(str, n, 1, options);
    str[*n] = '%';
    (*n)++;
  }
}
