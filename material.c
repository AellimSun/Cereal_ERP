#include <time.h>
#include "cereal.h"

void stock();
void all_read();
void code_read();
void material_create();
void get_Materials_From_Bom(BOM_TREE* CurNode, Element1* NODE_CODE);
void _get_Materials_From_Bom(BOM_TREE* CurNode, int Depth);
void freeNodes(bomRes* obj);

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

//��� ��� ��ȸ
void all_read() {
	char* conditional = "*";
	char* select_column = "PRD_CODE, STATUS, DATE, ACC_CODE, LOT";
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
		file_column_free();
		result_print(_result, result_count);
		printf("\n\n");
	}

	result_free(_result, result_count);

	system("pause");
	system("cls");
	stock();
}

//�ڵ��ȣ�� �˻��Ͽ� ��ȸ
void code_read(char* condition) {
	char* select_column = "PRD_CODE, STATUS, DATE, ACC_CODE, LOT";
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

	if (initalizing("material") == -1) {
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
	char LOT[5];

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

	//LOT��ȣ �����
	int random = 0;
	char tmpRand[4];
	srand(time(NULL));
	random = (rand() % 10000);
	strcpy(LOT, "L");
	strcat(LOT, itoa(random, tmpRand, 10));

	strcpy(values, "'");
	strcat(values, PRD_CODE);
	strcat(values, "', '");
	strcat(values, STATUS);
	strcat(values, "', ");
	strcat(values, DATE);
	strcat(values, ", '");
	strcat(values, ACC_CODE);
	strcat(values, "', '");
	strcat(values, LOT);
	strcat(values, "'");
	printf("\n");

	//_create("material", "PRD_CODE VARCHAR(6) STATUS VARCHAR(6) DATE INT ACC_CODE VARCHAR(6) LOT VARCHAR(6)");

	if (initalizing("material") == -1) {
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
	//bom Ʈ���� �����ϱ� ���� ������ ����Ʈ
	bomRes* result = (bomRes*)malloc(sizeof(bomRes));
	result->next = NULL;
	bomRes* head1 = result;			//���� ���ƿ��� �Ҽ��ֵ��� ��� ��ġ ����

	//�����(�ܸ����)�� ������ ����Ʈ
	bomRes* result2 = (bomRes*)malloc(sizeof(bomRes));
	result2->next = NULL;
	bomRes* head2 = result2;		//���� ���ƿ��� �Ҽ��ֵ��� ��� ��ġ ����

	//BOM ��ȸ
	BOM_TREE* res = BOM_SEARCH(p->CODE);

	//��������� ��� ��� �f� result����Ʈ�� ���
	get_Materials_From_Bom(res, res->NODE_CODE, result);

	//�����(�ܸ����)�� ���� ����Ʈ �����
	result = result->next;
	int flag = 1;
	while (result->next != NULL) {
		//����� ����Ʈ�� ������ ����� �ٽ� �ű��
		result2 = head2;
		while (result2->next != NULL) {
			result2 = result2->next;
			//while���� �� ������ ���� ǰ���� ã�� ���ϸ�(flag�� 0���� ������ ������)
			//����� ����Ʈ�� �׸� �߰��Ҽ� �ֵ��� flag �����
			flag = 1;
			//����� ����Ʈ�� �̹� �ִ� ǰ���̸� ����Ʈ�� ���� �߰����� �ʰ� ������ ���ڸ� ������
			if (strcmp(result2->CODE, result->CODE) == 0) {
				result2->AMOUNT += result->AMOUNT;
				flag = 0;
				break;
			}
		}
		//while���� �� ������ ���� ǰ���� ã�� ���ϸ�(flag�� 0���� ������ ������)
		//����� ����Ʈ�� �׸� �߰�
		if (flag == 1) {
			bomRes* newNode = (bomRes*)malloc(sizeof(bomRes));
			newNode->CODE = result->CODE;
			newNode->AMOUNT = result->AMOUNT;
			newNode->next = result2->next;
			result2->next = newNode;
		}
		result = result->next;
	}
	//Ʈ���� �״�� ��ƿ� ����Ʈ�� ���� �ʿ�����Ƿ� free
	freeNodes(head1);

	//�����ȹ�� ������ ���߷��� �ʿ��� ����� ���� ���
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

	//���� �������ִ� ����� ���� ���
	printf("\n\t����\n");
	list = head2;
	while (list->next != NULL) {
		list = list->next;
		int stock = findStock(list->CODE);

		//���� ����ǰ�� ����Ʈ���� �ڵ������ ����� �������

		printf("%s : %d��\n", list->CODE, stock);
	}

	system("pause");
	system("cls");

	//������ - ������ = ������ �׸� ���
	bomRes* result3 = (bomRes*)malloc(sizeof(bomRes));
	result3->next = NULL;
	printf("���� ������ �׸���\n\n");
	list = head2;
	while (list->next != NULL) {
		list = list->next;
		bomRes* newnode = (bomRes*)malloc(sizeof(bomRes));
		newnode->CODE = list->CODE;
		int planedAmt = atoi(p->PLAN_PRODUCTION);
		//findStock(ǰ���)���� ��� ���� ����� ����
		int stock = findStock(list->CODE);			//����
		int need = list->AMOUNT;
		newnode->AMOUNT = need - stock;

		newnode->next = result3->next;
		result3->next = newnode;

		//���� ����ǰ�� ����Ʈ���� �ڵ������ ����� �������

		printf("%s : %d��\n", newnode->CODE, newnode->AMOUNT);
	}

	//freeNodes(result2);

	char input;
	printf("�Դϴ�. �ֹ��Ͻðڽ��ϱ�?(y / n) : ");
	scanf("%c", &input);

	if (input == 'y') {
		char values[50];
		char PRD_CODE[5];
		char STATUS = "store";
		char DATE[8];
		char ACC_CODE[5];
		char LOT[5];

		struct tm* t;
		time_t timer;

		timer = time(NULL);    // ���� �ð��� �� ������ ���
		t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�

		//DATE�� ���ó�¥ ����ֱ�(20001010����)
		sprintf(DATE, "%04d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

		//���ַ� ������
		Request_Order(result3);

		if (initalizing("material") == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		//������ ǰ�� ���翡 insert
		list = result3;
		while (list->next != NULL) {
			list = list->next;
			for (int i = 0; i < list->AMOUNT; i++) {
				strcpy(PRD_CODE, list->CODE);
				strcpy(ACC_CODE, list->ACC_CODE);

				//LOT��ȣ �����
				int random = 0;
				char tmpRand[4];
				srand(time(NULL));
				random = (rand() % 10000);
				strcpy(LOT, "L");
				strcat(LOT, itoa(random, tmpRand, 10));

				strcpy(values, "'");
				strcat(values, PRD_CODE);
				strcat(values, "', '");
				strcat(values, STATUS);
				strcat(values, "', ");
				strcat(values, DATE);
				strcat(values, ", '");
				strcat(values, ACC_CODE);
				strcat(values, "', '");
				strcat(values, LOT);
				strcat(values, "'");

				if (_insert(values) == -1) {
					printf("%s\n", err_msg);

					file_column_free();
					return -1;
				}
			}
		}

		file_column_free();
		//freeNodes(result3);

		//�������� ������
	}
	else {
		printf("\n��Ҹ� �����ϼ̽��ϴ�.\n�۾��� ��� ��ҵǰ� ���� ��ȹ �޴��� ���ư��ϴ�.\n");
		system("pause");
		system("cls");
		production_menu();
	}
	
}

//�ش� �ڵ��� ��� ����� ��� ����
int findStock(char* code) {
	int res = 0;
	char* select_column = "PRD_CODE, STATUS, DATE, ACC_CODE";
	int result_count;
	result* _result;
	char conditional[50];
	strcpy(conditional, "PRD_CODE = '");
	strcat(conditional, code);
	strcat(conditional, "'");

	if (initalizing("material") == -1) {
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
		//��� ����ϴ� �κ�
		while (_result->next != NULL) {
			//���� ����� �÷����� STATUS�� ���
			if (strcmp(_result->name, "STATUS") == 0) {
				//STATUS�÷��� �����ϴ� �����Ͱ� store(�������)�� ���
				if (strcmp(*(_result->_string_data), "store") == 0) {
					//��� +1
					res++;
					break;
				}
			}
			_result = _result->next;
		}

		file_column_free();
		result_free(_result, result_count);
		return res;
	}

	file_column_free();
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

void freeNodes(bomRes* obj) {
	while (obj->next != NULL) {
		obj = obj->next;
		bomRes* tmp = obj;
		obj = obj->next;
		free(tmp);
	}
}