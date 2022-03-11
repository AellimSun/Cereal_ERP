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
	int BACKUP;
	char MSP[3]; // 자재:M 반제품:S 완제품:P
	struct Materialsnode* next;
}Matls;

void insertMaterials();
void updateMaterials();
void readMaterials();
void deleteMaterials();

void read_CODE();
void read_NAME();
void read_MSP();
void read_ALL();


void product_list()
{
	//_create("list", "CODE VARCHAR(6) NAME VARCHAR(30) BACKUP INT MSP CHAR");
	/*print_data();*/
	
		//if (initalizing("list") == -1)
		//{
		//printf("%s\n", err_msg);

		//file_column_free();
		//return -1;
		//}
	
		//_insert("'A0000', '바나나', 10");
		//
		//print_data();

		//file_column_free();

	int menu;
	printf("1.자재품목 등록\n");
	printf("2.자재품목 수정\n");
	printf("3.자재품목 조회\n");
	printf("4.자재품목 삭제\n");
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
	char values[50];
	char CODE[5];
	char NAME[30];
	int BACKUP=0;
	char MSP[3];

	printf("==================\n");
	printf("자재를 등록합니다.\n");
	printf("==================\n\n");

	printf("자재품목 코드 등록 : ");
	//printf("현재 사용 중인 코드 : ****");
	scanf("%s", CODE);
	printf("자재품목 이름 등록 : ");
	scanf("%s", NAME);
	printf("안전 재고 등록(g) :  ");
	scanf("%d", &BACKUP);
	printf("원자재:'M', 반제품:'S', 완제품:'P'\n 자재의 계정을 입력하세요 : ");
	scanf("%s", MSP);

	char temp = "M\n" || "S\n" || "P\n";
	while (temp == 0)
	{
		printf("잘못 입력했습니다.\n");
		printf("자재의 계정을 다시 입력해주세요\n");
		printf("원자재:'M', 반제품:'S', 완제품:'P'\n");
	}

	char BACKUP_S[30];
	itoa(BACKUP, BACKUP_S, 10);

	//Matls* newNode = (Matls*)malloc(sizeof(Matls));
	//if (newNode == NULL)
	//	return;
	//strcpy(newNode->CODE, CODE);
	//strcpy(newNode->materials_name, Materials_name);
	//strcpy(newNode->backup, safe_stock);

	strcpy(values, "'");
	strcat(values, CODE);
	strcat(values, "','");
	strcat(values, NAME);
	strcat(values, "','");
	strcat(values, BACKUP_S);
	strcat(values, "','");
	strcat(values, MSP);
	strcat(values, "'");

	printf("%s\n", values);

	if (initalizing("list") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//char ex1[50] = "'M1001', '옥수수', '10', 'M'";
	//char ex2[50] = "'M1002', '설탕', '50'";
	//char ex3[50] = "'M1003', '소금', '10'";

	//if (_insert(ex1) == -1)
	//{
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert(ex2) == -1)
	//{
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert(ex3) == -1)
	//{
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	if (_insert(values) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();

	printf("새로운 자재품목 등록완료. 자재품목 관리로 이동합니다.\n\n");
	system("pause");
	system("cls");
	product_list();
}

void updateMaterials()
{
	//result* _result;
	//int result_count;

	//char *conditional = temp;
	//char *set = 

	//if (initalizing("product_list") == -1)
	//{
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_update(conditional, set) == -1)
	//{
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}
}

void readMaterials()
{
	int menu;

	printf("1. 자재품목 코드로 조회\n");
	printf("2. 자재품목 이름으로 조회\n");
	printf("3. 자재품목 계정으로 조회\n");
	printf("4. 자재품목 전체조회\n");
	printf("0. 이전으로\n");
	scanf("%d", &menu);

	switch (menu)
	{
	case 1:
		read_CODE();
		break;
	case 2:
		read_NAME();
		break;
	case 3:
		read_MSP();
		break;
	case 4:
		read_ALL();
		break;
	case 0:
		product_list();
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

	result* _result;
	int result_count;

	printf("검색할 자재품목 코드를 입력 : ");
	scanf("%s", search);

	strcat(temp, search);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "CODE, NAME, BACKUP, MSP";

	if (initalizing("list") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	//printf("%s", conditional);

	if (_select(conditional, select_column, &select_result_str) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else 
	{
		printf("%s\n", select_result_str);
	}
	if ((result_count = recv_result(&_result, select_result_str)) == -1) 
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);

	print_data();
	printf("\n");
	file_column_free();

	main();

}

void read_NAME()
{
	char search[5];
	char temp[20] = "NAME='";

	result* _result;
	int result_count;

	printf("검색할 자재품목 이름을 입력하세요 : ");
	scanf("%s", search);

	strcat(temp, search);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "CODE, NAME, BACKUP, MSP";

	if (initalizing("list") == -1)
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
	else 
	{
		printf("%s\n", select_result_str);
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) 
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");


	print_data();
	printf("\n");
	file_column_free();

	main();
}

void read_MSP()
{

	char search[5];
	char temp[20] = "MSP='";

	result* _result;
	int result_count;

	printf("검색할 자재품목 계정을 입력하세요 : \n 원자재:M, 반제품:S, 완제품:P\n");
	scanf("%s", search);

	strcat(temp, search);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "CODE, NAME, BACKUP, MSP";

	if (initalizing("list") == -1)
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
	else
	{
		printf("%s\n", select_result_str);
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");


	print_data();
	printf("\n");
	file_column_free();

	main();
}

void read_ALL()
{
	if (initalizing("list") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();

	product_list();
}