#ifndef FUNCS_H
#define FUNCS_H
#define PUBLIC
#define PRIVATE static
#define MAX 100
#define KEY_LENGTH 8
#define MAX_FILENAME_LENGTH 20
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

PUBLIC void fill(const char* Curname);
PUBLIC void output(const char* Curname);
PUBLIC void del(const char* Curname);
PUBLIC void edit(const char* Curname);
PUBLIC void rating_search(const char* Curname);
PUBLIC void annual_turnover(const char* Curname);

PUBLIC bool valid();
PUBLIC void file_change_name(const char* Curname);
PUBLIC void generation_key();
PUBLIC void CSV(const char* Curname);
#endif
