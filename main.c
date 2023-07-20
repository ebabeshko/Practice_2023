#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include "settings.h"
#include "database.h"

// робота з строками
#pragma warning(disable : 4996)

// перевірка валідності ключа
int valid_key_check(int key) {
	if ((key % 10) == 7) {
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]) {

	char operation;
	int flag;
	struct product* head = NULL;  // Початок списку
	char program_activate;		  // активація програми
	int key;					  // зчитаний ключ
	char path[100];				  // шлях до бд
	char cfg_filename[100];		  // шлях до налаштувань
	int for_id;
	char name[50];
	float price;
	int q;
	float l_price;
	float h_price;
	char prod_name[100];
	char csvfile[100];
	// отримуємо назву
	strcpy(cfg_filename, argv[0]);
	int lengh = strlen(cfg_filename);

	// замінюємо після крапки
	cfg_filename[lengh] = '\0';
	cfg_filename[lengh - 1] = 'g';
	cfg_filename[lengh - 2] = 'f';
	cfg_filename[lengh - 3] = 'c';

	config_read(cfg_filename, &path, &key);

	// перевіряємо валідність ключа
	program_activate = valid_key_check(key);

	// виводимо інформацію щодо активації
	program_activate == 1 ? printf("Program activated\n") : printf("Program not activated input valid key\n");

	// нескінченний цикл де все "крутиться"
	for (;;) {

		// очищаємо список
		while (head != NULL) {
			struct product* temp = head;
			head = head->next;
			free(temp);
		}
		// для вибору режиму
		printf("\n0 exit program\n1 full list\n2 add new position\n3 delete product by id\n4 edit product\n5 show in price gap only\n6 show products this name only\n7 edit database path\n8 edit lic key\n9 export to .csv\n");
		scanf("%d", &operation);
		switch (operation)
		{
			//q - вихід з программи
		case 0:
			exit(0);
			break;

			// вивід списку в діапазоні цін
		case 5:
			system("cls");
			if (program_activate == 1) {
				// зчитуємо діапазон цін
				printf("\nlower price: ");
				scanf("%f", &l_price);
				printf("\nhigher price: ");
				scanf("%f", &h_price);
				system("cls");
				// виводимо в цьому діапазоні
				printf("\n  List of products in this price gap:\n");
				read_base(path, &head);

				while (head != NULL) {
					// виводими в цьому діапазоні та якщо не видалено
					if (head->deleted == 0 && head->price >= l_price && head->price <= h_price) {
						printf("%-6d %-50s %-8.2lf %-5d\n", head->id, head->product_name, head->price, head->quantity);
					}
					head = head->next;
				}
				break;
			}
			// виведення помилки активації
			else printf("\n You can`t use this func input velid key\n"); break;

			// вивід повного списку
		case 6:
			system("cls");
			if (program_activate == 1) {
				// отримуємо назву продукту
				printf("\nProduct name: ");
				//scanf("%s", &prod_name);
				gets(prod_name);
				gets(prod_name);
				system("cls");
				printf("\n  List of products with this name\n");
				read_base(path, &head);

				while (head != NULL) {
					// виводимо не видалені та з таким ім'ям
					if (head->deleted == 0 && !(strcmp(head->product_name, prod_name))) {
						printf("%-6d %-50s %-8.2lf %-5d\n", head->id, head->product_name, head->price, head->quantity);
					}
					head = head->next;
				}
				break;
			}
			// виведення помилки активації
			else printf("\n You can`t use this func input velid key\n"); break;

		case 1:
			system("cls");
			// виводимо всі записи
			printf("\n  Full list of products:\n");
			read_base(path, &head);

			while (head != NULL) {
				// виводимо якщо продукт не видалено
				if (head->deleted == 0) {
					printf("%-6d %-50s %-8.2lf %-5d\n", head->id, head->product_name, head->price, head->quantity);
				}
				head = head->next;
			}
			break;

			// додавання продукту
		case 2:
			printf("Adding product");

			struct product product;
			// ввід айді
			printf("\nProduct code: ");
			scanf_s("%d", &for_id);
			product.id = for_id;
			product.deleted = 0;

			// ввід імені
			printf("\nProduct name: ");
			gets(name);
			if (strlen(name) == 0) gets(name);
			strcpy(product.product_name, name);

			// ввід ціни
			printf("\nProduct price: ");
			scanf_s("%f", &price);
			product.price = price;

			// ввід кількості
			printf("\nProduct quantity: ");
			scanf_s("%d", &q);
			product.quantity = q;

			// створюємо новий запис
			add_new_product(path, &product);
			system("cls");
			break;

			// видалення
		case 3:
			printf(" Deleting product by id:\n");
			scanf("%d", &for_id);
			delete_product(path, for_id);

			//  радегування
		case 4:
			// запрощення до вводу айді яке потрібно редагувати
			printf("\n ID of Product to edit: ");
			scanf_s("%u", &for_id);
			read_base(path, &head);

			// перебираємо всі записи
			while (head != NULL) {
				if (head->id == for_id) {

					struct product product_mod;
					// Заповнення структури старими данними
					product_mod.id = for_id;
					product_mod.deleted = 0;
					strcpy(product_mod.product_name, head->product_name);
					product_mod.price = head->price;
					product_mod.quantity = head->quantity;
					product_mod.next = NULL;
					// для вибору режиму що саме змінювати
					printf("\nwhat you want to edit 1 - id, 2 - product name, 3 - price, 4 - quatity: ");
					// отримуємо користувацький вибір
					scanf("%d", &operation);
					switch (operation)
					{
					case 1:
						// ввід айді
						scanf_s("%d", &for_id);
						product_mod.id = for_id;
						break;
					case 2:
						// ввід назви
						gets(name);
						if (strlen(name) == 0) gets(name);
						strcpy(product_mod.product_name, name);
						break;
					case 3:
						// ввід ціни
						scanf_s("%f", &price);
						product_mod.price = price;
						break;
					case 4:
						// ввід кількості
						scanf_s("%d", &q);
						product_mod.quantity = q;
						break;

					default:
						break;
					}

					// в наявну структуру записуємо відредаговану
					update_product(path, for_id, &product_mod);

					break;
				}
				// наступний
				head = head->next;
			}
			system("cls");
			break;

			//зміна шляху до бази даних
		case 7:
			// введень нової назви бази даних
			printf("\nInput name  of DB: ");
			scanf("%s", path);
			//зміна ключа успішна
			edit_pathDB(cfg_filename, path);
			// зміна успішна
			printf("\nNew DB path saved\n");
			// перечитуємо налаштування
			config_read(cfg_filename, &path, &key);
			break;

			// зміна ліцензійного ключа
		case 8:
			printf("\nInput license key: ");
			scanf("%d", &key);
			edit_key(cfg_filename, key);
			//зміна ключа успішна
			system("cls");
			printf("\nNew license key saved\n");
			// перечитуємо налаштування
			config_read(cfg_filename, &path, &key);
			// перевіряємо валідність ключа
			program_activate = valid_key_check(key);
			// виводимо інформацію щодо активації
			program_activate == 1 ? printf("Program activated\n") : printf("Program not activated input valid key\n");
			break;

			// експорт в ексель
		case 9:
			// очищуємо консоль
			system("cls");
			// запитуємо ім'я для збереження
			printf("\n Please input name for .cvs file: ");
			scanf("%s", csvfile);
			// читаємо наші значення
			read_base(path, &head);
			// записуємо в інший формат
			csv(csvfile, &head);
			break;
			}
		}
	}
