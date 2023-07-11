#include "Modules.h"
#include "Payment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Функція для додавання платежів
void addPayment(Payment** payments, int* count) {
    *payments = (Payment*)realloc(*payments, (*count + 1) * sizeof(Payment));

    Payment newPayment;
    printf("Enter surname: \n");
    fgets(newPayment.surname, sizeof(newPayment.surname), stdin);
    newPayment.surname[strcspn(newPayment.surname, "\n")] = '\0';

    printf("Enter account number:\n");
    scanf("%d", &newPayment.account_number);
    printf("Enter date (day month year): \n");
    scanf("%d %d %d", &newPayment.date[0], &newPayment.date[1], &newPayment.date[2]);
    printf("Enter amount: \n");
    scanf("%f", &newPayment.amount);

    (*payments)[*count] = newPayment;
    (*count)++;

    printf("Payment added successfully.\n");
}
//Функція видалення платежів
void deletePayment(Payment** payments, int* count) {
    int index;
    printf("Enter the index of the payment to delete: ");
    scanf("%d", &index);

    if (index >= 0 && index < *count) {
        for (int i = index; i < *count - 1; i++) {
            (*payments)[i] = (*payments)[i + 1];
        }

        *payments = (Payment*)realloc(*payments, (*count - 1) * sizeof(Payment));
        (*count)--;
        printf("Payment deleted successfully.\n");
    }
    else {
        printf("Invalid index. No payment deleted.\n");
    }
}
//Функція перегляду списку платежів
void viewPayments(const Payment* payments, int count) {
    printf("Payments:\n");
    for (int i = 0; i < count; i++) {
        printf("Payment %d:\n", i);
        printf("Surname: %s\n", payments[i].surname);
        printf("Account Number: %d\n", payments[i].account_number);
        printf("Date: %d %d %d\n", payments[i].date[0], payments[i].date[1], payments[i].date[2]);
        printf("Amount: %.2f\n", payments[i].amount);
        printf("-----------------------\n");
    }
}
//Функція змінення платежів
void editPayment(Payment* payments, int count) {
    int index;
    printf("Enter the index of the payment to edit: ");
    scanf("%d", &index);

    if (index >= 0 && index < count) {
        Payment* payment = &payments[index];

        printf("Enter new surname (or enter the old one): ");
        getchar();
        fgets(payment->surname, sizeof(payment->surname), stdin);
        payment->surname[strcspn(payment->surname, "\n")] = '\0';

        printf("Enter new account number: ");
        scanf("%d", &payment->account_number);
        printf("Enter new date (day month year): ");
        scanf("%d %d %d", &payment->date[0], &payment->date[1], &payment->date[2]);
        printf("Enter new amount: ");
        scanf("%f", &payment->amount);

        printf("Payment edited successfully.\n");
    }
    else {
        printf("Invalid index. No payment edited.\n");
    }
}
//Функція виведення усіх платежів конкретної людини
void specialFunction1(const Payment* payments, int count) {
    char surname[50];
    printf("Enter surname: ");
    fflush(stdin);
    fgets(surname, sizeof(surname), stdin);
    surname[strcspn(surname, "\n")] = '\0';

    printf("Payments for customer with surname '%s':\n", surname);
    for (int i = 0; i < count; i++) {
        if (strcmp(payments[i].surname, surname) == 0) {
            printf("Payment %d:\n", i);
            printf("Surname: %s\n", payments[i].surname);
            printf("Account Number: %d\n", payments[i].account_number);
            printf("Date: %d %d %d\n", payments[i].date[0], payments[i].date[1], payments[i].date[2]);
            printf("Amount: %.2f\n", payments[i].amount);
            printf("-----------------------\n");
        }
    }
}
//Функція виведення усіх платежів сума яких перевищує задану суму
void specialFunction2(const Payment* payments, int count) {
    int day, month, year;
    float amount;
    printf("Enter date (day month year): ");
    scanf("%d %d %d", &day, &month, &year);
    printf("Enter minimum amount: ");
    scanf("%f", &amount);

    printf("Payments with amount exceeding %.2f on %d %d %d:\n", amount, day, month, year);
    for (int i = 0; i < count; i++) {
        if (payments[i].amount > amount && payments[i].date[0] == day && payments[i].date[1] == month && payments[i].date[2] == year) {
            printf("Payment %d:\n", i);
            printf("Surname: %s\n", payments[i].surname);
            printf("Account Number: %d\n", payments[i].account_number);
            printf("Date: %d %d %d\n", payments[i].date[0], payments[i].date[1], payments[i].date[2]);
            printf("Amount: %.2f\n", payments[i].amount);
            printf("-----------------------\n");
        }
    }
}
//Функція очищення бази даних
void clearFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for clearing.\n");
        return;
    }

    fclose(file);
    printf("File '%s' cleared successfully.\n", filename);
}
//Функція збереження бази даних
void savePaymentsToFile(const Payment* payments, int count, const char* filename) {
    FILE* file = fopen(filename, "a+");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "Payment %d:\n", i);
        fprintf(file, "Surname: %s\n", payments[i].surname);
        fprintf(file, "Account Number: %d\n", payments[i].account_number);
        fprintf(file, "Date: %d %d %d\n", payments[i].date[0], payments[i].date[1], payments[i].date[2]);
        fprintf(file, "Amount: %.2f\n", payments[i].amount);
        fprintf(file, "-----------------------\n");
    }

    fclose(file);
    printf("Payments saved to file '%s' successfully.\n", filename);
}

//Перевірка ключа
int checkActivationKey(const char* filename, const char* userInput) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening activation key file.\n");
        return 0;  // Помилка читання файлу
    }

    char storedKey[100];
    fgets(storedKey, sizeof(storedKey), file);
    storedKey[strcspn(storedKey, "\n")] = '\0';

    fclose(file);

    if (strcmp(storedKey, userInput) == 0) {
        return 1;  // Ключ активації співпадає
    }
    else {
        return 0;  // Ключ активації не співпадає
    }
}
}
