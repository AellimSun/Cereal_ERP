#include "cereal.h"
#include <stdio.h>

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

void read_CODE(char* search);
void read_NAME();
void read_MSP();
void read_ALL();

result* read_CODE2(char* search);


void product_list()
{
	//_create("list", "CODE VARCHAR(6) NAME VARCHAR(30) BACKUP INT MSP CHAR");
	//print_data();
	
	int menu;

	printf("위치 : 메인메뉴 -> 생산관리 -> 기초정보관리 -> 자재품목 리스트\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     메뉴를 선택하세요.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      1.자재품목 등록      |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      2.자재품목 수정      |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      3.자재품목 조회      |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      4.자재품목 삭제      |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      0.이전으로           |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t 입력 :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 17);
	

	scanf("%d", &menu);
	system("cls");

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
	case 0:
		base_information();
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
	scanf("%s", CODE);
	printf("자재품목 이름 등록 : ");
	scanf("%s", NAME);
	printf("안전 재고 등록(g) :  ");
	scanf("%d", &BACKUP);
	printf("원자재:'M', 반제품:'S', 완제품:'P'\n 자재의 계정을 입력하세요 : ");
	scanf("%s", MSP);

	while (1)
	{
		if ((strcmp(MSP, "M") != 0) && (strcmp(MSP, "S") != 0) && (strcmp(MSP, "P") != 0))
		{
			printf("잘못 입력했습니다. 다시 입력하세요.");
			scanf("%s", MSP);
		}
		else
			break;
	}

	char BACKUP_S[30];
	itoa(BACKUP, BACKUP_S, 10);

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

	/*
	char ex1[50] = "'M1001', '옥수수', '10', 'M'";
	char ex2[50] = "'M1002', '설탕', '50'";

	if (_insert(ex1) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert(ex2) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	*/

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
	//먼저 수정할 리스트 볼 수 있게 조회하기
	if (initalizing("list") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");

	char search1[10];
	char temp[30] = "CODE='";
	char search2[10], search3[10];
	char temp2[30];
 
	printf("수정할 거래처의 코드(CODE)를 입력 : ");
	scanf("%s", search1);

	strcat(temp, search1);
	strcat(temp, "'");

	char *conditional = temp;

	printf("수정할 컬럼명을 입력 : ");
	scanf("%s", search2);
	printf("새로운 값을 입력 : ");
	scanf("%s", search3);
	strcat(search2, "='");
	strcat(search2, search3);
	strcat(search2, "='");

	char* set = search2;

	if (_update(conditional, set) == -1)
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

void readMaterials()
{
	int menu;

	printf("위치 : 메인메뉴 -> 생산관리 -> 기초정보관리 -> 자재품목 리스트 -> 자재품목 조회\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     메뉴를 선택하세요.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|  1. 자재품목 코드로 조회  |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t| 2. 자재품목 이름으로 조회 |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t| 3. 자재품목 계정으로 조회 |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|   4. 자재품목 전체조회    |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        0. 이전으로        |\n");
	printf("\t\t\t-----------------------------\n\n");
	printf("\t\t\t\t 입력 :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 17);

	scanf("%d", &menu);
	system("cls");
	
	switch (menu)
	{
	case 1:
		read_CODE(NULL);
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
	if (initalizing("list") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");

	char search[10];
	char temp[20] = "CODE='";

	printf("삭제할 자재품목코드를 입력 : ");
	scanf("%s", search);
	strcat(temp, search);
	strcat(temp, search);

	char* conditional = temp;

	if (_delete(conditional) == -1)
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

void read_CODE(char* search)
{
	char temp[20] = "CODE='";

	result* _result;
	int result_count;
	
	char input[20];
	printf("검색할 자재품목 코드를 입력 : ");
	scanf("%s", input);
	strcat(temp, input);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "CODE, NAME, BACKUP, MSP";

	if (initalizing("list") == -1)
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
	printf("\n");
	file_column_free();

	printf("자재품목 리스트로 이동합니다. \n");
	system("pause");
	system("cls");

	product_list();
}

result* read_CODE2(char* search)
{
	char temp[20] = "CODE='";

	result* _result;
	int result_count;

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
	printf("%s", conditional);

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

	file_column_free();
	return _result;
}

void read_NAME()
{
	char search[5];
	char temp[20] = "NAME='";

	result* _result;
	int result_count;

	printf("검색할 자재품목 이름을 입력 : ");
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

	printf("\n");
	file_column_free();

	printf("자재품목 리스트로 이동합니다. \n");
	system("pause");
	system("cls");

	product_list();
}

void read_MSP()
{

	char search[5];
	char temp[20] = "MSP='";

	result* _result;
	int result_count;

	printf("원자재:M, 반제품:S, 완제품:P\n 검색할 자재품목 계정을 입력 : ");
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

	printf("\n");
	file_column_free();

	printf("자재품목 리스트로 이동합니다. \n");
	system("pause");
	system("cls");

	product_list();
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

	printf("자재품목 리스트로 이동합니다. \n");
	//getch();
	system("pause");
	system("cls");

	product_list();
}