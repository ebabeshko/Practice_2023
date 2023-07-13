#include "functions.h"

void config_check(const char* fname, char* bname, char* key) {
	FILE* fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("\n   Конфiгурацiйний файл не знайдено.\n   Конфiгурацiйний файл та нову базу даних створено.\n");
		strcpy(bname, "../Practice/new_base.dat");
		keygen(fname, bname, key);
		printf("   Новий лiцензiйний ключ: %s\n", key);

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



Employee* load_database(const char* bname) {
	FILE* file = fopen(bname, "rb");
	if (file == NULL) {
		printf("   Помилка при вiдкриттi файлу!\n");
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
	printf("   Базу даних завантажено з файлу %s\n", bname);
	return head;
}

void add_record(Employee** head) {
	Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
	getchar();
	printf("   Введiть ПiБ спiвробiтника: ");
	fgets(newEmployee->name, sizeof(newEmployee->name), stdin);
	newEmployee->name[strcspn(newEmployee->name, "\n")] = '\0';
	printf("   Введiть посаду спiвробiтника: ");
	fgets(newEmployee->post, sizeof(newEmployee->post), stdin);
	newEmployee->post[strcspn(newEmployee->post, "\n")] = '\0';
	printf("   Введiть дату прийняття на роботу (формат: ДД ММ РРРР): ");
	scanf("%d %d %d", &newEmployee->hire_date[0], &newEmployee->hire_date[1],
		&newEmployee->hire_date[2]);
	printf("   Введiть заробiтну плату спiвробiтника: ");
	scanf("%f", &newEmployee->salary);
	// Очищення вхiдного буфера
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
	printf("   Запис успiшно додано!\n");
}



// Функцiя для видалення запису
void delete_record(Employee** head, int id) {
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
			printf("   Запис з iдентифiкацiйним номером %d видалено!\n", id);
			return;
		}
		previous = current;
		current = current->next;
	}
	printf("   Запис з iдентифiкацiйним номером %d не знайдено!\n", id);
}



// Функцiя для перегляду всiх записiв
void display_records(Employee* head) {
	if (head == NULL) {
		printf("   База даних порожня!\n");
		return;
	}
	Employee* current = head;
	printf("   Список записiв:\n");
	while (current != NULL) {
		printf("  --------------------------\n");
		printf("   ID: %d\n", current->id);
		printf("   Прiзвище, iм'я та по батьковi: %s\n", current->name);
		printf("   Посада: %s\n", current->post);
		printf("   Дата прийняття на роботу: %d %d %d\n", current->hire_date[0],
			current->hire_date[1], current->hire_date[2]);
		printf("   Заробiтна плата: %.2f\n", current->salary);
		printf("  --------------------------\n");
		current = current->next;
	}
}



// Функцiя для змiни запису
void modify_record(Employee* head, int id) {
	Employee* current = head;
	while (current != NULL) {
		if (current->id == id) {
			getchar();
			printf("   Введiть нове прiзвище, iм'я та по батьковi спiвробiтника: ");
			fgets(current->name, sizeof(current->name), stdin);
			current->name[strcspn(current->name, "\n")] = '\0';
			printf("   Введiть нову посаду спiвробiтника: ");
			fgets(current->post, sizeof(current->post), stdin);
			current->post[strcspn(current->post, "\n")] = '\0';
			printf("   Введiть нову дату прийняття на роботу (формат: ДД ММ РРРР): ");
			scanf("%d %d %d", &current->hire_date[0], &current->hire_date[1],
				&current->hire_date[2]);
			printf("   Введiть нову заробiтну плату спiвробiтника: ");
			scanf("%f", &current->salary);
			printf("   Запис з iдентифiкацiйним номером %d змiнено!\n", id);

			return;
		}
		current = current->next;
	}
	printf("   Запис з iдентифiкацiйним номером %d не знайдено!\n", id);
}



// Збереження бази даних
void save_database(Employee* head, const char* fname) {
	FILE* file = fopen(fname, "wb");
	if (file == NULL) {
		printf("   Помилка при вiдкриттi файлу!\n");
		return;
	}
	Employee* current = head;
	while (current != NULL) {
		fwrite(current, sizeof(Employee), 1, file);
		current = current->next;
	}
	fclose(file);
	printf("   Базу даних збережено!\n");
}


// Звiльнення пам'ятi, використаної пiд зв'язний список
void free_memory(Employee* head) {
	Employee* current = head;
	Employee* next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
}


void export_cvs(Employee* head) {
	char fname[50];
	printf("   Введiть назву файлу експорту (без розширення): ");
	scanf("%49s", fname);

	char filepath[100];
	sprintf(filepath, "../Practice/%s.csv", fname);

	FILE* file = fopen(filepath, "w");
	if (file == NULL) {
		printf("   Помилка при вiдкриттi файлу %s\n", filepath);
		return;
	}

	Employee* current = head;
	while (current != NULL) {
		fprintf(file, "%d; %s; %s; %d %d %d; %.2f\n", current->id, current->name, current->post,
			current->hire_date[0], current->hire_date[1], current->hire_date[2], current->salary);
		current = current->next;
	}

	fclose(file);
	printf("   Базу даних збережено у файлi %s (CSV формат)\n", filepath);
}

void export_dat(Employee* head) {
	char fname[50];
	printf("   Введiть назву файлу експорту (без розширення): ");
	scanf("%49s", fname);

	char filepath[100];
	sprintf(filepath, "../Practice/%s.dat", fname);

	FILE* file = fopen(filepath, "wb");
	if (file == NULL) {
		printf("   Помилка при вiдкриттi файлу %s\n", filepath);
		return;
	}

	Employee* current = head;
	while (current != NULL) {
		fwrite(current, sizeof(Employee), 1, file);
		current = current->next;
	}

	fclose(file);
	printf("   Базу даних збережено у файлi %s (DAT формат)\n", filepath);
}


void filter_post_date(Employee* head, const char* post, int day, int month, int year) {
	printf("   Спiвробiтники з посадою \"%s\", прийнятi пiсля %02d %02d %04d:\n", post, day, month, year);

	Employee* current = head;
	int foundEmployees = 0;

	while (current != NULL) {
		if (strcmp(current->post, post) == 0 &&
			(current->hire_date[2] > year ||
				(current->hire_date[2] == year && current->hire_date[1] > month) ||
				(current->hire_date[2] == year && current->hire_date[1] == month && current->hire_date[0] > day))) {
			printf("   ID: %d\n", current->id);
			printf("   ПiБ: %s\n", current->name);
			printf("   Посада: %s\n", current->post);
			printf("   Дата прийняття на роботу: %02d %02d %04d\n", current->hire_date[0], current->hire_date[1], current->hire_date[2]);
			printf("   Заробiтна плата: %.2f\n", current->salary);
			printf("\n");
			foundEmployees++;
		}
		current = current->next;
	}

	if (foundEmployees == 0) {
		printf("   Спiвробiтники з посадою \"%s\", прийнятi пiсля %02d %02d %04d не знайденi.\n", post, day, month, year);
	}
}


void filter_salary(Employee* head, float salary_threshold) {
	printf("   Спiвробiтники заробiтна плата яких бiльше %.2f:\n", salary_threshold);

	Employee* current = head;
	int foundEmployees = 0;

	while (current != NULL) {
		if (current->salary > salary_threshold) {
			printf("   ID: %d\n", current->id);
			printf("   ПiБ: %s\n", current->name);
			printf("   Посада: %s\n", current->post);
			printf("   Дата прийняття на роботу: %02d %02d %04d\n", current->hire_date[0], current->hire_date[1], current->hire_date[2]);
			printf("   Заробiтна плата: %.2f\n", current->salary);
			printf("\n");
			foundEmployees++;
		}
		current = current->next;
	}

	if (foundEmployees == 0) {
		printf("   Спiвробiтники заробiтна плата яких бiльше %.2f не знайденi.\n", salary_threshold);
	}
}