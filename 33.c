#include "cereal.h"
#include <stdio.h>


//int main(void)
//{
//	char* values = "NULL, 800, 'q', 69.11212, 4215.134555666777";
//	char* conditional = "TP='q'";
//	char *set = "TP='c'";
//	char* select_column = "code, number, TP, FLT, DBL";
//
//	result* _result;
//	result* find;
//	int result_count;
//
//	if (initalizing("D:\\git\\my\\Project1\\samplec") == -1)
//	{
//		printf("%s\n", err_msg);
//
//		file_column_free();
//		return -1;
//	}
//	print_data();
//
//	printf("n");
//
//}


typedef struct Materialsnode {
	char CODE[5];
	char materials_name[20];
	int backup;
	struct Materialsnode* next;
}Matls;

void insertMaterials();
void updateMaterials();
void readMaterials();
void deleteMaterials();

void product_list()
{
	//_create("list", "CODE VARCHAR(6) NAME VARCHAR(30) BACKUP INT");
	//print_data();
	
		if (initalizing("list") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	
		_insert("'A0000', '�ٳ���', 10");
		
		print_data();

		file_column_free();

	int menu;
	printf("����ǰ�� ���\n");
	printf("����ǰ�� ����\n");
	printf("����ǰ�� ��ȸ\n");
	printf("����ǰ�� ����\n");
	scanf("%d", &menu);

	switch (menu)
	{
	case 1:
		insertMaterials();
		break;
	case 2:
		updateMaterials();
		break;
	case 3:
		readMaterials();
		break;
	case 4:
		deleteMaterials();
		break;
	}
}


void insertMaterials()
{
	char new_code[5];
	char new_name[30];
	int safe_stock;

	printf("==================\n");
	printf("���縦 ����մϴ�.\n");
	printf("==================\n\n");

	printf("����ǰ�� �ڵ� ��� : \n");
	printf("���� ��� ���� �ڵ� : ****");
	scanf("%d", &new_code);
	printf("����ǰ�� �̸� ��� : ");
	scanf("%s", &new_name);
	printf("���� ��� ��� : ");
	scanf("%d", &safe_stock);

	Matls* newNode = (Matls*)malloc(sizeof(Matls));
	if (newNode == NULL)
		return;
	strcpy(newNode->CODE, new_code);
	strcpy(newNode->materials_name, new_name);
	strcpy(newNode->backup, safe_stock);

}

void updateMaterials()
{

}

void readMaterials()
{

}

void deleteMaterials()
{

}

//void Materials()
//{
//	int menu;
//	printf("����ǰ�� ���\n");
//	printf("����ǰ�� ����\n");
//	printf("����ǰ�� ��ȸ\n");
//	printf("����ǰ�� ����\n");
//	scanf("%d", &menu);
//
//	switch (menu)
//	{
//	case 1:
//		insertMaterials();
//		break;
//	case 2:
//		updateMaterials();
//		break;
//	case 3:
//		readMaterials();
//		break;
//	case 4:
//		deleteMaterials();
//		break;
//	}
//}


