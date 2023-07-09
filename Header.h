#pragma once

typedef struct {
    char purpose[100];
    char payer[100];
    int account_number;
    float amount;
} Payment;

int checkLicenseKey(const char* key);
void addRecord(Payment** database, int* numRecords, FILE* file);
void deleteRecord(Payment** database, int* numRecords, int recordId, FILE* file);
void viewRecords(Payment* database, int numRecords);
void modifyRecord(Payment* database, int numRecords, int recordId, FILE* file);
void viewPaymentsByAccount(Payment* database, int numRecords, int accountNumber);
void viewPaymentsByPurpose(Payment* database, int numRecords, const char* searchText);
