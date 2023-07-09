/*
* @file main.c
* @author Півонос.О.І.,гр. 515і
* @date 7 липня 2023
* @brief Практична робота, варіант 14
*
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Header.h"
#define scanf scanf_s
#define MAX_RECORDS 100


int checkLicenseKey(const char* key);
void addRecord(Payment** database, int* numRecords, FILE* file);
void deleteRecord(Payment** database, int* numRecords, int recordId, FILE* file);
void viewRecords(Payment* database, int numRecords);
void modifyRecord(Payment* database, int numRecords, int recordId, FILE* file);
void viewPaymentsByAccount(Payment* database, int numRecords, int accountNumber);
void viewPaymentsByPurpose(Payment* database, int numRecords, const char* searchText);

int main(FILE* file) {
    setlocale(LC_ALL, "Ukrainian");
    // Отримання імені виконуваного файлу
    char executableName[50];
    strcpy(executableName, "Practice_OPI.exe");

    // Створення імені конфігураційного файлу
    char configFileName[50];
    strcpy(configFileName, executableName);
    strcat(configFileName, ".cfg");

    // Відкриття конфігураційного файлу для читання
    FILE* configFile = fopen(configFileName, "r");
    if (configFile == NULL) {
        // Конфігураційний файл відсутній, створення нового

        // Створення бази даних
        FILE* file = fopen("Practice_OPI.bin", "wb+");
        if (file == NULL) {
            printf("Помилка створення файлу бази даних!\n");
            return 1;
        }
        fclose(file);

        // Створення конфігураційного файлу
        configFile = fopen(configFileName, "w");
        if (configFile == NULL) {
            printf("Помилка створення конфiгураційного файлу!\n");
            return 1;
        }

        fprintf(configFile, "; Файл бази даних\n");
        fprintf(configFile, "DB = Practice_OPI.bin\n");
        fprintf(configFile, "; Ліцензійний ключ\n");
        fprintf(configFile, "KEY = 01AFC567\n");
        fclose(configFile);

        printf("Створено новий конфiгурацiйний файл та базу даних.\n");
    }
    else {
        // Зчитування конфігураційного файлу

        char line[MAX_RECORDS];
        char dbName[MAX_RECORDS];
        char licenseKey[MAX_RECORDS];
        int foundDB = 0;
        int foundKey = 0;

        while (fgets(line, sizeof(line), configFile) != NULL) {
            // Ігнорування коментарів
            if (line[0] == ';') {
                continue;
            }

            // Зчитування імені бази даних
            if (sscanf(line, "DB = %s", dbName) == 1) {
                foundDB = 1;
            }

            // Зчитування ліцензійного ключа
            if (sscanf(line, "KEY = %s", licenseKey) == 1) {
                foundKey = 1;
            }
        }

        fclose(configFile);

        if (!foundDB) {
            printf("Iм'я файлу бази даних не вказано в конфiгурацiйному файлi.\n");
            return 1;
        }

        if (!foundKey) {
            printf("Лiцензiйний ключ не вказано в конфiгураційному файлi.\n");
            return 1;
        }

        // Перевірка ліцензійного ключа
        if (!checkLicenseKey(licenseKey)) {
            printf("Некоректний лiцензiйний ключ. Доступ заборонено.\n");
            return 1;
        }

        printf("Зчитано конфiгурацiйний файл. База даних: %s, Лiцензiйний ключ: %s\n", dbName, licenseKey);
    }

    Payment* database = NULL;
    int numRecords = 0;

    file = fopen("Practice_OPI.bin", "ab+");

    // Зчитування даних із файлу при запуску програми
    Payment payment;
    while (fread(&payment, sizeof(Payment), 1, file) == 1) {
        numRecords++;
        database = (Payment*)realloc(database, numRecords * sizeof(Payment));
        database[numRecords - 1] = payment;
    }

    while (1) {
        printf("\nМеню:\n");
        printf("1. Додати запис\n");
        printf("2. Видалити запис\n");
        printf("3. Переглянути записи\n");
        printf("4. Змiнити запис\n");
        printf("5. Вивести платежi за заданим рахунком\n");
        printf("6. Вивести платежi за заданим призначенням\n");
        printf("7. Вийти\n");
        printf("Ваш вибiр: ");

        int choice;
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            addRecord(&database, &numRecords, file);
            break;
        case 2: {
            int recordId;
            printf("Введiть iдентифiкацiйний номер запису для видалення: ");
            scanf("%d", &recordId);
            deleteRecord(&database, &numRecords, recordId, file);
            break;
        }
        case 3:
            viewRecords(database, numRecords);
            break;
        case 4: {
            int recordId;
            printf("Введiть iдентифiкацiйний номер запису для змiни: ");
            scanf("%d", &recordId);
            modifyRecord(database, numRecords, recordId, file);
            break;
        }
        case 5: {
            int accountNumber;
            printf("Введiть номер рахунку: ");
            scanf("%d", &accountNumber);
            viewPaymentsByAccount(database, numRecords, accountNumber);
            break;
        }
        case 6: {
            char searchText[100];
            printf("Введiть текст для пошуку в призначеннi платежу: ");
            fgets(searchText, sizeof(searchText), stdin);
            searchText[strcspn(searchText, "\n")] = '\0';
            viewPaymentsByPurpose(database, numRecords, searchText);
            break;
        }
        case 7:
            fclose(file);
            free(database);
            return 0;
        default:
            printf("Невiрний вибiр. Спробуйте ще раз.\n");
        }
    }
}
