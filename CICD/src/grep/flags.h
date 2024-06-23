#ifndef FLAGS
#define FLAGS

#include "s21_grep.h"

int flag_realisation(flags *flag, char *pattern, char *string,
                     int *count_match);
void pattern_generation(flags *flag, char *pattern, regex_t *regex);
int pattern_search(flags *flag, char *string, regex_t *regex, int *count_match);
int output_strings(flags *flag, char *string, int *count_match, regex_t regex);
void output_info(flags *flag, int count_match, char *name, int count_files,
                 int str_number);

void check_n_and_files(int count_files, char *name, int *str_number,
                       flags *flag);
void add_end(char *str);
void flag_o(char *str, char *pattern);
#endif