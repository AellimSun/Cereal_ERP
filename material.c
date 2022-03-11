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
	printf("위치 : 메인메뉴 -> 자재관리 -> 재고관리\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     메뉴를 선택하세요.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|     1. 전품목 조회        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|     2. 품목코드로 조회    |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|     3. create             |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|     0. 이전으로           |\n");
	printf("\t\t\t-----------------------------\n\n");


	printf("\t\t\t\t 입력 :\n");
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

	printf("위치 : 메인메뉴 -> 자재관리 -> 재고관리 -> 전품목 조회\n\n");

	if (initalizing("material") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("\n\t\t\t < 조회할 데이터가 없습니다. >\n");

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
	printf("위치 : 메인메뉴 -> 자재관리 -> 재고관리 -> 품목코드조회\n");
	printf("\n\t\t< 검색할 품목코드를 입력해 주세요 :               >");
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
		printf("\t\t\t < 조회할 데이터가 없습니다. > \n");

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

	printf("위치 : 메인메뉴 -> 자재관리 -> 재고관리 -> create\n\n");

	printf("\t       =============================================\n\n");
	printf("\t\t등록하려는 자재의 코드를 입력해 주세요 :   \n\n");
	printf("\t       =============================================\n");
	printf("\n\t\t등록하려는 자재의 상태를 입력해 주세요 :   \n\n");
	printf("\t       =============================================\n");
	printf("\n\t\t자재의 입고일자를 입력해 주세요 :   \n\n");
	printf("\t       =============================================\n");
	printf("\n\t\t자재의 거래처를 입력해 주세요 :   \n\n");
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

//생산계획 입력 후 받아와서 재고 확인
void confirm_Material(plan* p) {
	char* PLAN_PRODUCTION = p->PLAN_PRODUCTION;
	bomRes* result = (bomRes*)malloc(sizeof(bomRes));
	result->next = NULL;
	bomRes* head1 = result;
	bomRes* result2 = (bomRes*)malloc(sizeof(bomRes));
	result2->next = NULL;
	bomRes* head2 = result2;

	//BOM 조회
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

	printf("\t필요\n");
	bomRes* list = head2;
	while (list->next != NULL) {
		list = list->next;
		int planedAmt = atoi(p->PLAN_PRODUCTION);
		//char* name = (char*)malloc(sizeof(char));
		list->AMOUNT *= planedAmt;
		
		//추후 자재품목 리스트에서 코드명으로 자재명 끌어오기

		printf("%s : %d개\n", list->CODE, list->AMOUNT);
	}

	printf("\n\t현재\n");
	list = head2;
	while (list->next != NULL) {
		list = list->next;
		int planedAmt = atoi(p->PLAN_PRODUCTION);
		//char* name = (char*)malloc(sizeof(char));
		
		int stock = findStock(list->CODE)*planedAmt;

		//추후 자재품목 리스트에서 코드명으로 자재명 끌어오기

		printf("%s : %d개\n", list->CODE, stock);
	}

	system("pause");
	system("cls");

	bomRes* result3 = (bomRes*)malloc(sizeof(bomRes));
	result3->next = NULL;
	printf("현재 부족한 항목은\n\n");
	list = head2;
	while (list->next != NULL) {
		list = list->next;
		bomRes* newnode = (bomRes*)malloc(sizeof(bomRes));
		newnode->CODE = list->CODE;
		int planedAmt = atoi(p->PLAN_PRODUCTION);
		int stock = findStock(list->CODE) * planedAmt;			//현재
		int need = list->AMOUNT;
		newnode->AMOUNT = need - stock;

		newnode->next = result3->next;
		result3->next = newnode;

		//추후 자재품목 리스트에서 코드명으로 자재명 끌어오기

		printf("%s : %d개\n", newnode->CODE, newnode->AMOUNT);
	}

	char input;
	printf("입니다. 주문하시겠습니까?(y / n)");
	scanf("%c", &input);

	if (input == 'y') {
		//발주로 보내기.....
	}
	else {
		printf("취소를 선택하셨습니다.\n 작업이 모두 취소되고 생산 계획 메뉴로 돌아갑니다.\n");
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
	//int i = 0; // 들여쓰기로 트리의 Depth 표현 
	//for (i = 0; i < Depth; i++)
	//   printf("   ");

	printf("%4d\t%8s\t%5d\n", Depth, CurNode->NODE_CODE, CurNode->REQ_NUM);

	if (CurNode->LeftChild != NULL) // 차일드 존재시
		_get_Materials_From_Bom(CurNode->LeftChild, Depth + 1, result); // 재귀 호출 - Node의 Child의 깊이는 Node의 Depth에 +1 한 값과 같음
	
	if (CurNode->LeftChild == NULL) {
		bomRes* newNode = (bomRes*)malloc(sizeof(bomRes));
		newNode->CODE = CurNode->NODE_CODE;
		newNode->AMOUNT = CurNode->REQ_NUM;
		newNode->next = result->next;
		result->next = newNode;
	}
	if (CurNode->RightSibling != NULL) // 형제 존재시
		_get_Materials_From_Bom(CurNode->RightSibling, Depth, result); // 재귀 호출 - 형제 노드의 깊이는 모두 같음(같은 레벨의 노드
}