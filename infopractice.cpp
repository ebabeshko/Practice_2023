#include "infopractice.h"
struct info {
    int number;
    char name[MAX + 1];
    char group_product[MAX + 1];
    float price;
    char provider[MAX + 1];
    struct info* next;
};
struct info* first = NULL;



int code_num = 0;
float price_num = 0;


PUBLIC int menu() {
    char str[MAX + 1];
    while (1) {
        scanf_s("%s", str, MAX + 1);
        if (strcmp(str, "input") == 0) {
            return 1;
        }
        else if (strcmp(str, "delete") == 0) {
            return 2;

        }
        else if (strcmp(str, "print") == 0) {
            return 3;
        }
        else if (strcmp(str, "change") == 0) {
            return 4;

        }
        else if (strcmp(str, "search") == 0) {
            return 5;
        }
        else if (strcmp(str, "price") == 0) {
            return 6;
        }
        else if (strcmp(str, "settings") == 0) {
            return 7;
        }
        else if (strcmp(str, "exit") == 0) {
            return 0;
        }
        else {
            printf("\nНе вірна операція. Будь ласка, введіть оперію з вище названих\n");
        }
    }
}
PRIVATE int code_exists(int code_num, const char* CurfileName) {
    // Відкриття файлу для читання
    FILE* f_my = fopen(CurfileName, "a+");
    if (f_my == NULL) {
        printf("Помилка відкриття файлу.\n");
        return 0; // Помилка при відкритті файлу, повертаємо 0
    }

    int exists = 0; // Прапорець для позначення наявності коду товару
    struct info* current_info = (struct info*)malloc(sizeof(struct info));
    if (current_info == NULL) {
        printf("Помилка виділення пам'яті.\n");
        fclose(f_my);
        return 0; // Помилка при виділенні пам'яті, повертаємо 0
    }

    // Перебір записів у файлі
    while (fscanf(f_my, "%d", &(current_info->number)) == 1) {
        // Перевірка, чи зустрічається введений код товару
        if (current_info->number == code_num) {
            exists = 1; // Код товару знайдений, позначаємо наявність
            break;
        }

        // Пропуск решти рядка
        char c;
        while ((c = fgetc(f_my)) != '\n' && c != EOF);
    }

    fclose(f_my); // Закриття файлу
    free(current_info); // Звільнення виділеної пам'яті

    return exists; // Повертаємо значення прапорця наявності
}
PUBLIC void input(const char* CurfileName) {
    struct info* new_info = (struct info*)malloc(sizeof(struct info));
    if (new_info == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return;
    }

    FILE* f_my = fopen(CurfileName, "a");  // Відкриття файлу для читання записів
    if (f_my == NULL) {
        printf("Помилка відкриття файлу.\n");
        return;
    }

    if (code_num == MAX) {
        printf("База заповнена, додавання неможливе.\n");
        fclose(f_my);
        free(new_info);  // Звільнення виділеної пам'яті перед поверненням
        return;
    }

    printf("Введіть код товару: ");
    while (1) {
        if (scanf_s("%d", &code_num) != 1 || code_num < 0 || code_num >= MAX || code_exists(code_num, CurfileName)) {
            printf("Помилка: недопустимий номер продукту або такий номер вже використовується. Введіть код товару ще раз: ");
            while (getchar() != '\n');
            
        }
        else {
            new_info->number = code_num;
            while (getchar() != '\n');
            break;
        }
    }
    printf("Введіть назву товару: ");
    fgets(new_info->name, MAX + 1, stdin);
    new_info->name[strcspn(new_info->name, "\n")] = '\0'; // Видалення символу нового рядка

    printf("Введіть групу товару: ");
    fgets(new_info->group_product, MAX + 1, stdin);
    new_info->group_product[strcspn(new_info->group_product, "\n")] = '\0'; // Видалення символу нового рядка

    printf("Введіть ціну товару: ");
    while (1) {
        if (scanf_s("%f", &price_num) != 1 || price_num < 0) {
            printf("Помилка: ціна не може бути відємна. Введіть ще раз: ");
            while (getchar() != '\n');
            
        }
        else {
            new_info->price = price_num;
            while (getchar() != '\n');
            break;
        }
    }
    printf("Введіть постачальника товару: ");
    fgets(new_info->provider, MAX + 1, stdin);
    new_info->provider[strcspn(new_info->provider, "\n")] = '\0'; // Видалення символу нового рядка

    new_info->next = first;
    first = new_info;

    fprintf(f_my, "%d %s %s %.2f %s\n", new_info->number, new_info->name, new_info->group_product, new_info->price, new_info->provider);

    fclose(f_my);  // Закриття файлу
}
PUBLIC void print(const char* CurfileName) {
    struct info* new_info = (struct info*)malloc(sizeof(struct info));
    if (new_info == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return;
    }

    FILE* f_my = fopen(CurfileName, "a+");  // Відкриття файлу для читання записів
    if (f_my == NULL) {
        printf("Помилка відкриття файлу.\n");
        return;
    }

    printf("| Код товару |   Назва товару  |  Група товару  | Ціна товару | Постачальник товару |\n");
    printf("+-----------------------------------------------------------------------------------+\n");
    while (fscanf(f_my, "%d %s %s %f %s", &new_info->number, &new_info->name, &new_info->group_product, &new_info->price, &new_info->provider) != EOF) {
        printf("|%11d | %15s | %14s | %11.2f | %18s  |\n", new_info->number, new_info->name, new_info->group_product, new_info->price, new_info->provider);
        new_info->next = first;
        first = new_info;
    }
    printf("+-----------------------------------------------------------------------------------+\n");

    fclose(f_my);  // Закриття файлу

}
PUBLIC void delet(const char* CurfileName) {
    struct info* new_info = (struct info*)malloc(sizeof(struct info));
    if (new_info == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return;
    }

    int s;
    printf("Введіть номер продукту для видалення: ");
    scanf_s("%d", &s);

    FILE* f_my = fopen(CurfileName, "r");  // Відкриття файлу для читання записів
    if (f_my == NULL) {
        printf("Помилка відкриття файлу.\n");
        free(new_info);
        return;
    }

    FILE* f_temp = fopen("temp.txt", "w");  // Відкриття тимчасового файлу для запису
    if (f_temp == NULL) {
        printf("Помилка відкриття тимчасового файлу.\n");
        free(new_info);
        fclose(f_my);
        return;
    }

    while (fscanf(f_my, "%d %s %s %f %s", &new_info->number, new_info->name, new_info->group_product, &new_info->price, new_info->provider) != EOF) {
        if (new_info->number != s) {
            fprintf(f_temp, "%d %s %s %.2f %s\n", new_info->number, new_info->name, new_info->group_product, new_info->price, new_info->provider);
        }

    }

    free(new_info);
    fclose(f_my);    // Закриття файлів
    fclose(f_temp);

    remove(CurfileName);      // Видалення початкового файлу
    rename("temp.txt", CurfileName);  // Перейменування тимчасового файлу

    printf("Запис з номером %d успішно видалений.\n", s);
}
PUBLIC void change(const char* CurfileName) {
    int col, cod;

    struct info* first = NULL;
    struct info* new_info = (struct info*)malloc(sizeof(struct info));
    if (new_info == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return;
    }

    FILE* f_my = fopen(CurfileName, "r");  // Відкриття файлу для читання записів
    if (f_my == NULL) {
        printf("Помилка відкриття файлу.\n");
        return;
    }

    FILE* f_temp = fopen("temp.txt", "w");  // Відкриття тимчасового файлу для запису
col:
    printf("Введіть номер стовпця: ");
    scanf_s("%d", &col);

    switch (col) {
    case 1:
        printf("Введіть номер товару: ");
        scanf_s("%d", &cod);
        while (getchar() != '\n');

        while (fscanf(f_my, "%d %s %s %f %s", &new_info->number, new_info->name, new_info->group_product, &new_info->price, new_info->provider) != EOF) {
            if (new_info->number == cod) {
                printf("Введіть новий номер товару: ");
                while (1) {
                    if (scanf_s("%d", &code_num) != 1 || code_num < 0 || code_num >= MAX || code_exists(code_num, CurfileName)) {
                        printf("Помилка: недопустимий номер продукту або такий номер вже використовується. Введіть код товару ще раз: ");
                        while (getchar() != '\n');
                    }
                    else {
                        new_info->number = code_num;
                        while (getchar() != '\n');
                        break;
                    }
                }
            }
            fprintf(f_temp, "%d %s %s %.2f %s\n", new_info->number, new_info->name, new_info->group_product, new_info->price, new_info->provider);
        }
        break;

    case 2: {
        char name2[MAX + 1];
        printf("Введіть номер товару: ");
        scanf_s("%d", &cod);
        while (getchar() != '\n');

        while (fscanf(f_my, "%d %s %s %f %s", &new_info->number, &new_info->name, &new_info->group_product, &new_info->price, &new_info->provider) != EOF) {

            if (new_info->number == cod) {
                printf("Введіть нову назву товару: ");
                fgets(name2, MAX + 1, stdin);
                strcpy(new_info->name, name2);
                new_info->name[strcspn(new_info->name, "\n")] = '\0';
            }

            fprintf(f_temp, "%d %s %s %.2f %s\n", new_info->number, new_info->name, new_info->group_product, new_info->price, new_info->provider);

        }

    }break;
    case 3: {
        char name2[MAX + 1];
        printf("Введіть номер товару: ");
        scanf_s("%d", &cod);
        while (getchar() != '\n');

        while (fscanf(f_my, "%d %s %s %f %s", &new_info->number, &new_info->name, &new_info->group_product, &new_info->price, &new_info->provider) != EOF) {

            if (new_info->number == cod) {
                printf("Введіть нову групу товару: ");
                fgets(name2, MAX + 1, stdin);
                strcpy(new_info->group_product, name2);
                new_info->group_product[strcspn(new_info->group_product, "\n")] = '\0';
            }

            fprintf(f_temp, "%d %s %s %.2f %s\n", new_info->number, new_info->name, new_info->group_product, new_info->price, new_info->provider);

        }

    }break;
    case 4: {
    
        printf("Введіть номер товару: ");
        scanf_s("%d", &cod);
        while (getchar() != '\n');

        while (fscanf(f_my, "%d %s %s %f %s", &new_info->number, &new_info->name, &new_info->group_product, &new_info->price, &new_info->provider) != EOF) {


            if (new_info->number == cod) {
                printf("Введіть нову ціну: ");
                while (1) {
                    if (scanf_s("%f", &price_num) != 1 || price_num < 0) {
                        printf("Помилка: недопустимий номер продукту або такий номер вже використовується. Введіть код товару ще раз: ");
                        while (getchar() != '\n');
                        
                    }
                    else {
                        new_info->price = price_num;
                        while (getchar() != '\n');
                        break;
                    }
                }



            }

            fprintf(f_temp, "%d %s %s %.2f %s\n", new_info->number, new_info->name, new_info->group_product, new_info->price, new_info->provider);

        }

    }break;
    case 5: {
        char name2[MAX + 1];
        printf("Введіть номер товару: ");
        scanf_s("%d", &cod);
        while (getchar() != '\n');

        while (fscanf(f_my, "%d %s %s %f %s", &new_info->number, &new_info->name, &new_info->group_product, &new_info->price, &new_info->provider) != EOF) {


            if (new_info->number == cod) {
                printf("Введіть нового постачальника товару: ");
                fgets(name2, MAX + 1, stdin);
                strcpy(new_info->provider, name2);
                new_info->provider[strcspn(new_info->provider, "\n")] = '\0';
            }

            fprintf(f_temp, "%d %s %s %.2f %s\n", new_info->number, new_info->name, new_info->group_product, new_info->price, new_info->provider);

        }

    }break;
    default: {
        printf("Неправильний номер стовпця.\n");
        goto col;
        break; }
    }

    free(new_info);
    fclose(f_my);    // Закриття файлів
    fclose(f_temp);

    remove(CurfileName);      // Видалення початкового файлу
    rename("temp.txt", CurfileName);  // Перейменування тимчасового файлу

    printf("Зміна даних успішно виконана.\n");


}
PUBLIC void search_by_supplier(const char* CurfileName) {
    struct info* new_info = (struct info*)malloc(sizeof(struct info));
    if (new_info == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return;
    }
    char name1[MAX + 1];

    FILE* f_my = fopen(CurfileName, "a+");
    if (f_my == NULL) {
        printf("Помилка відкриття файлу.\n");
        return;
    }

    printf("Введіть назву постачальника: ");
    scanf_s("%s", name1, MAX);
    while (getchar() != '\n');

    printf("| Код товару |   Назва товару  |  Група товару  | Ціна товару | Постачальник товару |\n");
    printf("+-----------------------------------------------------------------------------------+\n");
    while (fscanf(f_my, "%d %s %s %f %s", &new_info->number, &new_info->name,
        &new_info->group_product, &new_info->price, &new_info->provider) != EOF) {
        if (strcmp(name1, new_info->provider) == 0) {
            printf("|%11d | %15s | %14s | %11.2f | %18s  |\n", new_info->number, new_info->name,
                new_info->group_product, new_info->price, new_info->provider);
            new_info->next = first;
            first = new_info;
        }

        code_num++;
    }

    printf("+-----------------------------------------------------------------------------------+\n");

    fclose(f_my);

}
PUBLIC void low_prices(const char* CurfileName) {
    float low_price;
    printf("Введіть бажану ціну: ");
    scanf_s("%f", &low_price);
    struct info* new_info = (struct info*)malloc(sizeof(struct info));
    if (new_info == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return;
    }
    FILE* f_my = fopen(CurfileName, "a+");
    if (f_my == NULL) {
        printf("Помилка відкриття файлу.\n");
        return;
    }

    printf("| Код товару |   Назва товару  |  Група товару  | Ціна товару | Постачальник товару |\n");
    printf("+-----------------------------------------------------------------------------------+\n");
    while (fscanf(f_my, "%d %s %s %f %s", &new_info->number, &new_info->name, &new_info->group_product, &new_info->price, &new_info->provider) != EOF) {
        if (low_price > new_info->price) {
            printf("|%11d | %15s | %14s | %11.2f | %18s  |\n", new_info->number, new_info->name,
                new_info->group_product, new_info->price, new_info->provider);
            new_info->next = first;
            first = new_info;

        }
        code_num++;

    }
    printf("+-----------------------------------------------------------------------------------+\n");

    fclose(f_my);

}
PUBLIC int menu_settings() {
    char str[MAX + 1];
    while (1) {
        scanf_s("%s", str, MAX + 1);
        if (strcmp(str, "name") == 0) {
            return 1;
        }
        else if (strcmp(str, "csv") == 0) {
            return 2;
        }
        else {
            return 0;
        }
    }
}
PUBLIC void generation_key() {
    char key[KEY_LENGTH + 1];
    char sixteen_num[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    srand(time(0));
    int randomNumber;

    FILE* f_my_key = fopen("infopractice.cfg", "a+");
    if (f_my_key == NULL) {
        printf("Помилка відкриття файлу.\n");
        return;
    }

    for (int i = 0; i < KEY_LENGTH; i++) {
        randomNumber = rand() % 16;
        key[i] = sixteen_num[randomNumber];
    }
    key[KEY_LENGTH] = '\0';

    fprintf(f_my_key, "DB = mybd.dat\n");
    fprintf(f_my_key, "KEY = %s\n", key);

    fclose(f_my_key);
}
PUBLIC bool is_valid_key() {
    // Відкриття файлу для зчитування ключа 
    FILE* f_my_key = fopen("infopractice.cfg", "a+");
    if (f_my_key == NULL) {
        printf("Помилка відкриття файлу.\n");
        return false;
    }

    // Зчитування ключа з файлу
    char stored_key[KEY_LENGTH + 1];
    fgets(stored_key, sizeof(stored_key), f_my_key);

    // Видалення символу нового рядка, який може бути прочитаний з файлу
    stored_key[strcspn(stored_key, "\n")] = '\0';

    // Закриття файлу
    fclose(f_my_key);

    // Перевірка довжини ключа
    if (strlen(stored_key) != KEY_LENGTH)
        return false;

    // Перевірка допустимих символів
    char sixteen_num[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    for (int i = 0; i < KEY_LENGTH; i++) {
        bool valid_char = false;
        for (int j = 0; j < 16; j++) {
            if (stored_key[i] == sixteen_num[j]) {
                valid_char = true;
                break;
            }
        }
        if (!valid_char)
            return false;
    }

    return true;
}
PUBLIC void file_change_name(const char* CurfileName) {
    char NewNameFile[MAX_FILENAME_LENGTH + 1]; // Замінити на потрібне початкове ім'я файлу

    struct info* new_info = (struct info*)malloc(sizeof(struct info));
    if (new_info == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return;
    }

    while (getchar() != '\n');
    printf("Введіть нову назву файла: ");
    fgets(NewNameFile, MAX_FILENAME_LENGTH + 1, stdin);
    NewNameFile[strcspn(NewNameFile, "\n")] = '\0';


    FILE* f_my = fopen(CurfileName, "r");  // Відкриття файлу для читання записів
    if (f_my == NULL) {
        printf("Помилка відкриття файлу.\n");
        free(new_info);
        return;
    }

    FILE* f_temp = fopen(NewNameFile, "w");  // Відкриття тимчасового файлу для запису
    if (f_temp == NULL) {
        printf("Помилка відкриття тимчасового файлу.\n");
        free(new_info);
        fclose(f_my);
        return;
    }


    while (fscanf(f_my, "%d %s %s %f %s", &new_info->number, new_info->name,
        new_info->group_product, &new_info->price, new_info->provider) != EOF) {
        fprintf(f_temp, "%d %s %s %.2f %s\n", new_info->number, new_info->name, new_info->group_product, new_info->price, new_info->provider);
    }

    free(new_info);
    fclose(f_my);    // Закриття файлів
    fclose(f_temp);
    
    remove(CurfileName);  // Видалення початкового файлу
}
PUBLIC void exportCSV(const char* CurfileName) {
    struct info* new_info = (struct info*)malloc(sizeof(struct info));
    struct info* first = NULL;

    char csv[MAX_FILENAME_LENGTH+1];
    printf("Введіть назву CSV файла: Приклад 'data.csv' -  ");
    while (getchar() != '\n');
    fgets(csv, MAX_FILENAME_LENGTH, stdin);
    csv[strcspn(csv, "\n")] = '\0';

    FILE* f_my = fopen(CurfileName, "r");
    if (f_my == NULL) {
        printf("Не вдалося відкрити файл для зчитування.\n");
        return;
    }

    FILE* file = fopen(csv, "w+");
    if (file == NULL) {
        printf("Не вдалося відкрити файл для запису csv.\n");
        fclose(f_my);
        return;
    }

    while (1) {

        if (fscanf(f_my, "%d %s %s %f %s", &new_info->number, new_info->name, new_info->group_product, &new_info->price, new_info->provider) != 5) {
            free(new_info);
            break;
        }

        fprintf(file, "%d;%s;%s;%.2f;%s\n", new_info->number, new_info->name, new_info->group_product, new_info->price, new_info->provider);

        new_info->next = first;
        first = new_info;
    }

    fclose(file);
    fclose(f_my);

    printf("Дані успішно експортовано у файл з розширенням csv -  %s\n", csv);

}
