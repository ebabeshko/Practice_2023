/*
* @file   Functions.cpp
* @author Хоменко А.В., гр. 515i
* @date   10 липня 2023
* @brief  Практична робота. Варіант 4.
*
* База даних авіарейсів
*/

#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


#define MAX_FLIGHTS 100

struct Flight {
    char departure[50];
    char destination[50];
    int flightNumber;
    char aircraftType[50];
    int seats;
};

struct Flight* flights[MAX_FLIGHTS];
int numFlights = 0;

void openFile() {
    // Зчитування даних з файлу
    FILE* file = fopen("flights.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            struct Flight* newFlight = (struct Flight*)malloc(sizeof(struct Flight));
            sscanf(line, "%[^;];%[^;];%d;%[^;];%d", newFlight->departure, newFlight->destination, &(newFlight->flightNumber), newFlight->aircraftType, &(newFlight->seats));
            flights[numFlights++] = newFlight;
        }
        fclose(file);
    }
}

void addFlight() {
    if (numFlights >= MAX_FLIGHTS) {
        printf("Неможливо додати бiльше рейсiв. База заповнена.\n");
        return;
    }

    struct Flight* newFlight = (struct Flight*)malloc(sizeof(struct Flight));
    if (newFlight == NULL) {
        printf("Помилка видiлення пам'ятi.\n");
        return;
    }

    printf("Введiть пункт вiдправлення: ");
    scanf("%s", newFlight->departure);
    printf("Введiть пункт призначення: ");
    scanf("%s", newFlight->destination);
    printf("Введiть номер рейсу: ");
    scanf("%d", &(newFlight->flightNumber));
    printf("Введiть тип лiтака: ");
    scanf("%s", newFlight->aircraftType);
    printf("Введiть кiлькiсть мiсць у лiтаку: ");
    scanf("%d", &(newFlight->seats));

    flights[numFlights++] = newFlight;

    printf("Рейс успiшно додано.\n");

    // Оновлення файлу
    FILE* file = fopen("flights.txt", "a");
    if (file == NULL) {
        printf("Помилка вiдкриття файлу.\n");
        return;
    }

    fprintf(file, "%s;%s;%d;%s;%d\n", newFlight->departure, newFlight->destination, newFlight->flightNumber, newFlight->aircraftType, newFlight->seats);

    fclose(file);
}

void deleteFlight() {
    int flightNumber;
    printf("Введiть номер рейсу для видалення: ");
    scanf("%d", &flightNumber);

    int found = 0;
    for (int i = 0; i < numFlights; i++) {
        if (flights[i]->flightNumber == flightNumber) {
            found = 1;
            free(flights[i]);
            for (int j = i; j < numFlights - 1; j++) {
                flights[j] = flights[j + 1];
            }
            numFlights--;
            printf("Рейс було успiшно видалено.\n");
            break;
        }
    }

    if (!found) {
        printf("Рейс не знайдено.\n");
    }

    // Оновлення файлу
    FILE* file = fopen("flights.txt", "w");
    if (file == NULL) {
        printf("Помилка вiдкриття файлу.\n");
        return;
    }

    for (int i = 0; i < numFlights; i++) {
        fprintf(file, "%s;%s;%d;%s;%d\n", flights[i]->departure, flights[i]->destination, flights[i]->flightNumber, flights[i]->aircraftType, flights[i]->seats);
    }

    fclose(file);
}

void displayFlights() {
    printf("Список рейсiв:\n");
    printf("-----------------------------------------------------------------------\n");
    printf("Вiдправлення\tПризначення\tНомер рейсу\tТип лiтака\tСидiння\n");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < numFlights; i++) {
        printf("%s\t\t%s\t\t%d\t\t%s\t\t%d\n",
            flights[i]->departure,
            flights[i]->destination,
            flights[i]->flightNumber,
            flights[i]->aircraftType,
            flights[i]->seats);
    }
    printf("-----------------------------------------------------------------------\n");
}

void modifyFlight() {
    int flightNumber;
    printf("Введiть номер рейсу для редагування: ");
    scanf("%d", &flightNumber);

    int found = 0;
    for (int i = 0; i < numFlights; i++) {
        if (flights[i]->flightNumber == flightNumber) {
            found = 1;
            printf("Рейс знайдено.\n");
            printf("Виберiть, якi характеристики рейсу потрiбно змiнити:\n");
            printf("1. Пункт вiдправлення\n");
            printf("2. Пункт призначення\n");
            printf("3. Тип лiтака\n");
            printf("4. Кiлькiсть мiсць в лiтаку\n");
            printf("0. Вихiд без змiн\n");
            printf("Введiть номер команди: ");
            int choice;
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Введiть новий пункт вiдправлення: ");
                scanf("%s", flights[i]->departure);
                break;
            case 2:
                printf("Введiть новий пункт призначення: ");
                scanf("%s", flights[i]->destination);
                break;
            case 3:
                printf("Введiть новий тип лiтака: ");
                scanf("%s", flights[i]->aircraftType);
                break;
            case 4:
                printf("Введiть нову кiлькiсть мiсць в лiтаку: ");
                scanf("%d", &(flights[i]->seats));
                break;
            case 0:
                printf("Вихiд без змiн.\n");
                return;
            default:
                printf("Некоректний вибiр.\n");
                return;
            }

            printf("Рейс успiшно вiдредаговано.\n");
            break;
        }
    }

    if (!found) {
        printf("Рейс не знайдено.\n");
    }

    // Оновлення файлу
    FILE* file = fopen("flights.txt", "w");
    if (file == NULL) {
        printf("Помилка вiдкриття файлу.\n");
        return;
    }

    for (int i = 0; i < numFlights; i++) {
        fprintf(file, "%s;%s;%d;%s;%d\n", flights[i]->departure, flights[i]->destination, flights[i]->flightNumber, flights[i]->aircraftType, flights[i]->seats);
    }

    fclose(file);
}

int checkKey() {
    FILE* keyFile = fopen("key.txt", "r");
    if (keyFile == NULL) {
        printf("Помилка вiдкриття файлу з ключем.\n");
        return 0;
    }

    char key[50];
    printf("Введiть ключ: ");
    scanf("%s", key);

    char correctKey[50];
    fgets(correctKey, sizeof(correctKey), keyFile);
    fclose(keyFile);

    // Видалення символу нового рядка з correctKey
    correctKey[strcspn(correctKey, "\n")] = '\0';

    if (strcmp(key, correctKey) == 0) {
        return 1; // Ключ правильний
    }
    else {
        printf("Неправильний ключ.\n");
        return 0; // Ключ неправильний
    }
}

void searchByDestination() {
    if (!checkKey()) {
        return; // Помилка перевiрки ключа, функцiя не виконується
    }
    char destination[50];
    printf("Введiть пункт призначення: ");
    scanf("%s", destination);

    printf("Рейси до %s:\n", destination);
    printf("-----------------------------------------\n");
    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i]->destination, destination) == 0) {
            printf("Номер рейсу: %d, Тип лiтака: %s\n",
                flights[i]->flightNumber,
                flights[i]->aircraftType);
        }
    }
    printf("-----------------------------------------\n");
}

void searchByAircraftType() {
    if (!checkKey()) {
        return; // Помилка перевiрки ключа, функцiя не виконується
    }
    char aircraftType[50];
    printf("Введiть тип лiтака: ");
    scanf("%s", aircraftType);

    printf("Рейси за типом лiтака %s:\n", aircraftType);
    printf("-----------------------------------------\n");
    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i]->aircraftType, aircraftType) == 0) {
            printf("Номер рейсу: %d, Пункт призначення: %s\n",
                flights[i]->flightNumber,
                flights[i]->destination);
        }
    }
    printf("-----------------------------------------\n");
}
