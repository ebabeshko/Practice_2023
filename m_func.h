#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

typedef struct {
	int id;
	char name[100];
	char post[100];
	int hire_date[3];
	float salary;
	struct Employee* next;
} Employee;

void config_check(const char* fname, char* bname, char* key);
void keygen(const char* fname, const char* bname, char* key);
Employee* loadDatabase(const char* bname);
void addRecord(Employee** head);
void deleteRecord(Employee** head, int id);
void displayRecords(Employee* head);
void modifyRecord(Employee* head, int id);
void saveDatabase(Employee* head, const char* filename);