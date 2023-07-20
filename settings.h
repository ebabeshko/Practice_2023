#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>
#include <String.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// функція зчитування значень з файлу бази даних
void config_read(char configname[100], char path_db[100], int* key);

// редагування ключа
void edit_key(char configname[100], int key);

// редагування бази даних
void edit_pathDB(char configname[100], char path_db[100]);

#endif
