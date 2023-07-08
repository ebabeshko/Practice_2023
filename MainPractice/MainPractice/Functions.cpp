#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


#define MAX_FLIGHTS 100

struct Flight {
    char departure[50];
    char destination[50];
    int flightNumber;
    char aircraftType[50];
    int seats;
};

struct Flight* flights[MAX_FLIGHTS];
int numFlights = 0;

void openFile() {
    // ���������� ����� � �����
    FILE* file = fopen("flights.txt", "r");
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            struct Flight* newFlight = (struct Flight*)malloc(sizeof(struct Flight));
            sscanf(line, "%[^;];%[^;];%d;%[^;];%d", newFlight->departure, newFlight->destination, &(newFlight->flightNumber), newFlight->aircraftType, &(newFlight->seats));
            flights[numFlights++] = newFlight;
        }
        fclose(file);
    }
}

void addFlight() {
    if (numFlights >= MAX_FLIGHTS) {
        printf("��������� ������ ����� �����. ���� ���������.\n");
        return;
    }

    struct Flight* newFlight = (struct Flight*)malloc(sizeof(struct Flight));
    if (newFlight == NULL) {
        printf("������� �������� ���'��.\n");
        return;
    }

    printf("������ ����� �����������: ");
    scanf("%s", newFlight->departure);
    printf("������ ����� �����������: ");
    scanf("%s", newFlight->destination);
    printf("������ ����� �����: ");
    scanf("%d", &(newFlight->flightNumber));
    printf("������ ��� �����: ");
    scanf("%s", newFlight->aircraftType);
    printf("������ ������� ���� � �����: ");
    scanf("%d", &(newFlight->seats));

    flights[numFlights++] = newFlight;

    printf("���� ������ ������.\n");

    // ��������� �����
    FILE* file = fopen("flights.txt", "a");
    if (file == NULL) {
        printf("������� �������� �����.\n");
        return;
    }

    fprintf(file, "%s;%s;%d;%s;%d\n", newFlight->departure, newFlight->destination, newFlight->flightNumber, newFlight->aircraftType, newFlight->seats);

    fclose(file);
}

void deleteFlight() {
    int flightNumber;
    printf("������ ����� ����� ��� ���������: ");
    scanf("%d", &flightNumber);

    int found = 0;
    for (int i = 0; i < numFlights; i++) {
        if (flights[i]->flightNumber == flightNumber) {
            found = 1;
            free(flights[i]);
            for (int j = i; j < numFlights - 1; j++) {
                flights[j] = flights[j + 1];
            }
            numFlights--;
            printf("���� ���� ������ ��������.\n");
            break;
        }
    }

    if (!found) {
        printf("���� �� ��������.\n");
    }

    // ��������� �����
    FILE* file = fopen("flights.txt", "w");
    if (file == NULL) {
        printf("������� �������� �����.\n");
        return;
    }

    for (int i = 0; i < numFlights; i++) {
        fprintf(file, "%s;%s;%d;%s;%d\n", flights[i]->departure, flights[i]->destination, flights[i]->flightNumber, flights[i]->aircraftType, flights[i]->seats);
    }

    fclose(file);
}

void displayFlights() {
    printf("������ �����:\n");
    printf("-----------------------------------------------------------------------\n");
    printf("³����������\t�����������\t����� �����\t��� �����\t������\n");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < numFlights; i++) {
        printf("%s\t\t%s\t\t%d\t\t%s\t\t%d\n",
            flights[i]->departure,
            flights[i]->destination,
            flights[i]->flightNumber,
            flights[i]->aircraftType,
            flights[i]->seats);
    }
    printf("-----------------------------------------------------------------------\n");
}

void modifyFlight() {
    int flightNumber;
    printf("������ ����� ����� ��� �����������: ");
    scanf("%d", &flightNumber);

    int found = 0;
    for (int i = 0; i < numFlights; i++) {
        if (flights[i]->flightNumber == flightNumber) {
            found = 1;
            printf("���� ��������.\n");
            printf("�������, �� �������������� ����� ������� ������:\n");
            printf("1. ����� �����������\n");
            printf("2. ����� �����������\n");
            printf("3. ��� �����\n");
            printf("4. ʳ������ ���� � �����\n");
            printf("0. ����� ��� ���\n");
            printf("������ ����� �������: ");
            int choice;
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("������ ����� ����� �����������: ");
                scanf("%s", flights[i]->departure);
                break;
            case 2:
                printf("������ ����� ����� �����������: ");
                scanf("%s", flights[i]->destination);
                break;
            case 3:
                printf("������ ����� ��� �����: ");
                scanf("%s", flights[i]->aircraftType);
                break;
            case 4:
                printf("������ ���� ������� ���� � �����: ");
                scanf("%d", &(flights[i]->seats));
                break;
            case 0:
                printf("����� ��� ���.\n");
                return;
            default:
                printf("����������� ����.\n");
                return;
            }

            printf("���� ������ ������������.\n");
            break;
        }
    }

    if (!found) {
        printf("���� �� ��������.\n");
    }

    // ��������� �����
    FILE* file = fopen("flights.txt", "w");
    if (file == NULL) {
        printf("������� �������� �����.\n");
        return;
    }

    for (int i = 0; i < numFlights; i++) {
        fprintf(file, "%s;%s;%d;%s;%d\n", flights[i]->departure, flights[i]->destination, flights[i]->flightNumber, flights[i]->aircraftType, flights[i]->seats);
    }

    fclose(file);
}

int checkKey() {
    FILE* keyFile = fopen("key.txt", "r");
    if (keyFile == NULL) {
        printf("������� �������� ����� � ������.\n");
        return 0;
    }

    char key[50];
    printf("������ ����: ");
    scanf("%s", key);

    char correctKey[50];
    fgets(correctKey, sizeof(correctKey), keyFile);
    fclose(keyFile);

    // ��������� ������� ������ ����� � correctKey
    correctKey[strcspn(correctKey, "\n")] = '\0';

    if (strcmp(key, correctKey) == 0) {
        return 1; // ���� ����������
    }
    else {
        printf("������������ ����.\n");
        return 0; // ���� ������������
    }
}

void searchByDestination() {
    if (!checkKey()) {
        return; // ������� �������� �����, ������� �� ����������
    }
    char destination[50];
    printf("������ ����� �����������: ");
    scanf("%s", destination);

    printf("����� �� %s:\n", destination);
    printf("-----------------------------------------\n");
    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i]->destination, destination) == 0) {
            printf("����� �����: %d, ��� �����: %s\n",
                flights[i]->flightNumber,
                flights[i]->aircraftType);
        }
    }
    printf("-----------------------------------------\n");
}

void searchByAircraftType() {
    if (!checkKey()) {
        return; // ������� �������� �����, ������� �� ����������
    }
    char aircraftType[50];
    printf("������ ��� �����: ");
    scanf("%s", aircraftType);

    printf("����� �� ����� ����� %s:\n", aircraftType);
    printf("-----------------------------------------\n");
    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i]->aircraftType, aircraftType) == 0) {
            printf("����� �����: %d, ����� �����������: %s\n",
                flights[i]->flightNumber,
                flights[i]->destination);
        }
    }
    printf("-----------------------------------------\n");
}
