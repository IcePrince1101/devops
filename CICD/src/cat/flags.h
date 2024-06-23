#ifndef FLAGS
#define FLAGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_cat.h"

void no_flag(flags *flag, char *final_str);
void flag_e(flags *flag, char *final_str, char *str, char enter);
int flag_s(flags *flag, char *final_str, int *count_void_string);
void flag_t(flags *flag, char *final_str);
void flag_b_n(flags *flag, char *final_str, int *str_number);
void flag_v(flags *flag, char *final_str);
void add_end(char *str);
void notation(char *str, int place, char note);
#endif