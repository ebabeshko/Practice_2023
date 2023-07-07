
//////////|
//define//|
//////////|

//������� �������
#define PRIVATE static
#define PUBLIC
//������������
/*#define DEF*/
//����� �������
#define ERROR_TYPE 1
#define SIZE 246

/////////////////////////////////////|
// ��������� ��� �����, �� �� �����//|
/////////////////////////////////////|

/**
* ��'����� ������ ������
*
* @type id		, ����� ������
* @type name	, ����� ������
* @type	groupe	, ������ ������
* @type	price	, ���� ������
* @type	from	, ������������ ������
* @type delstat	, ���� ���������(0 - �� ��������, 1 - ��������)
* @type * next	, ��������� ����� ������������ ������
*/
struct Stuff {			/* ���������� ��'����� ������ ������ */
	int id;				/* ����� ������ */
	char* name;			/* ����� ������ */
	char* group;		/* ������ ������ */
	double price;		/* ���� ������ */
	char* from;			/* ������������ ������ */
	int delstat = 0;	/* ����� ����� ���������� ����� */
	struct Stuff* next;	/* ��������� ����� */
};

/////////////////////////////////////////////////////////////////////|
// ��������� �������� �������, �� �� ������������� ������� �������//|
/////////////////////////////////////////////////////////////////////|

/**
* ������� ���� ���������
*
* @param arr, �������� �� ��'����� ������
* @return 0, �� ���������� ����
*/
int menu(struct Stuff** arr);
/**
* ����������� ��������
*
* @param ptr, ����� ��'������ ������
* @return 0
*/
int SetStuff(struct Stuff* ptr);
/**
* ��������� �����
*
* @param ptr, ����� ��'������ ������
* @return void
*/
void PrintStuff(struct Stuff* ptr);
/**
* ��������� ������ ������
*
* @param arr, �������� �� ��'����� ������
* @return 0, �� ���������� ����
*/
int AddStuff(struct Stuff** arr);
/**
* ����������� ������ ����� ������
*
* @param help_new_stuff, �������� �� �����, ���� ����� ������������
* @return 0, �� ���������� ����
*/
int AddHelper(struct Stuff* help_new_stuff);
/**
* �������� ����� ������
*
* @param str, ������
* @param n, ������� �������
* @return i, ������� ��������� �������
*/
int read_line(char* str, int n);
/**
* ������� ����� �������
*
* @param NULL
* @return Csymb, ������� ������
*/
char getsymb();
/**
* ��������� �����
*
* @param arr, �������� �� ��'����� ������
* @return 0, �� ���������� ����
*/
int DeleteStuff(struct Stuff** arr);
/**
* ��������� ��� �����
*
* @param arr, �������� �� ��'����� ������
* @return void
*/
void PrintAll(struct Stuff** arr);
/**
* ���� ����� �� ���� Id
*
* @param ptr, ����� ��'������ ������
* @return void
*/
void ChangeSet(struct Stuff* ptr);
/**
* ����� ����� �� ���� Id
*
* @param ptr, ����� ��'������ ������
* @return void
*/
void PrintId(struct Stuff* ptr);
/**
* ��������� ��� ������, �� ������������ ������� ��������������.
*
* @param ptr, ����� ��'������ ������
* @return 0, �� ���������� ����
*/
int PrintFrom(struct Stuff* ptr);
/**
* ��������� ��� ������ ������ �����, ���� ���� ����� �� ������.
*
* @param ptr, ����� ��'������ ������
* @return 0, �� ���������� ����
*/
int GroupPriceFall(struct Stuff* ptr);
/**
* ����� ���������� � ��, �� �������� �� � ��'����� ������
*
* @param arr, �������� �� ��'����� ������
* @param pcsv, �������� �� ����
* @return 0, �� ���������� ����
*/
int readDataFromFile(struct Stuff** arr, FILE* pcsv);
/**
* ����� ���������� �� ���������, �� �������� �� � ��
*
* @param arr, �������� �� ��'����� ������
* @param pcsv, �������� �� ����
* @return 0, �� ���������� ����
*/
int writeDataToFile(struct Stuff** arr);
/**
* ����� ���������� �� ��'����� ������, �� �������� �� � ��
*
* @param arr, �������� �� ��'����� ������
* @return count, ������� ������
*/
int CountOfWork(struct Stuff** arr);
/**
* AddStuff ��� ������� ��� ������ ������ ������
*
* @param ptr, ����� ��'������ ������
* @return true, �� ���������� ����
*/
bool TheDogma(struct Stuff* ptr);