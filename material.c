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
	printf("�޴��� �����ϼ���.\n");
	printf("1. ��ǰ�� ��ȸ\n");
	printf("2. ǰ���ڵ�� ��ȸ\n");
	printf("3. create\n");
	printf("0. ��������\n");

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

void code_read(char* condition) {
	char* select_column = "PRD_CODE, STATUS, DATE, ACC_CODE";
	int result_count;
	result* _result;
	char* conditional = condition;

	if (conditional == NULL) {
		char search[5];
		char tmpCondition[30] = "PRD_CODE='";

		getchar();
		printf("�˻��� ǰ���ڵ带 �Է��� �ּ��� : ");
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

void material_create() {
	char values[50];
	char PRD_CODE[5];
	char STATUS[5];
	char DATE[8];
	char ACC_CODE[5];

	printf("����Ϸ��� ������ �ڵ带 �Է��� �ּ��� : ");
	scanf("%s", PRD_CODE);
	printf("����Ϸ��� ������ ���¸� �Է��� �ּ��� : ");
	scanf("%s", STATUS);
	printf("������ �԰����ڸ� �Է��� �ּ��� : ");
	scanf("%s", DATE);
	printf("������ �ŷ�ó�� �Է��� �ּ��� : ");
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

//�����ȹ �Է� �� �޾ƿͼ� ��� Ȯ��
void confirm_Material(plan* p) {
	char* PLAN_PRODUCTION = p->PLAN_PRODUCTION;

	//BOM ��ȸ
	//char* con = "ROOT_CODE = 'A0002'";
	char* con = (char*)malloc(sizeof(char));

	BOM_TREE* res = BOM_SEARCH(p->CODE);
	BOM_Forward_PrintTree(res, p->CODE);

	//���
	printf("ǰ��� : ");
	printf("\t�ʿ�\t\t\t��Ȳ\n\n");
	printf("������ : 3��\t\t\t������ : 1��");
}