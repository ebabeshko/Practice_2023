#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <locale.h>
#include "function.h"

using namespace std;

int main() {
    string configFilename = "config.txt";
    string databaseFilename;
    string licenseKey;
    string city;
    string exportFilename;
    setlocale(LC_ALL, "Russian");

    // Проверка наличия конфигурационного файла
    ifstream configFile(configFilename);
    if (configFile.is_open()) {
        string line;
        while (getline(configFile, line)) {
            if (line.substr(0, 3) == "DB=") {
                databaseFilename = line.substr(3);
            }
            else if (line.substr(0, 4) == "KEY=") {
                licenseKey = line.substr(4);
            }
        }

        configFile.close();
    }
    else {
        cout << "Конфигурационный файл не найден. Создание нового файла." << endl;
        // Создание нового конфигурационного файла
        ofstream newConfigFile(configFilename);
        if (newConfigFile.is_open()) {
            newConfigFile << "DB=mybd.txt" << endl;
            newConfigFile << "KEY=01AFC56" << endl;
            newConfigFile.close();
            databaseFilename = "mybd.txt";
            licenseKey = "01AFC56";
            cout << "Создан новый конфигурационный файл." << endl;
        }
        else {
            cout << "Ошибка создания конфигурационного файла." << endl;
            return 1;
        }

        // Создание нового текстового файла CSV
        ofstream newDatabaseFile(databaseFilename);
        if (newDatabaseFile.is_open()) {
            newDatabaseFile.close();
            cout << "Создан новый файл базы данных." << endl;
        }
        else {
            cout << "Ошибка создания файла базы данных." << endl;
            return 1;
        }
    }

    cout << "Имя файла базы данных: " << databaseFilename << endl;
    cout << "Лицензионный ключ: " << licenseKey << endl;

    // Загрузка базы данных из файла
    list<Ad> ads;
    ifstream databaseFile(databaseFilename, ios::binary);
    if (databaseFile.is_open()) {
        while (!databaseFile.eof()) {
            Ad ad;
            databaseFile.read(reinterpret_cast<char*>(&ad), sizeof(Ad));
            if (!databaseFile.eof()) {
                ads.push_back(ad);
            }
        }
        databaseFile.close();
        cout << "База данных загружена из файла." << endl;
    }
    else {
        cout << "Файл базы данных не найден. Создан новый файл." << endl;
    }

    int choice;
    do {
        cout << "--------------------------" << endl;
        cout << "Ввод данных на анг "<< endl;
        cout << "--------------------------" << endl;
        cout << "Меню:" << endl;
        cout << "1. Добавить запись" << endl;
        cout << "2. Удалить запись" << endl;
        cout << "3. Вывести информацию обо всех объявлениях заданного города" << endl;
        cout << "4. Вывести информацию о объявлениях с ценой меньше заданной" << endl;
        cout << "5. Просмотреть все записи" << endl;
        cout << "6. Изменить запись" << endl;
        cout << "7. Сохранить базу данных в файл" << endl;
        cout << "8. Экспортировать базу данных в файл CSV" << endl;
        cout << "9. Изменить настройки" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: " << endl;
        
        cin >> choice;

        switch (choice) {
        case 1:
            addRecord(ads);
            break;
        case 2:
            int number;
            cout << "Введите номер записи для удаления: ";
            cin >> number;
            deleteRecord(ads, number);
            break;
        case 3:
            cout << "Введите город: ";
            getline(cin >> ws, city);
            printAdsByCity(ads, city);
            break;
        case 4:
            float maxCost;
            cout << "Введите максимальную стоимость: ";
            cin >> maxCost;
            printAdsByCost(ads, maxCost);
            break;
        case 5:
            viewRecords(ads);
            break;
        case 6:
            int editNumber;
            cout << "Введите номер записи для изменения: ";
            cin >> editNumber;
            editRecord(ads, editNumber);
            break;
        case 7:
            saveToFile(ads, databaseFilename);
            break;
        case 8:
            cout << "Введите имя файла для экспорта в формате CSV: ";
            cin >> exportFilename;
            exportToCSV(ads, exportFilename);
            break;
        case 9:
            changeSettings();
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте еще раз." << endl;
        }
    } while (choice != 0);

    return 0;
}
