#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "contacts.h"

#define MAX_ACCESS_KEY_LENGTH 50

int main() {
    setlocale(LC_ALL, "Ukr");
    char accessKey[MAX_ACCESS_KEY_LENGTH];

    getAccessKey(accessKey);

    // �������� ����� �������
    if (!checkAccessKey(accessKey, "access_key.txt")) {
        printf("���i���� ���� �������. �������� �����������.\n");
        return 0;
    }
    Contact* contacts = NULL;
    int numContacts = 0;
    int choice;

    do {
        printf("����:\n");
        printf("1. ������ �������\n");
        printf("2. �������� �������\n");
        printf("3. ������� ��i ��������\n");
        printf("4. ���������� �������\n");
        printf("5. ������� �������� � �����������\n");
        printf("6. ������� ��������, �� ����������� � �i������\n");
        printf("7. �������� �������� � ����(�� �����)\n");
        printf("8. ����������� �������� � �����\n");
        printf("��� ���i�: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addContact(&contacts, &numContacts);
            break;
        case 2: {
            int index;
            printf("������ i����� �������� ��� ���������: ");
            scanf("%d", &index);
            deleteContact(&contacts, &numContacts, index);
            break;
        }
        case 3:
            displayContacts(contacts, numContacts);
            break;
        case 4: {
            int index;
            printf("����i�� i����� �������� ��� �����������: ");
            scanf("%d", &index);
            editContact(contacts, numContacts, index);
            break;
        }
        case 5:
            displayContactsByMessenger(contacts, numContacts);
            break;
        case 6: {
            char substring[50];
            printf("����i�� �������: ");
            scanf("%s", substring);
            displayContactsBySubstring(contacts, numContacts, substring);
            break;
        }
        case 7: {
            char filename[50];
            printf("����i�� ����� ����� ��� ����������: ");
            scanf("%s", filename);
            saveContactsToFile(contacts, numContacts, filename);
            printf("�� ���������");
            break;
        }
        case 8: {
            char filename[50];
            printf("����i�� ����� ����� ��� ������������: ");
            scanf("%s", filename);
            loadContactsFromFile(&contacts, &numContacts, filename);
            break;
        }
        default:
            printf("���i���� ���i�. ��������� �� ���.\n");
            break;
        }
    } while (choice != 7);

    return 0;
}