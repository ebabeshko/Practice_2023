#include "database.h"

// функція зчитує всі записи з бази даних
void read_base(const char* filename, struct node** head) {
	FILE* file = fopen(filename, "rb");
	// якщо фалйлу не існує створюємо
	if (file == NULL) {
		printf("\ndatа base file doesnt exist!\n");
		printf("generating data base file\n");
		file = fopen(filename, "wb");
		return;
	}
	// Генерація з'вязного списку
	while (1) {
		struct product* product = (struct Person*)malloc(sizeof(struct product));
		// якщо зчитана структура порожня не читаємо
		if (fread(product, sizeof(struct product), 1, file) != 1) {
			free(product);
			break;
		}
		// зв'язуємо список
		product->next = *head;
		*head = product;
	}
	fclose(file);
}

// Функція для додавання нових продуктів
void add_new_product(const char* filename, const struct product* person) {
	// Відкриття файлу для додавання у режимі бінарного запису
	FILE* file = fopen(filename, "ab");
	// Запис структури в файл
	fwrite(person, sizeof(struct product), 1, file);
	fclose(file);
}

// функція зміни будь якого продукту
void update_product(const char* filename, unsigned int id, struct product* new_person) {
	FILE* file = fopen(filename, "r+b");
	struct product product;
	int found = 0;
	while (fread(&product, sizeof(struct product), 1, file) == 1) {
		if (product.id == id) {
			// змінна для зміщення курсору по байтам файлу
			long offset = sizeof(struct product) * (-1);
			fseek(file, offset, SEEK_CUR);
			fwrite(new_person, sizeof(struct product), 1, file);
			found = 1;
			break;
		}
	}
	// не знайшли з таким айді виводимо помилку
	if (!found) {
		printf("Can`t edit this product\n");
	}
	fclose(file);
}

void delete_product(const char* filename, unsigned int id) {
	struct product* seak_product = NULL;
	struct product deleted;
	read_base(filename, &seak_product);

	// перебираємо всі значення
	while (seak_product != NULL) {
		// якщо запис з таким айді є
		if (seak_product->id == id) {

			// старі дані не змінюємо
			deleted.id = id;
			// ліше змінюємо поле deleted
			deleted.deleted = 1;
			strcpy(deleted.product_name, seak_product->product_name);
			deleted.price = seak_product->price;
			deleted.quantity = seak_product->quantity;
			deleted.next = NULL;
			break;
		}
		// наступне значення
		seak_product = seak_product->next;
	}
	FILE* file = fopen(filename, "r+b");
	struct product product;
	//знайдено/не знайдено
	int found = 0;
	while (fread(&product, sizeof(struct product), 1, file) == 1) {
		if (product.id == id) {
			// змінна для зміщення курсору по байтам файлу
			long offset = sizeof(struct product) * (-1);
			fseek(file, offset, SEEK_CUR);
			// заміняємо на нашу структуру
			fwrite(&deleted, sizeof(struct product), 1, file);
			found = 1;
			break;
		}
	}
	// не знайшли з таким айді виводимо помилку
	if (!found) {
		printf("Can`t edit this product\n");
	}
	fclose(file);
}


// експорт у .csv
void csv(char* csvfile, struct node** head) {
	struct product* product = *head;
	FILE* file = fopen(csvfile, "wb");
	// заголовок таблиці
	fprintf(file, "Id;Product name;Price;Quantity;\n");
	while (product != NULL) {
		// якщо не видалено
		if (product->deleted == 0) {
			fprintf(file, "%u;%s;%f;%d;\n", product->id, product->product_name, product->price, product->quantity);
		}
		product = product->next;
	}
	fclose(file);
}
