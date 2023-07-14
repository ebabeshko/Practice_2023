/**
* @file functions.cpp
* @author Золотарьов Д.А., гр. 515б, варіант 13
* @date 13 липня 2023
* @brief Навчальна практика
*
* База даних співробітників
*/
// Вимкнення попереджень
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 6031)
// Для зміни мови
#include <Windows.h>
// Основні бібліотеки
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main() {
    // Працездатна зміна мови
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    short user_choice; // (змінна) вибір користувача
    char db_file[50];
    char key[KEY_LENGTH + 1];

    // Читання конфігураційного файлу
    read_config(db_file, key);

    // Перевірка ліцензійного ключа
    if (key[0] == '\0') {
        printf("Ліцензійний ключ не вказано у конфігураційному файлі. Програма недоступна.\n");
        return 0;
    }

    printf("Введіть ліцензійний ключ: ");
    char user_key[KEY_LENGTH + 1];
    scanf("%s", user_key);
    read_config(db_file, key);
    // Перевірка ліцензійного ключа, введеного користувачем
    if (strcmp(user_key, key) == 0) {
        printf("Ліцензійний ключ вірний. Усі функції доступні.\n");
    }
    else {
        printf("Невірний ліцензійний ключ. Деякі функції будуть недоступні.\n");
    }

    do {
        printf("\n========== Меню ==========\n");
        printf("1. Додати персону\n");
        printf("2. Видалити персону\n");
        printf("3. Показати усіх\n");
        printf("4. Вивести співробітників заданої посади, прийнятих після заданої дати ");
        if (strcmp(user_key, key) != 0) {
            printf("(LICENSE ONLY)\n");
        }
        else {
            printf("\n");
        }
        printf("5. Вивести співробітників зарплата яких вища заданої ");
        if (strcmp(user_key, key) != 0) {
            printf("(LICENSE ONLY)\n");
        }
        else {
            printf("\n");
        }
        printf("6. Зберегти базу даних у файл ");
        if (strcmp(user_key, key) != 0) {
            printf("(LICENSE ONLY)\n");
        }
        else {
            printf("\n");
        }
        printf("7. Експортувати базу даних у CSV файл ");
        if (strcmp(user_key, key) != 0) {
            printf("(LICENSE ONLY)\n");
        }
        else {
            printf("\n");
        }
        printf("8. Змінити налаштування конфігураційного файлу ");
        if (strcmp(user_key, key) != 0) {
            printf("(LICENSE ONLY)\n");
        }
        else {
            printf("\n");
        }
        printf("9. Змінити запис ");
        if (strcmp(user_key, key) != 0) {
            printf("(LICENSE ONLY)\n");
        }
        else {
            printf("\n");
        }
        printf("10. Вийти з програми\n");
        printf("===========================\n");
        printf("Оберіть варіант дії: ");
        scanf("%hd", &user_choice);

        switch (user_choice) {
        case 1:
            add_person(db_file);
            break;
        case 2:
            delete_person(db_file);
            break;
        case 3:
            display_all(db_file);
            break;
        case 4:
            if (strcmp(user_key, key) == 0) {
                display_by_position_and_date(db_file, key);
            }
            else {
                printf("Дана функція доступна тільки з валідним ліцензійним ключем.\n");
            }
            break;
        case 5:
            if (strcmp(user_key, key) == 0) {
                display_by_salary(db_file, key);
            }
            else {
                printf("Дана функція доступна тільки з валідним ліцензійним ключем.\n");
            }
            break;
        case 6:
            if (strcmp(user_key, key) == 0) {
                save_database(db_file, key);
            }
            else {
                printf("Дана функція доступна тільки з валідним ліцензійним ключем.\n");
            }
            break;
        case 7:
            if (strcmp(user_key, key) == 0) {
                export_database(db_file, key);
            }
            else {
                printf("Дана функція доступна тільки з валідним ліцензійним ключем.\n");
            }
            break;
        case 8:
            if (strcmp(user_key, key) == 0) {
                change_config();
            }
            else {
                printf("Дана функція доступна тільки з валідним ліцензійним ключем.\n");
            }
            break;
        case 9:
            if (strcmp(user_key, key) == 0) {
                modify_person(db_file, key);
            }
            else {
                printf("Дана функція доступна тільки з валідним ліцензійним ключем.\n");
            }
            break;
        case 10:
            printf("Вихід з програми.\n");
            break;
        default:
            printf("Невірний вибір. Спробуйте ще раз.\n");
            break;
        }
    } while (user_choice != 10);

    return 0;
}
