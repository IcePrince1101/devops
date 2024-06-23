#include "s21_cat.h"

int main(int argc, char **argv) {
  flags flag = {0};

  char *short_flags = "+beEvnstT";
  struct option long_flags[] = {{"number-nonblank", 0, NULL, 'b'},
                                {"number", 0, NULL, 'n'},
                                {"squeeze-blank", 0, NULL, 's'},
                                {"show-nonprinting", 0, NULL, 'v'}};

  int error = 0;  // Переменная для выхода по ошибке
  int work = 0;  // Рабочая переменная для работы функции getopt_long
  int code_result = 0;  // Хранит результат функции getopt_long

  while (code_result != -1 && error == 0) {
    code_result = getopt_long(argc, argv, short_flags, long_flags, &work);
    error = flag_options(code_result, &flag);
  }

  if (error == 1) {
    printf("Error. No such option!");
    return 1;
  }

  get_filenames(argc, argv, &flag);

  return 0;
}

// проверка на флаги
int flag_options(int code_result, flags *flag) {
  switch (code_result) {
    case 'b':
      flag->b = 1;
      return 0;
    case 'e':
      flag->e = 1;
      flag->v = 1;
      return 0;
    case 'E':
      flag->e = 1;
      return 0;
    case 'n':
      flag->n = 1;
      return 0;
    case 's':
      flag->s = 1;
      return 0;
    case 't':
      flag->t = 1;
      flag->v = 1;
      return 0;
    case 'T':
      flag->t = 1;
      return 0;
    case 'v':
      flag->v = 1;
      return 0;
    case '?':
      return 1;
    default:
      return 2;
  }
}

void get_filenames(int argc, char **argv, flags *flag) {
  int flag_to_file =
      0;  // Функция переключатель с чтения флагов на чтение файлов

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      flag_to_file = 1;
    }

    if (flag_to_file == 1) {
      file_format(argv[i], flag);
    }
  }
}