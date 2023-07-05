#ifndef DB_PRETTY_OUTPUT_H
#define DB_PRETTY_OUTPUT_H

#include <stdio.h>
#include"db_manager.h"

// Форматоване виведення таблиці
void pretty_output_base(struct node** head);

// Форматоване виведення таблиці контактів що немають телеграму
void pretty_output_base_telegram(struct node** head);

// вивід контактів в даному місяці народження (мінімально відрізняється від функції вище, але зручніше було зробити окрему функцію)
void pretty_output_base_month(struct node** head, int month);

#endif