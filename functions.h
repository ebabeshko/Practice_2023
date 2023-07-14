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
Employee* load_database(const char* bname);
void add_record(Employee** head);
void delete_record(Employee** head, int id);
void display_records(Employee* head);
void modify_record(Employee* head, int id);
void save_database(Employee* head, const char* filename);

void export_cvs(Employee* head);
void export_dat(Employee* head);

void filter_post_date(Employee* head, const char* post, int day, int month, int year);
void filter_salary(Employee* head, float salary_threshold);