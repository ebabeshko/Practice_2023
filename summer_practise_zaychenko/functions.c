#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

bool readConfig(Config* config, const char* configFileName) {
	FILE* file = fopen(configFileName, "r");
	if (file == NULL) {
		return false;
	}
	char line[100];
	while (fgets(line, sizeof(line), file) != NULL) {
		char key[50];
		char value[50];
		sscanf(line, "%s = %s", key, value);
		if (strcmp(key, "DB") == 0) {
			strcpy(config->dbFileName, value);
		}
		else if (strcmp(key, "KEY") == 0) {
			strcpy(config->licenseKey, value);
		}
	}
	fclose(file);
	return true;
}
void saveConfig(const Config* config, const char* fileName) {
	FILE* file = fopen(fileName, "w");
	if (file != NULL) {
		fprintf(file, "DB: %s\n", config->dbFileName);
		fprintf(file, "KEY: %s\n", config->licenseKey);
		fclose(file);
	}
}
// Задаємо назву бази даних за замовчуванням
void initializeConfig(Config* config) {
	strcpy(config->dbFileName, "new_base");
	char licenseKey[LICENSE_KEY_SIZE + 1];
	const char charset[] =
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	const int charsetSize = sizeof(charset) - 1;
	srand(time(NULL));
	for (int i = 0; i < LICENSE_KEY_SIZE; i++) {
		int index = rand() % charsetSize;
		licenseKey[i] = charset[index];
	}
	licenseKey[LICENSE_KEY_SIZE] = '\0';
	strcpy(config->licenseKey, licenseKey);
}
void addRecord(Student** database, int* size, int* nextId) {
	// Перевірка наявності видалених записів
	for (int i = 0; i < *size; i++) {
		if ((*database)[i].deleted) {
			Student* deletedRecord = &((*database)[i]);
			deletedRecord->deleted = 0; // Встановлюємо deleted в 0 для заміненого запису
			printf("Enter name: ");
			scanf(" %[^\n]s", deletedRecord->name);
			printf("Enter group: ");
			scanf("%d", &(deletedRecord->group));
			printf("Enter grades (separated by spaces): ");
			for (int j = 0; j < 10; j++) {
				scanf("%d", &(deletedRecord->grades[j]));
			}
			printf("Record added with ID: %d\n", deletedRecord->id);
			return;
		}
	}
	// Якщо немає видалених записів, створюємо новий запис
	(*size)++;
	*database = (Student*)realloc(*database, (*size) * sizeof(Student));
	Student* newRecord = &((*database)[(*size) - 1]);
	newRecord->id = (*nextId)++;
	newRecord->deleted = 0; // Встановлюємо deleted в 0 для нового запису
	printf("Enter name: ");
	scanf(" %[^\n]s", newRecord->name);
	printf("Enter group: ");
	scanf("%d", &(newRecord->group));
	printf("Enter grades (separated by spaces): ");
	for (int i = 0; i < 10; i++) {
		scanf("%d", &(newRecord->grades[i]));
	}
	printf("Record added with ID: %d\n", newRecord->id);
}
void deleteRecord(Student* database, int size) {
	int id;
	printf("Enter ID of record to delete: ");
	scanf("%d", &id);
	int found = 0;
	for (int i = 0; i < size; i++) {
		if (!database[i].deleted && database[i].id == id) {
			database[i].deleted = 1; // Встановлюємо deleted в 1 для видаленого запису
			printf("Record with ID %d deleted.\n", id);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("No record found with ID %d.\n", id);
	}
}
void displayRecords(Student* database, int size) {
	printf("ID\tName\t\tGroup\tGrades\n");
	for (int i = 0; i < size; i++) {
		if (!database[i].deleted) {
			printf("%d\t%s\t%d\t", database[i].id, database[i].name, database[i].group);
			for (int j = 0; j < 10; j++) {
				printf("%d ", database[i].grades[j]);
			}
			printf("\n");
		}
	}
}
void modifyRecord(Student* database, int size) {
	int id;
	printf("Enter ID of record to modify: ");
	scanf("%d", &id);
	int found = 0;
	for (int i = 0; i < size; i++) {
		if (!database[i].deleted && database[i].id == id) {
			printf("Enter new name: ");
			scanf(" %[^\n]s", database[i].name);
			printf("Enter new group: ");
			scanf("%d", &(database[i].group));
			printf("Enter new grades (separated by spaces): ");
			for (int j = 0; j < 10; j++) {
				scanf("%d", &(database[i].grades[j]));
			}
			printf("Record with ID %d modified.\n", id);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("No record found with ID %d.\n", id);
	}
}
void saveDatabase(Student* database, int size, const char* filename) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		printf("Error opening file for writing.\n");
		return;
	}
	for (int i = 0; i < size; i++) {
		if (!database[i].deleted) {
			fwrite(&(database[i]), sizeof(Student), 1, file);
		}
	}
	fclose(file);
	printf("Database saved to %s.\n", filename);
}
void exportToCSV(Student* database, int size, const char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error opening file for writing.\n");
		return;
	}
	fprintf(file, "ID,Name,Group,Grades\n");
	for (int i = 0; i < size; i++) {
		if (!database[i].deleted) {
			fprintf(file, "%d,%s,%d,", database[i].id, database[i].name,
				database[i].group);
			for (int j = 0; j < 10; j++) {
				fprintf(file, "%d", database[i].grades[j]);
				if (j < 9) {
					fprintf(file, " ");
				}
			}
			fprintf(file, "\n");
		}
	}
	fclose(file);
	printf("Database exported to %s.\n", filename);
}
void searchByLastName(Student* database, int size) {
	char lastName[50];
	printf("Enter last name to search: ");
	scanf(" %[^\n]s", lastName);
	int found = 0;
	printf("ID\tName\t\tGroup\tGrades\n");
	for (int i = 0; i < size; i++) {
		if (!database[i].deleted && strstr(database[i].name, lastName) != NULL) {
			printf("%d\t%s\t%d\t", database[i].id, database[i].name, database[i].group);
			for (int j = 0; j < 10; j++) {
				printf("%d ", database[i].grades[j]);
			}
			printf("\n");
			found = 1;
		}
	}
	if (!found) {
		printf("No records found with last name: %s\n", lastName);
	}
}
void listAboveAverage(Student* database, int size) {
	printf("ID\tName\t\tGroup\tGrades\n");
	int found = 0;
	for (int i = 0; i < size; i++) {
		if (!database[i].deleted) {
			double sum = 0.0;
			for (int j = 0; j < 10; j++) {
				sum += database[i].grades[j];
			}
			double average = sum / 10.0;
			if (average > 75.0) {
				printf("%d\t%s\t%d\t", database[i].id, database[i].name,
					database[i].group);
				for (int j = 0; j < 10; j++) {
					printf("%d ", database[i].grades[j]);
				}
				printf("\n");
				found = 1;
			}
		}
	}
	if (!found) {
		printf("No records found above the average.\n");
	}
}
void loadDatabase(Student** database, int* size, int* nextId, const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Error opening file for reading. Working with empty database\n");
		return;
	}
	*size = 0;
	*nextId = 1;
	while (1) {
		(*size)++;
		*database = (Student*)realloc(*database, (*size) * sizeof(Student));
		Student* record = &((*database)[(*size) - 1]);
		int bytesRead = fread(record, sizeof(Student), 1, file);
		if (bytesRead != 1) {
			break;
		}
		if (record->id >= *nextId) {
			*nextId = record->id + 1;
		}
	}
	fclose(file);
	printf("Database loaded from %s.\n", filename);
}