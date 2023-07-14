/**
* @file functions.
* @author Золотарьов Д.А., гр. 515б, варіант 13
* @date 13 липня 2023
* @brief Навчальна практика
*
* База даних співробітників
*/

#define KEY_LENGTH 9

void read_config(char* db_file, char* key);
void generate_license_key(char* key);
void create_config_file(const char* key);
void add_person(const char* db_file);
void delete_person(const char* db_file);
void display_all(const char* db_file);
void display_by_position_and_date(const char* db_file, const char* key);
void display_by_salary(const char* db_file, const char* key);
void save_database(const char* db_file, const char* key);
void export_database(const char* db_file, const char* key);
void change_config();
void modify_person(const char* db_file, const char* key);
