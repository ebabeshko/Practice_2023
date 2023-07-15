/**
* @file TAsk.cpp
* @author Костянюк Михайло Віталійович, гр. 515і, варіант 11
* @date 11.07.2023
* @brief Практика
*
* База даних студентів
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define CONFIG_FILE "configurating.txt"
#define MAX_KEY_LENGTH 10

typedef struct {
    int id_product; /* Код товару */
    char name[MAX_NAME_LENGTH]; /* Назва товару */
    char group[MAX_NAME_LENGTH]; /* Група товару */
    float cost; /* Ціна */
    char provider[MAX_NAME_LENGTH]; /* Постачальник товару */
    int date[6]; /* Дата та час */
    int isDeleted;
} AuctionProduct;

typedef struct {
    char dbFile[MAX_NAME_LENGTH];
    char key[MAX_KEY_LENGTH];
} Config;

// Функція для отримання налаштувань з конфігураційного файлу
Config getConfig() {

    Config config = { 0 };;
    FILE* configFile = fopen(CONFIG_FILE, "r");
    if (configFile == NULL) {
        // Створення нового конфігураційного файлу, якщо він не існує
        configFile = fopen(CONFIG_FILE, "w");
        if (configFile == NULL) {
            perror("Failed to create configuration file"); // Не вдалося створити конфігураційний файл
            exit(EXIT_FAILURE);
        }
        fprintf(configFile, "DB = database.db\n");
        fprintf(configFile, "KEY = ABCD12345\n");
        fclose(configFile);

        // Повторне відкриття щойно створеного файлу
        configFile = fopen(CONFIG_FILE, "r");
        if (configFile == NULL) {
            perror("Failed to open configuration file"); // Не вдалося відкрити конфігураційний файл
            exit(EXIT_FAILURE);
        }
    }

    char strin[100];
    while (fgets(strin, sizeof(strin), configFile)) {
        if (strncmp(strin, "DB =", 4) == 0) {
            int result = sscanf(strin, "DB = %s", config.dbFile);
            if (result != 1) {
                // Обробка помилки при розборі рядка
            }
        }
        else if (strncmp(strin, "KEY =", 5) == 0) {
            int result = sscanf(strin, "KEY = %s", config.key);
            if (result != 1) {

            }
        }
    }

    fclose(configFile);
    return config;
}

// Функція для додавання запису до бази даних
AuctionProduct* addRecord(AuctionProduct** products, int* count) {
    AuctionProduct product;
    printf("\n");
    printf("Enter the name of the product: ");
    fgets(product.name, sizeof(product.name), stdin);
    product.name[strcspn(product.name, "\n")] = '\0'; // Удаление символа новой строки

    printf("Enter the product group: ");
    fgets(product.group, sizeof(product.group), stdin);
    product.group[strcspn(product.group, "\n")] = '\0'; // Удаление символа новой строки

    printf("Enter the price of the product: ");
    scanf("%f", &product.cost);
    getchar();

    printf("Enter the name of the product supplier: ");
    fgets(product.provider, sizeof(product.provider), stdin);
    product.provider[strcspn(product.provider, "\n")] = '\0'; // Удаление символа новой строки

    printf("Enter the date and time of delivery of the goods (YYYY MM DD HH MM): ");
    scanf("%d %d %d %d %d", &product.date[0], &product.date[1], &product.date[2], &product.date[3], &product.date[4]);
    printf("\n");
    getchar();

    product.isDeleted = 0;

    product.id_product = *count;
    AuctionProduct* newProducts = (AuctionProduct*)realloc(*products, (*count + 1) * sizeof(AuctionProduct));
    if (newProducts == NULL) {
        perror("Failed to reallocate memory");
        exit(EXIT_FAILURE);
    }
    else {
        *products = newProducts;
        (*products)[*count] = product;
        (*count)++;
    }

    return *products;
}

// Функція для видалення запису з бази даних
void deleteRecord(AuctionProduct* products, int* count, int id_product) {
    if (id_product < 0 || id_product >= *count) {
        printf("Invalid record ID\n");
        return;
    }

    if (products[id_product].isDeleted) {
        printf("Record has already been deleted\n");
        return;
    }

    products[id_product].isDeleted = 1;
    printf("Record with ID %d has been deleted\n", id_product);
    printf("\n");
    // Зсуваємо товари після віддаленого елемента
    for (int i = id_product + 1; i < *count; i++) {
        products[i - 1] = products[i];
        products[i - 1].id_product = i - 1;
    }

    (*count)--;
}

// Функція для перегляду записів бази даних
void viewRecords(AuctionProduct* products, int count) {
    printf("\n");
    printf("%-5s|%-20s|%-20s|%-10s|%-20s|%-20s|\n", "ID", "Name", "Group", "Cost", "Provider", "Date");
    printf("\n");
    for (int i = 0; i < count; i++) {
        if (!products[i].isDeleted) {
            printf("%-5d|%-20s|%-20s|%-10.2f|%-20s|%.2d/%.2d/%.2d %.2d:%.2d|\n",
                products[i].id_product, products[i].name, products[i].group, products[i].cost, products[i].provider,
                products[i].date[0], products[i].date[1], products[i].date[2],
                products[i].date[3], products[i].date[4]);
        }
    }
}

// Функція для зміни запису в базі даних
void modifyRecord(AuctionProduct* products, int count, int id_product) {
    if (id_product < 0 || id_product >= count) {
        printf("Invalid record ID\n");
        return;
    }

    if (products[id_product].isDeleted) {
        printf("Record has been deleted\n");
        return;
    }

    AuctionProduct modifiedProduct = products[id_product];
    printf("\n");
    printf("Enter new product name (leave blank to keep the same): ");
    fgets(modifiedProduct.name, sizeof(modifiedProduct.name), stdin);
    modifiedProduct.name[strcspn(modifiedProduct.name, "\n")] = '\0'; // Удаляем символ новой строки

    printf("Enter new group name (leave blank to keep the same): ");
    fgets(modifiedProduct.group, sizeof(modifiedProduct.group), stdin);
    modifiedProduct.group[strcspn(modifiedProduct.group, "\n")] = '\0'; // Удаляем символ новой строки

    printf("Enter new product cost (leave blank to keep the same): ");
    char costInput[10];
    fgets(costInput, sizeof(costInput), stdin);
    if (costInput[0] != '\n') {
        sscanf(costInput, "%f", &modifiedProduct.cost);
    }

    printf("Enter new provider name (leave blank to keep the same): ");
    fgets(modifiedProduct.provider, sizeof(modifiedProduct.provider), stdin);
    modifiedProduct.provider[strcspn(modifiedProduct.provider, "\n")] = '\0'; // Удаляем символ новой строки

    printf("Enter new product date and time (YYYY MM DD HH MM, leave blank to keep the same): ");
    char dateInput[50];
    fgets(dateInput, sizeof(dateInput), stdin);
    if (dateInput[0] != '\n') {
        sscanf(dateInput, "%d %d %d %d %d",
            &modifiedProduct.date[0], &modifiedProduct.date[1], &modifiedProduct.date[2],
            &modifiedProduct.date[3], &modifiedProduct.date[4]);
    }

    // Проверяем, были ли введены новые значения, и сохраняем предыдущие значения при отсутствии ввода
    if (modifiedProduct.name[0] == '\0') {
        strcpy(modifiedProduct.name, products[id_product].name);
    }
    if (modifiedProduct.group[0] == '\0') {
        strcpy(modifiedProduct.group, products[id_product].group);
    }
    if (costInput[0] == '\n') {
        modifiedProduct.cost = products[id_product].cost;
    }
    if (modifiedProduct.provider[0] == '\0') {
        strcpy(modifiedProduct.provider, products[id_product].provider);
    }
    if (dateInput[0] == '\n') {
        memcpy(modifiedProduct.date, products[id_product].date, sizeof(modifiedProduct.date));
    }

    products[id_product] = modifiedProduct;
}


// Функция для виведення усіх товарів заданої групи, ціна яких нижче за задану
void printProductsInRange(AuctionProduct* products, int count, const char* group, float maxCost) {
    printf("\n");
    printf("Products within the specified cost range:\n");
    printf("%-5s|%-20s|%-20s|%-10s|%-20s|\n", "ID", "Name", "Group", "Cost", "Provider");
    for (int i = 0; i < count; i++) {
        if (!products[i].isDeleted && strcmp(products[i].group, group) == 0 && products[i].cost < maxCost) {
            printf("%-5d|%-20s|%-20s|%-10.2f|%-20s|\n", products[i].id_product, products[i].name, products[i].group, products[i].cost, products[i].provider);
        }
    }
}

// Функція для виведення усіх товарів, що постачаються заданим постачальником
void printProductsByProvider(AuctionProduct* products, int count, const char* purveyor) {
    printf("\n");
    printf("Products owned by one provider:\n");
    printf("%-5s|%-20s|%-20s|%-10s|%-20s|\n", "ID", "Name", "Group", "Cost", "Date");
    for (int i = 0; i < count; i++) {
        if (!products[i].isDeleted && strcmp(products[i].provider, purveyor) == 0) {
            printf("%-5d|%-20s|%-20s|%-10.2f|%.2d/%.2d/%.2d %.2d:%.2d|\n",
                products[i].id_product, products[i].name, products[i].group, products[i].cost,
                products[i].date[0], products[i].date[1], products[i].date[2],
                products[i].date[3], products[i].date[4]);
        }
    }
}

// Функція для збереження бази даних у файлі
void saveDatabase(AuctionProduct* products, int count) {
    char dbFileName[MAX_NAME_LENGTH];
    printf("\n");
    printf("Enter the name of the database file: ");
    fgets(dbFileName, sizeof(dbFileName), stdin);
    dbFileName[strcspn(dbFileName, "\n")] = '\0'; // Удаление символа новой строки

    FILE* file = fopen(dbFileName, "wb");
    if (file == NULL) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    fwrite(products, sizeof(AuctionProduct), count, file);

    fclose(file);

    printf("Database saved successfully as %s\n", dbFileName);
    printf("\n");
}

// Функція для експорту бази даних у текстовий файл формату CSV
void exportCSV(AuctionProduct* products, int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }
    printf("\n");
    fprintf(file, "ID;Name;Group;Cost;Provider;Date\n");
    printf("\n");
    for (int i = 0; i < count; i++) {
        if (!products[i].isDeleted) {
            fprintf(file, "%d;%s;%s;%.2f;%s; %d.%d.%d %02d:%02d\n",
                products[i].id_product, products[i].name, products[i].group, products[i].cost, products[i].provider,
                products[i].date[0], products[i].date[1], products[i].date[2],
                products[i].date[3], products[i].date[4]);
        }
    }
    fclose(file);
}




void open_input_database(AuctionProduct** products, int* count) {
    if (*products != NULL) {
        free(*products);
        *products = NULL;
        *count = 0;
    }
    printf("\n");
    char db_file_name[MAX_NAME_LENGTH];
    printf("Enter the name of the database file to open: ");
    fgets(db_file_name, sizeof(db_file_name), stdin);
    db_file_name[strcspn(db_file_name, "\n")] = '\0'; // Удаление символа новой строки

    FILE* db_file;
    if (fopen_s(&db_file, db_file_name, "rb") != 0) {
        printf("Error opening the database file.\n");
        return;
    }

    AuctionProduct product;
    while (fread(&product, sizeof(AuctionProduct), 1, db_file)) {
        AuctionProduct* temp = (AuctionProduct*)realloc(*products, (*count + 1) * sizeof(AuctionProduct));
        if (temp == NULL) {
            perror("Memory reallocation failed");
            fclose(db_file);
            exit(EXIT_FAILURE);
        }
        *products = temp;
        (*products)[*count] = product;
        (*count)++;
    }

    fclose(db_file);
    printf("\n");
    printf("Database file %s opened successfully.\n", db_file_name);
    printf("\n");
}


void createDatabaseFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        file = fopen(filename, "wb");
        if (file == NULL) {
            printf("\n");
            perror("Database file creation failed");
            exit(EXIT_FAILURE);
        }
        fclose(file);
        printf("\n");
        printf("Database file created: %s\n", filename);
    }
    else {
        fclose(file);
    }
}

int main() {

    Config config = getConfig();
    // Запрос ліцензійного ключа у користувача
    char licenseKey[MAX_KEY_LENGTH];
    printf("Enter license key: ");
    fgets(licenseKey, sizeof(licenseKey), stdin);
    licenseKey[strcspn(licenseKey, "\n")] = '\0'; // Видалення символу нового рядка

    // Перевірка ліцензійного ключа
    int isValidKey = 0;
    if (atoi(licenseKey) % 1024 == 0) {
        isValidKey = 1;
    }

    // Перевірка доступу до функцій
    if (isValidKey) {
        printf("License key is valid. Access granted to all functions.\n");
        printf("\n");
    }
    else {
        printf("Invalid license key. Access restricted.\n");
        printf("\n");
    }

    AuctionProduct* products = NULL;
    int count = 0;

    FILE* file = fopen(config.dbFile, "rb");
    if (file != NULL) {
        AuctionProduct product;
        while (fread(&product, sizeof(AuctionProduct), 1, file)) {

            AuctionProduct* temp = (AuctionProduct*)realloc(products, (count + 1) * sizeof(AuctionProduct));
            if (temp == NULL) {
                perror("Memory reallocation failed");
                free(products); // Звільняємо пам'ять, виділену раніше
                exit(EXIT_FAILURE);
            }
            products = temp;
            products[count] = product;
            count++;
        }

        fclose(file);
    }


    int choice;
    do {
        printf("\n");
        printf("Menu:\n");
        printf("1. Add record\n");
        printf("2. Delete record\n");
        printf("3. View records\n");
        printf("4. Modify record\n");
        printf("5. Print products within cost range\n");
        printf("6. Print products owned by one provider\n");
        printf("7. Save database\n");
        printf("8. Export database to CSV\n");
        printf("9. Input database\n");
        printf("0. Exit\n");
        printf("\n");
        printf("Enter your choice: ");
        scanf_s("%d", &choice);
        (void)getchar(); // Читання символу нового рядка після введення вибору

        switch (choice) {
        case 1:
            if (isValidKey) {
                products = addRecord(&products, &count);
            }
            else {
                printf("\n");
                printf("Access denied. Invalid license key.\n");
                printf("\n");
            }
            break;
        case 2:
            if (isValidKey) {
                int id;
                printf("\n");
                printf("Enter the ID of the record to delete: ");
                scanf_s("%d", &id);
                printf("\n");
                deleteRecord(products, &count, id);
            }
            else {
                printf("\n");
                printf("Access denied. Invalid license key.\n");
                printf("\n");
            }
            break;
        case 3:
            viewRecords(products, count);
            break;
        case 4: {
            if (isValidKey) {
                int id;
                printf("\n");
                printf("Enter the ID of the record to modify: ");
                scanf_s("%d", &id);
                printf("\n");
                (void)getchar(); // Читання символу нового рядка після введення ID
                modifyRecord(products, count, id);
                break;
            }
            else {
                printf("\n");
                printf("Access denied. Invalid license key.\n");
                printf("\n");
            }
            break;
        }
        case 5: {
            if (isValidKey) {
                char group[100];
                float maxCost;
                printf("\n");
                printf("Enter the group of product: ");
                fgets(group, sizeof(group), stdin);
                group[strcspn(group, "\n")] = '\0'; // Удаление символа новой строки

                printf("Enter the special cost: ");
                scanf("%f", &maxCost);
                printf("\n");
                getchar(); // Читання нового рядка після введення вартості

                printProductsInRange(products, count, group, maxCost);
            }
            else {
                printf("\n");
                printf("Access denied. Invalid license key.\n");
                printf("\n");
            }
            break;
        }
        case 6: {
            if (isValidKey) {
                char purveyor[50];
                printf("\n");
                printf("Enter the provider: ");
                scanf(" %[^\n]", purveyor);
                printf("\n");
                (void)getchar(); // Читання символу нового рядка після введення дати
                printProductsByProvider(products, count, purveyor);
                break;
            }
            else {
                printf("\n");
                printf("Access denied. Invalid license key.\n");
                printf("\n");
            }
            break;
        }
        case 7:
        {if (isValidKey) {
            saveDatabase(products, count);
            break;
        }
        else {
            printf("\n");
            printf("Access denied. Invalid license key.\n");
            printf("\n");
        }
        break;

        }

        case 8: if (isValidKey) {
            exportCSV(products, count, "database.csv");
            printf("\n");
            printf("Database exported to 'database.csv'\n");
            printf("\n");
        }
              else {
            printf("\n");
            printf("Access denied. Invalid license key.\n");
            printf("\n");
        }
              break;


        case 9:
            open_input_database(&products, &count);
            break;
        case 0:
            printf("\n");
            printf("Goodbye!\n");
            break;
        default:
            printf("\n");
            printf("Invalid choice\n");
            break;
        }
    } while (choice != 0);

    free(products);

    return EXIT_SUCCESS;
}