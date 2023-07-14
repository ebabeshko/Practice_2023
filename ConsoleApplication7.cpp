// ConsoleApplication7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// @file practice.c
// @author Гуща В.В., гр. 515б, варіант 5
// @date 13 липень 2023
// @brief Навчальна практика
//База даних студентів



#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Структура, що відображає інформацію про автомобіль
struct Car {
    std::string licensePlate;
    std::string brand;
    std::string model;
    int year;
    int mileage;
    std::string bodyType;
};

// Функція додавання запису
void addRecord(std::vector<Car>& database) {
    Car car;

    std::cout << "Enter license plate: ";
    std::cin >> car.licensePlate;

    std::cout << "Enter brand: ";
    std::cin >> car.brand;

    std::cout << "Enter model: ";
    std::cin >> car.model;

    std::cout << "Enter year: ";
    std::cin >> car.year;

    std::cout << "Enter mileage: ";
    std::cin >> car.mileage;

    std::cout << "Enter body type: ";
    std::cin >> car.bodyType;

    database.push_back(car);

    std::cout << "Record added successfully!" << std::endl;
}

// Функція видалення запису
void deleteRecord(std::vector<Car>& database) {
    int id;

    std::cout << "Enter record ID to delete: ";
    std::cin >> id;

    if (id >= 0 && id < database.size()) {
        database.erase(database.begin() + id);
        std::cout << "Record deleted successfully!" << std::endl;
    }
    else {
        std::cout << "Invalid record ID!" << std::endl;
    }
}

// Функція перегляду записів
void viewRecords(const std::vector<Car>& database) {
    std::cout << "----- Records -----" << std::endl;

    for (int i = 0; i < database.size(); ++i) {
        std::cout << "ID: " << i << std::endl;
        std::cout << "License Plate: " << database[i].licensePlate << std::endl;
        std::cout << "Brand: " << database[i].brand << std::endl;
        std::cout << "Model: " << database[i].model << std::endl;
        std::cout << "Year: " << database[i].year << std::endl;
        std::cout << "Mileage: " << database[i].mileage << std::endl;
        std::cout << "Body Type: " << database[i].bodyType << std::endl;
        std::cout << "-------------------" << std::endl;
    }
}

// Функція зміни запису
void modifyRecord(std::vector<Car>& database) {
    int id;

    std::cout << "Enter record ID to modify: ";
    std::cin >> id;

    if (id >= 0 && id < database.size()) {
        Car& car = database[id];

        std::cout << "Enter new license plate: ";
        std::cin >> car.licensePlate;

        std::cout << "Enter new brand: ";
        std::cin >> car.brand;

        std::cout << "Enter new model: ";
        std::cin >> car.model;

        std::cout << "Enter new year: ";
        std::cin >> car.year;

        std::cout << "Enter new mileage: ";
        std::cin >> car.mileage;

        std::cout << "Enter new body type: ";
        std::cin >> car.bodyType;

        std::cout << "Record modified successfully!" << std::endl;
    }
    else {
        std::cout << "Invalid record ID!" << std::endl;
    }
}

// Функція виведення інформації про електромобілі
void printElectricCars(const std::vector<Car>& database) {
    std::cout << "----- Electric Cars -----" << std::endl;

    for (const Car& car : database) {
        if (car.licensePlate[6] == 'Z') {
            std::cout << "License Plate: " << car.licensePlate << std::endl;
            std::cout << "Brand: " << car.brand << std::endl;
            std::cout << "Model: " << car.model << std::endl;
            std::cout << "Year: " << car.year << std::endl;
            std::cout << "Mileage: " << car.mileage << std::endl;
            std::cout << "Body Type: " << car.bodyType << std::endl;
            std::cout << "-------------------" << std::endl;
        }
    }
}

// Функція виведення інформації про автомобілі за діапазоном років випуску та заданим типом кузову
void printCarsByYearAndBodyType(const std::vector<Car>& database, int minYear, int maxYear, const std::string& bodyType) {
    std::cout << "----- Cars by Year and Body Type -----" << std::endl;

    for (const Car& car : database) {
        if (car.year >= minYear && car.year <= maxYear && car.bodyType == bodyType) {
            std::cout << "License Plate: " << car.licensePlate << std::endl;
            std::cout << "Brand: " << car.brand << std::endl;
            std::cout << "Model: " << car.model << std::endl;
            std::cout << "Year: " << car.year << std::endl;
            std::cout << "Mileage: " << car.mileage << std::endl;
            std::cout << "Body Type: " << car.bodyType << std::endl;
            std::cout << "-------------------" << std::endl;
        }
    }
}

int main() {
    std::vector<Car> database;

    int choice;

    do {
        std::cout << "----- Car Database -----" << std::endl;
        std::cout << "1. Add Record" << std::endl;
        std::cout << "2. Delete Record" << std::endl;
        std::cout << "3. View Records" << std::endl;
        std::cout << "4. Modify Record" << std::endl;
        std::cout << "5. Print Electric Cars" << std::endl;
        std::cout << "6. Print Cars by Year and Body Type" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addRecord(database);
            break;
        case 2:
            deleteRecord(database);
            break;
        case 3:
            viewRecords(database);
            break;
        case 4:
            modifyRecord(database);
            break;
        case 5:
            printElectricCars(database);
            break;
        case 6:
            int minYear, maxYear;
            std::string bodyType;

            std::cout << "Enter minimum year: ";
            std::cin >> minYear;

            std::cout << "Enter maximum year: ";
            std::cin >> maxYear;

            std::cout << "Enter body type: ";
            std::cin >> bodyType;

            printCarsByYearAndBodyType(database, minYear, maxYear, bodyType);
            break;
        case 0:
            std::cout << "Exiting program..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            break;
        }

        std::cout << std::endl;
    } while (choice != 0);

    return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
