#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "contacts.h"
#define MAX_ACCESS_KEY_LENGTH 50

void addContact(Contact** contacts, int* numContacts) {
    Contact newContact;
    getchar();
    newContact.surname = (char*)malloc(50 * sizeof(char));
    printf("Введiть прiзвище: ");
    fgets(newContact.surname, 50, stdin);
    newContact.surname[strcspn(newContact.surname, "\n")] = '\0';

    newContact.name = (char*)malloc(50 * sizeof(char));
    printf("Введiть iм'я: ");
    fgets(newContact.name, 50, stdin);
    newContact.name[strcspn(newContact.name, "\n")] = '\0';

    newContact.phone = (char*)malloc(20 * sizeof(char));
    printf("Введiть номер телефона: ");
    fgets(newContact.phone, 20, stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = '\0';

    newContact.messenger = (char*)malloc(50 * sizeof(char));
    printf("Введiть логiн у месенджерi: ");
    fgets(newContact.messenger, 50, stdin);
    newContact.messenger[strcspn(newContact.messenger, "\n")] = '\0';

    (*numContacts)++;

    *contacts = (Contact*)realloc(*contacts, (*numContacts) * sizeof(Contact));
    (*contacts)[(*numContacts) - 1] = newContact;

    printf("Контакт успiшно доданий!\n");
}

// Функція для видалення контакту за індексом
void deleteContact(Contact** contacts, int* numContacts, int index) {
    if (index >= 0 && index < *numContacts) {
        free((*contacts)[index].surname);
        free((*contacts)[index].name);
        free((*contacts)[index].phone);
        free((*contacts)[index].messenger);

        for (int i = index; i < *numContacts - 1; i++) {
            (*contacts)[i] = (*contacts)[i + 1];
        }

        (*numContacts)--;
        *contacts = (Contact*)realloc(*contacts, (*numContacts) * sizeof(Contact));

        printf("Контакт успiшно видалений!\n");
    }
    else {
        printf("Неприпустимий iндекс контакту!\n");
    }
}

// Функція для виведення всіх контактів
void displayContacts(Contact* contacts, int numContacts) {
    
    if (numContacts > 0) {
        printf("Список контактiв:\n");
        for (int i = 0; i < numContacts; i++) {
            printf("Контакт %d:\n", i);
            printf("Прiзвище: %s\n", contacts[i].surname);
            printf("Iм'я: %s\n", contacts[i].name);
            printf("Номер телефона: %s\n", contacts[i].phone);
            printf("Логiн у месенджерi: %s\n", contacts[i].messenger);
            printf("-----------------------\n");
        }
    }
    else {
        printf("Список контактiв порожнiй!\n");
    }
}

void editContact(Contact* contacts, int numContacts, int index) {
    if (index >= 0 && index < numContacts) {
        int choice;
        printf("Виберiть поле для змiни:\n");
        printf("1. Прiзвище\n");
        printf("2. Iм'я\n");
        printf("3. Номер телефона\n");
        printf("4. Логiн у месенджерi\n");
        printf("Ваш вибiр: ");
        scanf_s("%d", &choice);
        getchar(); // Очистити буфер введення
        char buffer[100];
        switch (choice) {
        case 1:
            printf("Введiть нове прiзвище: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            free(contacts[index].surname);
            contacts[index].surname = _strdup(buffer);
            break;
        case 2:
            printf("Введiть нове iм'я: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            free(contacts[index].name);
            contacts[index].name = _strdup(buffer);
            break;
        case 3:
            printf("Введiть новий номер телефона: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            free(contacts[index].phone);
            contacts[index].phone = _strdup(buffer);
            break;
        case 4:
            printf("Введiть новий логiн у месенджерi: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            free(contacts[index].messenger);
            contacts[index].messenger = _strdup(buffer);
            break;
        default:
            printf("Неприпустимий вибiр!\n");
        }
        printf("Контакт успішно змiнений!\n");
    }
    else {
        printf("Неприпустимий iндекс контакту!\n");
    }
}


void displayContactsByMessenger(Contact* contacts, int numContacts) {
    int found = 0;

    printf("Контакти з месенджером:\n");
    for (int i = 0; i < numContacts; i++) {
        if (strlen(contacts[i].messenger) > 1) {
            printf("Контакт %d:\n", i);
            printf("Прiзвище: %s\n", contacts[i].surname);
            printf("Iм'я: %s\n", contacts[i].name);
            printf("Номер телефона: %s\n", contacts[i].phone);
            printf("Логiн у месенджерi: %s\n", contacts[i].messenger);
            printf("-----------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Немає контактiв з месенджером.\n");
    }
}
void displayContactsBySubstring(Contact* contacts, int numContacts, const char* substring) {
    int found = 0;

    printf("Контакти, що починаються з пiдрядка \"%s\":\n", substring);
    for (int i = 0; i < numContacts; i++) {
        if (strstr(contacts[i].surname, substring) != NULL ||
            strstr(contacts[i].name, substring) != NULL ||
            strstr(contacts[i].phone, substring) != NULL ||
            strstr(contacts[i].messenger, substring) != NULL) {
            printf("Контакт %d:\n", i + 1);
            printf("Прiзвище: %s\n", contacts[i].surname);
            printf("iм'я: %s\n", contacts[i].name);
            printf("Номер телефона: %s\n", contacts[i].phone);
            printf("Логiн у месенджерi: %s\n", contacts[i].messenger);
            printf("-----------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("Немає контактiв, що починаються з пiдрядка \"%s\".\n", substring);
    }
}


// Функція для збереження контактів у файл
void saveContactsToFile(Contact* contacts, int numContacts, const char* filename) {
    char filename_with_extension[100];
    const char* extension = ".csv";
    // Перевірка, чи містить назва файлу потрібне розширення
    if (strstr(filename, extension) == NULL) {
        snprintf(filename_with_extension, sizeof(filename_with_extension), "%s%s", filename, extension);
    }
    else {
        strncpy(filename_with_extension, filename, sizeof(filename_with_extension));
    }

    FILE* file = fopen(filename_with_extension, "w");
    if (file == NULL) {
        printf("Помилка вiдкриття файлу для запису.\n");
        return;
    }

    for (int i = 0; i < numContacts; i++) {
        fprintf(file, "%s.%s.%s.%s\n", contacts[i].surname, contacts[i].name, contacts[i].phone, contacts[i].messenger);
    }

    fclose(file);
}

// Функція для завантаження контактів з файлу
void loadContactsFromFile(Contact** contacts, int* numContacts, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Помилка вiдкриття файлу для читання.\n");
        return;
    }

    *numContacts = 0;
    char buffer[100];

    // Звіряємо кожен рядок у файлі
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        (*numContacts)++;
        *contacts = (Contact*)realloc(*contacts, (*numContacts) * sizeof(Contact));

        // Виділяємо пам'ять для полів контакту
        (*contacts)[(*numContacts) - 1].surname = (char*)malloc(50 * sizeof(char));
        (*contacts)[(*numContacts) - 1].name = (char*)malloc(50 * sizeof(char));
        (*contacts)[(*numContacts) - 1].phone = (char*)malloc(20 * sizeof(char));
        (*contacts)[(*numContacts) - 1].messenger = (char*)malloc(50 * sizeof(char));

        // Розділяємо рядок на поля за допомогою функції sscanf
        sscanf(buffer, "%[^.].%[^.].%[^.].%[^.]",
            (*contacts)[(*numContacts) - 1].surname,
            (*contacts)[(*numContacts) - 1].name,
            (*contacts)[(*numContacts) - 1].phone,
            (*contacts)[(*numContacts) - 1].messenger);
    }

    fclose(file);
}


int checkAccessKey(const char* accessKey, const char* keyFilename) {
    FILE* file = fopen(keyFilename, "r");
    if (file == NULL) {
        printf("Помилка вiдкриття файлу з ключем доступу.\n");
        return 0;
    }

    char storedKey[MAX_ACCESS_KEY_LENGTH];
    fgets(storedKey, sizeof(storedKey), file);
    storedKey[strcspn(storedKey, "\n")] = '\0';

    fclose(file);

    if (strcmp(accessKey, storedKey) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

// Функція для отримання ключа доступу від користувача
void getAccessKey(char* accessKey) {
    printf("Введiть ключ доступу: ");
    fgets(accessKey, MAX_ACCESS_KEY_LENGTH, stdin);
    accessKey[strcspn(accessKey, "\n")] = '\0';
}
