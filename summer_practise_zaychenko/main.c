/**
* @file rr3.c
* @author Зайченко Д.І. , гр. 515і, варіант 1
* @date 29 травня 2023
* @brief Розрахункова робота
*
* База даних студентів
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "functions.h"

int main() {
	Config config;
	char configFileName[100];
	// Отримання назви виконуваного файлу
	char executableName[100];
	// Отримання повного шляху до виконуваного файлу
	// і використання лише імені файлу зі шляху
	snprintf(executableName, sizeof(executableName), "%s", __FILE__);
	// Видалення розширення виконуваного файлу (розширення .exe)
	char* dot = strrchr(executableName, '.');
	if (dot != NULL) {
		*dot = '\0';
	}
	// Створення імені конфігураційного файлу з розширенням .cfg
	snprintf(configFileName, sizeof(configFileName), "%s.cfg", executableName);
	FILE* file = fopen(configFileName, "r");
	char license_key[50];
	if (file != NULL) {
		// Файл конфігурації вже існує, читаємо з нього дані
		fscanf(file, "DB: %s\n", config.dbFileName);
		fscanf(file, "KEY: %s\n", config.licenseKey);
		fclose(file);
		printf("Config file loaded.\n");
		printf("DB: %s\n", config.dbFileName);
		printf("KEY: %s\n", config.licenseKey);
	}
	else {
		// Файл конфігурації не існує, створюємо новий
		initializeConfig(&config);
		// Зберігаємо конфігурацію до файлу
		saveConfig(&config, configFileName);
		printf("Config file created and saved.\n");
		printf("DB: %s\n", config.dbFileName);
		printf("KEY: %s\n", config.licenseKey);
	}
	Student* database = NULL;
	int size = 0;
	int nextId = 1;
	int choice;
	char filename[50];
	if (strcmp(filename, "-") != 0) {
		loadDatabase(&database, &size, &nextId, config.dbFileName);
	}
	while (1) {
		printf("\n--- Menu ---\n");
		printf("1. Add record\n");
		printf("2. Delete record\n");
		printf("3. Display records\n");
		printf("4. Modify record\n");
		printf("5. Save database\n");
		printf("6. Export database to CSV\n");
		printf("7. Search by last name\n");
		printf("8. List records with above average grades\n");
		printf("9. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			addRecord(&database, &size, &nextId);
			break;
		case 2:
			deleteRecord(database, size);
			break;
		case 3:
			displayRecords(database, size);
			break;
		case 4:
			modifyRecord(database, size);
			break;
		case 5:
			printf("Enter the filename to save the database: ");
			scanf("%s", filename);
			saveDatabase(database, size, filename);
			break;
		case 6:
			printf("Enter the filename to export the database to CSV: ");
			scanf("%s", filename);
			exportToCSV(database, size, filename);
			break;
		case 7:
			searchByLastName(database, size);
			break;
		case 8:
			listAboveAverage(database, size);
			break;
		case 9:
			saveDatabase(database, size, "database.bin");
			free(database);
			printf("Exiting...\n");
			return 0;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	}
	saveDatabase(database, size, nextId, config.dbFileName);
	return 0;
}