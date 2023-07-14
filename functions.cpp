/**
* @file functions.cpp
* @author ���������� �.�., ��. 515�, ������ 13
* @date 13 ����� 2023
* @brief ��������� ��������
*
* ���� ����� �����������
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

    // �������� �������� ���
    time(&current_time);
    time_info = localtime(&current_time);

    // ��������� ���� � �������� ��� ������
    strftime(date_str, sizeof(date_str), "%d%m%Y", time_info);

    // ������� ���� � ����
    strcpy(key, date_str);
}

void create_config_file(const char* key) {
    char generated_key[KEY_LENGTH + 1];
    generate_license_key(generated_key);

    FILE* config_file = fopen("config.txt", "w");
    if (config_file == NULL) {
        printf("������� ��������� ���������������� �����.\n");
        return;
    }

    // �������� ���������� � ��������������� ����
    fprintf(config_file, "; ���� ���� �����\n");
    fprintf(config_file, "; ���������� � ������ DB = <����_��_�����>\n");
    fprintf(config_file, "DB = new_base.dat\n");
    fprintf(config_file, "; ˳�������� ����\n");
    fprintf(config_file, "KEY = %s\n", generated_key);

    fclose(config_file);

    // �������� �������� ����� ���� ����� new_base.dat
    FILE* db_file = fopen("new_base.dat", "rb");
    if (db_file == NULL) {
        // ���� �� ����, ��������� ����
        db_file = fopen("new_base.dat", "wb");
        if (db_file == NULL) {
            printf("������� ��������� ����� ���� �����.\n");
            return;
        }
        printf("�������� ���� ���� ����� � ������ new_base.dat.\n");
        fclose(db_file);
    }
    else {
        fclose(db_file);
        printf("���� ���� ����� new_base.dat ��� ����.\n");
    }
}



void read_config(char* db_file, char* key) {
    FILE* config_file = fopen("config.txt", "r");
    if (config_file == NULL) {
        printf("������� �������� ���������������� �����.\n���� ���� �������� �����������.\n");
        create_config_file(key);
        return;
    }
    char line[50];
    while (fgets(line, sizeof(line), config_file) != NULL) {
        if (strstr(line, "DB = ") != NULL) {
            // �������� ����� � ��������� ���� �����
            // ������� �������� ���� "DB = " � ����� db_file
            strcpy(db_file, line + strlen("DB = "));
        }
        else if (strstr(line, "KEY = ") != NULL) {
            // �������� ����� � ��������� �����
            // ������� �������� ���� "KEY = " � ����� key
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
        printf("������� �������� ����� ���� �����.\n");
        return;
    }

    Person person;
    printf("������ �������, ��'� �� �� ������� (����� �����): ");
    scanf(" %[^\n]s", person.name);
    printf("������ ������: ");
    scanf(" %[^\n]s", person.position);
    printf("������ ���� ��������� �� ������ (����� �����): ");
    scanf("%d %d %d", &person.hire_date[0], &person.hire_date[1], &person.hire_date[2]);
    printf("������ ����������� �������� �����: ");
    scanf("%f", &person.salary);

    fwrite(&person, sizeof(Person), 1, file);
    fclose(file);

    printf("������� ������ ������.\n");
}

void delete_person(const char* db_file) {
    FILE* file = fopen(db_file, "rb");
    if (file == NULL) {
        printf("������� �������� ����� ���� �����.\n");
        return;
    }

    int id;
    printf("������ ���������������� ����� �������, ��� ������ ��������: ");
    scanf("%d", &id);

    FILE* temp_file = fopen("temp.dat", "wb");
    if (temp_file == NULL) {
        printf("������� �������� ����������� �����.\n");
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
        printf("������� ������ ��������.\n");
    }
    else {
        printf("������� � ���������������� ������� %d �� ��������.\n", id);
        remove("temp.dat");
    }
}

void display_all(const char* db_file) {
    FILE* file = fopen(db_file, "rb");
    if (file == NULL) {
        printf("������� �������� ����� ���� �����.\n");
        return;
    }

    Person person;
    int count = 0;
    while (fread(&person, sizeof(Person), 1, file) == 1) {
        printf("=== ������� %d ===\n", count + 1);
        printf("�������, ��'� �� �� �������: %s\n", person.name);
        printf("������: %s\n", person.position);
        printf("���� ��������� �� ������: %d.%d.%d\n", person.hire_date[0], person.hire_date[1], person.hire_date[2]);
        printf("����������� �������� �����: %.2f\n", person.salary);
        printf("=================\n");
        count++;
    }

    fclose(file);

    if (count == 0) {
        printf("� ��� ����� ���� ������.\n");
    }
    else {
        printf("������� �������� %d ������.\n", count);
    }
}

void display_by_salary(const char* db_file, const char* key) {
    FILE* file = fopen(db_file, "rb");
    if (file == NULL) {
        printf("������� �������� ����� ���� �����.\n");
        return;
    }

    float salary;
    printf("������ �������� �������� �����: ");
    scanf("%f", &salary);

    Person person;
    int count = 0;
    while (fread(&person, sizeof(Person), 1, file) == 1) {
        if (person.salary > salary) {
            printf("=== ������� %d ===\n", count + 1);
            printf("�������, ��'� �� �� �������: %s\n", person.name);
            printf("������: %s\n", person.position);
            printf("���� ��������� �� ������: %d.%d.%d\n", person.hire_date[0], person.hire_date[1], person.hire_date[2]);
            printf("����������� �������� �����: %.2f\n", person.salary);
            printf("=================\n");
            count++;
        }
    }

    fclose(file);

    if (count == 0) {
        printf("�� �������� ����������� � ��������� ������ ���� �������.\n");
    }
    else {
        printf("������� �������� %d �����������.\n", count);
    }
}

void display_by_position_and_date(const char* db_file, const char* key) {
    FILE* file = fopen(db_file, "rb");
    if (file == NULL) {
        printf("������� �������� ����� ���� �����.\n");
        return;
    }

    char position[MAX_POSITION_LENGTH];
    printf("������ ������: ");
    scanf(" %[^\n]s", position);
    getchar();  // �������� ����� �����

    int year, month, day;
    printf("������ ���� (��, �����, ���� (����� �����)): ");
    scanf("%d %d %d", &year, &month, &day);
    getchar();  // �������� ����� �����

    Person person;
    int count = 0;

    while (fread(&person, sizeof(Person), 1, file) == 1) {
        if (strcmp(person.position, position) == 0 &&
            (person.hire_date[2] > year ||
                (person.hire_date[2] == year && person.hire_date[1] > month) ||
                (person.hire_date[2] == year && person.hire_date[1] == month && person.hire_date[0] > day))) {
            printf("=== ������� %d ===\n", count + 1);
            printf("�������, ��'� �� �� �������: %s\n", person.name);
            printf("������: %s\n", person.position);
            printf("���� ��������� �� ������: %d.%d.%d\n", person.hire_date[0], person.hire_date[1], person.hire_date[2]);
            printf("����������� �������� �����: %.2f\n", person.salary);
            printf("=================\n");
            count++;
        }
    }

    fclose(file);

    if (count == 0) {
        printf("�� �������� ����������� � ������� '%s', ��������� ���� %d.%d.%d.\n", position, day, month, year);
    }
    else {
        printf("������� �������� %d ����������� � ������� '%s', ��������� ���� %d.%d.%d.\n", count, position, day, month, year);
    }
}

void save_database(const char* db_file, const char* key) {
    FILE* source = fopen(db_file, "rb");
    if (source == NULL) {
        printf("������� �������� ����� ���� �����.\n");
        return;
    }

    FILE* dest = fopen("backup.dat", "wb");
    if (dest == NULL) {
        printf("������� ��������� �������� ��ﳿ ����� ���� �����.\n");
        fclose(source);
        return;
    }

    int ch;
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, dest);
    }

    fclose(source);
    fclose(dest);

    printf("�������� ���� ���� ����� ��������� � ���� backup.dat\n");
}

void export_database(const char* db_file, const char* key) {
    FILE* file = fopen(db_file, "rb");
    if (file == NULL) {
        printf("������� �������� ����� ���� �����.\n");
        return;
    }

    FILE* export_file = fopen("database.csv", "w");
    if (export_file == NULL) {
        printf("������� ��������� ����� ��� �������� ���� �����.\n");
        fclose(file);
        return;
    }

    Person person;
    while (fread(&person, sizeof(Person), 1, file) == 1) {
        fprintf(export_file, "%s, %s, %d.%d.%d, %.2f\n", person.name, person.position, person.hire_date[0], person.hire_date[1], person.hire_date[2], person.salary);
    }

    fclose(file);
    fclose(export_file);

    printf("���� ����� ������������ � ���� database.csv\n");
}
#define MAX_FILENAME_LENGTH 100
#define MAX_KEY_LENGTH 100
void change_config() {
    char db_file[MAX_FILENAME_LENGTH];
    char key[MAX_KEY_LENGTH];
    char user_key[MAX_KEY_LENGTH];

    printf("������ ���� ��'� ����� ���� �����: ");
    scanf("%s", db_file);

    printf("������ ����� ��������� ����: ");
    scanf("%s", user_key);

    // ���������� �������� ������� � ���������������� �����
    char current_db_file[MAX_FILENAME_LENGTH];
    char current_key[MAX_KEY_LENGTH];

    FILE* config_file = fopen("config.txt", "r");
    if (config_file == NULL) {
        printf("������� �������� ���������������� �����.\n");
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
        printf("������� �������� ���������������� �����.\n");
        return;
    }

    fprintf(config_file, "; ���� ���� �����\n");
    fprintf(config_file, "DB = %s\n", db_file);
    fprintf(config_file, "; ˳�������� ����\n");
    fprintf(config_file, "KEY = %s\n", user_key);

    fclose(config_file);

    printf("��������������� ���� ������ �������.\n");
}


void modify_person(const char* db_file, const char* key) {
    FILE* file = fopen(db_file, "r+b");
    if (file == NULL) {
        printf("������� �������� ����� ���� �����.\n");
        return;
    }

    int id;
    printf("������ ���������������� ����� ������, ���� ������ ������: ");
    scanf("%d", &id);

    // ���������� ��������� ����� �� ���������� ������
    fseek(file, (id - 1) * sizeof(Person), SEEK_SET);

    Person person;
    fread(&person, sizeof(Person), 1, file);

    if (strlen(person.name) == 0) {
        printf("����� � ���������������� ������� %d �� ��������.\n", id);
        fclose(file);
        return;
    }

    printf("������ ��� ��� ��� ������ � ���������������� ������� %d:\n", id);

    // ���������� ����� ������� ���� �� �����������
    printf("�������, ��'� �� �� ������� (����� �����): ");
    scanf(" %[^\n]s", person.name);
    printf("������ ������: ");
    scanf(" %[^\n]s", person.position);
    printf("������ ���� ��������� �� ������ (����� �����): ");
    scanf("%d %d %d", &person.hire_date[0], &person.hire_date[1], &person.hire_date[2]);
    printf("������ ����������� �������� �����: ");
    scanf("%f", &person.salary);

    // ���������� ��������� ����� �� ������� ������� ������
    fseek(file, -((long)sizeof(Person)), SEEK_CUR);

    // ����� ����� ������� ���� � ����
    fwrite(&person, sizeof(Person), 1, file);

    fclose(file);

    printf("����� � ���������������� ������� %d ������ ������.\n", id);
}