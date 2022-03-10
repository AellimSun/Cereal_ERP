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
	char NAME[20];
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
	char value[50];
	char CODE[5];
	char NAME[30];
	int safe_stock;

	printf("==================\n");
	printf("자재를 등록합니다.\n");
	printf("==================\n\n");

	printf("자재품목 코드 등록 : \n");
	//printf("현재 사용 중인 코드 : ****");
	scanf("%s", CODE);
	printf("자재품목 이름 등록 : ");
	scanf("%s", NAME);
	printf("안전 재고 등록 : ");
	scanf("%d", &safe_stock);

	//Matls* newNode = (Matls*)malloc(sizeof(Matls));
	//if (newNode == NULL)
	//	return;
	//strcpy(newNode->CODE, CODE);
	//strcpy(newNode->materials_name, Materials_name);
	//strcpy(newNode->backup, safe_stock);

	strcpy(value, "'");
	strcat(value, CODE);
	strcat(value, "','");
	strcat(value, NAME);
	strcat(value, "'");
	//strcat(value, safe_stock);
	//strcat(value, "'");

	printf("%s\n", value);

	if (initalizing("33") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	char ex1[50] = "'M1001', '옥수수'";
	char ex2[50] = "'M1002', '설탕'";
	char ex3[50] = "'M1003', '소금'";

	if (_insert(value) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();

	printf("새로운 자재품목 등록완료. 메인으로 이동합니다.");
	system("pause");
	system("cls");
	main();
}

void updateMaterials()
{

}

void readMaterials()
{
	int menu;

	printf("1. 자재품목 코드로 조회\n");
	printf("2. 자재품목 이름으로 조회\n");
	scanf("%d", &menu);

	switch (menu)
	{
	case 1:
		read_CODE();
		break;
	case 2:
		read_materials_name();
		break;
	}
}

void deleteMaterials()
{

}

void read_CODE()
{
	char search[5];
	char temp[20] = "CODE='";

	printf("검색할 자재품목 코드를 입력 : ");
	scanf("%s", search);

	strcat(temp, search);
	strcat(temp, "'");

	char* conditional = "CODE='M1001'";
	char* select_column = "CODE, NAME";

	if (initalizing("33") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	printf("%s", conditional);

	if (_select(conditional, select_column, &select_result_str) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		printf("%s\n", select_result_str);
	}

	print_data();
	printf("\n");
	file_column_free();

	main();

}

void read_materials_name()
{
	char search[5];
	char temp[20] = "NAME='";

	printf("검색할 거래처의 사업자 번호를 입력하세요 : ");
	scanf("%s", search);

	strcat(temp, search);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "CODE, NAME";

	if (initalizing("33") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	if (_select(conditional, select_column, &select_result_str) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		printf("%s\n", select_result_str);
	}

	print_data();
	printf("\n");
	file_column_free();

	main();
}

