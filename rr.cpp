/**
* @file Practice2023.cpp
* @author Попов В. О., гр. 515-а, варіант 24
* @date 9 липня 2023
* @brief Практика
*
* База даних студентів
*/

#include "funcs.h"
#include <locale.h>


int main() {

    setlocale(LC_CTYPE, "ukr");
    int menunum, menu_settings;
    char db[MAX_FILENAME_LENGTH+1];
    char licenseKey[KEY_LENGTH+1];
    char curname[MAX_FILENAME_LENGTH+1];
    printf("Введіть назву файлу (з розширенням .txt) :  -  ");
    fgets(curname, MAX_FILENAME_LENGTH, stdin);
    curname[strcspn(curname, "\n")] = '\0';

    
    FILE* configFile = fopen("funcs.cfg", "r");
    if (configFile == NULL) {
        

        printf("Створено конфігураційний файл та пусту базу даних.\n");
        generation_key();
        strcpy(db, "new_base.dat");
    }

    else {
        
        char line[100];
        while (fgets(line, sizeof(line), configFile) != NULL) {
            if (strstr(line, "DB") != NULL) {
                sscanf(line, "DB = %s", db);
            }
            else if (strstr(line, "KEY") != NULL) {
                sscanf(line, "KEY = %s", licenseKey);
            }
        }
        fclose(configFile);
    }

    
mark:
    if (valid() == true) {
        printf("Некоректний ліцензійний ключ. Деякі функції можуть бути недоступні.\n");
        printf("Доступні дії"
            "\n1. Для заповнення БД введіть - 1"
            "\n2. Для зчитування БД з файлу та виведення на екран - 2"
            "\n3. Для видалення запису з БД введіть - 3"
            "\n4. Для внесення змін у БД введіть - 4"
            "\n5. Для завершення програми введіть - 0"
            "\n Оберіть дію - ");

        while (1) {
            scanf_s("%d", &menunum);
            switch (menunum) {
                case 1:
                    fill(curname);
                    goto mark;
                    break;
                case 2:
                    output(curname);
                    goto mark;
                    break;
                case 3:
                    goto mark;
                    del(curname);
                    break;
                case 4:
                    edit(curname);
                    goto mark;
                    break;
                 case 0:
                    printf("Кінець.");
                    return 0;
                    break;

                default:
                    printf("\nНевірна операція. Повторне введення.\n");
                    goto mark;
                    break;

            }

        }

    }

    else {
        
        printf("Доступні дії"
            "\n1. Для заповнення БД введіть - 1"
            "\n2. Для зчитування БД з файлу та виведення на екран - 2"
            "\n3. Для видалення запису з БД введіть - 3"
            "\n4. Для внесення змін у БД введіть - 4"
            "\n5. Для пошуку за рейтингом, введіть - 5"
            "\n6. Для пошуку товару за річним оборотом,введіть - 6"
            "\n7. Налаштування, введіть - 7 "
            "\n8. Для завершення програми введіть - 0"
            "\n Оберіть дію - ");
        while (1) {
            scanf_s("%d", &menunum);
            switch (menunum) {
            case 1:
                fill(curname);
                goto mark;
                break;
            case 2:
                output(curname);
                goto mark;
                break;
            case 3:
                del(curname);
                goto mark;
                break;
            case 4:
                edit(curname);
                goto mark;
                break;
            case 5:
                rating_search(curname);
                goto mark;
                break;
            case 6:
                annual_turnover(curname);
                goto mark;
                break;
            case 7:
                printf("Налаштування:"
                    "\n Для перейменування файлу, введіть - 1 "
                    "\n Для експорту txt в csv, введіть - 2 "
                    "\n Оберіть дію - ");
                scanf_s("%d", &menu_settings);
              switch (menu_settings) {
                case 1:
                        printf("Після заміни назви, програма завершить роботу.\n");
                        file_change_name(curname);
                        printf("Назву файла успішно змінено. \n");
                        return 0;
                    break;
                case 2:
                    CSV(curname);
                    goto mark;
                    break;
                    default:
                    printf("\nНевірна операція. Повернення на головну сторінку.\n");
                    goto mark;
                    break;
              }
              break;

                case 0:
                printf("Кінець.");
                return 0;
              break;

                default:
                    printf("\nНевірна операція. Повторне введення.\n");
                    goto mark;
                    break;

            }
        }
    }
    return 0;
}
