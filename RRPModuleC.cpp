#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "RRPModuleC.h"

PUBLIC int readDataFromFile(struct Stuff** arr, FILE* fcsv) {		/* ���������� ������ �� �� */

	//����� ������
	char temp[SIZE] = " ";
	//���� ����� ������
	bool isFirstLine = true;
	//�������� �����
	struct Stuff* current = NULL;
	//�������� �� ������ ���� ���������
	struct Stuff** lastNextPtr = arr;

	//���� �� ���������� �����
	while (fgets(temp, sizeof(temp), fcsv)) {

		//�������� �� ����� ������
		if (isFirstLine) {
			isFirstLine = false;
			continue; // ������� �� �������� ������
		}

		//����������� ��������� �����
		current = (struct Stuff*)malloc(sizeof(struct Stuff));
		if (current == NULL) {
#ifdef DEF
			printf("err: reading stuff is failed");
#endif
			return ERROR_TYPE;
		}

		//������ ����������� ���������
		AddHelper(current);

		//�������� �� ��������� �����, ��� �������� ������ �� ��������
		char* token = NULL;
		char* next_token = NULL;

		//���������� ���� �� ; �� �������
		token = strtok_s(temp, ";", &next_token);
		if (token != NULL) {
			// ���������� Id
			current->id = atoi(token);

			// ���������� ��'�
			token = strtok_s(NULL, ";", &next_token);
			strncpy_s(current->name, SIZE, token, _TRUNCATE);

			// ���������� ������
			token = strtok_s(NULL, ";", &next_token);
			strncpy_s(current->group, SIZE, token, _TRUNCATE);

			// ���������� ֳ��
			token = strtok_s(NULL, ";", &next_token);
			current->price = atof(token);

			// ���������� �������������
			token = strtok_s(NULL, ";", &next_token);
			strncpy_s(current->from, SIZE, token, _TRUNCATE);

			// ���������� ����� ���������
			token = strtok_s(NULL, ";", &next_token);
			current->delstat = atoi(token);

			//������� �� ��������� �����
			current->next = NULL;

			//���� ��'����� ������ �� �� �����, �� �������� �����, ����� ������
			if (*arr == NULL) {
				*arr = current;
			}
			//������� �� ��������� �����
			*lastNextPtr = current;
			lastNextPtr = &(current->next);
		}
	}
	//���������� ������
	return 0;
}

PUBLIC int CountOfWork(struct Stuff** arr) {		/* ���� ������ ������ ��� ���� */

	//�������� �����
	struct Stuff* current = *arr;

	//������� ������
	int count = 0;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	//��������� ������� ������
	return count;
}

PUBLIC int menu(struct Stuff** arr) {		/* ������� ���� */

	while (true) {		/* ���� �� ��������� �������� */

		//���������� ������
		int choise;
		char continum = ' ';

		//��������� ���������� �� �����������
		printf("\t������� ������� ����.\n");
		printf("\t��������:\n");
		printf(
			"\t\t1. �������� ����� �����\n"
			"\t\t2. ������������ ������ �� Id\n"
			"\t\t3. ��������� ������ �� Id\n"
			"\t\t4. ����������� ����� �� Id\n"
			"\t\t5. ����������� �� ������\n"
			"\t\t6. ��������� ��� ������ �� ��������������\n"
			"\t\t7. ��������� ��� ������ �� ������, � ���� ���� ����� �� ������\n"
			"\t\t8. ���������� ������ �� CSV �����\n"
			"\t\t0. ��������� ��������\n"
		);

		//�������� ������
		fflush(stdin);
		scanf_s("%i", &choise);

		//���� ������� �� ��������
		switch (choise) {
		case 1:		/* ��������� ������ */
			system("cls");
			printf("\t��������� ����� �����...\n");
			AddStuff(arr);
			break;
		case 2:		/* ������ ����� */
			system("cls");
			printf("\t������� ����� �� Id...\n");
			ChangeSet(*arr);
			break;
		case 3:		/* �������� ����� */
			system("cls");
			printf("\t��������� ����� �� Id...\n");
			DeleteStuff(arr);
			break;
		case 4:		/* ��������� ����� �� Id */
			system("cls");
			printf("\t�������� ����� �� Id...\n");
			PrintId(*arr);
			break;
		case 5:		/* ������� �� ���� ������ */
			system("cls");
			printf("\t�������� ���� ������...\n");
			PrintAll(arr);
			break;
		case 6:		/* ������� ������� ������ �� �������������� */
			system("cls");
			printf("\t�������� ������ �� ��������������...\n");
			PrintFrom(*arr);
			break;
		case 7:		/* ��������� ��� ������ ������ �����, ���� ���� ����� �� ������. */
			system("cls");
			printf("\t�������� ������ �� ������� � �������� �� ����...\n");
			GroupPriceFall(*arr);
			break;
		case 8:		/* ���������� ����� �� �� */
			system("cls");
			printf("\t�������� ����...\n");
			writeDataToFile(arr);
			break;
		case 0:		/* ��������� �������� */
			system("cls");
			printf("\t���������� ��������...\n");
			return 0;
		default:	/* ĳ� �� ���� �������� */
#ifdef DEF
			printf("err: menu choice is wrong");
#endif
			return ERROR_TYPE;
		}
	}
}

PRIVATE int writeDataToFile(struct Stuff** arr) {		/* ������ ��� �� ��'������ ������ �� �� */

	//��������� ���� ��
	FILE* fcsv;
	if (fopen_s(&fcsv, "mybd.csv", "w+")) {
		puts("\n ������� �������� ����� mybd.csv");
		return ERROR_TYPE;
	}

	//�������� ����� ��'������ ������
	struct Stuff* current = *arr;

	//����� ����� ������
	fprintf(fcsv, "ID;Name;Group;Price;From;Del. Stat.\n");

	//���� �� ����� ������ �� ��'������ ������
	while (current != NULL) {

		//�����
		fprintf(fcsv, "%d;%s;%s;%.2lf;%s;%i\n"
			, current->id
			, current->name
			, current->group
			, current->price
			, current->from
			, current->delstat
		);

		//������� �� ��������� ����� ��'������ ������
		current = current->next;
	}
	//�������� ����� �� ���������� ������
	fclose(fcsv);
	return 0;
}

PRIVATE char getsymb() {		/* ������ ����� ������� */
	char Csymb = ' ';
	do {
		scanf_s("%c", &Csymb);
	} while (Csymb == '\n');
	return Csymb;
}

PRIVATE int read_line(char* str, int n) {		/* �������� ����� ������ */
	int ch, i = 0;
	while (getchar() != '\n');  // �������� stdin
	while ((ch = getchar()) != '\n' && i < n - 1)
		str[i++] = ch;
	str[i] = '\0';
	return i;
}

PRIVATE bool TheDogma(struct Stuff* ptr) {		/* ������� ����� �� ���������� ������� */

	//����������� ��'������ ����� ������ �������
	AddHelper(ptr);
	
	//���� ���������� �������
	ptr->delstat = false;

	//������������ ��'������ �����
	SetStuff(ptr);

	//������� true, �� ��������� �������� ������
	return true;
}

PRIVATE int AddStuff(struct Stuff** arr) {		/* ��������� ������ ����� */

	//���������� ������ ���������
	printf("��������� ������ ������...\n");

	//���������� new_node, ���� ���� ������ ���� ��� ����������� ������ ������
	struct Stuff* new_node = *arr;
	//�������� �� ��, �� ���� �� �������� �� ���������� ����, �� ���� ���������� ����� ������ ����
	bool dogmaticKnowlege = false;

	//����� ���� �� ����� �����
	while (new_node != NULL) {
		if (new_node->delstat == 1) {
			dogmaticKnowlege = TheDogma(new_node);
			break;
		}
		new_node = new_node->next;
	}

	//���� ��������� ����� �������� �� ����
	if (!dogmaticKnowlege) {
		//����������� ���������� �����
		new_node = (Stuff*)malloc(SIZE * sizeof(Stuff));
		if (new_node == NULL) {
#ifdef DEF
			printf("err: adding new stuff is failed");
#endif
			return ERROR_TYPE;
		}

		//������ ��������
		AddHelper(new_node);

		//������ ������������ ������
		new_node->id = CountOfWork(arr) + 1;
		SetStuff(new_node);

		//����������� ���������� ����� �����
		new_node->next = NULL;

		//������������ �����
		struct Stuff* last = *arr;
		while (last->next != NULL) {
			last = last->next;
		}

		//�� ��� ����������� �������� �� ���������� ����������
		last->next = new_node;
	}

	//���������� ������
	return 0;
}

PRIVATE int AddHelper(struct Stuff* help_new_stuff) {		/* �������� ������� ��������� ������ */
	
	//����������� ������
	help_new_stuff->name = (char*)malloc(SIZE * sizeof(char));
	if (help_new_stuff->name == NULL) {
#ifdef DEF
		printf("err: helping_adding stuff is failed");
#endif
		return ERROR_TYPE;
	}
	help_new_stuff->group = (char*)malloc(SIZE * sizeof(char));
	if (help_new_stuff->group == NULL) {
#ifdef DEF
		printf("err: helping_adding stuff is failed");
#endif
		return ERROR_TYPE;
	}
	help_new_stuff->from = (char*)malloc(SIZE * sizeof(char));
	if (help_new_stuff->from == NULL) {
#ifdef DEF
		printf("err: helping_adding stuff is failed");
#endif
		return ERROR_TYPE;
	}
	
	//���������� ������ �������� �������
	strcpy_s(help_new_stuff->name, SIZE, "zero");
	strcpy_s(help_new_stuff->group, SIZE, "zero");
	help_new_stuff->price = 0;
	strcpy_s(help_new_stuff->from, SIZE, "zero");
	help_new_stuff->delstat = 0;

	//���������� ������
	return 0;
}

PRIVATE int SetStuff(struct Stuff* ptr) {		/* ���������� �������� */
	
	//��������� �������� ������
	int choise;
	char continum = ' ';

	//���� �� ������� ������
	while (true) {
		
		//��������� ������ �� �����
		PrintStuff(ptr);
		
		//����� 䳿
		printf("\t��������:\n"
			"\t\t1. ������ ��'�\n"
			"\t\t2. ������ �����\n"
			"\t\t3. ������ ���� ������\n"
			"\t\t4. ������ �������������\n"
			"\t\t0. ����� �� ���������\n"
		);

		//�������� ������
		scanf_s("%i", &choise);
		
		//䳿 ��� �������
		switch (choise) {
		case 1:		/* ������ ��'� */
			printf("������ ���� ��'� ������: ");
			read_line(ptr->name, SIZE);
			break;
		case 2:		/* ������ ����� */
			printf("������ ���� ����� ������: ");
			read_line(ptr->group, SIZE);
			break;
		case 3:		/* ������ ���� */
			printf("������ ���� ���� ��� ������ ������: ");
			scanf_s("%lg", &ptr->price);
			break;
		case 4:		/* ������ ������������� */
			printf("������ ������ ������������� ������: ");
			read_line(ptr->from, SIZE);
			break;
		case 0:		/* ������� �������� */
			system("cls");
			printf("�������� ��� ������.");
			return 0;
		default:	/* ĳ� �� ���� �������� */
			printf("����������� ���\n");
#ifdef DEF
			printf("err: set stuff char break");
#endif
			return ERROR_TYPE;
		}
		system("cls");
	}
}

PRIVATE void ChangeSet(struct Stuff* ptr) {		/* ������ ����� �� Id */
	
	//����������� ��������� �����
	struct Stuff* current = ptr;
	
	//���������� �� ����� Id ������, ���� ����� ������
	int setId;
	printf("������ Id ������, ���� ����� ������: ");
	scanf_s("%i", &setId);

	// ����������� �����
	while (current != NULL && current->id != setId) {
		current = current->next;
	}
	// ������������ ����� �� Id
	if (current != NULL && current->delstat == 0) {
		SetStuff(current);
	}
	// ���� Id �� ��������
	else {
		printf("����� �� Id %i �� ��������.\n", setId);
	}
}

PRIVATE int DeleteStuff(struct Stuff** arr) {		/* ��������� ������ */
	
	// ���������� �� �������� Id
	printf("���� ����� ������� ��������? ������ id ������:\n");
	int d;
	scanf_s("%i", &d);
	
	// ����������� ��'������ ����� ���������, �� ��������
	struct Stuff* prev = NULL;
	struct Stuff* current = *arr;
	
	// ����� ������ �� Id
	while (current != NULL && current->id != d) {
		prev = current;
		current = current->next;
	}
	// ���� ���� ������ �� Id
	if (current == NULL) {
		printf("����� �� Id %i �� �������\n", d);
		return ERROR_TYPE;
	}
	// ���� ����� �� ��������� 
	if (prev != NULL) {
		current->delstat = 1;
	}
	// ���� ������� ����� ��
	else {
		*arr = current->next;
	}
	//���������� ������
	return 0;
}

PRIVATE void PrintStuff(struct Stuff* ptr) {		/* ��������� ��������� */
	if (ptr->delstat == 1) { return; }		/* �������� �� ��������� */
	else
		printf(
			"\t\t+--------------------------------------------------+\n"
			"\t\t| Id ������ ������: %i\n"
			"\t\t+--------------------------------------------------+\n"
			"\t\t| ��'� ������ ������: %s\n"
			"\t\t+--------------------------------------------------+\n"
			"\t\t| ������ ������ ������: %s\n"
			"\t\t+--------------------------------------------------+\n"
			"\t\t| ֳ�� ������ ������: %.2f ���\n"
			"\t\t+--------------------------------------------------+\n"
			"\t\t| ������������ ������ ������: %s\n"
			"\t\t+--------------------------------------------------+\n\n"

			, ptr->id
			, ptr->name
			, ptr->group
			, ptr->price
			, ptr->from
		);
}

PRIVATE void PrintAll(struct Stuff** arr) {		/* ��������� ��� ������ */
	
	//����������� ��������� �����
	struct Stuff* current = *arr;
	
	//���������� ��� ���������
	printf("\t������ ����� ������:\n");
	while (current != NULL) {
		PrintStuff(current);
		current = current->next;
		printf("\n");
	}
	printf("\n");
}

PRIVATE void PrintId(struct Stuff* ptr) {		/* ��������� ������ �� Id */
	
	// ����������� ��������� �����
	struct Stuff* current = ptr;
	// ���������� �� ����� Id
	int setId;
	printf("������ Id ������, ���� ����� ������: ");
	scanf_s("%i", &setId);
	
	// ������ ����� �� ������� Id
	while (current != NULL && current->id != setId) {
		current = current->next;
	}
	// ������� ����� �� ������� Id
	if (current != NULL && current->delstat == 0) {
		PrintStuff(current);
	}
	// ���� ����� �� �������
	else {
		printf("����� �� Id %i �� ��������.\n", setId);
	}
}

PRIVATE int PrintFrom(struct Stuff* ptr) {		/* �������� ������ �� ������ ������������� */
	
	// ��������� ����������� ���
	struct Stuff* current = ptr;
	
	// ���������� �� ����� �������������
	char* from = (char*)malloc(SIZE * sizeof(char));
	if (from == NULL) {
#ifdef DEF
		printf("err: print from stuff is failed");
#endif
		return ERROR_TYPE;
	}
	printf("������ ������������� ������, ������ ����� ����� ������: ");
	read_line(from, SIZE);
	
	//���� �� ����� �� ���������
	while (current != NULL) {
		if (strcmp(current->from, from) == 0) {
			PrintStuff(current);
		}
		current = current->next;
	}

	//���������� ������
	return 0;
}

PRIVATE int GroupPriceFall(struct Stuff* ptr) {		/* �������� ������ �� �������, ��� ���� �, �� ����� �� ����� */
	
	// ����������� ��������� �����
	struct Stuff* current = ptr;
	
	// ���������� �� ����� �����, ����
	double price;
	char* group = (char*)malloc(SIZE * sizeof(char));
	if (group == NULL) {
#ifdef DEF
		printf("err: group price fall stuff is failed");
#endif
		return ERROR_TYPE;
	
	}
	printf("������ ����� ������: ");
	read_line(group, SIZE);
	printf("������ ���� ������: ");
	scanf_s("%lg", &price);

	//����� ���������� ����
	while (current != NULL) {
		if (strcmp(current->group, group) == 0 && current->price < price) {
			PrintStuff(current);
		}
		current = current->next;
	}

	//���������� ������
	return 0;
}