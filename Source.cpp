#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Modules.h"

int main() {
    // Зчитування введеного ключа активації від користувача
    char userActivationKey[100];
    printf("Enter activation key: ");
    fgets(userActivationKey, sizeof(userActivationKey), stdin);
    userActivationKey[strcspn(userActivationKey, "\n")] = '\0';

    // Перевірка ключа активації
    if (!checkActivationKey("source.cfg", userActivationKey)) {
        printf("Invalid activation key. Exiting the program...\n");
        return 0;
    }


    Payment* payments = NULL;
    int paymentCount = 0;
    int choice;

    while (1) {
        printf("Menu:\n");
        printf("1. Add Payment\n");
        printf("2. Delete Payment\n");
        printf("3. View Payments\n");
        printf("4. Edit Payment\n");
        printf("5. Special Function 1\n");
        printf("6. Special Function 2\n");
        printf("7. Save Payments to File\n");
        printf("8. Clear File\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        getchar(); // Видалення символу нового рядка (\n) з буфера

        switch (choice) {
        case 0:
            printf("Exiting the program...\n");
            free(payments);
            return 0;
        case 1:
            addPayment(&payments, &paymentCount);
            break;
        case 2:
            deletePayment(&payments, &paymentCount);
            break;
        case 3:
            viewPayments(payments, paymentCount);
            break;
        case 4:
            editPayment(payments, paymentCount);
            break;
        case 5:
            specialFunction1(payments, paymentCount);
            break;
        case 6:
            specialFunction2(payments, paymentCount);
            break;
        case 7:
            savePaymentsToFile(payments, paymentCount, "payments.dat");
            break;
        case 8:
            clearFile("payments.dat");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    return 0;
}
