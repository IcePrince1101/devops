#include "flags.h"

// Функция обработки строки без флагов
void no_flag(flags *flag, char *final_str) {
  if (flag->e == 0 && flag->s == 0 && flag->t == 0) {
    add_end(final_str);
  }
}

// Функция обработки флага е
void flag_e(flags *flag, char *final_str, char *str, char enter) {
  if (flag->e == 1) {
    if (enter == '\n') {  // Выполняем условие для исключения - конца файла
      strcat(final_str, "$");
    } else {
      strcpy(final_str, str);
    }

    // add_end(final_str);
  }
}

// Функция обработки флага s
int flag_s(flags *flag, char *final_str, int *count_void_string) {
  int string_length = strlen(final_str);
  if (flag->s == 1) {
    if (string_length == flag->e) {
      (*count_void_string)++;
    } else {
      *count_void_string = 0;
      // add_end(final_str);
    }

    if (*count_void_string > 1) {
      strcpy(final_str, "");
      return 1;
    }
  }
  return 0;
}

// функция обработки флага t
void flag_t(flags *flag, char *final_str) {
  if (flag->t == 1) {
    int i = 0;

    while (final_str[i] != '\0') {
      if (final_str[i] == '\t') {
        int j = strlen(final_str) + 2;  // Вычисляем длину новой строки
        char *work = calloc(j, sizeof(char));
        char *temp_str = calloc(j, sizeof(char));

        strncpy(work, final_str + i + 1, j);  // Копируем остаток строки

        temp_str[0] = '\0';
        strncat(temp_str, final_str, i);  // Копируем символы до табуляции
        strcat(temp_str, "^I");  // Добавляем строку "^I"
        strcat(temp_str, work);  // Добавляем остаток строки

        strcpy(final_str, temp_str);  // Копируем результат обратно в final_str

        free(temp_str);
        free(work);
      }

      i++;
    }

    // add_end(final_str);
  }
}

// Функция вывода в соответствии с флагами b и n
void flag_b_n(flags *flag, char *final_str, int *str_number) {
  if (flag->b == 1) {
    if ((int)strlen(final_str) > flag->e) {
      printf("%6d\t%s", *str_number, final_str);
      (*str_number)++;
    } else {
      printf("%s", final_str);
    }

  } else if (flag->n == 1) {
    printf("%6d\t%s", *str_number, final_str);
    (*str_number)++;

  } else {
    printf("%s", final_str);
  }
}

// Функция реализации флага -v
void flag_v(flags *flag, char *final_str) {
  if (flag->v == 1) {
    for (int i = 0; i < (int)strlen(final_str); i++) {
      // необходимо для обхода ограниченного диапазона значений char
      unsigned char uchar_value = (unsigned char)final_str[i];
      if (uchar_value > 127 && uchar_value < 160) {
        // М- нотация
        notation(final_str, i, 'M');
      } else if (final_str[i] >= 0 && final_str[i] <= 31 &&
                 final_str[i] != '\t' && final_str[i] != '\n') {
        // ^ нотация
        notation(final_str, i, '^');
      }
    }
  }
}

// Функция добавления переноса строки в конец строки
void add_end(char *str) {
  if (str[strlen(str) - 1] != '\n' && str[strlen(str) - 1] != EOF) {
    strcat(str, "\n");
  }
}

void notation(char *str, int place, char note) {
  int j = strlen(str) + 4;  // Вычисляем длину новой строки
  char *work = calloc(j, sizeof(char));
  char *temp_str = calloc(j, sizeof(char));
  strncpy(work, str + place + 1, j);  // Копируем остаток строки

  temp_str[0] = '\0';
  strncat(temp_str, str, place);  // Копируем символы до табуляции
  if (note == 'M') {
    strcat(temp_str, "M-^");  // Добавляем поддержку М- нотации
  } else if (note == '^') {
    strcat(temp_str, "^");  // Добавляем поддержку ^ нотации
  }
  char temp[2];
  if (note == 'M') {
    temp[0] = (char)((int)str[place] - 64);
  } else if (note == '^') {
    temp[0] = (char)((int)str[place] + 64);
  }
  temp[1] = '\0';
  strcat(temp_str, temp);  // вставляем символ
  strcat(temp_str, work);  // Добавляем остаток строки

  strcpy(str, temp_str);  // Копируем результат обратно в final_str

  free(temp_str);
  free(work);
}