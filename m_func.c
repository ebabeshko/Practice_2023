#include "m_func.h"

void config_check(const char* fname, char* bname, char* key) {
	FILE* fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("\n   ����i�����i���� ���� �� ��������.\n   ����i�����i���� ���� �� ���� ���� ����� ��������.\n");
		strcpy(bname, "../Practice/new_base.dat");
		keygen(fname, bname, key);
		printf("   ����� �i����i���� ����: %s\n", key);
		
	}
	else {
		char buffer[100];
		while (fgets(buffer, sizeof(buffer), fp) != NULL) {
			if (strstr(buffer, "DB") != NULL) {
				sscanf(buffer, "DB = %s", bname);
			}
			else if (strstr(buffer, "KEY") != NULL) {
				sscanf(buffer, "KEY = %s", key);
			}
		}
		fclose(fp);
	}
	return;
}



void keygen(const char* fname, const char* bname, char* key) {
	const char* characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int charactersCount = 36;
	char gkey[11];

	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		int randomIndex = rand() % charactersCount;
		gkey[i] = characters[randomIndex];
	}

	gkey[10] = '\0';
	strcpy(key, gkey);

	FILE* fp = fopen(fname, "w");
	if (fp != NULL) {
		fprintf(fp, "DB = %s\n", bname);
		fprintf(fp, "KEY = %s", key);
		fclose(fp);
	}
}



Employee* loadDatabase(const char* bname) {
	FILE* file = fopen(bname, "rb");
	if (file == NULL) {
		printf("   ������� ��� �i������i �����!\n");
		exit(1);
	}
	Employee* head = NULL;
	Employee* current = NULL;
	Employee* newEmployee;
	while (1) {
		newEmployee = (Employee*)malloc(sizeof(Employee));
		size_t bytesRead = fread(newEmployee, sizeof(Employee), 1, file);
		if (bytesRead < 1) {
			free(newEmployee);
			break;
		}
		newEmployee->next = NULL;
		if (head == NULL) {
				head = newEmployee;
		}
		else {
			current->next = newEmployee;
		}
		current = newEmployee;
	}
	fclose(file);
	printf("   ���� ����� ����������� � ����� %s\n", bname);
	return head;
}

void addRecord(Employee** head) {
	Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
	getchar();
	printf("   ����i�� �i� ��i����i�����: ");
	fgets(newEmployee->name, sizeof(newEmployee->name), stdin);
	newEmployee->name[strcspn(newEmployee->name, "\n")] = '\0';
	printf("   ����i�� ������ ��i����i�����: ");
	fgets(newEmployee->post, sizeof(newEmployee->post), stdin);
	newEmployee->post[strcspn(newEmployee->post, "\n")] = '\0';
	printf("   ����i�� ���� ��������� �� ������ (������: �� �� ����): ");
	scanf("%d %d %d", &newEmployee->hire_date[0], &newEmployee->hire_date[1],
		&newEmployee->hire_date[2]);
	printf("   ����i�� �����i��� ����� ��i����i�����: ");
	scanf("%f", &newEmployee->salary);
		// �������� ��i����� ������
		getchar();
	newEmployee->next = NULL;
	if (*head == NULL) {
		newEmployee->id = 1;
		*head = newEmployee;
	}
	else {
		Employee* current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		newEmployee->id = current->id + 1;
		current->next = newEmployee;
	}
	printf("   ����� ���i��� ������!\n");
}



// �����i� ��� ��������� ������
void deleteRecord(Employee** head, int id) {
	Employee* current = *head;
	Employee* previous = NULL;
	while (current != NULL) {
		if (current->id == id) {
			if (previous == NULL) {
				*head = current->next;
			}
			else {
				previous->next = current->next;
			}
			free(current);
			printf("   ����� � i������i���i���� ������� %d ��������!\n", id);
			return;
		}
		previous = current;
		current = current->next;
	}
	printf("   ����� � i������i���i���� ������� %d �� ��������!\n", id);
}



// �����i� ��� ��������� ��i� �����i�
void displayRecords(Employee* head) {
	if (head == NULL) {
		printf("   ���� ����� �������!\n");
		return;
	}
	Employee* current = head;
	printf("   ������ �����i�:\n");
	while (current != NULL) {
		printf("  --------------------------\n");
		printf("   ID: %d\n", current->id);
		printf("   ��i�����, i�'� �� �� �������i: %s\n", current->name);
		printf("   ������: %s\n", current->post);
		printf("   ���� ��������� �� ������: %d %d %d\n", current->hire_date[0],
			current->hire_date[1], current->hire_date[2]);
		printf("   �����i��� �����: %.2f\n", current->salary);
		printf("  --------------------------\n");
		current = current->next;
	}
}



// �����i� ��� ��i�� ������
void modifyRecord(Employee* head, int id) {
	Employee* current = head;
		while (current != NULL) {
			if (current->id == id) {
				getchar();
				printf("   ����i�� ���� ��i�����, i�'� �� �� �������i ��i����i�����: ");
				fgets(current->name, sizeof(current->name), stdin);
				current->name[strcspn(current->name, "\n")] = '\0';
				printf("   ����i�� ���� ������ ��i����i�����: ");
				fgets(current->post, sizeof(current->post), stdin);
				current->post[strcspn(current->post, "\n")] = '\0';
				printf("   ����i�� ���� ���� ��������� �� ������ (������: �� �� ����): ");
				scanf("%d %d %d", &current->hire_date[0], &current->hire_date[1],
					&current->hire_date[2]);
				printf("   ����i�� ���� �����i��� ����� ��i����i�����: ");
				scanf("%f", &current->salary);
				printf("   ����� � i������i���i���� ������� %d ��i����!\n", id);
				return;
			}
			current = current->next;
		}
	printf("   ����� � i������i���i���� ������� %d �� ��������!\n", id);
}



// ���������� ���� �����
void saveDatabase(Employee* head, const char* filename) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		printf("   ������� ��� �������i �����!\n");
		return;
	}
	Employee* current = head;
	while (current != NULL) {
		fwrite(current, sizeof(Employee), 1, file);
		current = current->next;
	}
	fclose(file);
	printf("   ���� ����� ��������� � ����i %s\n", filename);
}


// ��i������� ���'��i, ����������� �i� ��'����� ������
void freeMemory(Employee* head) {
	Employee* current = head;
	Employee* next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
}
