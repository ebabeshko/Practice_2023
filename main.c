/**
* @file practise *
* @author Lichakov V. O., гр. 515b, варіант 7 *
* @date *
* @brief Навчальна практика*
* База даних маршрутів потягів *
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "windows.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "cstdlib"

typedef struct {
	char trainNumber[20];
	char departureStation[25];
	char destinationStation[25];
	int departureTime[2]; // [0] - час, [1] - минуты
	struct node* next;// вказівник на наступний вузол
} trains;

void addTrain(FILE* file) {
	trains train;

	printf("Enter train number: ");
	scanf("%s", train.trainNumber);
	printf("Enter departure station: ");
	scanf("%s", train.departureStation);
	printf("Enter destination station: ");
	scanf("%s", train.destinationStation);
	printf("Enter departure time (hour minute): ");
	scanf("%d %d", &train.departureTime[0], &train.departureTime[1]);

	fwrite(&train, sizeof(trains), 1, file);
	printf("Train added successfully!\n");

};

void displayTrains(FILE* file) {
	trains train;

	fseek(file, 0, SEEK_SET); // Переходим в начало файла

	printf("Train List:\n\n");
	while (fread(&train, sizeof(trains), 1, file) == 1) {
		printf("Train Number: %s\n", train.trainNumber);
		printf("Departure Station: %s\n", train.departureStation);
		printf("Destination Station: %s\n", train.destinationStation);
		printf("Departure Time: %02d:%02d\n\n", train.departureTime[0], train.departureTime[1]);
	}
}

void deleteTrain(FILE* file) {
	trains train;
	char trainNumber[20];
	int found = 0;

	printf("Enter the train number to delete: ");
	scanf("%i", trainNumber);

	FILE* tempFile = fopen("temp.txt", "w+b");
	if (tempFile == NULL) {
		printf("Error creating temporary file.\n");
		return;
	}

	while (fread(&train, sizeof(trains), 1, file) == 1) {
		if (train.trainNumber != trainNumber) {
			fwrite(&train, sizeof(trains), 1, tempFile);
		}
		else {
			found = 1;
		}
	}

	fclose(file);
	fclose(tempFile);

	remove("data.txt");
	rename("temp.txt", "data.txt");

	if (found) {
		printf("Train deleted successfully!\n");
	}
	else {
		printf("Train not found.\n");
	}
}

int main()
{
	FILE* file;
	char line[100];
	char dataFileName[50] = "data.txt";

	file = fopen(dataFileName, "r+b");
	if (file == NULL) {
		// Если файл данных не существует, создаем его
		file = fopen(dataFileName, "w+b");
		if (file == NULL) {
			printf("Error creating data file.\n");
			return 1;
		}
	}

	int choice;
	while (1) {
		printf("Menu:\n");
		printf("1. Add Train\n");
		printf("2. Display Trains\n");
		printf("3. Change trains\n");
		printf("4. Delete trains\n");
		printf("5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			addTrain(file);
			break;
		case 2:
			displayTrains(file);
			break;
		case 4:
			deleteTrain(file);
			break;
		case 5:
			fclose(file);
			return 0;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	}
}
