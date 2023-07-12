/**
* @file ConsoleApplication.cpp
* @author Ніколаєв Ростислав Тимофійович, гр. 515б, варіант 3
* @date 9 червня 2023
* @brief Навчальна практика
*
* База даних студентів
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Kontakt {
    char familiya[50];
    char imya[50];
    char telefon[50];
    char messendzher[50];
    struct Kontakt* sleduyushiy;
} Kontakt;

Kontakt* golova = NULL;
char BD[50] = "kontakty.dat";
char KLUCH[50] = "1";

Kontakt* sozdatKontakt(const char* familiya, const char* imya, const char* telefon, const char* messendzher);
void dobavitKontakt(Kontakt* kontakt);
void udalitKontakt(int id);
void prosmotrKontaktov();
void obnovitKontakt(int id, const char* familiya, const char* imya, const char* telefon, const char* messendzher);
void sohranitVFail(const char* imyaFaila);
void zagruzitIzFaila(const char* imyaFaila);
void pokazatKontaktySMessendzherom();
void pokazatKontaktySPodstrokom(const char* podstroka);
void sohranitVFailCSV(const char* imyaFaila);
void prochitatKonfig();
int proverkaKlyucha();

int main() {
    prochitatKonfig();
    zagruzitIzFaila(BD);

    int vybor;
    char familiya[50], imya[50], telefon[50], messendzher[50];
    int id;

    do {
        printf("\n--- Menedzher kontaktov ---");
        printf("\n1. Dobavit kontakt");
        printf("\n2. Udalit kontakt");
        printf("\n3. Prosmotr kontaktov");
        printf("\n4. Obnovit kontakt");

        if (proverkaKlyucha()) {
            printf("\n5. Pokazat kontakty s messendzherom");
            printf("\n6. Pokazat kontakty s podstrokom");
            printf("\n7. Sohranit kontakty v binarnyi fail");
            printf("\n8. Sohranit kontakty v CSV fail");
        }

        printf("\n9. Vyhod");
        printf("\n---------------------------");
        printf("\nVvedite svoi vybor: ");
        scanf_s("%d", &vybor);
        while (getchar() != '\n');

        switch (vybor) {
        case 1:
            printf("\nVvedite familiyu: ");
            scanf_s("%[^\n]s", familiya, sizeof(familiya));
            while (getchar() != '\n');
            printf("\nVvedite imya: ");
            scanf_s("%[^\n]s", imya, sizeof(imya));
            while (getchar() != '\n');
            printf("\nVvedite telefon: ");
            scanf_s("%[^\n]s", telefon, sizeof(telefon));
            while (getchar() != '\n');
            printf("\nVvedite messendzher: ");
            scanf_s("%[^\n]s", messendzher, sizeof(messendzher));
            while (getchar() != '\n');
            dobavitKontakt(sozdatKontakt(familiya, imya, telefon, messendzher));
            break;
        case 2:
            printf("\nVvedite ID kontakta dlia udaleniya: ");
            scanf_s("%d", &id);
            while (getchar() != '\n');
            udalitKontakt(id);
            break;
        case 3:
            prosmotrKontaktov();
            break;
        case 4:
            printf("\nVvedite ID kontakta dlia obnovleniya: ");
            scanf_s("%d", &id);
            while (getchar() != '\n');
            printf("\nVvedite novuyu familiyu: ");
            scanf_s("%[^\n]s", familiya, sizeof(familiya));
            while (getchar() != '\n');
            printf("\nVvedite novoe imya: ");
            scanf_s("%[^\n]s", imya, sizeof(imya));
            while (getchar() != '\n');
            printf("\nVvedite novyi telefon: ");
            scanf_s("%[^\n]s", telefon, sizeof(telefon));
            while (getchar() != '\n');
            printf("\nVvedite novyi messendzher: ");
            scanf_s("%[^\n]s", messendzher, sizeof(messendzher));
            while (getchar() != '\n');
            obnovitKontakt(id, familiya, imya, telefon, messendzher);
            break;
        case 5:
            if (proverkaKlyucha()) {
                pokazatKontaktySMessendzherom();
            }
            else {
                printf("\nNekorrektynyi litsenzionnyi klyuch. Spetsialnaya funktsiya otmenena.\n");
            }
            break;
        case 6:
            if (proverkaKlyucha()) {
                printf("\nVvedite podstroku: ");
                scanf_s("%[^\n]s", familiya, sizeof(familiya));
                while (getchar() != '\n');
                pokazatKontaktySPodstrokom(familiya);
            }
            else {
                printf("\nNekorrektynyi litsenzionnyi klyuch. Spetsialnaya funktsiya otmenena.\n");
            }
            break;
        case 7:
            if (proverkaKlyucha()) {
                sohranitVFail(BD);
            }
            else {
                printf("\nNekorrektynyi litsenzionnyi klyuch. Spetsialnaya funktsiya otmenena.\n");
            }
            break;
        case 8:
            if (proverkaKlyucha()) {
                sohranitVFailCSV("kontakty.csv");
            }
            else {
                printf("\nNekorrektynyi litsenzionnyi klyuch. Spetsialnaya funktsiya otmenena.\n");
            }
            break;
        case 9:
            printf("\nZavershenie programmy.");
            break;
        default:
            printf("\nNekorrektynyi vybor! Vvedite chislo ot 1 do 9.");
            break;
        }
    } while (vybor != 9);
    return 0;
}

Kontakt* sozdatKontakt(const char* familiya, const char* imya, const char* telefon, const char* messendzher) {
    Kontakt* novyjKontakt = (Kontakt*)malloc(sizeof(Kontakt));
    strcpy_s(novyjKontakt->familiya, 50, familiya);
    strcpy_s(novyjKontakt->imya, 50, imya);
    strcpy_s(novyjKontakt->telefon, 50, telefon);
    strcpy_s(novyjKontakt->messendzher, 50, messendzher);
    novyjKontakt->sleduyushiy = NULL;
    return novyjKontakt;
}

void dobavitKontakt(Kontakt* kontakt) {
    if (golova == NULL) {
        golova = kontakt;
    }
    else {
        Kontakt* tekushiy = golova;
        while (tekushiy->sleduyushiy != NULL) {
            tekushiy = tekushiy->sleduyushiy;
        }
        tekushiy->sleduyushiy = kontakt;
    }
}

void udalitKontakt(int id) {
    if (id == 0) {
        Kontakt* udalit = golova;
        golova = golova->sleduyushiy;
        free(udalit);
    }
    else {
        Kontakt* tekushiy = golova;
        for (int i = 0; i < id - 1; i++) {
            tekushiy = tekushiy->sleduyushiy;
        }
        Kontakt* udalit = tekushiy->sleduyushiy;
        tekushiy->sleduyushiy = udalit->sleduyushiy;
        free(udalit);
    }
}

void prosmotrKontaktov() {
    Kontakt* tekushiy = golova;
    int id = 0;
    while (tekushiy != NULL) {
        printf("Kontakt %d: %s, %s, %s, %s\n", id++, tekushiy->familiya, tekushiy->imya, tekushiy->telefon, tekushiy->messendzher);
        tekushiy = tekushiy->sleduyushiy;
    }
}

void obnovitKontakt(int id, const char* familiya, const char* imya, const char* telefon, const char* messendzher) {
    Kontakt* tekushiy = golova;
    for (int i = 0; i < id; i++) {
        tekushiy = tekushiy->sleduyushiy;
    }
    strcpy_s(tekushiy->familiya, 50, familiya);
    strcpy_s(tekushiy->imya, 50, imya);
    strcpy_s(tekushiy->telefon, 50, telefon);
    strcpy_s(tekushiy->messendzher, 50, messendzher);
}

void sohranitVFail(const char* imyaFaila) {
    FILE* fail;
    fopen_s(&fail, imyaFaila, "wb");
    Kontakt* tekushiy = golova;
    while (tekushiy != NULL) {
        fwrite(tekushiy, sizeof(Kontakt), 1, fail);
        tekushiy = tekushiy->sleduyushiy;
    }
    fclose(fail);
}

void zagruzitIzFaila(const char* imyaFaila) {
    FILE* fail;
    fopen_s(&fail, imyaFaila, "rb");
    if (fail != NULL) {
        Kontakt* tekushiy;
        Kontakt* predidushiy = NULL;
        while (!feof(fail)) {
            tekushiy = (Kontakt*)malloc(sizeof(Kontakt));
            if (fread(tekushiy, sizeof(Kontakt), 1, fail) == 1) {
                tekushiy->sleduyushiy = NULL;
                if (golova == NULL) {
                    golova = tekushiy;
                }
                else {
                    predidushiy->sleduyushiy = tekushiy;
                }
                predidushiy = tekushiy;
            }
            else {
                free(tekushiy);
            }
        }
        fclose(fail);
    }
}

void pokazatKontaktySMessendzherom() {
    Kontakt* tekushiy = golova;
    int id = 0;
    printf("\nKontakty s messendzherom:\n");
    while (tekushiy != NULL) {
        if (strcmp(tekushiy->messendzher, "") != 0) {
            printf("Kontakt %d: %s, %s, %s, %s\n", id, tekushiy->familiya, tekushiy->imya, tekushiy->telefon, tekushiy->messendzher);
        }
        id++;
        tekushiy = tekushiy->sleduyushiy;
    }
}

void pokazatKontaktySPodstrokom(const char* podstroka) {
    Kontakt* tekushiy = golova;
    int id = 0;
    printf("\nKontakty s podstrokom \"%s\":\n", podstroka);
    while (tekushiy != NULL) {
        if (strstr(tekushiy->familiya, podstroka) != NULL || strstr(tekushiy->imya, podstroka) != NULL ||
            strstr(tekushiy->telefon, podstroka) != NULL || strstr(tekushiy->messendzher, podstroka) != NULL) {
            printf("Kontakt %d: %s, %s, %s, %s\n", id, tekushiy->familiya, tekushiy->imya, tekushiy->telefon, tekushiy->messendzher);
        }
        id++;
        tekushiy = tekushiy->sleduyushiy;
    }
}

void sohranitVFailCSV(const char* imyaFaila) {
    FILE* fail;
    fopen_s(&fail, imyaFaila, "w");
    if (fail != NULL) {
        Kontakt* tekushiy = golova;
        fprintf(fail, "ID,Familiya,Imya,Telefon,Messendzher\n");
        int id = 0;
        while (tekushiy != NULL) {
            fprintf(fail, "%d,%s,%s,%s,%s\n", id, tekushiy->familiya, tekushiy->imya, tekushiy->telefon, tekushiy->messendzher);
            tekushiy = tekushiy->sleduyushiy;
            id++;
        }
        fclose(fail);
    }
}

void prochitatKonfig() {
    FILE* fail;
    fopen_s(&fail, "konfig.cfg", "r");
    if (fail == NULL) {
        fopen_s(&fail, "konfig.cfg", "w");
        fprintf(fail, "BD = kontakty.dat\n");
        fprintf(fail, "KLUCH = rosyslav2023\n");
        fclose(fail);
        fopen_s(&fail, "kontakty.dat", "wb");
        fclose(fail);
        printf("\nSozdany konfiguratsionnyi fail i fail dannih.\n");
    }
    else {
        char stroka[100];
        while (fgets(stroka, sizeof(stroka), fail)) {
            if (strncmp(stroka, "BD =", 3) == 0) {
                sscanf_s(stroka, "BD = %s", BD, sizeof(BD));
            }
            else if (strncmp(stroka, "KLUCH =", 5) == 0) {
                sscanf_s(stroka, "KLUCH = %s", KLUCH, sizeof(KLUCH));
            }
        }
        fclose(fail);
    }
}

int proverkaKlyucha() {
    return strcmp(KLUCH, "rosyslav2023") == 0;
}