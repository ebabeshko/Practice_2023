#ifndef MODULES_H
#define MODULES_H

#include "Payment.h"

void addPayment(Payment** payments, int* count);
void deletePayment(Payment** payments, int* count);
void viewPayments(const Payment* payments, int count);
void editPayment(Payment* payments, int count);
void specialFunction1(const Payment* payments, int count);
void specialFunction2(const Payment* payments, int count);
void savePaymentsToFile(const Payment* payments, int count, const char* filename);
void clearFile(const char* filename);
int checkActivationKey(const char* filename, const char* userInput);

#endif  // MODULES_H
