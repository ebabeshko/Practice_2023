#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "module.h"
#include <stdio.h>

Record* create_record(int id, char* state_car_num, char* mark, int graduation_year, int car_mileage, char* vin_code, int status) {
    Record* new_record = (Record*)malloc(sizeof(Record));
    if (new_record == NULL) {
        return NULL;
    }

    new_record->id = id;
    strcpy(new_record->state_car_num, state_car_num);
    strcpy(new_record->mark, mark);
    new_record->graduation_year = graduation_year;
    new_record->car_mileage = car_mileage;
    strcpy(new_record->vin_code, vin_code);
    new_record->status = status;
    new_record->next = NULL;

    return new_record;
}

// Функція для створення конфігураційного файлу
int createConfigFile() {
    // Отримання імені виконуваного файлу
    char* executableName = "rr"; // Приклад - замініть на власне ім'я

    // Формування імені конфігураційного файлу
    char configFileName[256];
    sprintf(configFileName, "%s.cfg", executableName);

    // Перевірка наявності конфігураційного файлу
    FILE* configFile = fopen(configFileName, "r");
    if (configFile != NULL) {
        fclose(configFile);
        return 0; // Конфігураційний файл вже існує
    }

    // Створення нового конфігураційного файлу
    configFile = fopen(configFileName, "w");
    if (configFile == NULL) {
        return 2; // Помилка створення конфігураційного файлу
    }

    // Запис інформації в конфігураційний файл
    fprintf(configFile, "; Файл бази даних\n");
    fprintf(configFile, "DB = mybd.dat\n");
    fprintf(configFile, "; Ліцензійний ключ\n");
    fprintf(configFile, "KEY = 01AFC567\n");

    fclose(configFile);
    return 1; // Конфігураційний файл успішно створений
}

int createDatabaseFile() {
    // Відкриття конфігураційного файлу
    FILE* configFile = fopen("rr.cfg", "r");
    if (configFile == NULL) {
        // Конфігураційний файл відсутній, створення файла з назвою "new_base.dat"
        FILE* dbFile = fopen("new_base.dat", "w");
        if (dbFile == NULL) {
            return 0; // Помилка створення файлу
        }
        else {
            fclose(dbFile);
            return 1; // Файл створений успішно
        }
    }

    // Читання конфігураційного файлу
    char line[256];
    char* dbFileName = "new_base.dat"; // Назва файла за замовчуванням
    while (fgets(line, sizeof(line), configFile) != NULL) {
        // Ігнорувати коментарі та шукати рядок з назвою файла
        if (line[0] != ';' && strstr(line, "DB") != NULL) {
            char* token = strtok(line, "=");
            if (token != NULL) {
                token = strtok(NULL, "=");
                if (token != NULL) {
                    // Записати назву файла з конфігураційного файлу
                    dbFileName = strtok(token, " \t\n");
                    break;
                }
            }
        }
    }

    fclose(configFile);

    // Перевірка наявності файла
    FILE* dbFile = fopen(dbFileName, "r");
    if (dbFile != NULL) {
        fclose(dbFile);
        return 0; // Файл вже існує
    }

    // Створення нового файла бази даних
    dbFile = fopen(dbFileName, "w");
    if (dbFile == NULL) {
        return 0; // Помилка створення файла
    }

    fclose(dbFile);
    return 1; // Файл створений успішно
}

// Функція перевіряє ключ ліцензійності, виводить 0 якщо ключ пройшов перевірку, та 1 якщо ні.
int checkLicenseKey() {
    // Відкриття конфігураційного файлу
    FILE* configFile = fopen("rr.cfg", "r");
    if (configFile == NULL) {
        return 2;
    }

    // Читання конфігураційного файлу
    char line[256];
    char* licenseKey = NULL;
    while (fgets(line, sizeof(line), configFile) != NULL) {
        // Ігнорувати коментарі та шукати рядок з ліцензійним ключем
        if (line[0] != ';' && strstr(line, "KEY") != NULL) {
            char* token = strtok(line, "=");
            if (token != NULL) {
                token = strtok(NULL, "=");
                if (token != NULL) {
                    // Записати ліцензійний ключ з конфігураційного файлу
                    licenseKey = strtok(token, " \t\n");
                    break;
                }
            }
        }
    }

    fclose(configFile);

    if (licenseKey == NULL) {
        return 2;
    }


    // Перевірка довжини ключа
    if (strlen(licenseKey) != 10) {
        return 1;
    }

    // Перевірка перших двох символів (мають бути літерами)
    if (!((licenseKey[0] >= 'A' && licenseKey[0] <= 'Z') || (licenseKey[0] >= 'a' && licenseKey[0] <= 'z')) ||
        !((licenseKey[1] >= 'A' && licenseKey[1] <= 'Z') || (licenseKey[1] >= 'a' && licenseKey[1] <= 'z'))) {
        return 1;
    }

    // Перевірка наявності тире на третій позиції
    if (licenseKey[2] != '-') {
        return 1;
    }

    // Перевірка решти символів (мають бути цифрами)
    for (int i = 3; i < 10; i++) {
        if (licenseKey[i] < '0' || licenseKey[i] > '9') {
            return 1;
        }
    }

    // Ліцензійний ключ валідний
    return 0;
}


int add_record(Record** head, int id, char* state_car_num, char* mark, int graduation_year, int car_mileage, char* vin_code, int status) {
    Record* new_record = create_record(id, state_car_num, mark, graduation_year, car_mileage, vin_code, status);
    if (new_record == NULL) {
        // Помилка створення запису
        return 1;
    }

    if (*head == NULL) {
        // Список порожній, просто додаємо новий запис
        *head = new_record;
        return 0;
    }

    // Перевіряємо, чи є записи зі статусом 1 і замінюємо перший такий запис
    if ((*head)->status == 1) {
        (*head)->id = new_record->id;
        strcpy((*head)->state_car_num, new_record->state_car_num);
        strcpy((*head)->mark, new_record->mark);
        (*head)->graduation_year = new_record->graduation_year;
        (*head)->car_mileage = new_record->car_mileage;
        strcpy((*head)->vin_code, new_record->vin_code);
        (*head)->status = new_record->status;
        free(new_record);
    }
    else {
        // Шукаємо перший запис зі статусом 1
        Record* current = *head;
        while (current->next != NULL && current->next->status != 1) {
            current = current->next;
        }

        // Додаємо новий запис на потрібну позицію
        new_record->next = current->next;
        current->next = new_record;
    }
    return 0;
}

// Виведення всіх записів у списку
int view_records(Record** head) {
    Record* current = *head;
    if (current == NULL) {
        return 1;
    }
    while (current != NULL) {
        if (current->status == 0) {
            printf("ID: %d\n", current->id);
            printf("Держномер автомобіля: %s\n", current->state_car_num);
            printf("Марка: %s\n", current->mark);
            printf("Рік випуску: %d\n", current->graduation_year);
            printf("Пробіг: %d\n", current->car_mileage);
            printf("VIN код: %s\n", current->vin_code);
            printf("--------------------------------\n");

        }
        current = current->next;
    }
    return 0;
}

int del_record(Record** head, int id) {
    Record* current = *head;

    while (current != NULL) {
        if (current->id == id) {
            current->status = 1;
            return 0;
        }
        current = current->next;

    }
    return 1;
}

int changing_record(Record** head, int id, char* state_car_num, char* mark, int graduation_year, int car_mileage, char* vin_code, int status) {
    Record* current = *head;

    while (current != NULL) {
        if (current->id == id) {
            // Изменение данных записи
            if (state_car_num != NULL) {
                strncpy(current->state_car_num, state_car_num, sizeof(current->state_car_num) - 1);
                current->state_car_num[sizeof(current->state_car_num) - 1] = '\0';
            }
            if (mark != NULL) {
                strncpy(current->mark, mark, sizeof(current->mark) - 1);
                current->mark[sizeof(current->mark) - 1] = '\0';
            }
            if (graduation_year != -1) {
                current->graduation_year = graduation_year;
            }
            if (car_mileage != -1) {
                current->car_mileage = car_mileage;
            }
            if (vin_code != NULL) {
                strncpy(current->vin_code, vin_code, sizeof(current->vin_code) - 1);
                current->vin_code[sizeof(current->vin_code) - 1] = '\0';
            }
            if (status != -1) {
                current->status = status;
            }
            return 0;
        }
        current = current->next;
    }
    return 1;
}

int check_record_exists(Record** head, int id) {
    Record* current = *head;

    while (current != NULL) {
        if (current->id == id) {
            // Запись с указанным идентификатором найдена
            return 1;
        }
        current = current->next;
    }

    // Запись с указанным идентификатором не найдена
    return 0;
}

int save_list_to_file(Record** head) {
    // Открыть конфигурационный файл для чтения
    FILE* config_file = fopen("rr.cfg", "r");
    if (config_file == NULL) {
        return 1;
    }

    // Поиск параметра "DB" в конфигурационном файле
    char line[100];
    char* db_param = NULL;
    while (fgets(line, sizeof(line), config_file) != NULL) {
        if (line[0] == ';' || line[0] == '\n') {
            continue;  // Пропустить комментарии и пустые строки
        }
        if (strncmp(line, "DB", 2) == 0) {
            db_param = strchr(line, '=');
            if (db_param != NULL) {
                db_param++;  // Пропустить знак "="
                break;
            }
        }
    }

    // Закрыть конфигурационный файл
    fclose(config_file);

    if (db_param == NULL) {
        return 1;
    }

    // Удалить пробелы и символы новой строки из названия файла
    char save_file_name[100];
    sscanf(db_param, " %99[^\n]", save_file_name);

    // Открыть файл для записи
    FILE* save_file = fopen(save_file_name, "wb");
    if (save_file == NULL) {
        return 1;
    }

    // Записать список в файл
    Record* current = *head;
    while (current != NULL) {
        // Записать значения в файл
        fprintf(save_file, "%d %s %s %d %d %s %d\n", current->id, current->state_car_num, current->mark,
            current->graduation_year, current->car_mileage, current->vin_code, current->status);

        current = current->next;
    }

    // Закрыть файл
    fclose(save_file);

    return 0;
}

int convert_records_to_csv() {
    // Открыть конфигурационный файл для чтения
    FILE* config_file = fopen("rr.cfg", "r");
    if (config_file == NULL) {
        return 1;
    }

    // Поиск параметра "DB" в конфигурационном файле
    char line[100];
    char* db_param = NULL;
    while (fgets(line, sizeof(line), config_file) != NULL) {
        if (line[0] == ';' || line[0] == '\n') {
            continue;  // Пропустить комментарии и пустые строки
        }
        if (strncmp(line, "DB", 2) == 0) {
            db_param = strchr(line, '=');
            if (db_param != NULL) {
                db_param++;  // Пропустить знак "="
                break;
            }
        }
    }

    // Закрыть конфигурационный файл
    fclose(config_file);

    if (db_param == NULL) {
        return 1;
    }

    // Удалить пробелы и символы новой строки из названия файла
    char save_file_name[100];
    sscanf(db_param, " %99[^\n]", save_file_name);

    // Открыть файл с записями для чтения
    FILE* records_file = fopen(save_file_name, "r");
    if (records_file == NULL) {
        return 1;
    }

    // Создать файл .csv для записи
    char csv_file_name[100];
    snprintf(csv_file_name, sizeof(csv_file_name), "%s.csv", save_file_name);
    FILE* csv_file = fopen(csv_file_name, "w");
    if (csv_file == NULL) {
        fclose(records_file);
        return 1;
    }

    // Прочитать записи из файла и записать в .csv формат
    char record_line[100];
    while (fgets(record_line, sizeof(record_line), records_file) != NULL) {
        // Извлечь значения из строки записи
        int id, graduation_year, car_mileage, status;
        char state_car_num[9], mark[21], vin_code[21];
        sscanf(record_line, "%d %8s %20s %d %d %20s %d",
            &id, state_car_num, mark, &graduation_year, &car_mileage, vin_code, &status);

        // Записать значения в .csv файл
        fprintf(csv_file, "%d;%s;%s;%d;%d;%s;%d\n",
            id, state_car_num, mark, graduation_year, car_mileage, vin_code, status);
    }

    // Закрыть файлы
    fclose(records_file);
    fclose(csv_file);

    return 0;
}

int change_config_value(const char* param, const char* new_value) {
    // Открыть конфигурационный файл для чтения и записи
    FILE* config_file = fopen("rr.cfg", "r+");
    if (config_file == NULL) {
        return 1;
    }

    // Создать временный файл для записи
    FILE* temp_file = fopen("rr_temp.cfg", "w");
    if (temp_file == NULL) {
        fclose(config_file);
        return 1;
    }

    // Перебрать строки конфигурационного файла
    char line[100];
    int param_changed = 0;
    while (fgets(line, sizeof(line), config_file) != NULL) {
        // Проверить, является ли текущая строка комментарием
        if (line[0] == ';' || line[0] == '#') {
            // Пропустить комментарий, просто записав его во временный файл
            fputs(line, temp_file);
        }
        else {
            // Проверить, является ли текущая строка нужным параметром
            if (strncmp(line, param, strlen(param)) == 0) {
                // Найти позицию символа '=', чтобы заменить значение
                char* equal_sign = strchr(line, '=');
                if (equal_sign != NULL) {
                    // Заменить значение параметра на новое значение и записать во временный файл
                    fprintf(temp_file, "%s = %s\n", param, new_value);
                    param_changed = 1;
                }
            }
            else {
                // Просто записать текущую строку во временный файл
                fputs(line, temp_file);
            }
        }
    }

    // Закрыть файлы
    fclose(config_file);
    fclose(temp_file);

    // Удалить исходный файл
    remove("rr.cfg");

    // Переименовать временный файл в исходное имя
    rename("rr_temp.cfg", "rr.cfg");

    if (param_changed) {
        return 0;
    }
    else {
        return 1;
    }

    return 0;
}

int print_cars_by_brand_and_region(const Record* head, const char* brand, const char* region) {
    const Record* current = head;
    if (current == NULL) {
        return 1;
    }
    while (current != NULL) {
        // Проверяем марку и регион автомобиля
        if (strcmp(current->mark, brand) == 0 && strncmp(current->state_car_num, region, 2) == 0) {
            // Выводим информацию об автомобиле
            printf("ID: %d\n", current->id);
            printf("Держномер: %s\n", current->state_car_num);
            printf("Марка: %s\n", current->mark);
            printf("Регион: %s\n", current->state_car_num);
            printf("Рік випуску: %d\n", current->graduation_year);
            printf("Пробіг: %d\n", current->car_mileage);
            printf("VIN код: %s\n", current->vin_code);
            printf("-----------------\n");
        }

        current = current->next;
    }
    return 0;
}

int print_cars_by_year_and_mileage(const Record* head, int min_year, int max_year, int min_mileage, int max_mileage) {
    const Record* current = head;

    while (current != NULL) {
        // Проверяем год выпуска и пробег автомобиля
        if (current->graduation_year >= min_year && current->graduation_year <= max_year &&
            current->car_mileage >= min_mileage && current->car_mileage <= max_mileage) {
            // Выводим информацию об автомобиле
            printf("ID: %d\n", current->id);
            printf("Держномер: %s\n", current->state_car_num);
            printf("Марка: %s\n", current->mark);
            printf("Рік випуску: %d\n", current->graduation_year);
            printf("Пробіг: %d\n", current->car_mileage);
            printf("VIN код: %s\n", current->vin_code);
            printf("-----------------\n");
        }

        current = current->next;
    }
    return 0;
}
