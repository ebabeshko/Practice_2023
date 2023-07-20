#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <String.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// структура
struct product {
	unsigned int id;			// код товару
	int deleted;				// видалено чи ні
	char product_name[100];		// назва товару
	float price;				// ціна товару
	int quantity;				// кількість товару
	struct Node* next;			// адресса наступного елементу списку
};

// функція зчитує всі записи з бази даних
void read_base(const char* filename, struct node** head);

// Функція для додавання нових продуктів
void add_new_product(const char* filename, const struct product* person);

// функція зміни будь якого продукту
void update_product(const char* filename, unsigned int id, struct product* new_person);

// функція видалення
void delete_product(const char* filename, unsigned int id);

// експорт у .csv
void csv(char* file, struct node** head);

#endif
