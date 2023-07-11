/**
* @file PP.c *
* @author Mosiazh. A.M., гр. 515b, варіант 4 *
* @date 27 травня 2023 * 
* @brief Розрахункова робота*
* База даних авіврейсів * 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TLEN 25
#define ALEN 25
const int pALL = 1, pTYPE = 2, pDEST = 3, pLONG = 1000;
const int mdEDIT = 1, mdDEL = 2;
const int modeCSV = 1, modeBIN = 2;
const char NOLIC[] = " (not licensed)";
long gFileKEY = -1, gEntKEY = -2;
//const char NOLIC[]="\n   -- не ліцензовано";

struct Flight
{
    long ID;
    char locFrom[TLEN];
    char locTo[TLEN];
    int flightID;
    char airtype[ALEN];
    int airplace;
};

struct BD
{
    char fname[32];
    //unsigned long key;
};

int islicensed()
{
    return gFileKEY == gEntKEY;
}

void nolicprintmessage()
{
    printf("Відсутня ліцензія на ці операції");
}

void readConfigFile(struct BD* base, char* configname)
{
    //спробуємо знайти конфіг аналог ім проги
    //strcpy(base->fname,"main.cfg");
    //char configname[32]="main.cfg";
    srand(time(0));
    long kkey = rand() % (0xFFFFFFFF);
    FILE* file = fopen(configname, "r");
    if (file == NULL)
    {
        //якщо не відкрився треба буде створити
        printf("файлу %s нема створюємо\n", configname);
        printf("запишіть ліцензійний ключ %lX\n", kkey);
        gFileKEY = kkey;
        file = fopen(configname, "w");
        fprintf(file, "DB=new_base.dat\n");
        fprintf(file, "KEY=%lX", kkey);
        FILE* newdb = fopen("new_base.dat", "w");
        fclose(file);
        fclose(newdb);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        // Ігноруємо рядки з коментарями
        if (line[0] == ';')
            continue;

        //  printf("%s\n", line);
        if (strncmp(line, "DB=", 3) == 0)
        {
            sscanf(line + 3, "%s", base->fname);
            FILE* bas = fopen(base->fname, "rb");
            if (bas == NULL)
            {
                printf("БД вказана в конфіг файлі не знайден\nстворено нову");
                bas = fopen(base->fname, "wb");
                if (bas == NULL)
                {
                    printf("помилка створення БД");
                    return;
                }
                fclose(bas);
            }
        }
        if ((strncmp(line, "KEY=", 4) == 0))
        {
            sscanf(line + 4, "%lx", &gFileKEY);
            //printf("%lx %lu", base->key, base->key);
        }

    }

    fclose(file);
}

void InputRecord(struct Flight* fly)
{
    printf("\nВведіть назву пункту відправлення: ");
    scanf("%s", fly->locFrom);
    printf("Введіть назву пункту призначення: ");
    scanf("%s", fly->locTo);
    printf("Введіть номер рейсу: ");
    scanf("%d", &fly->flightID);
    printf("Введіть тип літака: ");
    scanf("%s", fly->airtype);
    printf("Введіть кількість місць у літаку: ");
    scanf_s("%d", &fly->airplace);
}

void PrintRecord(struct Flight* fly)/*вывод*/
{
    printf("\nREC_ID %ld", fly->ID);
    printf("\nПункт відправлення: %s", fly->locFrom);
    printf("\nПункт призначення: %s", fly->locTo);
    printf("\nНомер рейсу: %d", fly->flightID);
    printf("\nТип літака: %s", fly->airtype);
    printf("\nКількість місць у літаку: %d", fly->airplace);
}

void PrintRec(struct Flight* fly)/*вывод*/
{
    printf("\n%9ld %10s %10s", fly->ID, fly->locFrom, fly->locTo);
    printf("%8d", fly->flightID);
    printf("%10s", fly->airtype);
    printf("%5d", fly->airplace);
}

void EditFly(struct Flight* fly)/*РЕдактирование*/
{
    printf("\n1. Пункт відправлення: %s", fly->locFrom);
    printf("\n2. Пункт призначення: %s", fly->locTo);
    printf("\n3. Номер рейсу: %d", fly->flightID);
    printf("\n4. Тип літака: %s", fly->airtype);
    printf("\n5. Кількість місць у літаку: %d", fly->airplace);
    printf("\n0. Вихід\n");
    int ch;
    do
    {
        scanf("%d", &ch); getchar();
        switch (ch)
        {
        case 0:
            break;
        case 1:
            printf("\nВведіть новий пункт відправлення: ");
            scanf("%s", fly->locFrom);
            break;
        case 2:
            printf("\nВведіть новий пункт призначення: ");
            scanf("%s", fly->locTo);
            break;
        case 3:
            printf("\nВведіть новий номер рейсу: ");
            scanf("%d", &fly->flightID);
            getchar();
            break;
        case 4:
            printf("\nВведіть новий nип літака: ");
            scanf("%s", fly->airtype);
            break;
        case 5:
            printf("\nВведіть нову кількість місць у літаку: ");
            scanf("%d", &fly->airplace);
            getchar();
            break;
        default:
            printf("\nНевірний вибір: ");
        }
    } while (ch != 0);
}

int EditRec(struct BD* db, int fl_id, int edit)/*Удалерение записи*/
{
    FILE* fl = fopen(db->fname, "rb+");
    if (fl == NULL)
    {
        printf("Помилка при відкритті файлу edrec");
        return -1;
    }
    int isfound = 0;
    const int SofSF = sizeof(struct Flight);
    struct Flight temp;
    while (fread((char*)&temp, SofSF, 1, fl) == 1)
    {
        if (temp.flightID == fl_id)
        {
            // Знайдено запис, видалимо його 
            fseek(fl, -SofSF, SEEK_CUR);
            if (edit == mdEDIT)
                EditFly(&temp);
            else //mdDEL
                temp.ID = -1L;
            fwrite((char*)&temp, SofSF, 1, fl);
            isfound = 1;
            break;
        }
    }
    if (!isfound)
        printf("нічого з таким FlyID не найдено");
    fclose(fl);
    return 0;
}

int DelRec(struct BD* db, int fl_id)
{
    return EditRec(db, fl_id, mdDEL);
}

int AddRecToFile(struct BD* db, struct Flight* f)
{
    char mode[5];
    {
        FILE* tst = fopen(db->fname, "rb");
        if (tst)
        {
            fclose(tst);
            strcpy(mode, "rb+");
        }
        else
            strcpy(mode, "wb");
    }

    const int SofSF = sizeof(struct Flight);
    long pos = 0;
    FILE* fl = fopen(db->fname, mode);
    if (fl == NULL)
    {        // 
        printf("Помилка при відкритті файлу addrec");
        return -1;
    }

    if (strcmp(mode, "wb") == 0)
    {
        //if strcmp new_base.dat....
        printf("\nфайл %s вказаний у файлі конфігурації незнайдено, створено файл", db->fname);
        f->ID = pos;
        fwrite((char*)f, SofSF, 1, fl);
        fclose(fl);
        return 0;
    }
    //////////////////////////////////////
    struct Flight temp;
    int emptySlotFound = 0;

    while (fread((char*)&temp, SofSF, 1, fl) == 1)
    {
        pos += SofSF;
        if (temp.ID == -1)
        {
            // Знайдено видалений запис, перезаписуємо його новим  
            pos = ftell(fl);
            pos -= SofSF;
            fseek(fl, pos, SEEK_SET);
            f->ID = pos / SofSF;
            //printf("----%ld--%ld--", f->ID,pos);
            fwrite((char*)f, SofSF, 1, fl);
            emptySlotFound = 1;
            break;
        }
    }

    if (!emptySlotFound)
    {
        // Не знайдено видаленого запису, записуємо в кінець файлу    
        fseek(fl, 0, SEEK_END);
        pos = ftell(fl);
        f->ID = pos / SofSF;
        //printf("--END--%ld----", f->ID);
        //f->ID=db->recID++;
        fwrite((char*)f, SofSF, 1, fl);
    }

    fclose(fl);
    return 0;
}

int PrintBase(struct BD* db, struct Flight* f, int mode)/*подвод к выводу*/
{
    const int SofSF = sizeof(struct Flight);
    FILE* fl = fopen(db->fname, "rb");
    if (fl == NULL)
    {        // 
        printf("Помилка при відкритті файлу");
        return -1;
    }

    struct Flight temp;
    printf("\n%9s %10s %10s", "ID", "From", "To");
    printf("%8s", "flyID");
    printf("%10s", "airtyp");
    printf("%5s", "sits");

    while (fread((char*)&temp, SofSF, 1, fl) == 1)
    {
        if (temp.ID == -1)
            continue;
        if (mode % pLONG == pALL ||
            mode % pLONG == pDEST && !strcmp(temp.locTo, f->locTo) ||
            mode % pLONG == pTYPE && !strcmp(temp.airtype, f->airtype))
        {
            if (mode < pLONG)
                PrintRec(&temp);
            else
                PrintRecord(&temp);
        }
    }
    fclose(fl);
    return 0;
}

void ProgNameCFGName(char* argv, char* filename)
{
    // Визначаємо останній роздільник шляху ("/" або "\\")
    char progname[256];
    strcpy(progname, argv);
    char* lastdelim = strrchr(progname, '/');
    if (lastdelim == NULL)
    {
        lastdelim = strrchr(progname, '\\');
    }

    // Визначаємо початок ім'я файлу після роздільника
    //char* 
    char* tmp = (lastdelim == NULL) ? progname : lastdelim + 1;

    // Визначаємо крапку, що позначає початок розширення
    char* dot = strrchr(tmp, '.');
    if (dot != NULL)
    {
        // Видаляємо розширення з імені файлу
        *dot = '\0';
    }
    strcat(tmp, ".cfg");
    strcpy(filename, tmp);
    // Друкуємо результат  printf("Ім'я файлу: %s\n", filename);

}

int AskMenu()
{
    int punkt;
    printf("\n-=- MENU -=-");
    printf("\n1. Ввести ліцензійний ключ");
    printf("\n2. Додати політ");
    printf("\n3. Редагувати політ");
    printf("\n4. Видалити політ");
    printf("\n5. Список польотів");
    printf("\n6. Номери рейсів і тип літака до пунку...");
    if (!islicensed())
        printf(NOLIC);
    printf("\n7. Рейси з типом літака ...");
    if (!islicensed())
        printf(NOLIC);
    printf("\n8. Експорт БД у CSV ");
    if (!islicensed())
        printf(NOLIC);
    printf("\n9. Запис БД в інший файл ");
    if (!islicensed())
        printf(NOLIC);

    printf("\n0. Вихід\n");
    scanf_s("%d", &punkt);
    getchar();//дозчитуємо '\n'
    return punkt;
}

int ExportTo(struct BD* db, int mode) /*Exel, dat*/
{
    const int SofSF = sizeof(struct Flight);
    FILE* fl = fopen(db->fname, "rb");
    if (fl == NULL)
    {
        printf("Помилка при відкритті файлу");
        return -1;
    }
    char SaveName[32];
    FILE* sv;
    printf("У який файл *%s експортувати базу польотів ",
        mode == modeCSV ? ".csv" : ".dat");
    scanf("%s", SaveName);

    if (mode == modeCSV)
    {
        strcat(SaveName, ".csv");
        sv = fopen(SaveName, "wt");
    }
    else
    {
        strcat(SaveName, ".dat");
        sv = fopen(SaveName, "wb");
    }

    if (sv == NULL)
    {
        printf("Помилка при відкритті файлу");
        fclose(fl);
        return -1;
    }

    struct Flight temp;
    while (fread((char*)&temp, SofSF, 1, fl) == 1)
    {
        if (temp.ID == -1)
            continue;
        if (mode == modeCSV)
        {
            fprintf(sv, "%ld;%s;%s;%d;%s;%d\n",
                temp.ID, temp.locFrom, temp.locTo, temp.flightID, temp.airtype, temp.airplace);
        }
        else
            fwrite((char*)&temp, SofSF, 1, sv);
    }
    fclose(fl);
    fclose(sv);
    return 0;
}

int main(int argc, char** argv)
{ 
    SetConsoleOutputCP(1251);
    struct BD base;
    char cfgfilename[256];  //printf("n\=============\n{%s}", argv[0]);  //strcpy(base.fname,"mydb.dat");
    ProgNameCFGName(argv[0], cfgfilename);//  printf("%s", cfgfilename);
    readConfigFile(&base, cfgfilename);    //printf("\n%s %lx", base.fname, base.key);


   
    int ch;
    int fid;
    struct Flight f;
    do
    {
        ch = AskMenu();
        switch (ch)
        {
        case 0:break;
        case 1:
            printf("\nВведіть ліц ключ ");
            scanf("%lx", &gEntKEY);
            break;
        case 2:
            InputRecord(&f);
            AddRecToFile(&base, &f);
            break;
        case 3:
            printf("\nВведіть ID польоту для редагування ");
            scanf("%d", &fid);
            EditRec(&base, fid, mdEDIT);
            break;
        case 4:
            printf("\nВведіть ID польоту для видалення ");
            scanf("%d", &fid);
            DelRec(&base, fid);
            break;
        case 5:
            PrintBase(&base, &f, pALL);
            break;
        case 6:
            if (islicensed())
            {
                printf("\nВведіть пункт призначення ");
                scanf("%s", f.locTo);
                PrintBase(&base, &f, pDEST);
            }
            else
                nolicprintmessage();
            break;
        case 7:
            if (islicensed())
            {
                printf("\nВведіть тип літака ");
                scanf("%s", f.airtype);
                PrintBase(&base, &f, pTYPE);
            }
            else
                nolicprintmessage();
            break;
        case 8:
            if (islicensed())
                ExportTo(&base, modeCSV);
            break;
        case 9:
            if (islicensed())
                ExportTo(&base, modeBIN);
            else
                nolicprintmessage();
            break;
        default:
            printf("\nневірний вибір");
        }
    } while (ch != 0);

    return 0;
}
