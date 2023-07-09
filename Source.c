#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Header.h"
#define scanf scanf_s
#define MAX_RECORDS 100


int checkLicenseKey(const char* key) {
    if (strcmp(key, "01AFC567") == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void addRecord(Payment** database, int* numRecords, FILE* file) {
    Payment newPayment;

    printf("Призначення платежу: ");
    fgets(newPayment.purpose, sizeof(newPayment.purpose), stdin);
    newPayment.purpose[strcspn(newPayment.purpose, "\n")] = '\0';

    printf("Платник: ");
    fgets(newPayment.payer, sizeof(newPayment.payer), stdin);
    newPayment.payer[strcspn(newPayment.payer, "\n")] = '\0';

    printf("Розрахунковий рахунок: ");
    scanf("%d", &newPayment.account_number);

    printf("Сума: ");
    scanf("%f", &newPayment.amount);
    getchar();

    (*numRecords)++;

    *database = (Payment*)realloc(*database, (*numRecords) * sizeof(Payment));
    if (*database == NULL) {
        printf("Помилка: не вдалося виділити пам'ять\n");
        return;
    }

    (*database)[*numRecords - 1] = newPayment;

    // Запись данных в файл
    if (file != NULL) {
        fseek(file, 0, SEEK_END); // Перемещение указателя файла в конец файла
        fwrite(&newPayment, sizeof(Payment), 1, file);
        fflush(file);
    }

    printf("Запис додано успiшно.\n");
}

void deleteRecord(Payment** database, int* numRecords, int recordId, FILE* file) {
    if (recordId < 1 || recordId > *numRecords) {
        printf("Невiрний iдентифiкацiйний номер запису.\n");
        return;
    }

    for (int i = recordId - 1; i < *numRecords - 1; i++) {
        (*database)[i] = (*database)[i + 1];
    }

    (*numRecords)--;

    *database = (Payment*)realloc(*database, (*numRecords) * sizeof(Payment));
    if (*database == NULL && *numRecords > 0) {
        printf("Помилка: не вдалося видiлити пам'ять\n");
        return;
    }

    // Перезапис даних в файл
    if (file != NULL) {
        fclose(file);
        file = fopen("Practice_OPI.bin", "wb"); // Відкриттся файу для перезапису

        for (int i = 0; i < *numRecords; i++) {
            fwrite(&(*database)[i], sizeof(Payment), 1, file);
        }

        fflush(file);
    }

    printf("Запис видалено успiшно.\n");
}

void viewRecords(Payment* database, int numRecords) {
    if (numRecords == 0) {
        printf("База даних порожня.\n");
        return;
    }

    printf("Записи у базi даних:\n");
    for (int i = 0; i < numRecords; i++) {
        printf("Iдентифiкацiйний номер: %d\n", i + 1);
        printf("Призначення платежу: %s\n", database[i].purpose);
        printf("Платник: %s\n", database[i].payer);
        printf("Розрахунковий рахунок: %d\n", database[i].account_number);
        printf("Сума: %.2f\n", database[i].amount);
        printf("\n");
    }
}

void modifyRecord(Payment* database, int numRecords, int recordId, FILE* file) {
    if (recordId < 1 || recordId > numRecords) {
        printf("Невiрний iдентифiкацiйний номер запису.\n");
        return;
    }

    Payment modifiedPayment = database[recordId - 1];

    printf("Поточнi данi для запису %d:\n", recordId);
    printf("Призначення платежу: %s\n", modifiedPayment.purpose);
    printf("Платник: %s\n", modifiedPayment.payer);
    printf("Розрахунковий рахунок: %d\n", modifiedPayment.account_number);
    printf("Сума: %.2f\n", modifiedPayment.amount);

    printf("\nВведiть новi данi для запису %d:\n", recordId);

    printf("Призначення платежу: ");
    getchar();
    fgets(modifiedPayment.purpose, sizeof(modifiedPayment.purpose), stdin);
    modifiedPayment.purpose[strcspn(modifiedPayment.purpose, "\n")] = '\0';

    printf("Платник: ");
    fgets(modifiedPayment.payer, sizeof(modifiedPayment.payer), stdin);
    modifiedPayment.payer[strcspn(modifiedPayment.payer, "\n")] = '\0';

    printf("Розрахунковий рахунок: ");
    scanf("%d", &modifiedPayment.account_number);

    printf("Сума: ");
    scanf("%f", &modifiedPayment.amount);

    database[recordId - 1] = modifiedPayment;

    // Перезапис даних в файл
    if (file != NULL) {
        fseek(file, sizeof(Payment) * (recordId - 1), SEEK_SET);
        fwrite(&modifiedPayment, sizeof(Payment), 1, file);
        fflush(file);
    }

    printf("Запис змiнено успiшно.\n");
}

void viewPaymentsByAccount(Payment* database, int numRecords, int accountNumber) {
    printf("Платежi за рахунком %d:\n", accountNumber);

    int found = 0;
    for (int i = 0; i < numRecords; i++) {
        if (database[i].account_number == accountNumber) {
            printf("Призначення платежу: %s\n", database[i].purpose);
            printf("Платник: %s\n", database[i].payer);
            printf("Розрахунковий рахунок: %d\n", database[i].account_number);
            printf("Сума: %.2f\n", database[i].amount);
            printf("\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Платежi за заданим рахунком вiдсутнi.\n");
    }
}

void viewPaymentsByPurpose(Payment* database, int numRecords, const char* searchText) {
    printf("Платежi з призначенням, що мiстить текст \"%s\":\n", searchText);

    int found = 0;
    for (int i = 0; i < numRecords; i++) {
        if (strstr(database[i].purpose, searchText) != NULL) {
            printf("Призначення платежу: %s\n", database[i].purpose);
            printf("Платник: %s\n", database[i].payer);
            printf("Розрахунковий рахунок: %d\n", database[i].account_number);
            printf("Сума: %.2f\n", database[i].amount);
            printf("\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Платежi з заданим призначенням вiдсутнi.\n");
    }
}
