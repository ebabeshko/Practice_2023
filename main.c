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


	printf("\n   ����i�� �i����i���� ����: ");
	char input[11];
	scanf("%10s", input);
	int checker = 1;
	if (strcmp(input, license_key) != 0) {
		printf("   �i����i���� ���� ������� ���i���! �����i���� ���� ��������!\n");
		checker = 0;
	}

	head = loadDatabase(db_file);

	while (1) {

		printf("\n   ����:\n");
		printf("   1. ������ �����\n");
		printf("   2. �������� �����\n");
		printf("   3. ����������� ������\n");
		printf("   4. ��i���� �����\n");
		printf("   5. �������� ���� ����� � ����\n");
		printf("   6. �����\n");

		if (checker == 1) {
			printf("   ��������� �������:\n");
			printf("   7. ������� ������ ����������� �������� ������ ��������� ���� �������� ����\n");
			printf("   8. �����\n");
			printf("   �������� �������:\n");
			printf("   9. �������� � ���� .dat\n");
			printf("   10. �������� � ���� .cvs\n");
		}

		printf("\n   ��� ���i�: ");
		scanf("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1:
			addRecord(&head);
			break;
		case 2:
			printf("   ����i�� i������i���i���� ����� ������ ��� ���������: ");
			scanf("%d", &id);
			deleteRecord(&head, id);
			break;
		case 3:
			displayRecords(head);
			break;
		case 4:
			printf("   ����i�� i������i���i���� ����� ������ ��� ��i��: ");
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
				printf("������ ����� ������: ");
				char post[50];
				scanf("%49s", post);

				printf("������ ����: ");
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
				printf("   ���i���� ���i�! ��������� �� ���.\n");
			break;
		}
	}

	return 0;
}
