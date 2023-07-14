#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>

struct Ad {
    int number;
    std::string title;
    float cost;
    std::string city;
    std::string phone;
};

void addRecord(std::list<Ad>& ads);
void deleteRecord(std::list<Ad>& ads, int number);
void printAdsByCity(const std::list<Ad>& ads, const std::string& city);
void printAdsByCost(const std::list<Ad>& ads, float maxCost);
void viewRecords(const std::list<Ad>& ads);
void editRecord(std::list<Ad>& ads, int number);
void saveToFile(const std::list<Ad>& ads, const std::string& filename);
void exportToCSV(const std::list<Ad>& ads, const std::string& filename);
void changeSettings();

#endif
