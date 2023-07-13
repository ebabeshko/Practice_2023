#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "functions.h"



int main() {
	setlocale(LC_ALL, "ukr");
	Employee* head = NULL;
	int choice, id;
	char c[11];
	char license_key[11];
	char db_file[50];
	char config_file[] = "../Practice/key.cfg";

	config_check(config_file, db_file, license_key);


	printf("\n   ����i�� �i����i���� ����: ");
	char input[11];
	scanf("%10s", input);
	int checker = 1;
	if (strcmp(input, license_key) != 0) {
		printf("   �i����i���� ���� ������� ���i���! �����i���� ���� ��������!\n");
		checker = 0;
	}

	head = load_database(db_file);

	while (1) {

		printf("\n   ����:\n");
		printf("   1. ������ �����\n");
		printf("   2. �������� �����\n");
		printf("   3. ����������� ������\n");
		printf("   4. ��i���� �����\n");
		printf("   5. �������� ���� �����\n");
		printf("   6. �����\n");

		if (checker == 1) {
			printf("   ����i����i �����i�:\n");
			printf("   7. ������� ������ ��i����i����i� �������� ������ ��������� �i��� �������� ����\n");
			printf("   8. ������� ������ ��i����i����i� �����i��� ����� ���� ���� ������\n");
			printf("   ��������i �����i�:\n");
			printf("   9. �������� � ����i .dat\n");
			printf("   10. �������� � ����i .cvs\n");
		}

		printf("\n   ��� ���i�: ");
		scanf("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1:
			add_record(&head);
			break;
		case 2:
			printf("   ����i�� i������i���i���� ����� ������ ��� ���������: ");
			scanf("%d", &id);
			delete_record(&head, id);
			getchar();
			break;
		case 3:
			display_records(head);
			break;
		case 4:
			printf("   ����i�� i������i���i���� ����� ������ ��� ��i��: ");
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
				printf("����i�� ����� ������: ");
				char post[50];
				getchar();
				scanf("%49s", post);

				printf("����i�� ����: ");
				int year, month, day;
				getchar();
				scanf("%d %d %d", &day, &month, &year);

				filter_post_date(head, post, day, month, year);
				break;
		case 8:
				printf("����i�� �����i��� �����: ");
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
				printf("   ���i���� ���i�! ��������� �� ���.\n");
			break;
		}
	}

	return 0;
}
