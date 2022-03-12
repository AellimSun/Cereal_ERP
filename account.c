#include "local.h"
#include "cereal.h"



void insertAccount();
void readAccount();
void read_all();
void read_ACC_CODE();
void read_BN_REGI_NUM();
void read_PRD_CODE();
void read_RorD();
void deleteAccount();
void updateAccount();
void read_prd(char* code);
//거래처 관리 초기화면
void account()
{
	int menu;
	printf("위치 : 메인메뉴 -> 자재관리 -> 거래처관리\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     메뉴를 선택하세요.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      1. 거래처 등록       |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      2. 거래처 수정       |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      3. 거래처 조회       |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      4. 거래처 삭제       |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      0. 메인으로          |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t 입력 :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 17);
	scanf("%d", &menu);

	system("cls");

	switch (menu)
	{
	case 1:
		insertAccount();
		break;
	case 2:
		updateAccount();
		break;
	case 3:
		readAccount();
		break;
	case 4:
		deleteAccount();
		break;
	case 0:
		main_manu();
		break;
	}
}

void insertAccount()
{
	char values[50];
	char ACC_CODE[5];		//거래처 코드
	char BN_REGI_NUM[20];	//사업자 등록 번호
	char PRD_CODE[5];			//취급 품목 코드
	char RorD[2];			//R:원자재 D:납품

	printf("위치 : 메인메뉴 -> 자재관리 -> 거래처관리 -> 거래처 등록\n\n");
	printf("\t\t\t==========================\n");
	printf("\t\t\t새로운 거래처를 등록합니다.\n");
	printf("\t\t\t==========================\n\n");

	printf("\t\t거래처 코드를 입력하세요. \n");
	printf("\n\t\t\t-> \n");
	printf("\n\t\t거래처의 사업자 등록 번호를 입력하세요. \n");
	printf("\n\t\t\t-> \n");
	printf("\n\t\t취급 품목 코드를 입력하세요. \n");
	printf("\n\t\t\t-> \n");
	printf("\n\t\t원자재 거래처는 'R' 납품 거래처는 'D'를 입력하세요. \n");
	printf("\n\t\t\t-> \n");
	gotoxy(27,8);
	scanf("%s", ACC_CODE);
	gotoxy(27, 12);
	scanf("%s", BN_REGI_NUM);
	gotoxy(27, 16);
	scanf("%s", PRD_CODE);
	gotoxy(27, 20);
	scanf("%s", RorD);
	//printf("%s", RorD);
	//char temp = ("R\n" || "D\n");

	read_prd(PRD_CODE);

	system("cls");
	while(1)
	{
		if ((strcmp(RorD, "R") != 0) && (strcmp(RorD, "D") != 0))
		{
			printf("\n\t\t\t< 잘못 입력했습니다! >\n");
			printf("\t  < 원자재 취급 거래처는 'R' 납품 취급 거래처는 'D를 입력해주세요! >\n\n");
			printf("\t\t\t 'R' 혹은 'D' 입력 :  ");
			scanf("%s", RorD);
			system("cls");
		}
		else
			break;
	}
	
		printf("\n\n");
		strcpy(values, "'");
		strcat(values, ACC_CODE);
		strcat(values, "', '");
		strcat(values, BN_REGI_NUM);
		strcat(values, "', '");
		strcat(values, PRD_CODE);
		strcat(values, "', '");
		strcat(values, RorD);
		strcat(values, "'");

		printf("%s\n\n", values);

		/*if (_create("account", "ACC_CODE VARCHAR(10) BN_REGI_NUM VARCHAR(30) PRD_CODE VARCHAR(10) RorD VARCHAR(2)") == -1)
		{
			printf("%s\n", err_msg);

			return -1;
		}*/
		if (initalizing("account") == -1)
		{
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		char ex1[50] = "'A1001', '18-854-1123', 'D0001', 'R'";
		char ex2[50] = "'A1002', '20-774-4556', 'D0002', 'R'";
		char ex3[50] = "'A1003', '21-814-9563', 'D0003', 'R'";

		/*if (_insert(ex1) == -1)
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
		if (_insert(ex3) == -1)
		{
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}*/
		if (_insert(values) == -1)
		{
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		print_data();
		printf("\n");
		file_column_free();

		printf("\n\t\t < 새로운 거래처 등록완료! 메인으로 이동합니다. >");
		system("pause");
		system("cls");
		account();
}

void readAccount()
{
	int menu;
	printf("위치 : 메인메뉴 -> 자재관리 -> 거래처관리 -> 거래처 조회\n\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     메뉴를 선택하세요.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|   1. 거래처 코드로 조회   |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t| 2. 사업자 등록 번호로 조회|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|    3. 품목 코드로 조회    |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|   4. 거래처 구분별 조회   |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|       5. 전체 조회        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|       0. 이전으로         |\n");
	printf("\t\t\t-----------------------------\n");
	//printf("7.test\n");
	printf("\t\t\t\t 입력 :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 19);
	scanf("%d", &menu);
	system("cls");
	switch (menu)
	{
	case 1:
		read_ACC_CODE();
		break;
	case 2:
		read_BN_REGI_NUM();
		break;
	case 3:
		read_PRD_CODE();
		break;
	case 4:
		read_RorD();
		break;
	case 5:
		read_all();
		break;
	case 0:
		account();
		break;
	case 7:
		//read_prd();
		break;
	}
}

void read_all()
{
	printf("위치 : 메인메뉴 -> 자재관리 -> 거래처관리 -> 거래처 조회 -> 전체 조회\n\n");
	if (initalizing("account") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void read_ACC_CODE()
{
	char naver[10];
	char temp[30] = "ACC_CODE='";

	result* _result;
	int result_count;


	printf("위치 : 메인메뉴 -> 자재관리 -> 거래처관리 -> 거래처 조회 -> 코드로 조회\n\n");
	printf("\t\t검색할 거래처의 코드를 입력하세요 \n");
	printf("\t\t\t -> ");
	scanf("%s", naver);

	strcat(temp, naver);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "ACC_CODE, BN_REGI_NUM, PRD_CODE";

	if (initalizing("account") == -1)
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
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");

	//print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void read_BN_REGI_NUM()
{
	char naver[10];
	char temp[20] = "BN_REGI_NUM='";

	result* _result;
	int result_count;

	printf("위치 : 메인메뉴 -> 자재관리 -> 거래처관리 -> 거래처 조회 -> 사업자 번호로 조회\n\n");
	printf("\t\t검색할 거래처의 사업자 번호를 입력하세요 : \n");
	printf("\t\t\t -> ");
	scanf("%s", naver);

	strcat(temp, naver);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "ACC_CODE, BN_REGI_NUM, PRD_CODE";

	if (initalizing("account") == -1)
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

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");

	//print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void read_PRD_CODE()
{
	char naver[10];
	char temp[20] = "PRD_CODE='";

	result* _result;
	int result_count;
	printf("위치 : 메인메뉴 -> 자재관리 -> 거래처관리 -> 거래처 조회 -> 품목 코드로 조회\n\n");
	printf("\t\t검색할 품목의 코드를 입력하세요 : \n");
	printf("\t\t\t -> ");
	scanf("%s", naver);

	strcat(temp, naver);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "ACC_CODE, BN_REGI_NUM, PRD_CODE";

	if (initalizing("account") == -1)
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

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");

	//print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void read_RorD()
{
	char naver[5];
	char temp[20] = "RorD='";

	result* _result;
	int result_count;
	printf("위치 : 메인메뉴 -> 자재관리 -> 거래처관리 -> 거래처 조회 -> 사업자 번호로 조회\n\n");
	printf("\t\t검색할 거래처의 유형을 입력하세요 : \n");
	printf("\t\t< 원자재 'R' 납품 'D' >");
	printf("\t\t\t -> ");
	scanf("%s", naver);

	strcat(temp, naver);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "ACC_CODE, BN_REGI_NUM, PRD_CODE";

	if (initalizing("account") == -1)
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

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");

	//print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void deleteAccount()
{
	if (initalizing("account") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	//file_column_free();

	char naver[20];
	char temp[30] = "BN_REGI_NUM='";
	printf("위치 : 메인메뉴 -> 자재관리 -> 거래처관리 -> 거래처 삭제\n\n");
	printf("\t\t삭제할 거래처의 사업자 번호를 입력하세요 : \n");
	printf("\t\t -> ");
	scanf("%s", naver);
	strcat(temp, naver);
	strcat(temp, "'");

	char* conditional = temp;
	//_delete(conditional);

	if (_delete(conditional) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void updateAccount()
{
	printf("\n");
	printf(" < 거래처 목록 >\n");
	printf("========================================================\n");

	//수정할 거래처 볼 수 있게 조회해주기
	if (initalizing("account") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	print_data();
	printf("\n");

	char naver1[10];
	char temp[30] = "ACC_CODE='";
	char naver2[20], naver3[10];
	char temp2[30];

	//char new_ACC_CODE[5];		//거래처 코드
	//char new_BN_REGI_NUM[20];	//사업자 등록 번호
	//char new_PRD_CODE[5];			//취급 품목 코드
	//char new_RorD[2];			//R:원자재 D:납품

	//result* _result;
	//int result_count;

	printf("========================================================\n\n");
	printf("\t\t수정할 거래처의 코드를 입력하세요 : ");
	scanf("%s", naver1);

	strcat(temp, naver1);
	strcat(temp, "'");

	char* conditional = temp;

	printf("\t\t수정할 컬럼명을 입력하세요 : ");
	scanf("%s", naver2);
	printf("\t\t새로운 값을 입력하세요 : ");
	scanf("%s", naver3);
	strcat(naver2, "='");
	strcat(naver2, naver3);
	strcat(naver2, "'");
	char* set = naver2;

	if (_update(conditional, set) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();
	
	account();
}

void read_prd(char *code)
{
	if (initalizing("list") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	char PRD_CODE[5];
	bomRes* list = (bomRes*)malloc(sizeof(bomRes));
	bomRes* head = (bomRes*)malloc(sizeof(bomRes));

	int result_count;
	result* _result;
	char* select_column = "CODE";
	char conditional[20] = "CODE='";
	strcat(conditional, code);
	strcat(conditional, "'");

	if (_select(conditional, select_column, &select_result_str) == -1) {
		file_column_free();
		system("cls");
		printf("존재하는 않는 품목코드입니다.\n");
		system("pause");
		system("cls");
		insertAccount();
	}
	else {
		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			file_column_free();
			result_free(_result, result_count);
			printf("존재하는 않는 품목코드입니다.\n");
			insertAccount();
		}
		
	}

	file_column_free();
	result_free(_result, result_count);

	for (int i = 0; i < list->AMOUNT; i++) {

		if (initalizing("account") == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		strcpy(PRD_CODE, list->CODE);

		printf("%s\n", list->CODE);

		printf("\n");
		file_column_free();

	}

	free(list);
	free(head);
}