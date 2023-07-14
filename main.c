

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "functions.h"



int main() {
	setlocale(LC_CTYPE, "ukr");
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

	head = load_database(db_file);

	while (1) {

		printf("\n   Меню:\n");
		printf("   1. Додати запис\n");
		printf("   2. Видалити запис\n");
		printf("   3. Переглянути записи\n");
		printf("   4. Змiнити запис\n");
		printf("   5. Зберегти базу даних\n");
		printf("   6. Вийти\n");

		if (checker == 1) {
			printf("   Спецiальнi функцiї:\n");
			printf("   7. Вивести список спiвробiтникiв введенної посади прийнятих пiсля введенної дати\n");
			printf("   8. Вивести список спiвробiтникiв заробiтня плата яких вище заданої\n");
			printf("   Додатковi функцiї:\n");
			printf("   9. Зберегти у файлi .dat\n");
			printf("   10. Зберегти у файлi .cvs\n");
		}

		printf("\n   Ваш вибiр: ");
		scanf("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1:
			add_record(&head);
			break;
		case 2:
			printf("   Введiть iдентифiкацiйний номер запису для видалення: ");
			scanf("%d", &id);
			delete_record(&head, id);
			getchar();
			break;
		case 3:
			display_records(head);
			break;
		case 4:
			printf("   Введiть iдентифiкацiйний номер запису для змiни: ");
			scanf("%d", &id);
			modify_record(head, id);
			getchar();
			break;
		case 5:
			save_database(head, db_file);
			break;
		case 6: {
			save_database(head, db_file);
			free_memory(head);
			return 0; }
			  if (checker = 1) {
		case 7:
				printf("Введiть назву посади: ");
				char post[50];
				getchar();
				scanf("%49s", post);

				printf("Введiть дату: ");
				int year, month, day;
				getchar();
				scanf("%d %d %d", &day, &month, &year);

				filter_post_date(head, post, day, month, year);
				break;
		case 8:
				printf("Введiть заробiтню плату: ");
				float salary_fil;
				scanf("%f", &salary_fil);
				filter_salary(head, salary_fil);
				break;

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
