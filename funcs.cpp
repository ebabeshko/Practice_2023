#include "funcs.h"
struct client_info {
    char name[MAX+1];           // ������� �� ��� (� ����� ����� �����)
    char email[MAX+1];          // ������ e-mail (�����)
    int rating;               // ������� (���� �����)
    float annual_turnove;    // ����� ������ �� �볺���� (����� � ��������� ������)
    struct client_info* next;
};

struct client_info* first = NULL;

int code_num = 0;

PUBLIC void fill(const char* CurfileName) {
    struct client_info* new_client = (struct client_info*)malloc(sizeof(struct client_info));
    if (new_client == NULL) {
        printf("������� �������� ���'��.\n");
        return;
    }

    FILE* f_my = fopen(CurfileName, "a"); 
    if (f_my == NULL) {
        printf("������� �������� �����.\n");
        free(new_client);
        return;
    }

    if (code_num == MAX) {
        printf("���� ���������, ��������� ���������.\n");
        fclose(f_my);
        free(new_client);
        return;
    }

    while (getchar() != '\n');
    printf("������ ������� �� ��� �볺���: ");
    fgets(new_client->name, MAX+1, stdin);
    new_client->name[strcspn(new_client->name, "\n")] = '\0';

    printf("������ e-mail �볺���: ");
    fgets(new_client->email, MAX+1, stdin);
    new_client->email[strcspn(new_client->email, "\n")] = '\0';

    printf("������ ������� �볺���: ");
    while (1) {
        if (scanf("%d", &new_client->rating) != 1 || new_client->rating < 0) {
            printf("�������: ������������ �������. ������ ������� �볺��� �� ���: ");
            while (getchar() != '\n');
        }
        else {
            while (getchar() != '\n');
            break;
        }
    }

    printf("������ ����� ������ �� �볺����: ");
    while (1) {
        if (scanf("%f", &new_client->annual_turnove) != 1 || new_client->annual_turnove < 0) {
            printf("�������: ������������ ����� ������. ������ ����� ������ �� �볺���� �� ���: ");
            while (getchar() != '\n');
        }
        else {
            while (getchar() != '\n');
            break;
        }
    }
    new_client->next = first;
    first = new_client;

    fprintf(f_my, "%s\t%s\t%d\t%.2f\n", new_client->name, new_client->email, new_client->rating, new_client->annual_turnove);

    fclose(f_my);
}
PUBLIC void output(const char* CurfileName) {
    FILE* f_my = fopen(CurfileName, "a+");
    if (f_my == NULL) {
        printf("������� �������� �����.\n");
        return;
    }

    fseek(f_my, 0, SEEK_SET);

    char line[200];

    
    printf("+--------------------------------+--------------------------------+----------+--------------+\n");
    printf("|           ������� �� ���     |           E-mail               |�������   |г���� ������ |\n");
    printf("+--------------------------------+--------------------------------+----------+--------------+\n");

    while (fgets(line, sizeof(line), f_my)) {
        struct client_info* new_client = (struct client_info*)malloc(sizeof(struct client_info));

        if (new_client == NULL) {
            printf("������� �������� ���'��.\n");
            break;
        }

        char* token;
        token = strtok(line, "\t\n");

        if (token) {
            strcpy(new_client->name, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            strcpy(new_client->email, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%d", &new_client->rating);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%f", &new_client->annual_turnove);
        }

        
        printf("| %-30s | %-30s | %-8d | %-12.2f |\n", new_client->name, new_client->email, new_client->rating, new_client->annual_turnove);

        free(new_client);
    }

    
    printf("+--------------------------------+--------------------------------+----------+--------------+\n");

    fclose(f_my);
}
PUBLIC void del(const char* CurfileName) {
    FILE* f_my = fopen(CurfileName, "r");
    if (f_my == NULL) {
        printf("������� �������� �����.\n");
        return;
    }

    
    FILE* f_temp = fopen("temp.txt", "w");
    if (f_temp == NULL) {
        printf("������� �������� ����������� �����.\n");
        fclose(f_my);
        return;
    }

    char line[200];
    int client_deleted = 0, rat; 
    printf("������ ������� �볺��� ��� ���������.\n");
    scanf_s("%d", &rat);
    while (fgets(line, sizeof(line), f_my)) {
        struct client_info* new_client = (struct client_info*)malloc(sizeof(struct client_info));
        if (new_client == NULL) {
            printf("������� �������� ���'��.\n");
            break;
        }

        char* token;
        token = strtok(line, "\t\n");

        if (token) {
            strcpy(new_client->name, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            strcpy(new_client->email, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%d", &new_client->rating);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%f", &new_client->annual_turnove);
        }

        if (new_client->rating== rat) {
           
            client_deleted = 1;
            free(new_client);
            continue;
        }

        fprintf(f_temp, "%s\t%s\t%d\t%.2f\n", new_client->name, new_client->email, new_client->rating, new_client->annual_turnove);

        free(new_client);
    }

    fclose(f_my);
    fclose(f_temp);

    
    remove(CurfileName);
    rename("temp.txt", CurfileName);

    if (client_deleted)
        printf("�볺�� � ��������� %d ��� ������ ���������.\n", rat);
    else
        printf("�볺�� � ��������� %d �� ���������.\n", rat);

}
PUBLIC void edit(const char* CurfileName) {
    int col, rat;
    char name2[MAX + 1];
    float annual_turnover;

    printf("������ ������� �볺���, ����� ������� ����������: ");
    if (scanf("%d", &rat) != 1) {
        printf("�������: ������� �������.\n");
        return;
    }
    while (getchar() != '\n');

    FILE* f_my = fopen(CurfileName, "r");
    if (f_my == NULL) {
        printf("������� �������� �����.\n");
        return;
    }

    FILE* f_temp = fopen("temp.txt", "w");
    if (f_temp == NULL) {
        printf("������� �������� ����������� �����.\n");
        fclose(f_my);
        return;
    }

    int found = 0;

    fseek(f_my, 0, SEEK_SET);
    char line[200];
    while (fgets(line, sizeof(line), f_my)) {
        struct client_info* new_client = (struct client_info*)malloc(sizeof(struct client_info));
        if (new_client == NULL) {
            printf("������� �������� ���'��.\n");
            break;
        }

        char* token;
        token = strtok(line, "\t\n");

        if (token) {
            strcpy(new_client->name, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            strcpy(new_client->email, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%d", &new_client->rating);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%f", &new_client->annual_turnove);
        }

        if (new_client->rating == rat) {
            found = 1;
            printf("�볺�� �� ��������� %d:\n", rat);
            printf("1. �������: %d\n", new_client->rating);
            printf("2. ������� �� ���: %s\n", new_client->name);
            printf("3. E-mail: %s\n", new_client->email);
            printf("4. г���� ������: %.2f\n", new_client->annual_turnove);

            printf("������ ����� �������, ���� ������ ������ (1-4): ");
            if (scanf("%d", &col) != 1) {
                printf("������� ����� �������.\n");
                fclose(f_my);
                fclose(f_temp);
                free(new_client); 
                return;
            }
            while (getchar() != '\n');

            switch (col) {
            case 1:
                printf("������ ����� �������: ");
                if (scanf("%d", &(new_client->rating)) != 1 || new_client->rating < 0) {
                    printf("�������: ������������ �������.\n");
                    fclose(f_my);
                    fclose(f_temp);
                    return;
                }
                break;

            case 2:
                printf("������ ���� ������� �� ��� �볺���: ");
                fgets(name2, MAX + 1, stdin);
                name2[strcspn(name2, "\n")] = '\0';
                strcpy(new_client->name, name2);
                break;

            case 3:
                printf("������ ����� e-mail �볺���: ");
                fgets(name2, MAX + 1, stdin);
                name2[strcspn(name2, "\n")] = '\0';
                strcpy(new_client->email, name2);
                break;


            case 4:
                printf("������ ����� ����� ������ �� �볺����: ");
                while (scanf("%f", &annual_turnover) != 1 || annual_turnover < 0) {
                    printf("�������: ������������ ����� ������. ������ �� ���: ");
                    while (getchar() != '\n'); 
                }
                new_client->annual_turnove = annual_turnover;
                break;

            default:
                printf("������� ����� �������.\n");
                fclose(f_my);
                fclose(f_temp);
                free(new_client); 
                return;
            }

            fprintf(f_temp, "%s\t%s\t%d\t%.2f\n", new_client->name, new_client->email, new_client->rating, new_client->annual_turnove);
        }
        else {
            fprintf(f_temp, "%s\t%s\t%d\t%.2f\n", new_client->name, new_client->email, new_client->rating, new_client->annual_turnove);
        }

        free(new_client);
    }

    fclose(f_my);
    fclose(f_temp);

    remove(CurfileName);
    rename("temp.txt", CurfileName);

    if (found)
        printf("���� ����� ������ ��������.\n");
    else
        printf("�볺�� � ��������� %d �� ���������.\n", rat);
}

PUBLIC void rating_search(const char* CurfileName) {
    int target_rating;
    printf("������ ������� ��� ������: ");
    scanf_s("%d", &target_rating);

    FILE* f_my = fopen(CurfileName, "a+");
    if (f_my == NULL) {
        printf("������� �������� �����.\n");
        return;
    }

    printf("+--------------------------------+--------------------------------+----------+--------------+\n");
    printf("|           ������� �� ���     |           E-mail               |�������   |г���� ������ |\n");
    printf("+--------------------------------+--------------------------------+----------+--------------+\n");

    fseek(f_my, 0, SEEK_SET);

    char line[200];
    while (fgets(line, sizeof(line), f_my)) {
        struct client_info* new_client = (struct client_info*)malloc(sizeof(struct client_info));
        if (new_client == NULL) {
            printf("������� �������� ���'��.\n");
            break;
        }

        char* token;
        token = strtok(line, "\t\n");

        if (token) {
            strcpy(new_client->name, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            strcpy(new_client->email, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%d", &new_client->rating);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%f", &new_client->annual_turnove);
        }

        
        if (new_client->rating < target_rating) {
            
            printf("| %-30s | %-30s | %-8d | %-12.2f |\n", new_client->name, new_client->email, new_client->rating, new_client->annual_turnove);
        }

        free(new_client);
    }

    
    printf("+--------------------------------+--------------------------------+----------+--------------+\n");

    fclose(f_my);
}
PUBLIC void annual_turnover(const char* CurfileName) {
    float annual_turnover;

    printf("������ ������ ��� ������: ");
    scanf("%f", &annual_turnover);

    FILE* f_my = fopen(CurfileName, "r");
    if (f_my == NULL) {
        printf("������� �������� �����.\n");
        return;
    }

    char line[200];
    struct client_info* first = NULL; 

    
    struct client_info* last = NULL;

    while (fgets(line, sizeof(line), f_my)) {
        struct client_info* new_client = (struct client_info*)malloc(sizeof(struct client_info));
        if (new_client == NULL) {
            printf("������� �������� ���'��.\n");
            break;
        }

        char* token;
        token = strtok(line, "\t\n");

        if (token) {
            strcpy(new_client->name, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            strcpy(new_client->email, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%d", &new_client->rating);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%f", &new_client->annual_turnove);
        }

        if (new_client->annual_turnove < annual_turnover) {
            new_client->next = NULL;

            if (first == NULL) {
                first = new_client;
                last = new_client;
                
            }
            else {
                last->next = new_client;
                last = new_client;
            }
            break;
        }
        else {
            free(new_client); 
        }
    }

    fclose(f_my);

    
    if (first != NULL) {
        printf("+--------------------------------+--------------------------------+----------+--------------+\n");
        printf("|           ������� �� ���     |           E-mail               |�������   |г���� ������ |\n");
        printf("+--------------------------------+--------------------------------+----------+--------------+\n");

        
        struct client_info* current = first;
        while (current != NULL) {
            printf("| %-30s | %-30s | %-8d | %-12.2f |\n", current->name, current->email, current->rating, current->annual_turnove);
            current = current->next;
        }

        printf("+--------------------------------+--------------------------------+----------+--------------+\n");
    }
    else {
        printf("�볺��� � �������� ����� ��������� �������� �� ��������.\n");
    }

    
    struct client_info* current = first;
    while (current != NULL) {
        struct client_info* temp = current;
        current = current->next;
        free(temp);
    }
}


PUBLIC void generation_key() {
  

    FILE* f_my_key = fopen("funcs.cfg", "a+");
    if (f_my_key == NULL) {
        printf("������� �������� �����.\n");
        return;
    }  
    srand(time(0));

    
    unsigned char key[KEY_LENGTH+1];

   
    for (int i = 0; i < KEY_LENGTH; i++) {
        key[i] = rand() % 256; 
    }

    
    printf("������������ ����: ");
    for (int i = 0; i < KEY_LENGTH; i++) {
        printf("%02X", key[i]); 
    }
    printf("\n");

    fprintf(f_my_key, "DB = mybd.dat\n");
    fprintf(f_my_key, "KEY = %02X\n", key);

    fclose(f_my_key);
}
PUBLIC bool valid() {
    // ³������� ����� ��� ���������� ����� 
    FILE* f_my_key = fopen("funcs.cfg", "a+");
    if (f_my_key == NULL) {
        printf("������� �������� �����.\n");
        return false;
    }

    // ���������� ����� � �����
    char stored_key[KEY_LENGTH + 1];
    fgets(stored_key, sizeof(stored_key), f_my_key);

    // ��������� ������� ������ �����, ���� ���� ���� ���������� � �����
    stored_key[strcspn(stored_key, "\n")] = '\0';

    // �������� �����
    fclose(f_my_key);

    // �������� ������� �����
    if (strlen(stored_key) != KEY_LENGTH)
        return false;

    // �������� ���������� �������
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
    char NewNameFile[MAX_FILENAME_LENGTH + 1];

    struct client_info* new_client = (struct client_info*)malloc(sizeof(struct client_info));
    if (new_client == NULL) {
        printf("������� �������� ���'��.\n");
        return;
    }

    while (getchar() != '\n');
    printf("������ ���� ����� �����: ");
    fgets(NewNameFile, MAX_FILENAME_LENGTH + 1, stdin);
    NewNameFile[strcspn(NewNameFile, "\n")] = '\0';

    FILE* f_my = fopen(CurfileName, "r");
    if (f_my == NULL) {
        printf("������� �������� �����.\n");
        free(new_client);
        return;
    }

    FILE* f_temp = fopen(NewNameFile, "w");
    if (f_temp == NULL) {
        printf("������� �������� ����������� �����.\n");
        free(new_client);
        fclose(f_my);
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), f_my)) {
        char* token;
        token = strtok(line, "\t\n");

        if (token) {
            strcpy(new_client->name, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            strcpy(new_client->email, token);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%d", &new_client->rating);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%f", &new_client->annual_turnove);
        }

        fprintf(f_temp, "%s\t%s\t%d\t%.2f\n", new_client->name, new_client->email, new_client->rating, new_client->annual_turnove);
    }

    free(new_client);
    fclose(f_my);
    fclose(f_temp);

    remove(CurfileName);
}

PUBLIC void CSV(const char* CurfileName) {
    struct client_info* new_client;
    char csv[MAX_FILENAME_LENGTH + 1];
    printf("������ ����� CSV �����: ������� 'data.csv' - ");

    while (getchar() != '\n');

    fgets(csv, MAX_FILENAME_LENGTH, stdin);
    csv[strcspn(csv, "\n")] = '\0';

    FILE* f_my = fopen(CurfileName, "r");
    if (f_my == NULL) {
        printf("�� ������� ������� ���� ��� ����������.\n");
        return;
    }

    FILE* file = fopen(csv, "w");
    if (file == NULL) {
        printf("�� ������� ������� ���� ��� ������ csv.\n");
        fclose(f_my);
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), f_my)) {
        new_client = (struct client_info*)malloc(sizeof(struct client_info));
        if (new_client == NULL) {
            printf("������� �������� ���'��.\n");
            fclose(file);
            fclose(f_my);
            return;
        }

        char* token;
        token = strtok(line, "\t\n"); 

        if (token) {
            strncpy(new_client->name, token, sizeof(new_client->name) - 1);
            new_client->name[sizeof(new_client->name) - 1] = '\0';
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            strncpy(new_client->email, token, sizeof(new_client->email) - 1);
            new_client->email[sizeof(new_client->email) - 1] = '\0';
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%d", &new_client->rating);
            token = strtok(NULL, "\t\n");
        }

        if (token) {
            sscanf(token, "%f", &new_client->annual_turnove);
        }

        fprintf(file, "%s;\t%s;\t%d;\t%.2f;\n", new_client->name, new_client->email, new_client->rating, new_client->annual_turnove);
        free(new_client);
    }

    fclose(file);
    fclose(f_my);

    printf("��� ������ ������������ � ���� � ����������� csv - %s\n", csv);
}
