/*
* @file   MainPractice.cpp
* @author Хоменко А.В., гр. 515i
* @date   10 липня 2023
* @brief  Практична робота. Варіант 4.
*
* База даних авіарейсів
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Functions.h"

int main() {
    setlocale(LC_ALL, "Ukr");
    int choice;
    openFile(); // Зчитування даних з файлу

    while (1) {
        printf("\n");
        printf("Функцiї керування базою даних рейсiв\n");
        printf("-------------------------------------\n");
        printf("1. Додати рейс\n");
        printf("2. Видалити рейс\n");
        printf("3. Показати рейси\n");
        printf("4. Редагувати рейс\n");
        printf("5. Пошук рейсiв за пунктом призначення\n");
        printf("6. Пошук рейсiв за типом лiтака\n");
        printf("0. Вихiд\n");
        printf("-------------------------------------\n");
        printf("Введiть номер команди: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            printf("Вихiд з програми...\n");
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
            printf("Неправильнi введенi данi. Введiть номер з запропонованих команд.\n");
            break;
        }
    }

    return 0;
}