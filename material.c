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

void stock()
{
	int input = 0;
	printf("�޴��� �����ϼ���.\n");
	printf("1. ��ǰ�� ��ȸ\n");
	printf("2. ǰ���ڵ�� ��ȸ\n");
	printf("0. ��������\n");

	scanf("%d", &input);
	system("cls");
	switch (input)
	{
	case 1:
		all_read();
		break;

	case 2:
		code_read();
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

	//_create("material", "PRD_CODE VARCHAR(6) STATUS VARCHAR(6) DATE INT ACC_CODE VARCHAR(6)");

	if (initalizing("material") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	/*if (_insert(values) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}*/

	if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("��ȸ�� �����Ͱ� �����ϴ�.\n");

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

void code_read() {
	char search[5];
	char tmpCondition[30] = "PRD_CODE='";

	getchar();
	printf("�˻��� ǰ���ڵ带 �Է��� �ּ��� : ");
	scanf("%s", search);

	strcat(tmpCondition, search);
	strcat(tmpCondition, "'");

	char* conditional = tmpCondition;
	char* select_column = "PRD_CODE, STATUS, DATE, ACC_CODE";
	int result_count;
	result* _result;

	if (initalizing("D:\\visual studio\\Sources\\Repos\\Cereal_ERP\\material") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("��ȸ�� �����Ͱ� �����ϴ�.\n");

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