#include "cereal.h"

typedef struct Material {
	char PRD_CODE[5];
	char STATUS[5];
	int DATE;
	char ACC_CODE[5];
};

typedef struct _bomRes {
	char* CODE;
	int AMOUNT;
	struct _bomRes* next;
}bomRes;

void stock();
void all_read();
void code_read();
void material_create();
void get_Materials_From_Bom(BOM_TREE* CurNode, Element1* NODE_CODE);
void _get_Materials_From_Bom(BOM_TREE* CurNode, int Depth);

void stock()
{
	int input = 0;
	printf("��ġ : ���θ޴� -> ������� -> ������\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     �޴��� �����ϼ���.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|     1. ��ǰ�� ��ȸ        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|     2. ǰ���ڵ�� ��ȸ    |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|     3. create             |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|     0. ��������           |\n");
	printf("\t\t\t-----------------------------\n\n");


	printf("\t\t\t\t �Է� :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 15);
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
		printf("\n\t\t\t < ��ȸ�� �����Ͱ� �����ϴ�. >\n");

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
	printf("��ġ : ���θ޴� -> ������� -> ������ -> ǰ���ڵ���ȸ\n");
	printf("\n\t\t< �˻��� ǰ���ڵ带 �Է��� �ּ��� :               >");
	gotoxy(52, 2);
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

	printf("��ġ : ���θ޴� -> ������� -> ������ -> create\n\n");

	printf("\t       =============================================\n\n");
	printf("\t\t����Ϸ��� ������ �ڵ带 �Է��� �ּ��� :   \n\n");
	printf("\t       =============================================\n");
	printf("\n\t\t����Ϸ��� ������ ���¸� �Է��� �ּ��� :   \n\n");
	printf("\t       =============================================\n");
	printf("\n\t\t������ �԰����ڸ� �Է��� �ּ��� :   \n\n");
	printf("\t       =============================================\n");
	printf("\n\t\t������ �ŷ�ó�� �Է��� �ּ��� :   \n\n");
	printf("\t       =============================================\n");
	gotoxy(57, 4);
	scanf("%s", PRD_CODE);
	gotoxy(57, 8);
	scanf("%s", STATUS);
	gotoxy(50, 12);
	scanf("%s", DATE);
	gotoxy(48, 16);
	scanf("%s", ACC_CODE);
	printf("\n\n");

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
	bomRes* result = (bomRes*)malloc(sizeof(bomRes));
	result->next = NULL;
	bomRes* result2 = (bomRes*)malloc(sizeof(bomRes));
	result2->next = NULL;

	//BOM ��ȸ
	//char* con = "ROOT_CODE = 'A0002'";
	char* code = p->CODE;
	BOM_TREE* res = BOM_SEARCH(code);
	//BOM_Forward_PrintTree(res, res->NODE_CODE);

	get_Materials_From_Bom(res, res->NODE_CODE, result);

	result = result->next;
	result2 = result2->next;
	while (result->next != NULL) {
		while (result2->next != NULL) {
			if (strcmp(result2->CODE, result->CODE) == 0) {
				result2->AMOUNT += result->AMOUNT;
			}
			result2 = result2->next;
		}
		bomRes* newNode = (bomRes*)malloc(sizeof(bomRes));
		newNode = result;
		result2->next = result;
	}
	//���
	/*printf("ǰ��� : ");
	printf("\t�ʿ�\t\t\t��Ȳ\n\n");
	printf("������ : 3��\t\t\t������ : 1��");*/
}

void get_Materials_From_Bom(BOM_TREE* CurNode, Element1* NODE_CODE, bomRes* result) {
	if (strcmp(CurNode->NODE_CODE, NODE_CODE) == 0)
	{
		_get_Materials_From_Bom(CurNode, 0, result);
		return;
	}

	if (CurNode->LeftChild != NULL)
		get_Materials_From_Bom(CurNode->LeftChild, NODE_CODE, result);
	if (CurNode->RightSibling != NULL)
		get_Materials_From_Bom(CurNode->RightSibling, NODE_CODE, result);
}

void _get_Materials_From_Bom(BOM_TREE* CurNode, int Depth, bomRes* result)
{
	//int i = 0; // �鿩����� Ʈ���� Depth ǥ�� 
	//for (i = 0; i < Depth; i++)
	//   printf("   ");

	printf("%4d\t%8s\t%5d\n", Depth, CurNode->NODE_CODE, CurNode->REQ_NUM);

	if (CurNode->LeftChild != NULL) // ���ϵ� �����
		_get_Materials_From_Bom(CurNode->LeftChild, Depth + 1, result); // ��� ȣ�� - Node�� Child�� ���̴� Node�� Depth�� +1 �� ���� ����
	
	if (CurNode->LeftChild == NULL) {
		bomRes* newNode = (bomRes*)malloc(sizeof(bomRes));
		newNode->CODE = CurNode->NODE_CODE;
		newNode->AMOUNT = CurNode->REQ_NUM;
		newNode->next = result->next;
		result->next = newNode;
	}
	if (CurNode->RightSibling != NULL) // ���� �����
		_get_Materials_From_Bom(CurNode->RightSibling, Depth, result); // ��� ȣ�� - ���� ����� ���̴� ��� ����(���� ������ ���
}