﻿#include <stdio.h>
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

struct Flight flights[MAX_FLIGHTS];
int numFlights = 0;

void addFlight() {
    if (numFlights >= MAX_FLIGHTS) {
        printf("Неможливо додати більше рейсів. База заповнена.\n");
        return;
    }

    struct Flight newFlight = { "", "", 0, "", 0 };
    // Код для введення даних нового рейсу
    printf("Введіть пункт відправлення: ");
    scanf("%s", newFlight.departure);
    printf("Введіть пункт призначення: ");
    scanf("%s", newFlight.destination);
    printf("Введіть номер рейсу: ");
    scanf("%d", &newFlight.flightNumber);
    printf("Введіть тип літака: ");
    scanf("%s", newFlight.aircraftType);
    printf("Введіть кількість місць у літаку: ");
    scanf("%d", &newFlight.seats);

    flights[numFlights++] = newFlight;

    printf("Рейс успішно додано.\n");

    // Оновлення файлу
    FILE* file = fopen("flights.txt", "a");
    if (file == NULL) {
        printf("Помилка відкриття файлу.\n");
        return;
    }

    fprintf(file, "%s;%s;%d;%s;%d\n", newFlight.departure, newFlight.destination, newFlight.flightNumber, newFlight.aircraftType, newFlight.seats);

    fclose(file);
}

void deleteFlight() {
    int flightNumber;
    printf("Введіть номер рейсу для видалення: ");
    scanf("%d", &flightNumber);

    int found = 0;
    for (int i = 0; i < numFlights; i++) {
        if (flights[i].flightNumber == flightNumber) {
            found = 1;
            for (int j = i; j < numFlights - 1; j++) {
                flights[j] = flights[j + 1];
            }
            numFlights--;
            printf("Рейс було успішно видалено.\n");
            break;
        }
    }

    if (!found) {
        printf("Рейс не знайдено.\n");
    }

    // Оновлення файлу
    FILE* file = fopen("flights.txt", "w");
    if (file == NULL) {
        printf("Помилка відкриття файлу.\n");
        return;
    }

    for (int i = 0; i < numFlights; i++) {
        fprintf(file, "%s;%s;%d;%s;%d\n", flights[i].departure, flights[i].destination, flights[i].flightNumber, flights[i].aircraftType, flights[i].seats);
    }

    fclose(file);
}

void displayFlights() {
    printf("Список рейсів:\n");
    printf("-----------------------------------------------------------------------\n");
    printf("Відправлення\tПризначення\tНомер рейсу\tТип літака\tСидіння\n");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < numFlights; i++) {
        printf("%s\t\t%s\t\t%d\t\t%s\t\t%d\n",
            flights[i].departure,
            flights[i].destination,
            flights[i].flightNumber,
            flights[i].aircraftType,
            flights[i].seats);
    }
    printf("-----------------------------------------------------------------------\n");
}

void modifyFlight() {
    int flightNumber;
    printf("Введіть номер рейсу для редагування: ");
    scanf("%d", &flightNumber);

    int found = 0;
    for (int i = 0; i < numFlights; i++) {
        if (flights[i].flightNumber == flightNumber) {
            found = 1;
            printf("Рейс знайдено.\n");
            printf("Виберіть, які характеристики рейсу потрібно змінити:\n");
            printf("1. Пункт відправлення\n");
            printf("2. Пункт призначення\n");
            printf("3. Тип літака\n");
            printf("4. Кількість місць в літаку\n");
            printf("0. Вихід без змін\n");
            printf("Введіть номер команди: ");
            int choice;
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Введіть новий пункт відправлення: ");
                scanf("%s", flights[i].departure);
                break;
            case 2:
                printf("Введіть новий пункт призначення: ");
                scanf("%s", flights[i].destination);
                break;
            case 3:
                printf("Введіть новий тип літака: ");
                scanf("%s", flights[i].aircraftType);
                break;
            case 4:
                printf("Введіть нову кількість місць в літаку: ");
                scanf("%d", &flights[i].seats);
                break;
            case 0:
                printf("Вихід без змін.\n");
                return;
            default:
                printf("Некоректний вибір.\n");
                return;
            }

            printf("Рейс успішно відредаговано.\n");
            break;
        }
    }

    if (!found) {
        printf("Рейс не знайдено.\n");
    }

    // Оновлення файлу
    FILE* file = fopen("flights.txt", "w");
    if (file == NULL) {
        printf("Помилка відкриття файлу.\n");
        return;
    }

    for (int i = 0; i < numFlights; i++) {
        fprintf(file, "%s;%s;%d;%s;%d\n", flights[i].departure, flights[i].destination, flights[i].flightNumber, flights[i].aircraftType, flights[i].seats);
    }

    fclose(file);
}

void searchByDestination() {
    char destination[50];
    printf("Введіть пункт призначення: ");
    scanf("%s", destination);

    printf("Рейси до %s:\n", destination);
    printf("-----------------------------------------\n");
    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i].destination, destination) == 0) {
            printf("Номер рейсу: %d, Тип літака: %s\n",
                flights[i].flightNumber,
                flights[i].aircraftType);
        }
    }
    printf("-----------------------------------------\n");
}

void searchByAircraftType() {
    char aircraftType[50];
    printf("Введіть тип літака: ");
    scanf("%s", aircraftType);

    printf("Рейси за типом літака %s:\n", aircraftType);
    printf("-----------------------------------------\n");
    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i].aircraftType, aircraftType) == 0) {
            printf("Номер рейсу: %d, Пункт призначення: %s\n",
                flights[i].flightNumber,
                flights[i].destination);
        }
    }
    printf("-----------------------------------------\n");
}

int main() {
    setlocale(LC_ALL, "Ukr");
    int choice;

    // Зчитування даних з файлу
    FILE* file = fopen("flights.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            struct Flight newFlight;
            sscanf(line, "%[^;];%[^;];%d;%[^;];%d", newFlight.departure, newFlight.destination, &newFlight.flightNumber, newFlight.aircraftType, &newFlight.seats);
            flights[numFlights++] = newFlight;
        }
        fclose(file);
    }

    while (1) {
        printf("\n");
        printf("Функції керування базою даних рейсів\n");
        printf("-------------------------------------\n");
        printf("1. Додати рейс\n");
        printf("2. Видалити рейс\n");
        printf("3. Показати рейси\n");
        printf("4. Редагувати рейс\n");
        printf("5. Пошук рейсів за пунктом призначення\n");
        printf("6. Пошук рейсів за типом літака\n");
        printf("0. Вихід\n");
        printf("-------------------------------------\n");
        printf("Введіть номер команди: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("Вихід з програми...\n");
            exit(0);
        case 1:
            addFlight();
            break;
        case 2:
            deleteFlight();
            break;
        case 3:
            displayFlights();
            break;
        case 4:
            modifyFlight();
            break;
        case 5:
            searchByDestination();
            break;
        case 6:
            searchByAircraftType();
            break;
        default:
            printf("Неправильні введені дані. Введіть номер з запропонованих команд.\n");
            break;
        }
    }

    return 0;
}