#include "pch.h"
#include "..\summer_practise_zaychenko\functions.c"

//Тест для функції displayRecords
TEST(DisplayRecordsTest, DisplaysNonDeletedRecords) {
    Student database[2];
    int size = 2;

    // Initialize the database records
    database[0].id = 1;
    database[0].deleted = 0;
    strcpy(database[0].name, "John Doe");
    database[0].group = 1;

    database[1].id = 2;
    database[1].deleted = 1; // Deleted record
    strcpy(database[1].name, "Jane Smith");
    database[1].group = 2;

    // Redirect stdout to a buffer
    testing::internal::CaptureStdout();
    displayRecords(database, size);
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the displayed records are correct
    EXPECT_NE(output.find("1\tJohn Doe\t1"), std::string::npos);
    EXPECT_EQ(output.find("2\tJane Smith\t2"), std::string::npos);
}
//Тестування функції saveConfig:
TEST(SaveConfigTest, SaveToFile) {
    Config config;
    strcpy(config.dbFileName, "database.db");
    strcpy(config.licenseKey, "abc123");
    const char* fileName = "test_config.txt";

    saveConfig(&config, fileName);

    // Перевірка наявності та вмісту файлу
    FILE* file = fopen(fileName, "r");
    ASSERT_TRUE(file != NULL);

    char line[100];
    fgets(line, sizeof(line), file); // Пропускаємо перший рядок
    fgets(line, sizeof(line), file); // Зчитуємо другий рядок
    fclose(file);

    // Перевірка, чи збереглися правильні значення
    EXPECT_STREQ(line, "KEY: abc123\n");

    // Видалення тестового файлу
    remove(fileName);
}

//Тестування функції initializeConfig
TEST(InitializeConfigTest, Initialize) {
    Config config;
    initializeConfig(&config);

    // Перевірка значень в структурі Config
    EXPECT_STREQ(config.dbFileName, "new_base");
    EXPECT_EQ(strlen(config.licenseKey), LICENSE_KEY_SIZE);
}



//Тестування функції loadDatabase
TEST(LoadDatabaseTest, LoadNonExistingFile) {
    const char* filename = "non_existing_file.bin";

    // Завантаження даних з неіснуючого файлу
    Student* loadedDatabase = nullptr;
    int loadedSize = 0;
    int nextId = 0;

    loadDatabase(&loadedDatabase, &loadedSize, &nextId, filename);

    // Перевірка, чи завантажено порожній масив
    EXPECT_EQ(loadedSize, 0);
    EXPECT_TRUE(loadedDatabase == nullptr);
}