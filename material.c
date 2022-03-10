#include "cereal.h"

typedef struct Material {
	char PRD_CODE[5];
	char STATUS[5];
	int DATE;
	char ACC_CODE[5];
};

void stock();
void all_read();
void code_read();
void material_create();

void stock()
{
	int input = 0;
	printf("메뉴를 선택하세요.\n");
	printf("1. 전품목 조회\n");
	printf("2. 품목코드로 조회\n");
	printf("3. create\n");
	printf("0. 이전으로\n");

	scanf("%d", &input);
	system("cls");
	switch (input)
	{
	case 1:
		all_read();
		break;

	case 2:
		code_read(NULL);
		break;

	case 3:
		material_create();
		break;

	case 0:
		material_management();
		break;
	}
}

void all_read() {
	char* conditional = "*";
	char* select_column = "PRD_CODE, STATUS, DATE, ACC_CODE";
	//char* values = "'B4001', 'store', 20220308, 'D0004'";
	int result_count;
	result* _result;

	if (initalizing("material") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("조회할 데이터가 없습니다.\n");

		file_column_free();
		system("pause");
		system("cls");
		stock();
	}
	else {
		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		result_print(_result, result_count);
		printf("\n\n");
	}

	file_column_free();
	result_free(_result, result_count);

	system("pause");
	system("cls");
	stock();
}

void code_read(char* condition) {
	char* select_column = "PRD_CODE, STATUS, DATE, ACC_CODE";
	int result_count;
	result* _result;
	char* conditional = condition;

	if (conditional == NULL) {
		char search[5];
		char tmpCondition[30] = "PRD_CODE='";

		getchar();
		printf("검색할 품목코드를 입력해 주세요 : ");
		scanf("%s", search);

		strcat(tmpCondition, search);
		strcat(tmpCondition, "'");

		conditional = tmpCondition;
	}

	if (initalizing("D:\\visual studio\\Sources\\Repos\\Cereal_ERP\\material") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("조회할 데이터가 없습니다.\n");

		file_column_free();
		system("pause");
		system("cls");
		stock();
	}
	else {
		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		result_print(_result, result_count);
		printf("\n\n");
	}

	file_column_free();
	result_free(_result, result_count);

	system("pause");
	system("cls");
	stock();
}

void material_create() {
	char values[50];
	char PRD_CODE[5];
	char STATUS[5];
	char DATE[8];
	char ACC_CODE[5];

	printf("등록하려는 자재의 코드를 입력해 주세요 : ");
	scanf("%s", PRD_CODE);
	printf("등록하려는 자재의 상태를 입력해 주세요 : ");
	scanf("%s", STATUS);
	printf("자재의 입고일자를 입력해 주세요 : ");
	scanf("%s", DATE);
	printf("자재의 거래처를 입력해 주세요 : ");
	scanf("%s", ACC_CODE);

	strcpy(values, "'");
	strcat(values, PRD_CODE);
	strcat(values, "', '");
	strcat(values, STATUS);
	strcat(values, "', ");
	strcat(values, DATE);
	strcat(values, ", '");
	strcat(values, ACC_CODE);
	strcat(values, "'");
	printf("\n");
	printf("%s", values);
	printf("\n");

	//_create("material", "PRD_CODE VARCHAR(6) STATUS VARCHAR(6) DATE INT ACC_CODE VARCHAR(6)");

	if (initalizing("D:\\visual studio\\Sources\\Repos\\Cereal_ERP\\material") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert(values) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();

	system("pause");
	system("cls");
	stock();
}

//생산계획 입력 후 받아와서 재고 확인
void confirm_Material(plan* p) {
	char* PLAN_PRODUCTION = p->PLAN_PRODUCTION;

	//BOM 조회
	//char* con = "ROOT_CODE = 'A0002'";
	char* con = (char*)malloc(sizeof(char));

	BOM_TREE* res = BOM_SEARCH(p->CODE);
	BOM_Forward_PrintTree(res, p->CODE);

	//출력
	printf("품목명 : ");
	printf("\t필요\t\t\t현황\n\n");
	printf("옥수수 : 3개\t\t\t옥수수 : 1개");
}