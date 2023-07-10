/*
* @file   KeyCreate.cpp
* @author Хоменко А.В., гр. 515i
* @date   10 липня 2023
* @brief  Практична робота. Варіант 4.
*
* Генератор випадкових ключів
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define KEY_LENGTH 16 // Довжина ключа

char generateRandomChar()
{
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int numCharacters = sizeof(characters) - 1; // -1 для врахування символу '\0'
    int randomIndex = rand() % numCharacters;
    return characters[randomIndex];
}

void generateRandomKey(char* key)
{
    int i;
    for (i = 0; i < KEY_LENGTH; i++) {
        key[i] = generateRandomChar();
    }
    key[i] = '\0'; // Додати завершуючий символ '\0' для отримання рядкового представлення ключа
}

int main()
{
    srand(time(NULL)); // Ініціалізувати генератор випадкових чисел зі значенням часу
    setlocale(LC_ALL, "Ukr");
    char key[KEY_LENGTH + 1]; // +1 для завершуючого символу '\0'

    generateRandomKey(key);

    FILE* file = fopen("F:\\111\\Practice_2023\\MainPractice\\MainPractice\\key.txt", "w"); // Відкрити файл для запису
    if (file == NULL) {
        printf("Не вдалося відкрити файл.\n");
        return 1;
    }

    fprintf(file, "%s\n", key); // Записати ключ у файл

    fclose(file); // Закрити файл
    char e;
    printf("Згенерований ключ записано в файл key.txt\n Key: %s\n Press e to exit: ", key);
    scanf("%c", &e);
    return 0;
}
