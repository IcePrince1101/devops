#include "file_work.h"

// Функция открытия файла и вывода содержимого на экран
void file_format(char *name, flags *flag) {
  FILE *f =
      fopen(name, "r");  // Открытие файла для посимвольного прохода по нему (и
                         // подсчета кол-ва символов в каждой строке)

  if (f != NULL) {  // Проверка на отсутствие файла в директории
    get_string(name, f, flag);
    fclose(f);

  } else {
    printf("Error! File not found.");
  }
}

// Функция получения строк и их обработки
int string_working(FILE *f, int count, flags *flag, int *str_number,
                   int *count_void_string) {
  char *str = calloc(count + 20, sizeof(char));
  char *final_str = calloc(count + 20, sizeof(char));
  char enter;  // Переменная, которая нужна для извлечения переноса строки из
               // файла и прохода на следующую строку
  int exit_code = 0;

  fgets(str, count, f);
  strcpy(final_str, str);
  enter = fgetc(f);

  // Сюда регулярные выражения и обработка строк в соответствии с флагами
  flag_e(flag, final_str, str, enter);
  flag_t(flag, final_str);
  flag_v(flag, final_str);
  if (flag_s(flag, final_str, count_void_string) == 0) {
    flag_b_n(flag, final_str, str_number);
    exit_code = 1;
  }

  // Oчистка памяти
  free(str);
  free(final_str);
  return exit_code;
}

void get_string(char *name, FILE *f, flags *flag) {
  int str_number = 1;
  int count = 0;  // Счетчик кол-ва символов в строке
  char c = fgetc(f);  // Считывание первого символа
  int count_void_string = 0;  // Счетчик пустых строк
  FILE *output_f =
      fopen(name, "r");  // Открываем файл для извлечения из него строк
  while (c != EOF) {
    count++;
    if (c == '\n') {  // Выделение строки и работа с ней при условии получения
                      // символа конца строки
      if (string_working(output_f, count, flag, &str_number,
                         &count_void_string) == 1) {
        printf("\n");
      }
      count = 0;
    }
    c = fgetc(f);
  }
  // Строку перед концом файла обрабатываем отдельно
  if (count > 0) {
    string_working(output_f, count + 1, flag, &str_number, &count_void_string);
  }
  fclose(output_f);
}