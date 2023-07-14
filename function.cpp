#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <locale.h>
using namespace std;
void addRecord(std::list<Ad>& ads) {
    Ad newAd;
    std::cout << "Введите заголовок объявления: ";
    std::getline(std::cin >> std::ws, newAd.title);
    std::cout << "Введите стоимость: ";
    std::cin >> newAd.cost;
    std::cout << "Введите город: ";
    std::getline(std::cin >> std::ws, newAd.city);
    std::cout << "Введите телефон: ";
    std::getline(std::cin >> std::ws, newAd.phone);

    if (ads.empty()) {
        newAd.number = 1;
    }
    else {
        int lastNumber = ads.back().number;
        newAd.number = lastNumber + 1;
    }

    ads.push_back(newAd);
    std::cout << "Запись добавлена." << std::endl;
}

void deleteRecord(std::list<Ad>& ads, int number) {
    auto it = ads.begin();
    while (it != ads.end()) {
        if (it->number == number) {
            it = ads.erase(it);
            std::cout << "Запись удалена." << std::endl;
            return;
        }
        else {
            ++it;
        }
    }

    std::cout << "Запись с номером " << number << " не найдена." << std::endl;
}

void printAdsByCity(const std::list<Ad>& ads, const std::string& city) {
    bool found = false;
    for (const auto& ad : ads) {
        if (ad.city == city) {
            std::cout << "Номер объявления: " << ad.number << std::endl;
            std::cout << "Заголовок объявления: " << ad.title << std::endl;
            std::cout << "Стоимость: " << ad.cost << std::endl;
            std::cout << "Город: " << ad.city << std::endl;
            std::cout << "Телефон: " << ad.phone << std::endl;
            std::cout << "--------------------------" << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Объявления в городе " << city << " не найдены." << std::endl;
    }
}

void printAdsByCost(const std::list<Ad>& ads, float maxCost) {
    bool found = false;
    for (const auto& ad : ads) {
        if (ad.cost < maxCost) {
            std::cout << "Номер объявления: " << ad.number << std::endl;
            std::cout << "Заголовок объявления: " << ad.title << std::endl;
            std::cout << "Стоимость: " << ad.cost << std::endl;
            std::cout << "Город: " << ad.city << std::endl;
            std::cout << "Телефон: " << ad.phone << std::endl;
            std::cout << "--------------------------" << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Объявления со стоимостью ниже " << maxCost << " не найдены." << std::endl;
    }
}

void viewRecords(const std::list<Ad>& ads) {
    if (ads.empty()) {
        std::cout << "База данных пуста." << std::endl;
        return;
    }

    for (const auto& ad : ads) {
        std::cout << "Номер объявления: " << ad.number << std::endl;
        std::cout << "Заголовок объявления: " << ad.title << std::endl;
        std::cout << "Стоимость: " << ad.cost << std::endl;
        std::cout << "Город: " << ad.city << std::endl;
        std::cout << "Телефон: " << ad.phone << std::endl;
        std::cout << "--------------------------" << std::endl;
    }
}

void editRecord(std::list<Ad>& ads, int number) {
    for (auto& ad : ads) {
        if (ad.number == number) {
            std::cout << "Введите новый заголовок объявления: ";
            std::getline(std::cin >> std::ws, ad.title);
            std::cout << "Введите новую стоимость: ";
            std::cin >> ad.cost;
            std::cout << "Введите новый город: ";
            std::getline(std::cin >> std::ws, ad.city);
            std::cout << "Введите новый телефон: ";
            std::getline(std::cin >> std::ws, ad.phone);
            std::cout << "Запись изменена." << std::endl;
            return;
        }
    }

    std::cout << "Запись с номером " << number << " не найдена." << std::endl;
}


void saveToFile(const std::list<Ad>& ads, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "Ошибка открытия файла " << filename << " для сохранения базы данных." << std::endl;
        return;
    }

    for (const auto& ad : ads) {
        file.write(reinterpret_cast<const char*>(&ad), sizeof(Ad));
    }

    file.close();
    if (file) {
        std::cout << "База данных сохранена в файле " << filename << "." << std::endl;
    }
    else {
        std::cout << "Ошибка при записи в файл " << filename << "." << std::endl;
    }
}

void exportToCSV(const std::list<Ad>& ads, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Номер объявления;Заголовок объявления;Стоимость;Город;Телефон" << std::endl;
        for (const auto& ad : ads) {
            file << ad.number << ";" << ad.title << ";" << ad.cost << ";" << ad.city << ";" << ad.phone << "\n";
        }
        file.close();
        std::cout << "База данных экспортирована в файл " << filename << " в формате CSV." << std::endl;
    }
    else {
        std::cout << "Ошибка открытия файла " << filename << " для экспорта базы данных." << std::endl;
    }
}

void changeSettings() {
    string configFilename = "config.txt";
    string databaseFilename;
    string licenseKey;

    ifstream configFile(configFilename);
    if (configFile.is_open()) {
        string line;
        while (getline(configFile, line)) {
            if (line.substr(0, 3) == "DB=") {
                cout << "Введите имя базы данных" << endl;
                cin >> databaseFilename;
                databaseFilename = line.substr(3);
            }
            else if (line.substr(0, 4) == "KEY=") {
                cout << "Введите ключ" << endl;
                cin >> licenseKey;
                licenseKey = line.substr(4);

            }
        }

        configFile.close();
    }
    else {
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
            return;
        }
    }


}
