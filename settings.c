#include "settings.h"

// функція зчитування значень з файлу бази даних
void config_read(char configname[100], char path_db[100], int* key) {
	FILE* configure;
	// якщо не існує фалу налаштувань наповнюємо його
	if ((configure = fopen(configname, "r+t")) == NULL) {
		// виводимо попередження
		printf("\n.cfg File doesnt exist!\n");
		printf("Creating .cfg file\n");
		// створюємо файл
		configure = fopen(configname, "w");
		fputs("; Файл налаштувань\n", configure);
		fputs("; шлях бази даних записується у форматі DB = <шлях_до_файлу>\n", configure);
		fputs("DB = new_base.dat\n", configure);
		fputs("; Ліцензійний ключ ліцензійний ключ\n", configure);
		fputs("KEY = 12345678", configure);
		fclose(configure);
		configure = fopen(configname, "r");
	}
	fseek(configure, 87, SEEK_SET);
	//база даних
	fgets(path_db, 100, configure);
	path_db[strlen(path_db) - 1] = '\0';
	fseek(configure, -9, SEEK_END);
	//ключ
	fscanf(configure, "%d", key);
}


// редагування ключа
void edit_key(char configname[100], int key) {
	FILE* configure;
	configure = fopen(configname, "r+");
	fseek(configure, -8, SEEK_END);
	fprintf(configure, "%d", key);
	fclose(configure);
}


// редагування бази даних
void edit_pathDB(char configname[100], char path_db[100]) {
	FILE* configure;
	configure = fopen(configname, "r+");
	fseek(configure, 87, SEEK_SET);
	fprintf(configure, "%s\n", path_db);
	fclose(configure);
}
