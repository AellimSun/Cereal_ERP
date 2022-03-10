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
	
		_insert("'A0000', '바나나', 10");
		
		print_data();

		file_column_free();

	int menu;
	printf("자재품목 등록\n");
	printf("자재품목 수정\n");
	printf("자재품목 조회\n");
	printf("자재품목 삭제\n");
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
	printf("자재를 등록합니다.\n");
	printf("==================\n\n");

	printf("자재품목 코드 등록 : \n");
	printf("현재 사용 중인 코드 : ****");
	scanf("%d", &new_code);
	printf("자재품목 이름 등록 : ");
	scanf("%s", &new_name);
	printf("안전 재고 등록 : ");
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
//	printf("자재품목 등록\n");
//	printf("자재품목 수정\n");
//	printf("자재품목 조회\n");
//	printf("자재품목 삭제\n");
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


