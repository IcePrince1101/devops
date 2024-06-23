#ifndef S21_GREP
#define S21_GREP

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGV_SIZE 50

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} flags;

#include "file_work.h"
#include "flags.h"

int flag_options(int code_result, flags *flag);
void activating_e(flags *flag);
void search_patterns_and_files(int argc, char **argv, regex_t *regex,
                               char ***patterns, int *count_patterns,
                               char ***files, int *count_files, int *exit_code);
void flag_analysis(int argc, char **argv, char *short_flags,
                   struct option *long_flags, flags *flag, int *error);
void analyze_files(char **files, int count_files, char **patterns,
                   int count_patterns, flags *flag);
void cleanup_memory(char **patterns, int count_patterns, char **files,
                    int count_files, regex_t *regex);
int counting_patterns(int argc, char **argv);
int counting_max_string_len(int argc, char **argv);

#endif