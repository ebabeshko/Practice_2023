/**
* @file functions.cpp
* @author Золотарьов Д.А., гр. 515б, варіант 13
* @date 13 липня 2023
* @brief Навчальна практика
*
* База даних співробітників
*/
// ---
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 6031)
// ---
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "functions.h"

#define MAX_NAME_LENGTH 50
#define MAX_POSITION_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    char position[MAX_POSITION_LENGTH];
    int hire_date[3];
    float salary;
} Person;


void generate_license_key(char* key) {
    time_t current_time;
    struct tm* time_info;
    char date_str[KEY_LENGTH + 1];

    // Отримуємо поточний час
    time(&current_time);
    time_info = localtime(&current_time);

    // Форматуємо дату у потрібний нам формат
    strftime(date_str, sizeof(date_str), "%d%m%Y", time_info);

    // Копіюємо дату у ключ
    strcpy(key, date_str);
}

void create_config_file(const char* key) {
    char generated_key[KEY_LENGTH + 1];
    generate_license_key(generated_key);

    FILE* config_file = fopen("config.txt", "w");
    if (config_file == NULL) {
        printf("Помилка створення конфігураційного файлу.\n");
        return;
    }

    // Записуємо інформацію у конфігураційний файл
    fprintf(config_file, "; Файл бази даних\n");
    fprintf(config_file, "; Записується у форматі DB = <шлях_до_файлу>\n");
    fprintf(config_file, "DB = new_base.dat\n");
    fprintf(config_file, "; Ліцензійний ключ\n");
    fprintf(config_file, "KEY = %s\n", generated_key);

    fclose(config_file);

    // Перевірка наявності файлу бази даних new_base.dat
    FILE* db_file = fopen("new_base.dat", "rb");
    if (db_file == NULL) {
        // Файл не існує, створюємо його
        db_file = fopen("new_base.dat", "wb");
        if (db_file == NULL) {
            printf("Помилка створення файлу бази даних.\n");
            return;
        }
        printf("Створено нову базу даних з іменем new_base.dat.\n");
        fclose(db_file);
    }
    else {
        fclose(db_file);
        printf("Файл бази даних new_base.dat вже існує.\n");
    }
}



void read_config(char* db_file, char* key) {
    FILE* config_file = fopen("config.txt", "r");
    if (config_file == NULL) {
        printf("Помилка відкриття конфігураційного файлу.\nФайл буде створено автоматично.\n");
        create_config_file(key);
        return;
    }
    char line[50];
    while (fgets(line, sizeof(line), config_file) != NULL) {
        if (strstr(line, "DB = ") != NULL) {
            // Знайдено рядок зі значенням бази даних
            // Копіюємо значення після "DB = " у змінну db_file
            strcpy(db_file, line + strlen("DB = "));
        }
        else if (strstr(line, "KEY = ") != NULL) {
            // Знайдено рядок зі значенням ключа
            // Копіюємо значення після "KEY = " у змінну key
            strcpy(key, line + strlen("KEY = "));
        }
    }

    db_file[strcspn(db_file, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    fclose(config_file);
}

void add_person(const char* db_file) {
    FILE* file = fopen(db_file, "ab");
    if (file == NULL) {
        printf("Помилка відкриття файлу бази даних.\n");
        return;
    }

    Person person;
    printf("Введіть прізвище, ім'я та по батькові (через пробіл): ");
    scanf(" %[^\n]s", person.name);
    printf("Введіть посаду: ");
    scanf(" %[^\n]s", person.position);
    printf("Введіть дату прийняття на роботу (через пробіл): ");
    scanf("%d %d %d", &person.hire_date[0], &person.hire_date[1], &person.hire_date[2]);
    printf("Введіть встановлену заробітну плату: ");
    scanf("%f", &person.salary);

    fwrite(&person, sizeof(Person), 1, file);
    fclose(file);

    printf("Персона додана успішно.\n");
}

void delete_person(const char* db_file) {
    FILE* file = fopen(db_file, "rb");
    if (file == NULL) {
        printf("Помилка відкриття файлу бази даних.\n");
        return;
    }

    int id;
    printf("Введіть ідентифікаційний номер персони, яку бажаєте видалити: ");
    scanf("%d", &id);

    FILE* temp_file = fopen("temp.dat", "wb");
    if (temp_file == NULL) {
        printf("Помилка відкриття тимчасового файлу.\n");
        fclose(file);
        return;
    }

    Person person;
    int found = 0;
    while (fread(&person, sizeof(Person), 1, file) == 1) {
        if (ftell(file) / sizeof(Person) == id) {
            found = 1;
            continue;
        }
        fwrite(&person, sizeof(Person), 1, temp_file);
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        remove(db_file);
        rename("temp.dat", db_file);
        printf("Персона успішно видалена.\n");
    }
    else {
        printf("Персону з ідентифікаційним номером %d не знайдено.\n", id);
        remove("temp.dat");
    }
}

void display_all(const char* db_file) {
    FILE* file = fopen(db_file, "rb");
    if (file == NULL) {
        printf("Помилка відкриття файлу бази даних.\n");
        return;
    }

    Person person;
    int count = 0;
    while (fread(&person, sizeof(Person), 1, file) == 1) {
        printf("=== Персона %d ===\n", count + 1);
        printf("Прізвище, ім'я та по батькові: %s\n", person.name);
        printf("Посада: %s\n", person.position);
        printf("Дата прийняття на роботу: %d.%d.%d\n", person.hire_date[0], person.hire_date[1], person.hire_date[2]);
        printf("Встановлена заробітна плата: %.2f\n", person.salary);
        printf("=================\n");
        count++;
    }

    fclose(file);

    if (count == 0) {
        printf("У базі даних немає записів.\n");
    }
    else {
        printf("Загалом знайдено %d персон.\n", count);
    }
}

void display_by_salary(const char* db_file, const char* key) {
    FILE* file = fopen(db_file, "rb");
    if (file == NULL) {
        printf("Помилка відкриття файлу бази даних.\n");
        return;
    }

    float salary;
    printf("Введіть мінімальну заробітну плату: ");
    scanf("%f", &salary);

    Person person;
    int count = 0;
    while (fread(&person, sizeof(Person), 1, file) == 1) {
        if (person.salary > salary) {
            printf("=== Персона %d ===\n", count + 1);
            printf("Прізвище, ім'я та по батькові: %s\n", person.name);
            printf("Посада: %s\n", person.position);
            printf("Дата прийняття на роботу: %d.%d.%d\n", person.hire_date[0], person.hire_date[1], person.hire_date[2]);
            printf("Встановлена заробітна плата: %.2f\n", person.salary);
            printf("=================\n");
            count++;
        }
    }

    fclose(file);

    if (count == 0) {
        printf("Не знайдено співробітників з заробітною платою вище вказаної.\n");
    }
    else {
        printf("Загалом знайдено %d співробітників.\n", count);
    }
}

void display_by_position_and_date(const char* db_file, const char* key) {
    FILE* file = fopen(db_file, "rb");
    if (file == NULL) {
        printf("Помилка відкриття файлу бази даних.\n");
        return;
    }

    char position[MAX_POSITION_LENGTH];
    printf("Введіть посаду: ");
    scanf(" %[^\n]s", position);
    getchar();  // Очистити буфер вводу

    int year, month, day;
    printf("Введіть дату (рік, місяць, день (через пробіл)): ");
    scanf("%d %d %d", &year, &month, &day);
    getchar();  // Очистити буфер вводу

    Person person;
    int count = 0;

    while (fread(&person, sizeof(Person), 1, file) == 1) {
        if (strcmp(person.position, position) == 0 &&
            (person.hire_date[2] > year ||
                (person.hire_date[2] == year && person.hire_date[1] > month) ||
                (person.hire_date[2] == year && person.hire_date[1] == month && person.hire_date[0] > day))) {
            printf("=== Персона %d ===\n", count + 1);
            printf("Прізвище, ім'я та по батькові: %s\n", person.name);
            printf("Посада: %s\n", person.position);
            printf("Дата прийняття на роботу: %d.%d.%d\n", person.hire_date[0], person.hire_date[1], person.hire_date[2]);
            printf("Встановлена заробітна плата: %.2f\n", person.salary);
            printf("=================\n");
            count++;
        }
    }

    fclose(file);

    if (count == 0) {
        printf("Не знайдено співробітників з посадою '%s', прийнятих після %d.%d.%d.\n", position, day, month, year);
    }
    else {
        printf("Загалом знайдено %d співробітників з посадою '%s', прийнятих після %d.%d.%d.\n", count, position, day, month, year);
    }
}

void save_database(const char* db_file, const char* key) {
    FILE* source = fopen(db_file, "rb");
    if (source == NULL) {
        printf("Помилка відкриття файлу бази даних.\n");
        return;
    }

    FILE* dest = fopen("backup.dat", "wb");
    if (dest == NULL) {
        printf("Помилка створення резервної копії файлу бази даних.\n");
        fclose(source);
        return;
    }

    int ch;
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, dest);
    }

    fclose(source);
    fclose(dest);

    printf("Резервна копія бази даних збережена у файлі backup.dat\n");
}

void export_database(const char* db_file, const char* key) {
    FILE* file = fopen(db_file, "rb");
    if (file == NULL) {
        printf("Помилка відкриття файлу бази даних.\n");
        return;
    }

    FILE* export_file = fopen("database.csv", "w");
    if (export_file == NULL) {
        printf("Помилка створення файлу для експорту бази даних.\n");
        fclose(file);
        return;
    }

    Person person;
    while (fread(&person, sizeof(Person), 1, file) == 1) {
        fprintf(export_file, "%s, %s, %d.%d.%d, %.2f\n", person.name, person.position, person.hire_date[0], person.hire_date[1], person.hire_date[2], person.salary);
    }

    fclose(file);
    fclose(export_file);

    printf("База даних експортована у файл database.csv\n");
}
#define MAX_FILENAME_LENGTH 100
#define MAX_KEY_LENGTH 100
void change_config() {
    char db_file[MAX_FILENAME_LENGTH];
    char key[MAX_KEY_LENGTH];
    char user_key[MAX_KEY_LENGTH];

    printf("Введіть нове ім'я файлу бази даних: ");
    scanf("%s", db_file);

    printf("Введіть новий ліцензійний ключ: ");
    scanf("%s", user_key);

    // Зчитування поточних значень з конфігураційного файлу
    char current_db_file[MAX_FILENAME_LENGTH];
    char current_key[MAX_KEY_LENGTH];

    FILE* config_file = fopen("config.txt", "r");
    if (config_file == NULL) {
        printf("Помилка відкриття конфігураційного файлу.\n");
        return;
    }

    while (!feof(config_file)) {
        char line[100];
        fgets(line, sizeof(line), config_file);
        if (strstr(line, "DB = ") != NULL) {
            sscanf(line, "DB = %[^\n]", current_db_file);
        }
        else if (strstr(line, "KEY = ") != NULL) {
            sscanf(line, "KEY = %[^\n]", current_key);
        }
    }

    fclose(config_file);

    config_file = fopen("config.txt", "w");
    if (config_file == NULL) {
        printf("Помилка відкриття конфігураційного файлу.\n");
        return;
    }

    fprintf(config_file, "; Файл бази даних\n");
    fprintf(config_file, "DB = %s\n", db_file);
    fprintf(config_file, "; Ліцензійний ключ\n");
    fprintf(config_file, "KEY = %s\n", user_key);

    fclose(config_file);

    printf("Конфігураційний файл успішно змінений.\n");
}


void modify_person(const char* db_file, const char* key) {
    FILE* file = fopen(db_file, "r+b");
    if (file == NULL) {
        printf("Помилка відкриття файлу бази даних.\n");
        return;
    }

    int id;
    printf("Введіть ідентифікаційний номер запису, який бажаєте змінити: ");
    scanf("%d", &id);

    // Переміщення покажчика файлу до відповідного запису
    fseek(file, (id - 1) * sizeof(Person), SEEK_SET);

    Person person;
    fread(&person, sizeof(Person), 1, file);

    if (strlen(person.name) == 0) {
        printf("Запис з ідентифікаційним номером %d не знайдено.\n", id);
        fclose(file);
        return;
    }

    printf("Введіть нові дані для запису з ідентифікаційним номером %d:\n", id);

    // Зчитування нових значень полів від користувача
    printf("Прізвище, ім'я та по батькові (через пробіл): ");
    scanf(" %[^\n]s", person.name);
    printf("Введіть посаду: ");
    scanf(" %[^\n]s", person.position);
    printf("Введіть дату прийняття на роботу (через пробіл): ");
    scanf("%d %d %d", &person.hire_date[0], &person.hire_date[1], &person.hire_date[2]);
    printf("Введіть встановлену заробітну плату: ");
    scanf("%f", &person.salary);

    // Переміщення покажчика файлу до поточної позиції запису
    fseek(file, -((long)sizeof(Person)), SEEK_CUR);

    // Запис нових значень полів у файл
    fwrite(&person, sizeof(Person), 1, file);

    fclose(file);

    printf("Запис з ідентифікаційним номером %d змінено успішно.\n", id);
}