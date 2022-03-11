#include "local.h"

typedef struct Accontnode {
	char ACC_CODE[10];
	char BN_REGI_NUM[10];
	char PRD_CODE[30];
	char RorD[5];
	struct Accountnode* next;
}Anode;

void insertAccount();
void readAccount();
void read_all();
void read_ACC_CODE();
void read_BN_REGI_NUM();
void read_PRD_CODE();
void read_RorD();
void deleteAccount();
void updateAccount();

void account()
{
	int menu;
	printf("1.거래처 등록\n");
	printf("2.거래처 수정\n");
	printf("3.거래처 조회\n");
	printf("4.거래처 삭제\n");
	printf("0.메인으로");
	printf("\n\n");
	scanf("%d", &menu);



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
		main();
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

	printf("==========================\n");
	printf("새로운 거래처를 등록합니다.\n");
	printf("==========================\n");

	printf("거래처 코드를 입력하세요 : ");
	scanf("%s", ACC_CODE);
	printf("거래처의 사업자 등록 번호를 입력하세요 : ");
	scanf("%s", BN_REGI_NUM);
	printf("취급 품목 코드를 입력하세요 : ");
	scanf("%s", PRD_CODE);
	printf("원자재 거래처는 'R' 납품 거래처는 'D'를 입력하세요 : ");
	scanf("%s", RorD);
	//printf("%s", RorD);
	//char temp = ("R\n" || "D\n");
	while (1)
	{
		if ((strcmp(RorD, "R") != 0) && (strcmp(RorD, "D") != 0))
		{
			printf("잘못 입력했습니다. 다시 입력하세요		");
			scanf("%s", RorD);
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

	char ex1[50] = "'A1001', '18-854-1123', 'C201', 'R'";
	char ex2[50] = "'A1002', '20-774-4556', 'C202', 'R'";
	char ex3[50] = "'A1003', '21-814-9563', 'D201', 'D'";

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

	printf("새로운 거래처 등록완료. 메인으로 이동합니다.");
	system("pause");
	system("cls");
	account();
}

void readAccount()
{
	int menu;

	printf("1. 거래처 코드로 조회\n");
	printf("2. 사업자 등록 번호로 조회\n");
	printf("3. 품목 코드로 조회\n");
	printf("4. 거래처 구분별 조회\n");
	printf("5. 전체 조회\n");
	printf("0. 이전으로\n");
	scanf("%d", &menu);
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
	case 6:
		account();
		break;
	}
}

void read_all()
{
	if (initalizing("account") == -1)
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

void read_ACC_CODE()
{
	char naver[10];
	char temp[30] = "ACC_CODE='";

	result* _result;
	int result_count;

	printf("검색할 거래처의 코드를 입력하세요 : ");
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

	account();
}

void read_BN_REGI_NUM()
{
	char naver[10];
	char temp[20] = "BN_REGI_NUM='";

	result* _result;
	int result_count;

	printf("검색할 거래처의 사업자 번호를 입력하세요 : ");
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

	account();
}

void read_PRD_CODE()
{
	char naver[10];
	char temp[20] = "PRD_CODE='";

	result* _result;
	int result_count;

	printf("검색할 품목의 코드를 입력하세요 : ");
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

	account();
}

void read_RorD()
{
	char naver[5];
	char temp[20] = "RorD='";

	result* _result;
	int result_count;

	printf("검색할 거래처의 유형을 입력하세요 : \n");
	printf("원자재 'R' 납품 'D'");
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

	printf("삭제할 거래처의 사업자 번호(BN_REGI_NUM)를 입력하세요 : ");
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

	account();
}

void updateAccount()
{
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

	printf("수정할 거래처의 코드(ACC_CODE)를 입력하세요 : ");
	scanf("%s", naver1);

	strcat(temp, naver1);
	strcat(temp, "'");

	char* conditional = temp;

	printf("수정할 컬럼명을 입력하세요 : ");
	scanf("%s", naver2);
	printf("새로운 값을 입력하세요 : ");
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