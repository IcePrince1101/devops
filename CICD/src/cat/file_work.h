#ifndef FILE_WORK
#define FILE_WORK

#include <stdio.h>
#include <stdlib.h>

#include "s21_cat.h"

void file_format(char *name, flags *flag);
int string_working(FILE *f, int count, flags *flag, int *str_number,
                   int *count_void_string);
void get_string(char *name, FILE *f, flags *flag);
#endif