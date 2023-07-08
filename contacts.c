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
    printf("����i�� ��i�����: ");
    fgets(newContact.surname, 50, stdin);
    newContact.surname[strcspn(newContact.surname, "\n")] = '\0';

    newContact.name = (char*)malloc(50 * sizeof(char));
    printf("����i�� i�'�: ");
    fgets(newContact.name, 50, stdin);
    newContact.name[strcspn(newContact.name, "\n")] = '\0';

    newContact.phone = (char*)malloc(20 * sizeof(char));
    printf("����i�� ����� ��������: ");
    fgets(newContact.phone, 20, stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = '\0';

    newContact.messenger = (char*)malloc(50 * sizeof(char));
    printf("����i�� ���i� � ���������i: ");
    fgets(newContact.messenger, 50, stdin);
    newContact.messenger[strcspn(newContact.messenger, "\n")] = '\0';

    (*numContacts)++;

    *contacts = (Contact*)realloc(*contacts, (*numContacts) * sizeof(Contact));
    (*contacts)[(*numContacts) - 1] = newContact;

    printf("������� ���i��� �������!\n");
}

// ������� ��� ��������� �������� �� ��������
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

        printf("������� ���i��� ���������!\n");
    }
    else {
        printf("������������� i����� ��������!\n");
    }
}

// ������� ��� ��������� ��� ��������
void displayContacts(Contact* contacts, int numContacts) {
    if (numContacts > 0) {
        printf("������ �������i�:\n");
        for (int i = 0; i < numContacts; i++) {
            printf("������� %d:\n", i);
            printf("��i�����: %s\n", contacts[i].surname);
            printf("I�'�: %s\n", contacts[i].name);
            printf("����� ��������: %s\n", contacts[i].phone);
            printf("���i� � ���������i: %s\n", contacts[i].messenger);
            printf("-----------------------\n");
        }
    }
    else {
        printf("������ �������i� ������i�!\n");
    }
}

void editContact(Contact* contacts, int numContacts, int index) {
    if (index >= 0 && index < numContacts) {
        int choice;
        printf("�����i�� ���� ��� ��i��:\n");
        printf("1. ��i�����\n");
        printf("2. I�'�\n");
        printf("3. ����� ��������\n");
        printf("4. ���i� � ���������i\n");
        printf("��� ���i�: ");
        scanf_s("%d", &choice);
        getchar(); // �������� ����� ��������
        char buffer[100];
        switch (choice) {
        case 1:
            printf("����i�� ���� ��i�����: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            free(contacts[index].surname);
            contacts[index].surname = _strdup(buffer);
            break;
        case 2:
            printf("����i�� ���� i�'�: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            free(contacts[index].name);
            contacts[index].name = _strdup(buffer);
            break;
        case 3:
            printf("����i�� ����� ����� ��������: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            free(contacts[index].phone);
            contacts[index].phone = _strdup(buffer);
            break;
        case 4:
            printf("����i�� ����� ���i� � ���������i: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            free(contacts[index].messenger);
            contacts[index].messenger = _strdup(buffer);
            break;
        default:
            printf("������������� ���i�!\n");
        }
        printf("������� ������ ��i�����!\n");
    }
    else {
        printf("������������� i����� ��������!\n");
    }
}


void displayContactsByMessenger(Contact* contacts, int numContacts) {
    int found = 0;

    printf("�������� � �����������:\n");
    for (int i = 0; i < numContacts; i++) {
        if (strcmp(contacts[i].messenger, "") != 0) {
            printf("������� %d:\n", i + 1);
            printf("��i�����: %s\n", contacts[i].surname);
            printf("I�'�: %s\n", contacts[i].name);
            printf("����� ��������: %s\n", contacts[i].phone);
            printf("���i� � ���������i: %s\n", contacts[i].messenger);
            printf("-----------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("���� �������i� � �����������.\n");
    }
}
void displayContactsBySubstring(Contact* contacts, int numContacts, const char* substring) {
    int found = 0;

    printf("��������, �� ����������� � �i������ \"%s\":\n", substring);
    for (int i = 0; i < numContacts; i++) {
        if (strstr(contacts[i].surname, substring) != NULL ||
            strstr(contacts[i].name, substring) != NULL ||
            strstr(contacts[i].phone, substring) != NULL ||
            strstr(contacts[i].messenger, substring) != NULL) {
            printf("������� %d:\n", i + 1);
            printf("��i�����: %s\n", contacts[i].surname);
            printf("i�'�: %s\n", contacts[i].name);
            printf("����� ��������: %s\n", contacts[i].phone);
            printf("���i� � ���������i: %s\n", contacts[i].messenger);
            printf("-----------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("���� �������i�, �� ����������� � �i������ \"%s\".\n", substring);
    }
}


// ������� ��� ���������� �������� � ����
void saveContactsToFile(Contact* contacts, int numContacts, const char* filename) {
    char filename_with_extension[100];
    const char* extension = ".csv";
    // ��������, �� ������ ����� ����� ������� ����������
    if (strstr(filename, extension) == NULL) {
        snprintf(filename_with_extension, sizeof(filename_with_extension), "%s%s", filename, extension);
    }
    else {
        strncpy(filename_with_extension, filename, sizeof(filename_with_extension));
    }

    FILE* file = fopen(filename_with_extension, "w");
    if (file == NULL) {
        printf("������� �i������� ����� ��� ������.\n");
        return;
    }

    for (int i = 0; i < numContacts; i++) {
        fprintf(file, "%s.%s.%s.%s\n", contacts[i].surname, contacts[i].name, contacts[i].phone, contacts[i].messenger);
    }

    fclose(file);
}

// ������� ��� ������������ �������� � �����
void loadContactsFromFile(Contact** contacts, int* numContacts, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("������� �i������� ����� ��� �������.\n");
        return;
    }

    *numContacts = 0;
    char buffer[100];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        (*numContacts)++;
        *contacts = (Contact*)realloc(*contacts, (*numContacts) * sizeof(Contact));

        // ��������� ����� �� ���� �� ��������� ������� strtok
        char* token = strtok(buffer, ".");
        int fieldIndex = 0;
        while (token != NULL) {
            // ��������� ����, �� ����� �������� �����
            switch (fieldIndex) {
            case 0:
                (*contacts)[(*numContacts) - 1].surname = _strdup(token);
                break;
            case 1:
                (*contacts)[(*numContacts) - 1].name = _strdup(token);
                break;
            case 2:
                (*contacts)[(*numContacts) - 1].phone = _strdup(token);
                break;
            case 3:
                (*contacts)[(*numContacts) - 1].messenger = _strdup(token);
                break;
            }

            // ���������� �� ���������� ������
            token = strtok(NULL, ".");
            fieldIndex++;
        }
    }

    fclose(file);
}

int checkAccessKey(const char* accessKey, const char* keyFilename) {
    FILE* file = fopen(keyFilename, "r");
    if (file == NULL) {
        printf("������� �i������� ����� � ������ �������.\n");
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

// ������� ��� ��������� ����� ������� �� �����������
void getAccessKey(char* accessKey) {
    printf("����i�� ���� �������: ");
    fgets(accessKey, MAX_ACCESS_KEY_LENGTH, stdin);
    accessKey[strcspn(accessKey, "\n")] = '\0';
}
