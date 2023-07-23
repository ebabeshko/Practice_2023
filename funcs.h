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

PUBLIC void fill(const char* CurfileName);
PUBLIC void output(const char* CurfileName);
PUBLIC void del(const char* CurfileName);
PUBLIC void edit(const char* CurfileName);
PUBLIC void rating_search(const char* CurfileName);
PUBLIC void annual_turnover(const char* CurfileName);

PUBLIC bool valid();
PUBLIC void file_change_name(const char* CurfileName);
PUBLIC void generation_key();
PUBLIC void CSV(const char* CurfileName);
#endif
