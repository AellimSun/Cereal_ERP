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

	printf("��ġ : ���θ޴� -> ������� -> ������ -> ��ǰ�� ��ȸ\n\n");

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
		printf("\t\t\t < ��ȸ�� �����Ͱ� �����ϴ�. > \n");

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
	bomRes* head1 = result;
	bomRes* result2 = (bomRes*)malloc(sizeof(bomRes));
	result2->next = NULL;
	bomRes* head2 = result2;

	//BOM ��ȸ
	//char* con = "ROOT_CODE = 'A0002'";
	char* code = p->CODE;
	BOM_TREE* res = BOM_SEARCH(code);
	//BOM_Forward_PrintTree(res, res->NODE_CODE);

	get_Materials_From_Bom(res, res->NODE_CODE, result);

	/*bomRes* newNode = (bomRes*)malloc(sizeof(bomRes));
	newNode->AMOUNT = 0;
	newNode->CODE = result->next->CODE;
	newNode->next = NULL;
	result2->next = newNode;*/
	result = result->next;
	int flag = 1;
	while (result->next != NULL) {
		result2 = head2;
		while (result2->next != NULL) {
			result2 = result2->next;
			flag = 1;
			if (strcmp(result2->CODE, result->CODE) == 0) {
				result2->AMOUNT += result->AMOUNT;
				flag = 0;
				break;
			}
		}
		if (flag == 1) {
			bomRes* newNode = (bomRes*)malloc(sizeof(bomRes));
			newNode->CODE = result->CODE;
			newNode->AMOUNT = result->AMOUNT;
			newNode->next = result2->next;
			result2->next = newNode;
		}
		result = result->next;
	}

	printf("\t�ʿ�\n");
	bomRes* list = head2;
	while (list->next != NULL) {
		list = list->next;
		int planedAmt = atoi(p->PLAN_PRODUCTION);
		//char* name = (char*)malloc(sizeof(char));
		list->AMOUNT *= planedAmt;
		
		//���� ����ǰ�� ����Ʈ���� �ڵ������ ����� �������

		printf("%s : %d��\n", list->CODE, list->AMOUNT);
	}

	printf("\n\t����\n");
	list = head2;
	while (list->next != NULL) {
		list = list->next;
		int planedAmt = atoi(p->PLAN_PRODUCTION);
		//char* name = (char*)malloc(sizeof(char));
		
		int stock = findStock(list->CODE)*planedAmt;

		//���� ����ǰ�� ����Ʈ���� �ڵ������ ����� �������

		printf("%s : %d��\n", list->CODE, stock);
	}

	system("pause");
	system("cls");

	bomRes* result3 = (bomRes*)malloc(sizeof(bomRes));
	result3->next = NULL;
	printf("���� ������ �׸���\n\n");
	list = head2;
	while (list->next != NULL) {
		list = list->next;
		bomRes* newnode = (bomRes*)malloc(sizeof(bomRes));
		newnode->CODE = list->CODE;
		int planedAmt = atoi(p->PLAN_PRODUCTION);
		int stock = findStock(list->CODE) * planedAmt;			//����
		int need = list->AMOUNT;
		newnode->AMOUNT = need - stock;

		newnode->next = result3->next;
		result3->next = newnode;

		//���� ����ǰ�� ����Ʈ���� �ڵ������ ����� �������

		printf("%s : %d��\n", newnode->CODE, newnode->AMOUNT);
	}

	char input;
	printf("�Դϴ�. �ֹ��Ͻðڽ��ϱ�?(y / n)");
	scanf("%c", &input);

	if (input == 'y') {
		//���ַ� ������.....
	}
	else {
		printf("��Ҹ� �����ϼ̽��ϴ�.\n �۾��� ��� ��ҵǰ� ���� ��ȹ �޴��� ���ư��ϴ�.\n");
		system("pause");
		system("cls");
		production_menu();
	}
	
}

int findStock(char* code) {
	int res = 0;
	char* select_column = "PRD_CODE, STATUS, DATE, ACC_CODE";
	int result_count;
	result* _result;
	char* conditional = (char*)malloc(sizeof(char));
	strcpy(conditional, "PRD_CODE = '");
	strcat(conditional, code);
	strcat(conditional, "'");

	if (initalizing("D:\\visual studio\\Sources\\Repos\\Cereal_ERP\\material") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select(conditional, select_column, &select_result_str) == -1) {
		file_column_free();
		return 0;
	}
	else {
		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			file_column_free();
			result_free(_result, result_count);
			return 0;
		}
		while (_result->next != NULL) {
			if (strcmp(_result->name, "STATUS") == 0) {
				res++;
			}
		}
		result_print(_result, result_count);

		return res;
	}

	file_column_free();
	free(conditional);
	result_free(_result, result_count);
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