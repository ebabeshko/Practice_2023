/**
* @file RRProject.cpp
* @author ��������� �. �., ��. 515-�, ������ 11
* @date 18.05.2023
* @brief ������������ ������
*
* ���� ����� ��������
*/

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include "RRPModuleC.h"

int main(int argc, char* argv[]) {

	//���������� �������� ������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ukr");

	//���������� ����� ������� �� �������� �� �� ��������
	FILE* fppr;
	FILE* fcsv;
	if (fopen_s(&fppr ,"Murka.txt", "r")) {
		puts("\n ������� �������� ����� Murka.txt");
		return ERROR_TYPE;
	}
	if (fopen_s(&fcsv, "mybd.csv", "r+b")) {
		puts("\n ������� �������� ����� mybd.csv");
		return ERROR_TYPE;
	}

	//������� ���������
	else {
		//������� ������
		char dbPath[100] = " ";
		char key[100] = " ";
		char buffer[100];

		//���� �� ���������� �������������� �����
		while (fgets(buffer, sizeof(buffer), fppr)) {
			// ���������� ������-�����������
			if (buffer[0] == ';' || buffer[0] == '#') {
				continue;
			}
			//�����
			sscanf_s(buffer, "DB = %99s\n", dbPath, 99);
			sscanf_s(buffer, "KEY = %99s\n", key, 99);
		}
				
				/*
						������� ��������� �����, ���� ����� ������� ������ 6,
					���� ������� �� 13 ��� ������, ��� ���� �����
				
						�����, 123 - 6 = 117; => 117 % 13 = 0;
				
						���� ����� 0, ����� ���� �������.
				*/
		int license = 6 + atoi(key);

		//�������� ����� �� ��
		if (strcmp(dbPath, "mybd.csv")) {
			printf("������� ��� ��������� �����.\n");
		}

		//�������� �� ����
		if (!(((license - 6) % 13) == 0)) {
#ifdef DEF
			printf("%i\n", (license % 13) == 0);
#endif
			printf("������� ��� ��������� ���������� �����.\n");
		}

		//������� ��������
		if ((strcmp(dbPath, "mybd.csv") == 0) && (((license - 6) % 13) == 0)) {
			
			//�������� �� ����������� ������, ���������� �� ��������
			struct Stuff** IKnowAll = (struct Stuff**)malloc(SIZE * sizeof(struct Stuff*));
			if (IKnowAll == NULL) {
#ifdef DEF
				printf("err: creating of list is down");
#endif
				return ERROR_TYPE;
			}
			
			//������������ ���������� ����� ������ �� �������
			*IKnowAll = NULL;

			//���������� ������ �� ���� ������
			readDataFromFile(IKnowAll, fcsv);
			fclose(fcsv);

			//��������� ���������� ��� ��������� �� �����������
			printf(
				"\n\t�� ��������� - � ����� ������ ��������.\n\n"
				"\t\t�� ����������� �� �������� ���������� ��� ������� ��������.\n\n"
				"\t\t\t��� ������������ ���������, ������������ ���� �� ������ �����.\n\n"
			);

			//������ ����
			menu(IKnowAll);

			//��������� ������
			free(IKnowAll);
		}
		//��������� �����
		fclose(fppr);
	}
	//���������� ������
	return 0;
}