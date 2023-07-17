// functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

#define LICENSE_KEY_SIZE 16
#define MAX_FILENAME_LENGTH 100

typedef struct {
    int id;
    char name[50];
    int group;
    int grades[10];
    int deleted;
} Student;

typedef struct {
    char dbFileName[MAX_FILENAME_LENGTH];
    char licenseKey[MAX_FILENAME_LENGTH];
} Config;

bool readConfig(Config* config, const char* configFileName);
void saveConfig(const Config* config, const char* fileName);
void initializeConfig(Config* config);
void addRecord(Student** database, int* size, int* nextId);
void deleteRecord(Student* database, int size);
void displayRecords(Student* database, int size);
void modifyRecord(Student* database, int size);
void saveDatabase(Student* database, int size, const char* filename);
void exportToCSV(Student* database, int size, const char* filename);
void searchByLastName(Student* database, int size);
void listAboveAverage(Student* database, int size);
void loadDatabase(Student** database, int* size, int* nextId, const char* filename);
void menuLoop(Student* database, int size, int nextId, const char* dbFileName);

#endif
