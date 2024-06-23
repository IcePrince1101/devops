#include "s21_grep.h"

int main(int argc, char **argv) {
  flags flag = {0};
  int exit_code = 0;

  char *short_flags = "eivclnhsfo";
  struct option long_flags[] = {{"regexp", 0, NULL, 'e'},
                                {"ignore-case", 0, NULL, 'i'},
                                {"invert-match", 0, NULL, 'v'},
                                {"count", 0, NULL, 'c'},
                                {"files-with-matches", 0, NULL, 'l'},
                                {"line-number", 0, NULL, 'n'},
                                {"no-filename", 0, NULL, 'h'},
                                {"no-messages", 0, NULL, 's'},
                                {"file", 0, NULL, 'f'},
                                {"only-matching", 0, NULL, 'o'}};

  // Поиск паттернов и файлов и запись их в массивы
  // выделение памяти
  int max_len = counting_max_string_len(argc, argv);
  char **patterns =
      (char **)malloc(counting_patterns(argc, argv) *
                      sizeof(char *));  // Массив указателей на паттерны
  char **files =
      (char **)malloc(argc * sizeof(char *));  // Массив указателей на файлы
  for (int i = 0; i < counting_patterns(argc, argv); i++) {
    patterns[i] = (char *)malloc(max_len * sizeof(char));
  }
  for (int i = 0; i < argc; i++) {
    files[i] = (char *)malloc(max_len * sizeof(char));
  }

  int count_patterns = 0;  // Счетчик паттернов
  int count_files = 0;     // Счетчик файлов для поиска

  for (int i = 1; i < argc; i++) {
    if (strstr(argv[i], "e") && argv[i][0] == '-') {
      flag.e = 1;
    } else if (strcmp(argv[i], "-f") == 0) {
      flag.f = 1;
    }
  }

  int one_pattern = 0;  // Маркер отработки поиска паттерна без флага -e
  for (int i = 1; i < argc; i++) {
    // Проверка, что это не флаг
    if (argv[i][0] != '-') {
      // Проверка, что флага -e  не было и это первое слово
      if (one_pattern == 0 && flag.e == 0 && flag.f == 0) {
        strcpy(patterns[count_patterns], argv[i]);
        count_patterns++;
        one_pattern++;

        // Ечли флаг -е был, то ищем его
      } else if (flag.e == 1 && (argv[i - 1][strlen(argv[i - 1]) - 1] == 'e' &&
                                 argv[i - 1][0] == '-')) {
        strcpy(patterns[count_patterns], argv[i]);
        count_patterns++;

      } else if (strcmp(argv[i - 1], "-f") == 0) {
        flag.e = 1;
        size_t buffer_size = 1024;  // начальный размер буфера
        char *buffer = malloc(buffer_size);  // буфер для сохранения всех строк
        FILE *pattern_f = fopen(argv[i], "r");
        if (pattern_f == NULL) {
          printf("Error! File not found.");
          exit_code = 1;
          break;
        }

        // считывание всех строк из файла в буфер
        size_t total_size = 0;
        while (fgets(buffer + total_size, buffer_size - total_size,
                     pattern_f) != NULL) {
          total_size += strlen(buffer + total_size);

          // если буфер заполнился полностью, увеличить его размер
          if (total_size + buffer_size >= MAX_ARGV_SIZE) {
            buffer_size *= 2;
            buffer = realloc(buffer, buffer_size);
          }
        }
        fclose(pattern_f);

        // разбить буфер на отдельные строки и скопировать их в массив
        // patterns
        char *p = strtok(buffer, "\n");
        while (p != NULL) {
          strcpy(patterns[count_patterns], p);
          count_patterns++;
          p = strtok(NULL, "\n");
        }
        free(buffer);

      } else {
        strcpy(files[count_files], argv[i]);
        count_files++;
      }
    }
  }
  // Конец поиска паттернов и файлов

  int error = 0;  // Переменная для выхода по ошибке
  int work = 0;  // Рабочая переменная для работы функции getopt_long
  int code_result = 0;  // Хранит результат функции getopt_long

  while (code_result != -1 && error == 0) {
    code_result = getopt_long(argc, argv, short_flags, long_flags, &work);
    error = flag_options(code_result, &flag);
  }

  if (error == 1 || exit_code == 1) {
    printf("Error!");
  } else {
    activating_e(&flag);

    // Основная логика
    for (int i = 0; i < count_files; i++) {
      file_format(files[i], &flag, patterns, count_patterns, count_files);
    }
  }

  // Очистка памяти
  for (int i = 0; i < counting_patterns(argc, argv); i++) {
    free(patterns[i]);
  }
  for (int i = 0; i < argc; i++) {
    free(files[i]);
  }
  free(patterns);
  free(files);
  return 0;
}

// Функция, присваивающая значения элементам структуры в соответствии с флагами
int flag_options(int code_result, flags *flag) {
  int end_point;
  switch (code_result) {
    case 'e':
      flag->e = 1;
      end_point = 0;
      break;
    case 'i':
      flag->i = 1;
      end_point = 0;
      break;
    case 'v':
      flag->v = 1;
      end_point = 0;
      break;
    case 'c':
      flag->c = 1;
      end_point = 0;
      break;
    case 'l':
      flag->l = 1;
      end_point = 0;
      break;
    case 'n':
      flag->n = 1;
      end_point = 0;
      break;
    case 'h':
      flag->h = 1;
      end_point = 0;
      break;
    case 's':
      flag->s = 1;
      end_point = 0;
      break;
    case 'f':
      flag->f = 1;
      end_point = 0;
      break;
    case 'o':
      flag->o = 1;
      end_point = 0;
      break;
    case '?':
      end_point = 1;
      break;
    default:
      end_point = 2;
      break;
  }
  return end_point;
}

void activating_e(flags *flag) {
  if ((flag->v == 0 && flag->e == 0) || (flag->v == 1 && flag->e == 0)) {
    flag->e = 1;
  }
}

int counting_patterns(int argc, char **argv) {
  int count = 0;
  for (int i = 1; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (f != NULL) {
      char c = fgetc(f);
      while (c != EOF) {
        if (c == '\n') {
          count++;
        }
        c = fgetc(f);
      }
      fclose(f);
    }
    count++;
  }

  return count;
}

int counting_max_string_len(int argc, char **argv) {
  int count = 1;
  int answer = 0;
  for (int i = 1; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (f != NULL) {
      char c = fgetc(f);
      while (c != EOF) {
        count++;
        if (c == '\n') {
          if (count > answer) {
            answer = count;
            count = 1;
          }
        }
        c = fgetc(f);
      }
      fclose(f);
    } else {
      if ((int)strlen(argv[i]) > answer) {
        answer = (int)strlen(argv[i]);
      }
    }
  }
  return answer;
}