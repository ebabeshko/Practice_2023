#include "a_func.h"

void export_cvs(Employee* head) {
    char filename[50];
    printf("Введіть назву файлу експорту (без розширення): ");
    scanf("%49s", filename);

    char filepath[100];
    sprintf(filepath, "../Practice/%s.csv", filename);

    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        printf("Помилка при відкритті файлу %s\n", filepath);
        return;
    }

    Employee* current = head;
    while (current != NULL) {
        fprintf(file, "%d,%s,%s,%d %d %d,%.2f\n", current->id, current->name, current->post,
            current->hire_date[0], current->hire_date[1], current->hire_date[2], current->salary);
        current = current->next;
    }

    fclose(file);
    printf("Базу даних збережено у файлі %s (CSV формат)\n", filepath);
}

void export_dat(Employee* head) {
    char filename[50];
    printf("Введіть назву файлу експорту (без розширення): ");
    scanf("%49s", filename);

    char filepath[100];
    sprintf(filepath, "../Practice/%s.dat", filename);

    FILE* file = fopen(filepath, "wb");
    if (file == NULL) {
        printf("Помилка при відкритті файлу %s\n", filepath);
        return;
    }

    Employee* current = head;
    while (current != NULL) {
        fwrite(current, sizeof(Employee), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Базу даних збережено у файлі %s (DAT формат)\n", filepath);
}