#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "m_func.h"



int main() {
	setlocale(LC_ALL, "ukr");
	Employee* head = NULL;
	int choice, id;
	char c[11];
	char license_key[11];
	char db_file[50];
	char config_file[] = "../Practice/key.cfg";

	config_check(config_file, db_file, license_key);


	printf("\n   Введiть лiцензiйний ключ: ");
	char input[11];
	scanf("%10s", input);
	int checker = 1;
	if (strcmp(input, license_key) != 0) {
		printf("   Лiцензiйний ключ введено невiрно! Функцiонал буде обмежено!\n");
		checker = 0;
	}

	head = loadDatabase(db_file);

	while (1) {

		printf("\n   Меню:\n");
		printf("   1. Додати запис\n");
		printf("   2. Видалити запис\n");
		printf("   3. Переглянути записи\n");
		printf("   4. Змiнити запис\n");
		printf("   5. Зберегти базу даних у файл\n");
		printf("   6. Вийти\n");

		if (checker == 1) {
			printf("   Спеціальні функції:\n");
			printf("   7. Вивести список співробітників введенної посади прийнятих після введенної дати\n");
			printf("   8. Вийти\n");
			printf("   Додаткові функції:\n");
			printf("   9. Зберегти у файлі .dat\n");
			printf("   10. Зберегти у файлі .cvs\n");
		}

		printf("\n   Ваш вибiр: ");
		scanf("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1:
			addRecord(&head);
			break;
		case 2:
			printf("   Введiть iдентифiкацiйний номер запису для видалення: ");
			scanf("%d", &id);
			deleteRecord(&head, id);
			break;
		case 3:
			displayRecords(head);
			break;
		case 4:
			printf("   Введiть iдентифiкацiйний номер запису для змiни: ");
			scanf("%d", &id);
			modifyRecord(head, id);
			break;
		case 5:
			saveDatabase(head, db_file);
			break;
		case 6: {
			saveDatabase(head, db_file);
			freeMemory(head);
			return 0; }
			  if (checker = 1) {
		case 7:
				printf("Введіть назву посади: ");
				char post[50];
				scanf("%49s", post);

				printf("Введіть дату: ");
				int year, month, day;
				scanf("%d %d %d", &day, &month, &year);

				filter_position_date(head, post, day, month, year);
		case 8:
		case 9: export_dat(head);
				break;
		case 10: export_cvs(head);
				 break;
			  }
		default:
				printf("   Невiрний вибiр! Спробуйте ще раз.\n");
			break;
		}
	}

	return 0;
}
