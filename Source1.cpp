/**
* @file practice3.cpp
* @author �������� �.�., ��. 515�, ������ 7
* @date 3 ����� 2023
* @brief ��������� ��������
*
* ���� ����� ������
*/

#pragma warning(disable : 4996)
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "locale.h"
// ��������� ��� ������//
typedef struct tagITEM
{
    int tr_num;
    char dis_po[20];
    char arr_po[20];
    char dep_ti[6];
} ITEM;

//����� (����. 20)
ITEM Train[20];

//ʳ������ ������� ������
int lock;

//������� ������ ����������
void print(void)
{
    int i;
    printf("|� | ����� ������ | ����� �i���������� | ����� ����������� | ��� �����������|\n");
    for (i = 0; i < lock; i++)
        printf("%2i   %i               %-20s  %-20s %s\n", i+1, Train[i].tr_num, Train[i].dis_po, Train[i].arr_po, Train[i].dep_ti);
}

//������� ��������� ���������� ��� �����
void add(void)
{
    printf("����i�� ����� ������: ");
    scanf_s("%i", &Train[lock].tr_num);
    printf("����i�� ����� �i�������: ");
    scanf_s("%19s", Train[lock].dis_po, sizeof(Train[lock].dis_po));
    printf("����i�� ����� ��������: ");
    scanf_s("%19s", Train[lock].arr_po, sizeof(Train[lock].arr_po));
    printf("����i�� ��� �i�������(� ������i HH:MM): ");
    scanf_s("%5s", &Train[lock].dep_ti, sizeof(Train[lock].dep_ti));

    lock++;
}

//������� ��������� ������
void deleting(void)
{
    int i;

    print();
    printf("����i�� ����� ��������: ");
    scanf_s("%i", &i);
    if (i < 1 || i > lock)
    {
        fprintf(stderr, " %i ������ ������ �� i���\n", i);
        return;
    }

    for (i--; i < lock - 1; i++)
        Train[i] = Train[i + 1];

    lock--;
}

//������� ���������� ���������� � ����
void save(void)
{
    FILE* TRAIN;
    int i;

    if ((TRAIN = fopen("train.dat", "wt")) == NULL)
    {
        fprintf(stderr, "��������� �i������\n");
        return;
    }

    fprintf(TRAIN, "%i\n", lock);
    for (i = 0; i < lock; i++)
        fprintf(TRAIN, "%i\n%s\n%s\n%s\n",Train[i].tr_num, Train[i].dis_po, Train[i].arr_po, Train[i].dep_ti);

    fclose(TRAIN);
}

//������� ������������ �����
void load(void)
{
    FILE* TRAIN;
    int i;

    if ((TRAIN = fopen("train.dat", "rt")) == NULL)
    {
        fprintf(stderr, "��������� ����������� ����\n");
        return;
    }

    fscanf_s(TRAIN, "%i", &lock);
    for (i = 0; i < lock; i++)
        fscanf_s(TRAIN, "%i%19s%19s%19s", &Train[i].tr_num, Train[i].dis_po, sizeof(Train[lock].dis_po), Train[i].arr_po, sizeof(Train[lock].arr_po), Train[i].dep_ti, sizeof(Train[lock].dep_ti));

    fclose(TRAIN);
    fclose(TRAIN);
} 
//���� ��� ������ ��
int menu(void)
{
    int c = 0;

    while ((c < '0' || c > '5') )
    {
        printf("0 : ���i�\n"
            "1 : ������\n"
            "2 : ��������\n"
            "3 : �����������\n"
            "4 : �������\n"
            "5 : ��������\n");
        c = _getch();
        printf("%c\n", c);
    }
    return c;
}

//������� �������
void main(int) {
    int Selection;
    setlocale(LC_ALL, "Ukr");
    lock = 0;
    while ((Selection = menu()) != '0' )
        switch (Selection)
        {
        case '1':
            add();
            break;
        case '2':
            save();
            break;
        case '3':
            load();
            break;
        case '4':
            print();
            break;
        case '5':
            deleting();
            break;
        }
}