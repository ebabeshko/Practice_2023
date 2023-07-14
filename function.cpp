#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <locale.h>
using namespace std;
void addRecord(std::list<Ad>& ads) {
    Ad newAd;
    std::cout << "������� ��������� ����������: ";
    std::getline(std::cin >> std::ws, newAd.title);
    std::cout << "������� ���������: ";
    std::cin >> newAd.cost;
    std::cout << "������� �����: ";
    std::getline(std::cin >> std::ws, newAd.city);
    std::cout << "������� �������: ";
    std::getline(std::cin >> std::ws, newAd.phone);

    if (ads.empty()) {
        newAd.number = 1;
    }
    else {
        int lastNumber = ads.back().number;
        newAd.number = lastNumber + 1;
    }

    ads.push_back(newAd);
    std::cout << "������ ���������." << std::endl;
}

void deleteRecord(std::list<Ad>& ads, int number) {
    auto it = ads.begin();
    while (it != ads.end()) {
        if (it->number == number) {
            it = ads.erase(it);
            std::cout << "������ �������." << std::endl;
            return;
        }
        else {
            ++it;
        }
    }

    std::cout << "������ � ������� " << number << " �� �������." << std::endl;
}

void printAdsByCity(const std::list<Ad>& ads, const std::string& city) {
    bool found = false;
    for (const auto& ad : ads) {
        if (ad.city == city) {
            std::cout << "����� ����������: " << ad.number << std::endl;
            std::cout << "��������� ����������: " << ad.title << std::endl;
            std::cout << "���������: " << ad.cost << std::endl;
            std::cout << "�����: " << ad.city << std::endl;
            std::cout << "�������: " << ad.phone << std::endl;
            std::cout << "--------------------------" << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "���������� � ������ " << city << " �� �������." << std::endl;
    }
}

void printAdsByCost(const std::list<Ad>& ads, float maxCost) {
    bool found = false;
    for (const auto& ad : ads) {
        if (ad.cost < maxCost) {
            std::cout << "����� ����������: " << ad.number << std::endl;
            std::cout << "��������� ����������: " << ad.title << std::endl;
            std::cout << "���������: " << ad.cost << std::endl;
            std::cout << "�����: " << ad.city << std::endl;
            std::cout << "�������: " << ad.phone << std::endl;
            std::cout << "--------------------------" << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "���������� �� ���������� ���� " << maxCost << " �� �������." << std::endl;
    }
}

void viewRecords(const std::list<Ad>& ads) {
    if (ads.empty()) {
        std::cout << "���� ������ �����." << std::endl;
        return;
    }

    for (const auto& ad : ads) {
        std::cout << "����� ����������: " << ad.number << std::endl;
        std::cout << "��������� ����������: " << ad.title << std::endl;
        std::cout << "���������: " << ad.cost << std::endl;
        std::cout << "�����: " << ad.city << std::endl;
        std::cout << "�������: " << ad.phone << std::endl;
        std::cout << "--------------------------" << std::endl;
    }
}

void editRecord(std::list<Ad>& ads, int number) {
    for (auto& ad : ads) {
        if (ad.number == number) {
            std::cout << "������� ����� ��������� ����������: ";
            std::getline(std::cin >> std::ws, ad.title);
            std::cout << "������� ����� ���������: ";
            std::cin >> ad.cost;
            std::cout << "������� ����� �����: ";
            std::getline(std::cin >> std::ws, ad.city);
            std::cout << "������� ����� �������: ";
            std::getline(std::cin >> std::ws, ad.phone);
            std::cout << "������ ��������." << std::endl;
            return;
        }
    }

    std::cout << "������ � ������� " << number << " �� �������." << std::endl;
}


void saveToFile(const std::list<Ad>& ads, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cout << "������ �������� ����� " << filename << " ��� ���������� ���� ������." << std::endl;
        return;
    }

    for (const auto& ad : ads) {
        file.write(reinterpret_cast<const char*>(&ad), sizeof(Ad));
    }

    file.close();
    if (file) {
        std::cout << "���� ������ ��������� � ����� " << filename << "." << std::endl;
    }
    else {
        std::cout << "������ ��� ������ � ���� " << filename << "." << std::endl;
    }
}

void exportToCSV(const std::list<Ad>& ads, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "����� ����������;��������� ����������;���������;�����;�������" << std::endl;
        for (const auto& ad : ads) {
            file << ad.number << ";" << ad.title << ";" << ad.cost << ";" << ad.city << ";" << ad.phone << "\n";
        }
        file.close();
        std::cout << "���� ������ �������������� � ���� " << filename << " � ������� CSV." << std::endl;
    }
    else {
        std::cout << "������ �������� ����� " << filename << " ��� �������� ���� ������." << std::endl;
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
                cout << "������� ��� ���� ������" << endl;
                cin >> databaseFilename;
                databaseFilename = line.substr(3);
            }
            else if (line.substr(0, 4) == "KEY=") {
                cout << "������� ����" << endl;
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
            cout << "������ ����� ���������������� ����." << endl;
        }
        else {
            cout << "������ �������� ����������������� �����." << endl;
            return;
        }
    }


}
