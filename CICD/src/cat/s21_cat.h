#ifndef S21_CAT
#define S21_CAT

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int v;
  int n;
  int s;
  int t;
} flags;

#include "file_work.h"
#include "flags.h"

int flag_options(int code_result, flags *flag);
void get_filenames(int argc, char **argv, flags *flag);

#endif