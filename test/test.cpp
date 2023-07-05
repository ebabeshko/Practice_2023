#include "gtest/gtest.h"
#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\FNCTS\FNCTS.h"
#include "..\modules\modules.c"

TEST(AnnouncementTest, AddAnnouncement) {
    // ������������ �������� �����
    Announcement data;
    data.id = 1;
    strcpy(data.title, "������� �����");
    data.price = 100.0;
    strcpy(data.city, "������� ����");
    strcpy(data.phone, "1234567890");

    // ������ ������� ��� ����������
    addAnnouncement();

    // �������� ����������
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data.id == data.id) {
            EXPECT_STREQ(temp->data.title, data.title);
            EXPECT_FLOAT_EQ(temp->data.price, data.price);
            EXPECT_STREQ(temp->data.city, data.city);
            EXPECT_STREQ(temp->data.phone, data.phone);
            break;
        }
        temp = temp->next;
    }
}
TEST(AnnouncementTest, DeleteAnnouncement) {
    // ������������ �������� �����
    Announcement data;
    data.id = 1;
    strcpy(data.title, "������� �����");
    data.price = 100.0;
    strcpy(data.city, "������� ����");
    strcpy(data.phone, "1234567890");

    // ��������� �������� ����� �� ��'������ ������
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = head;
    head = newNode;

    // ������ ������� ��� ����������
    deleteAnnouncement(data.id);

    // �������� ����������
    Node* temp = head;
    while (temp != NULL) {
        EXPECT_NE(temp->data.id, data.id);
        temp = temp->next;
    }
}

TEST(AnnouncementTest, ViewAnnouncementsByCity) {
    // ������������ �������� �����
    Announcement data1;
    data1.id = 1;
    strcpy(data1.title, "�����1");
    data1.price = 100.0;
    strcpy(data1.city, "̳���1");
    strcpy(data1.phone, "�������1");

    Announcement data2;
    data2.id = 2;
    strcpy(data2.title, "�����2");
    data2.price = 200.0;
    strcpy(data2.city, "̳���2");
    strcpy(data2.phone, "�������2");

    // ��������� �������� ����� �� ��'������ ������
    Node* newNode1 = (Node*)malloc(sizeof(Node));
    newNode1->data = data1;
    newNode1->next = head;
    head = newNode1;

    Node* newNode2 = (Node*)malloc(sizeof(Node));
    newNode2->data = data2;
    newNode2->next = head;
    head = newNode2;

    // ������ ������� ��� ����������
    viewAnnouncementsByCity("̳���1");

    // �������� ������
    // �� ������ �������� stdout �� �������� ���� � ���������� �������, ���� ������ �������������� �� ��������

    // �������� �������� �����
    head = NULL; // �������� ��'������ ������
    free(newNode1);
    free(newNode2);
}

TEST(AnnouncementTest, ViewAnnouncementsByPrice) {
    // ������� �������� �����
    Announcement data1;
    data1.id = 1;
    strcpy(data1.title, "�����1");
    data1.price = 100.0;
    strcpy(data1.city, "̳���1");
    strcpy(data1.phone, "�������1");

    Announcement data2;
    data2.id = 2;
    strcpy(data2.title, "�����2");
    data2.price = 200.0;
    strcpy(data2.city, "̳���2");
    strcpy(data2.phone, "�������2");

    Announcement data3;
    data3.id = 3;
    strcpy(data3.title, "�����3");
    data3.price = 50.0;
    strcpy(data3.city, "̳���3");
    strcpy(data3.phone, "�������3");

    // ������� ������ ��� �� ��'������� ������
    Node* newNode1 = (Node*)malloc(sizeof(Node));
    newNode1->data = data1;
    newNode1->next = head;
    head = newNode1;

    Node* newNode2 = (Node*)malloc(sizeof(Node));
    newNode2->data = data2;
    newNode2->next = head;
    head = newNode2;

    Node* newNode3 = (Node*)malloc(sizeof(Node));
    newNode3->data = data3;
    newNode3->next = head;
    head = newNode3;

    // ������ ������� ��� ����������
    viewAnnouncementsByPrice(150.0);
    // ������� ����� �����
    head = NULL; // �������� ��'������ ������
    free(newNode1);
    free(newNode2);
    free(newNode3);
}