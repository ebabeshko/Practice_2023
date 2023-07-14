/**
* @file ConsoleApplication4.cpp
* @author Іл'ющенко Андрій, гр. 515б
* @date 9 липня 2023 р.
* @brief Навчальна практика
*
* База даних авіарейсів, варіант 12
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

#define MAX_AIRPORT_LENGTH 50
#define MAX_FILENAME_LENGTH 50
#define MAX_FLIGHTS 100

// Структура для збереження даних про окремий рейс
struct Flight {
    char departure[MAX_AIRPORT_LENGTH];
    char destination[MAX_AIRPORT_LENGTH];
    int number;
    int departure_time[2];
};

// Структура для збереження бази даних рейсів
struct Database {
    struct Flight flights[MAX_FLIGHTS];
    int count;
};

// Структура для збереження конфігурації програми
struct Configuration {
    char db_filename[MAX_FILENAME_LENGTH];
    char license_key[10];
};

// Функція для створення конфігураційного файлу
void create_configuration_file();


// Функція для читання конфігурації з файлу
void read_configuration(struct Configuration* config) {
    FILE* config_file = fopen("config.txt", "r");
    if (config_file == NULL) {
        printf("Configuration file not found. Creating a new one.\n");
        create_configuration_file();
        return;
    }

    fscanf(config_file, "DB = %s\nKEY = %s", config->db_filename, config->license_key);
    fclose(config_file);
}

// Функція для перевірки ліцензійного ключа
void check_license_key(const struct Configuration* config) {
    char input_license_key[11];
    printf("Enter the license key: ");
    scanf("%10s", input_license_key);

    if (strcmp(input_license_key, config->license_key) != 0) {
        printf("Invalid license key. Program terminated.\n");
        exit(EXIT_FAILURE);
    }
    else {
        printf("The key is correct, the program is available\n");
    }
}

void create_configuration_file() {
    FILE* config_file = fopen("config.txt", "w");
    if (config_file == NULL) {
        printf("Failed to create configuration file.\n");
        return;
    }

    struct Configuration config;

    printf("Enter the database filename: ");
    fgets(config.db_filename, MAX_FILENAME_LENGTH, stdin);
    config.db_filename[strcspn(config.db_filename, "\n")] = '\0'; // Видалення кінцевого нового рядка

    printf("Enter the license key: ");
    fgets(config.license_key, sizeof(config.license_key), stdin);
    config.license_key[strcspn(config.license_key, "\n")] = '\0'; // Видалення кінцевого нового рядка

    fprintf(config_file, "DB = config.db\nKEY = 0302JJ1971\n", config.db_filename, config.license_key);
    fclose(config_file);
}

// Функція для створення пустої бази даних
void create_empty_database(const char* filename) {
    FILE* db_file = fopen(filename, "wb");
    if (db_file == NULL) {
        printf("Failed to create the database file.\n");
        return;
    }

    struct Database db;
    db.count = 0;

    fwrite(&db, sizeof(struct Database), 1, db_file);
    fclose(db_file);
}

// Функція для завантаження бази даних з файлу
void load_database(struct Database* db, const char* filename) {
    FILE* db_file = fopen(filename, "rb");
    if (db_file == NULL) {
        printf("Failed to open the database file.\n");
        return;
    }

    fread(db, sizeof(struct Database), 1, db_file);
    fclose(db_file);
}

// Функція для додавання нового рейсу до бази даних
void add_flight(struct Database* db) {
    if (db->count == MAX_FLIGHTS) {
        printf("Database is full. Cannot add more flights.\n");
        return;
    }

    struct Flight new_flight;

    printf("Enter the departure airport: ");
    fgets(new_flight.departure, MAX_AIRPORT_LENGTH, stdin);
    new_flight.departure[strcspn(new_flight.departure, "\n")] = '\0';

    printf("Enter the destination airport: ");
    fgets(new_flight.destination, MAX_AIRPORT_LENGTH, stdin);
    new_flight.destination[strcspn(new_flight.destination, "\n")] = '\0';

    printf("Enter the flight number: ");
    scanf("%d", &new_flight.number);

    printf("Enter the departure time (hour minute): ");
    scanf("%d %d", &new_flight.departure_time[0], &new_flight.departure_time[1]);

    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Очистити вхідний буфер

    db->flights[db->count++] = new_flight;

    printf("Flight added successfully.\n");
}

// Функція для видалення рейсу з бази даних
void delete_flight(struct Database* db, int flight_number) {
    int i;
    for (i = 0; i < db->count; i++) {
        if (db->flights[i].number == flight_number) {
            break;
        }
    }

    if (i == db->count) {
        printf("Flight not found.\n");
        return;
    }

    for (; i < db->count - 1; i++) {
        db->flights[i] = db->flights[i + 1];
    }

    db->count--;

    printf("Flight deleted successfully.\n");
}

// Функція для виведення списку всіх рейсів
void display_flights(const struct Database* db) {
    if (db->count == 0) {
        printf("No flights available.\n");
        return;
    }

    printf("Flight List:\n");
    for (int i = 0; i < db->count; i++) {
        printf("Flight %d:\n", i + 1);
        printf("Departure: %s\n", db->flights[i].departure);
        printf("Destination: %s\n", db->flights[i].destination);
        printf("Number: %d\n", db->flights[i].number);
        printf("Departure Time: %02d:%02d\n", db->flights[i].departure_time[0], db->flights[i].departure_time[1]);
        printf("\n");
    }
}

// Функція для редагування рейсу
void change_flight(struct Database* db, int flight_number) {
    int i;
    for (i = 0; i < db->count; i++) {
        if (db->flights[i].number == flight_number) {
            break;
        }
    }

    if (i == db->count) {
        printf("Flight not found.\n");
        return;
    }

    struct Flight* flight = &db->flights[i];

    printf("Flight found. Enter new details:\n");

    printf("Enter the departure airport: ");
    fgets(flight->departure, MAX_AIRPORT_LENGTH, stdin);
    flight->departure[strcspn(flight->departure, "\n")] = '\0';

    printf("Enter the destination airport: ");
    fgets(flight->destination, MAX_AIRPORT_LENGTH, stdin);
    flight->destination[strcspn(flight->destination, "\n")] = '\0';

    printf("Enter the new flight number: ");
    scanf("%d", &flight->number);

    printf("Enter the new departure time (hour minute): ");
    scanf("%d %d", &flight->departure_time[0], &flight->departure_time[1]);

    getchar();

    printf("Flight details updated successfully.\n");
}

// Функція для збереження бази даних у файл
void save_database(const struct Database* db, const char* filename) {
    FILE* db_file = fopen(filename, "wb");
    if (db_file == NULL) {
        printf("Failed to save the database.\n");
        return;
    }

    fwrite(db, sizeof(struct Database), 1, db_file);
    fclose(db_file);

    printf("Database saved successfully.\n");
}

// Функція для експорту бази даних у формат CSV
void export_to_csv(const struct Database* db, const char* filename) {
    FILE* csv_file = fopen(filename, "w");
    if (csv_file == NULL) {
        printf("Failed to export to CSV.\n");
        return;
    }

    fprintf(csv_file, "Departure, Destination, Number, Departure Time\n");

    for (int i = 0; i < db->count; i++) {
        fprintf(csv_file, "%s, %s, %d, %02d:%02d\n", db->flights[i].departure, db->flights[i].destination,
            db->flights[i].number, db->flights[i].departure_time[0], db->flights[i].departure_time[1]);
    }

    fclose(csv_file);

    printf("Export to CSV completed successfully.\n");
}

// Функція для виведення списку рейсів до певного пункту призначення
void display_flights_to_destination(const struct Database* db, const char* destination) {
    printf("Flights to %s:\n", destination);

    int found = 0;

    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->flights[i].destination, destination) == 0) {
            printf("Flight %d:\n", i + 1);
            printf("Departure: %s\n", db->flights[i].departure);
            printf("Destination: %s\n", db->flights[i].destination);
            printf("Number: %d\n", db->flights[i].number);
            printf("Departure Time: %02d:%02d\n", db->flights[i].departure_time[0], db->flights[i].departure_time[1]);
            printf("\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No flights found to %s.\n", destination);
    }
}

// Функція для виведення списку рейсів після певного часу
void display_flights_after_time(const struct Database* db, int hour) {
    printf("Flights after %02d:00:\n", hour);

    int found = 0;

    for (int i = 0; i < db->count; i++) {
        if (db->flights[i].departure_time[0] >= hour) {
            printf("Flight %d:\n", i + 1);
            printf("Departure: %s\n", db->flights[i].departure);
            printf("Destination: %s\n", db->flights[i].destination);
            printf("Number: %d\n", db->flights[i].number);
            printf("Departure Time: %02d:%02d\n", db->flights[i].departure_time[0], db->flights[i].departure_time[1]);
            printf("\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No flights found after %02d:00.\n", hour);
    }
}

// Функція для виведення всієї бази даних
void display_database(const struct Database* db) {
    printf("Database:\n");
    printf("Flight Count: %d\n", db->count);
    printf("Flights:\n");
    for (int i = 0; i < db->count; i++) {
        printf("Flight %d:\n", i + 1);
        printf("Departure: %s\n", db->flights[i].departure);
        printf("Destination: %s\n", db->flights[i].destination);
        printf("Number: %d\n", db->flights[i].number);
        printf("Departure Time: %02d:%02d\n", db->flights[i].departure_time[0], db->flights[i].departure_time[1]);
        printf("\n");
    }
}

int main() {
    struct Configuration config;
    read_configuration(&config);
    check_license_key(&config);
    struct Database db;

    FILE* db_file = fopen(config.db_filename, "rb");
    if (db_file == NULL) {
        printf("Database file not found. Creating a new one.\n");
        create_empty_database(config.db_filename);
    }
    else {
        load_database(&db, config.db_filename);
        fclose(db_file);
    }

    int choice;
    int flight_number;
    char destination[MAX_AIRPORT_LENGTH];
    int hour;

    // Меню вибору
    while (1) {
        printf("Menu:\n");
        printf("1. Add a flight\n");
        printf("2. Delete a flight\n");
        printf("3. View flights\n");
        printf("4. Change flight details\n");
        printf("5. Save database\n");
        printf("6. Export to CSV\n");
        printf("7. Display flights to destination\n");
        printf("8. Display flights after time\n");
        printf("9. Display database\n");
        printf("10. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Очистити символ нового рядка

        switch (choice) {
        case 1:
            add_flight(&db);
            break;
        case 2:
            printf("Enter the flight number to delete: ");
            scanf("%d", &flight_number);
            getchar();
            delete_flight(&db, flight_number);
            break;
        case 3:
            display_flights(&db);
            break;
        case 4:
            printf("Enter the flight number to change details: ");
            scanf("%d", &flight_number);
            getchar();
            change_flight(&db, flight_number);
            break;
        case 5:
            save_database(&db, config.db_filename);
            break;
        case 6:
            export_to_csv(&db, "database.csv");
            break;
        case 7:
            printf("Enter the destination airport: ");
            fgets(destination, MAX_AIRPORT_LENGTH, stdin);
            destination[strcspn(destination, "\n")] = '\0';
            display_flights_to_destination(&db, destination);
            break;
        case 8:
            printf("Enter the hour: ");
            scanf("%d", &hour);
            getchar();
            display_flights_after_time(&db, hour);
            break;
        case 9:
            display_database(&db);
            break;
        case 10:
            printf("Exiting...\n");
            return 0; // Вихід з програми
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }

        printf("\n");
    }

    return 0;
}
