#include "config_manager.h"


int read_pathDB(char* cfg_path, char* out_path) {
	// .cfg файл
	FILE* configure;

	char path[200];


	// якщо не існує
	if ((configure = fopen(cfg_path, "r+t")) == NULL) {
		// файл не відкритий повертаємо 1
		return 1;
	}
	// зміщуємося та зчитуємо шлях
	fseek(configure, 113, SEEK_SET);
	fgets(path, 200, configure);
	strcpy(out_path, path);
	fclose(configure);
	return 0;
}

int read_key(char* cfg_path, int* key) {
	// .cfg файл
	FILE* configure;

	// якщо не існує
	if ((configure = fopen(cfg_path, "r+t")) == NULL) {
		// файл не відкритий повертаємо 1
		return 1;
	}

	// зміщуємося та зчитуємо шлях
	fseek(configure, -8, SEEK_END);
	fscanf(configure, "%d", key);
	fclose(configure);
	return 0;
}