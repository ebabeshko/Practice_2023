#define _CRT_SECURE_NO_WARNINGS
#include "fyncc.h"
#include "stdlib.h"
#include "string.h"

void savePaymentsToFile(struct Payment* payments, int numPayments) {
    FILE* file = fopen("payments.txt", "w");
    if (file == NULL) {
        printf("�� ������� ������� ���� ���� �����.\n");
        return;
    }
    for (int i = 0; i < numPayments; i++) {
        fprintf(file, "%d;%s;%d;%d;%s;%.2f\n",
            payments[i].id,
            payments[i].surname,
            payments[i].account,
            payments[i].mfo,
            payments[i].date,
            payments[i].amount);
    }
    fclose(file);
}

void loadPaymentsFromFile(struct Payment** payments, int* numPayments) {
    FILE* file = fopen("payments.txt", "r");
    if (file == NULL) {
        printf("�� ������� ������� ���� ���� �����.\n");
        return;
    }
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    rewind(file);
    struct Payment* temp = (struct Payment*)malloc(count * sizeof(struct Payment));
    if (temp == NULL) {
        printf("������� �������� ���'��.\n");
        fclose(file);
        return;
    }
    int i = 0;
    while (fscanf(file, "%d;%[^;];%d;%d;%[^;];%f\n",
        &temp[i].id,
        temp[i].surname,
        &temp[i].account,
        &temp[i].mfo,
        temp[i].date,
        &temp[i].amount) == 6) {
        i++;
    }
    fclose(file);
    *payments = temp;
    *numPayments = count;
}

void addPayment(struct Payment** payments, int* numPayments) {
    struct Payment newPayment;
    printf("������ ������� ���������: ");
    scanf(" %[^\n]", newPayment.surname);
    printf("������ ������������� �������: ");
    scanf("%d", &newPayment.account);
    printf("������ ��� �����: ");
    scanf("%d", &newPayment.mfo);
    printf("������ ����: ");
    scanf(" %[^\n]", newPayment.date);
    printf("������ ����: ");
    scanf("%f", &newPayment.amount);
    newPayment.id = *numPayments + 1;
    (*numPayments)++;
    *payments = (struct Payment*)realloc(*payments, (*numPayments) * sizeof(struct Payment));
    (*payments)[*numPayments - 1] = newPayment;
}

void deletePayment(struct Payment** payments, int* numPayments, int id) {
    int index = -1;
    for (int i = 0; i < *numPayments; i++) {
        if ((*payments)[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("����� � ����� ID �� ��������.\n");
        return;
    }
    for (int i = index; i < *numPayments - 1; i++) {
        (*payments)[i] = (*payments)[i + 1];
    }
    (*numPayments)--;
    *payments = (struct Payment*)realloc(*payments, (*numPayments) * sizeof(struct Payment));
    printf("����� � ID %d ������ ��������.\n", id);
}

void modifyPayment(struct Payment* payments, int numPayments, int id) {
    int index = -1;
    for (int i = 0; i < numPayments; i++) {
        if (payments[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("����� � ����� ID �� ��������.\n");
        return;
    }
    struct Payment modifiedPayment;
    modifiedPayment.id = id;
    printf("������ ���� ������� ���������: ");
    scanf(" %[^\n]", modifiedPayment.surname);
    printf("������ ����� ������������� �������: ");
    scanf("%d", &modifiedPayment.account);
    printf("������ ���� ��� �����: ");
    scanf("%d", &modifiedPayment.mfo);
    printf("������ ���� ����: ");
    scanf(" %[^\n]", modifiedPayment.date);
    printf("������ ���� ����: ");
    scanf("%f", &modifiedPayment.amount);
    payments[index] = modifiedPayment;
    printf("����� � ID %d ������ ������.\n", id);
}

void displayPayments(struct Payment* payments, int numPayments) {
    for (int i = 0; i < numPayments; i++) {
        printf("ID: %d\n", payments[i].id);
        printf("������� ���������: %s\n", payments[i].surname);
        printf("������������� �������: %d\n", payments[i].account);
        printf("��� �����: %d\n", payments[i].mfo);
        printf("����: %s\n", payments[i].date);
        printf("����: %.2f\n", payments[i].amount);
        printf("\n");
    }
}

void displayPaymentsByAccountAndMFO(struct Payment* payments, int numPayments, int account, int mfo) {
    for (int i = 0; i < numPayments; i++) {
        if (payments[i].account == account && payments[i].mfo == mfo) {
            printf("ID: %d\n", payments[i].id);
            printf("������� ���������: %s\n", payments[i].surname);
            printf("������������� �������: %d\n", payments[i].account);
            printf("��� �����: %d\n", payments[i].mfo);
            printf("����: %s\n", payments[i].date);
            printf("����: %.2f\n", payments[i].amount);
            printf("\n");
        }
    }
}

void displayPaymentsByDateAndAmount(struct Payment* payments, int numPayments, char* date, float amount) {
    for (int i = 0; i < numPayments; i++) {
        if (strcmp(payments[i].date, date) == 0 && payments[i].amount == amount) {
            printf("ID: %d\n", payments[i].id);
            printf("������� ���������: %s\n", payments[i].surname);
            printf("������������� �������: %d\n", payments[i].account);
            printf("��� �����: %d\n", payments[i].mfo);
            printf("����: %s\n", payments[i].date);
            printf("����: %.2f\n", payments[i].amount);
            printf("\n");
        }
    }
}
