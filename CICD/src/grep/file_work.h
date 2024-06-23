#ifndef FILE_WORK
#define FILE_WORK

#include "flags.h"
#include "s21_grep.h"

int file_format(char *name, flags *flag, char **patterns, int count_patterns,
                int count_files);
void string_working(FILE *f, int count, flags *flag, int *str_number,
                    char **patterns, int count_patterns, char *name,
                    int count_files, int *count_match);
void file_working(FILE *f, char *name, flags *flag, int str_number,
                  char **patterns, int count_patterns, int count_files,
                  int *count_match);
#endif