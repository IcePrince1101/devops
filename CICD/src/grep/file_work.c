#include "file_work.h"

// Функция открытия файла и вывода содержимого на экран
int file_format(char *name, flags *flag, char **patterns, int count_patterns,
                int count_files) {
  int str_number = 0;   // номер строки
  int count_match = 0;  // счетчик совпадений для файла
  FILE *f =
      fopen(name, "r");  // Открытие файла для посимвольного прохода по нему (и
                         // подсчета кол-ва символов в каждой строке)

  if (f != NULL) {  // Проверка на отсутствие файла в директории
    file_working(f, name, flag, str_number, patterns, count_patterns,
                 count_files, &count_match);
    fclose(f);

  } else if (flag->s != 1) {
    printf("Error! File not found.");
    return 1;
  }
  output_info(flag, count_match, name, count_files, str_number);
  return 0;
}

void file_working(FILE *f, char *name, flags *flag, int str_number,
                  char **patterns, int count_patterns, int count_files,
                  int *count_match) {
  char c = fgetc(f);  // Считывание первого символа
  int count = 0;  // Счетчик кол-ва символов в строке
  FILE *output_f =
      fopen(name, "r");  // Открываем файл для извлечения из него строк

  while (c != EOF) {
    count++;
    if (c == '\n') {  // Выделение строки и работа с ней при условии получения
                      // символа конца строки
      string_working(output_f, count, flag, &str_number, patterns,
                     count_patterns, name, count_files, count_match);
      count = 0;
    }
    c = fgetc(f);
  }
  // Строку перед концом файла обрабатываем отдельно
  if (count > 0) {
    string_working(output_f, count + 1, flag, &str_number, patterns,
                   count_patterns, name, count_files, count_match);
  }
  fclose(output_f);
}

// Функция получения строк и их обработки
void string_working(FILE *f, int count, flags *flag, int *str_number,
                    char **patterns, int count_patterns, char *name,
                    int count_files, int *count_match) {
  char *str = calloc(count + 20, sizeof(char));
  fgets(str, ++count, f);
  (*str_number)++;
  int flag_output = 0;
  int flag_output_v = 0;
  // Сюда регулярные выражения и обработка строк в соответствии с флагами
  for (int i = 0; i < count_patterns; i++) {
    if (flag_realisation(flag, patterns[i], str, count_match) == 1) {
      if (flag->v == 1) {
        flag_output_v++;
      } else {
        flag_output = 1;
      }
      if (flag->c == 0 && flag->l == 0 && flag->o == 1) {
        flag_o(str, patterns[i]);
        break;
      }
    }
  }
  if (flag->c == 0 && flag->l == 0 && flag->o == 0 &&
      (flag_output == 1 || flag_output_v == count_patterns)) {
    check_n_and_files(count_files, name, str_number, flag);
    printf("%s", str);
  }
  // Oчистка памяти
  free(str);
}