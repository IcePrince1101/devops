#include "flags.h"

int flag_realisation(flags *flag, char *pattern, char *string,
                     int *count_match) {
  int exit_code = 0;
  regex_t regex;
  pattern_generation(flag, pattern, &regex);
  // Если нашли совпадение (и нет флагов -c и -l), вовращаем 1
  if (output_strings(flag, string, count_match, regex) != 0) {
    exit_code = 1;
  }
  regfree(&regex);
  return exit_code;
}

// Формирование паттерна
void pattern_generation(flags *flag, char *pattern, regex_t *regex) {
  if (flag->i == 1) {
    regcomp(regex, pattern, REG_ICASE);
  } else if (flag->e == 1) {
    regcomp(regex, pattern, 0);
  }
}

// Функция заглушка - не позволит вывести строки при активных флагах -c и -o
int output_strings(flags *flag, char *string, int *count_match, regex_t regex) {
  int output_code = pattern_search(
      flag, string, &regex, count_match);  // Определяет, что будет выводится -
                                           // соответствие или несоответствие
  return output_code;
}

// Вывод общей информации (если есть флаги -c и -l)
void output_info(flags *flag, int count_match, char *name, int count_files,
                 int str_number) {
  if (flag->l == 1 && flag->c == 1) {
    printf("1\n");
    printf("%s\n", name);
  } else {
    if (flag->c == 1) {
      check_n_and_files(count_files, name, &str_number, flag);
      printf("%d\n", count_match);
    }
    if (flag->l == 1) {
      printf("%s\n", name);
    }
  }
}

// Поиск по паттернам (возвращает 1, если нашел)
int pattern_search(flags *flag, char *string, regex_t *regex,
                   int *count_match) {
  regmatch_t pmatch[1];
  // Вывод только несоответствий
  if (flag->v == 1) {
    if (regexec(regex, string, 1, pmatch, 0) != 0) {
      (*count_match)++;
      return 1;
    }
  } else if (flag->e == 1 || flag->f == 1 || flag->o == 1) {
    if (regexec(regex, string, 1, pmatch, 0) == 0) {
      (*count_match)++;
      return 1;
    }
  }
  return 0;
}

// Проверка на флаг -n и наличие более 1 файла
void check_n_and_files(int count_files, char *name, int *str_number,
                       flags *flag) {
  if (count_files > 1 && flag->h != 1) {
    printf("%s:", name);
  }
  if (flag->n == 1 && flag->c != 1 && flag->l != 1) {
    printf("%d:", *str_number);
  }
}

// Функция добавления переноса строки в конец строки
void add_end(char *str) {
  if (str[strlen(str) - 1] != '\n') {
    strcat(str, "\n");
  }
}

void flag_o(char *str, char *pattern) {
  char *result = strstr(str, pattern);
  while (result != NULL) {
    for (int c = 0; c < (int)strlen(pattern); c++) {
      printf("%c", result[c]);
    }
    printf("\n");
    result += strlen(pattern);
    result = strstr(result, pattern);
  }
}