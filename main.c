/**
* @file main.c
* @author Саділов М.М., гр. 515а, варіант 22
* @date 11 липня 2023
* @brief Навчальна практика
*
* База даних автомобілів
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "module.h"


int main(int argc, char* argv[]) {
    int choice = 0;
    int id=0;
    Record* head = NULL;

    int  configFileCreated = createConfigFile();
    printf("------------------------------------------------\n");
    if (configFileCreated) {
        printf("Конфігураційний файл створений.\n");
    }
    else if (!configFileCreated){
        printf("Конфігураційний файл вже існує.\n");
    }
    else {
        printf("Помилка створення конфігураційного файлу.\n");
    }

    int fileCreated = createDatabaseFile();

    if (fileCreated) {
        printf("Файл бази даних створений.\n");
    }
    else {
        printf("Файл бази даних вже існує.\n");
    }

    int validLicense = checkLicenseKey();

    if (validLicense==0) {
        printf("Ліцензійний ключ є дійсним. Усі функції доступні\n");
    }
    else {
        printf("Ліцензійний ключ відсутній або не дійсний. Програма працює з обмеженнями.\n");
    }
    printf("------------------------------------------------\n");

        // Основна частина програми
    printf("+-----------------------------------------------------------------------------------------------------------------+\n");
    printf("| 1. Додати запис                | ");
    printf("2. Видалити запис                | ");
    printf("3. Переглянути всі записи                   | \n");
    printf("| 4. Змінити запис               | ");
    printf("5. Зберегти базу до файлу        |");
    printf(" 6. Експортувати базу з формату .dat до .csv |\n");
    printf("| 7. Змінити данні у конф. файлі | ");
    printf("8. Фільтр за маркою та регіоном  | ");
    printf("9. Фільтр за діапазоном років та пробігу.   | \n");
    printf("+-----------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                               10. Вийти                                                         |\n");
    printf("+-----------------------------------------------------------------------------------------------------------------+\n");

    while (choice != 10) {
        char state_car_num[9];
        char mark[21];
        int graduation_year;
        int car_mileage, min_year, max_year, min_mileage, max_mileage;
        char vin_code[21];
        int status = 0;
        int id_del, id_changing, result_check, choice_chang=0, choice_config=0;


        printf("Оберіть дію: ");
        scanf("%2d", &choice);
        getchar();

        switch (choice) {
        case 1:
            printf("Для додавання запису введіть такі данні в рядок:\n");
            printf("Держномер автомобіля, Марка, Рік випуску, Пробіг, VIN код: ");
            scanf("%8s%20s%d%d%20s", state_car_num, mark, &graduation_year, &car_mileage, vin_code);
            getchar();
            int result_add = add_record(&head, id, state_car_num, mark, graduation_year, car_mileage, vin_code, status);
            if (result_add == 0) {
                printf("Запис успішно додано\n");
            }
            else if (result_add == 1) {
                printf("Помилка запису. Будь ласка, перевірте введені данні.");
            }
            id++;
            break;
        case 2:
            printf("Введіть id для видалення запису з БД: ");
            scanf("%d", &id_del);
            int result_del = del_record(&head, id_del);
            if (result_del == 0) {
                printf("Запис було успішно видалено. \n");
            }
            else {
                printf("Такого запису не існує. \n");
            }
            break;
        case 3:
            printf("------------БАЗА ДАНИХ-----------\n");
            int result_view = view_records(&head);
            if (result_view == 1) {
                printf("База данних порожня\n");
            }

            break;
        case 4:
            printf("Введіть id запису який потрібно змінити: ");
            scanf("%d", &id_changing);
            getchar();
            result_check = check_record_exists(&head, id_changing);
            if (result_check == 0) {
                printf("Такого запису не існує. \n");
                break;
            }
            char state_car_num_chang[9] = { 0 };
            char mark_chang[21] = { 0 };
            int graduation_year_chang = -1;
            int car_mileage_chang = -1;
            char vin_code_chang[21] = { 0 };
            int status_chang = -1;
            char NEW_KEY[20];
            char NEW_NAME_DAT[20];
            char mark_filtr[20];
            char region_filtr[3];


            printf("1: Держномер автомобіля, 2: Марка, 3: Рік випуску, 4: Пробіг, 5: VIN код, 6: Статус\n");
            while (choice_chang != 7) {
                printf("Виберіть параметр який потрібно змінити (ВИХІД: 7): ");
                scanf("%2d", &choice_chang);
                switch (choice_chang) {
                case 1:
                    printf("Введіть новий держномер автомобіля: ");
                    scanf("%8s", state_car_num_chang);
                    printf("Держномер автомобіля змінено. \n");
                    break;
                case 2:
                    printf("Введіть нову марка: ");
                    scanf("%20s", mark_chang);
                    printf("Марку змінено. \n");
                    break;
                case 3:
                    printf("Введіть новий рік випуску:");
                    scanf("%d", &graduation_year_chang);
                    printf("Рік випуску змінено. \n");
                    break;
                case 4:
                    printf("Введіть новий пробіг автомобіля: ");
                    scanf("%d", &car_mileage_chang);
                    printf("Пробіг автомобіля змінено. \n");
                    break;
                case 5:
                    printf("Введіть новий VIN код: ");
                    scanf("%20s", vin_code_chang);
                    printf("VIN код автомобіля змінено. \n");
                    break;
                case 6:
                    printf("Введіть новий cтатус запису (0 - стандарт, 1 - видалено): ");
                    scanf("%d", &status_chang);
                    printf("Статус запису змінено. \n");
                    break;
                case 7:
                    break;
                default:
                    printf("Ви ввели невідому команду.\n");
                    printf("1: Держномер автомобіля, 2: Марка, 3: Рік випуску, 4: Пробіг, 5: VIN код, 6: Статус\n");
                    break;
                }
            }


            changing_record(&head, id_changing, state_car_num_chang, mark_chang, graduation_year_chang, car_mileage_chang, vin_code_chang, status_chang);

            break;
        case 5:
            if (validLicense != 0) {
                printf("Вибачте, данна функція працює лише за наявності ліцензійного ключа.\n");
                break;
            }
            printf("Базу даних буде збережено у файл, назву якого вказано у конфігураційному файлі\n");
            int result_save = save_list_to_file(&head);
            if (result_save == 0) {
                printf("Данні успішно записано.\n");
            }
            else {
                printf("Помилка збереження даних.\n");
            }
            break;
        case 6:
            if (validLicense != 0) {
                printf("Вибачте, данна функція працює лише за наявності ліцензійного ключа.\n");
                break;
            }
            printf("Конвертуємо файл .dat у формат .csv .\n");
            int result_convert = convert_records_to_csv();
            if (result_convert == 0) {
                printf("Данні успішно конвертовані.\n");
            }
            else {
                printf("Помилка конвертації даних.\n");
            }
            break;
        case 7:
            if (validLicense != 0) {
                printf("Вибачте, данна функція працює лише за наявності ліцензійного ключа.\n");
                break;
            }
            printf("Конфігураційний файл містить два параметри, назву бази даних(1) та ліцензійний ключ(2)\n");
            while (choice_config != 3) {
                printf("Виберіть параметр який потрібно змінити (ВИХІД: 3): ");
                scanf("%2d", &choice_config);
                switch (choice_config) {
                case 1:
                    printf("Введіть нову назву бази даних: ");
                    scanf("%20s", NEW_NAME_DAT);
                    int result_change_config_dat = change_config_value("DB", NEW_NAME_DAT);
                    if (result_change_config_dat == 0) {
                        printf("Назву бази данних успішно змінено.\n");
                    }
                    else {
                        printf("Не вдалось змінити назву бази даних.\n");
                    }
                    break;
                case 2:
                    printf("Введіть новий ліцензійний ключ: ");
                    scanf("%20s", NEW_KEY);
                    int result_change_config_key = change_config_value("KEY", NEW_KEY);
                    if (result_change_config_key == 0) {
                        printf("Ліцензійний ключ успішно змінено.\n");
                        printf("Щоб застосувати налаштування, перезапустіть програму.\n");
                    }
                    else {
                        printf("Не вдалось змінити ліцензійний ключ.\n");
                    }
                    break;
                case 3:
                    break;
                default:
                    break;
                    printf("Ви ввели невідому команду.\n");
                    printf("Конфігураційний файл містить два параметри, назву бази даних(1) та ліцензійний ключ(2)\n");
                }
            }

            break;
        case 8:
            if (validLicense != 0) {
                printf("Вибачте, данна функція працює лише за наявності ліцензійного ключа.\n");
                break;
            }
            printf("Для пошуку за маркою та регіоном(перші 2 літери номеру) укажіть ці дані: ");
            scanf("%20s%2s", mark_filtr, region_filtr);
            printf("-----------------\n");
            int result_filtr_by_brand_and_region = print_cars_by_brand_and_region(head, mark_filtr, region_filtr);
            if (result_filtr_by_brand_and_region == 1) {
                printf("База даних пуста.\n");
            }
            break;
        case 9:
            if (validLicense != 0) {
                printf("Вибачте, данна функція працює лише за наявності ліцензійного ключа.\n");
                break;
            }
            printf("Вкажіть мінімальний та максимальний роки випуску: ");
            scanf("%d%d", &min_year, &max_year);
            printf("Вкажіть мінімальну та максимальну кількість пробігу: ");
            scanf("%d%d", &min_mileage, &max_mileage);
            printf("-----------------\n");
            int result_filtr_by_year_and_mileage = print_cars_by_year_and_mileage(head, min_year, max_year, min_mileage, max_mileage);
            if (result_filtr_by_year_and_mileage != 0) {
                printf("Помилка пошуку. Перевірте корректність вводу данних.\n");
            }
            break;
        case 10:
            break;
        default:
            printf("Ви ввели невідому команду.\n");
            printf("+-----------------------------------------------------------------------------------------------------------------+\n");
            printf("| 1. Додати запис                | ");
            printf("2. Видалити запис                | ");
            printf("3. Переглянути всі записи                   | \n");
            printf("| 4. Змінити запис               | ");
            printf("5. Зберегти базу до файлу        |");
            printf(" 6. Експортувати базу з формату .dat до .csv |\n");
            printf("| 7. Змінити данні у конф. файлі | ");
            printf("8. Фільтр за маркою та регіоном  | ");
            printf("9. Фільтр за діапазоном років та пробігу.   | \n");
            printf("+-----------------------------------------------------------------------------------------------------------------+\n");
            printf("|                                               10. Вийти                                                         |\n");
            printf("+-----------------------------------------------------------------------------------------------------------------+\n");
            break;
        }

    }

    return 0;
}
