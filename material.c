#include <time.h>
#include "cereal.h"

void stock();
void all_read();
void code_read();
void material_create();
void get_Materials_From_Bom(BOM_TREE* CurNode, Element1* NODE_CODE);
void _get_Materials_From_Bom(BOM_TREE* CurNode, int Depth);
void freeNodes(bomRes* obj);
void _findMotherAmts(result* _result, int result_count, char* child, int res, char* root);

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
//	printf("\t\t\t|     3. create             |\n");
//	printf("\t\t\t-----------------------------\n");
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

	//case 3:
	//	material_create();
	//	break;

	case 0:
		material_management();
		break;
	}


}

//모든 재고 조회
void all_read() {
	char* conditional = "*";
	char* select_column = "PRD_CODE, PRD_NAME, STATUS, DATE, LOT";
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
		file_column_free();
		result_print(_result, result_count);
		printf("\n\n");
	}

	result_free(_result, result_count);

	system("pause");
	system("cls");
	stock();
}

//코드번호로 검색하여 조회
void code_read(char* condition) {
	char* select_column = "PRD_CODE, PRD_NAME, STATUS, DATE, LOT";
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

	if (initalizing("material") == -1) {
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
	char PRD_CODE[6];
	char PRD_NAME[20];
	char STATUS[5];
	char DATE[8];
	char LOT[5];

	printf("위치 : 메인메뉴 -> 자재관리 -> 재고관리 -> create\n\n");

	printf("\t       =============================================\n\n");
	printf("\t\t등록하려는 자재의 코드를 입력해 주세요 :   \n\n");
	printf("\t       =============================================\n");
	printf("\n\t\t등록하려는 자재의 상태를 입력해 주세요 :   \n\n");
	printf("\t       =============================================\n");
	printf("\n\t\t자재의 입고일자를 입력해 주세요 :   \n\n");
	printf("\t       =============================================\n");
	//printf("\n\t\t자재의 거래처를 입력해 주세요 :   \n\n");
	//printf("\t       =============================================\n");
	gotoxy(57, 4);
	scanf("%s", PRD_CODE);
	gotoxy(57, 8);
	scanf("%s", STATUS);
	gotoxy(50, 12);
	scanf("%s", DATE);
	gotoxy(48, 16);
	//scanf("%s", ACC_CODE);
	printf("\n\n");

	//LOT번호 만들기
	int random = 0;
	char tmpRand[4];
	srand(time(NULL));
	random = (rand() % 10000);
	strcpy(LOT, "L");
	strcat(LOT, itoa(random, tmpRand, 10));

	strcpy(values, "'");
	strcat(values, PRD_CODE);
	strcat(values, "', '");
	strcat(values, PRD_NAME);
	strcat(values, "', '");
	strcat(values, STATUS);
	strcat(values, "', ");
	strcat(values, DATE);
	strcat(values, ", '");
	strcat(values, LOT);
	strcat(values, "'");
	printf("\n");

	_create("material", "PRD_CODE VARCHAR(6) PRD_NAME VARCHAR(20) STATUS VARCHAR(6) DATE INT LOT VARCHAR(6)");

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

//int findMotherAmts(char* child, int res, char* root) {
//	while (1) {
//		if (strcmp(child, root) == 0) {
//			break;
//		}
//		int result_count;
//		result* _result;
//		char* select_column = "NODE_CODE, REQ_NUM, M_CODE";
//		char conditional[20] = "NODE_CODE='";
//		strcat(conditional, child);
//		strcat(conditional, "'");
//
//		if (initalizing("BOM_SAMPLE_3") == -1) {
//			printf("%s\n", err_msg);
//
//			file_column_free();
//			return -1;
//		}
//		if (_select(conditional, select_column, &select_result_str) == -1) {
//			file_column_free();
//			return 0;
//		}
//		else {
//			if ((result_count = recv_result(&_result, select_result_str)) == -1) {
//				file_column_free();
//				result_free(_result, result_count);
//				return 0;
//			}
//			else {
//				_findMotherAmts(_result, result_count, child, res, root);
//			}
//		}
//	}
//	return res;
//}

//void _findMotherAmts(result* _result, int result_count, char* child, int res, char* root) {
//	if (strcmp(child, root) == 0) {
//		return;
//	}
//	//_result 다시 맨처음으로 보낸뒤 모코드로 다시 올라가 반복
//	char mCode[10];
//	while (1) {
//		if (strcmp(_result->name, "REQ_NUM") == 0) {
//			res *= _result->_int_data[0];
//			break;
//		}
//		_result = _result->next;
//	}
//	while (1) {
//		if (strcmp(_result->name, "M_CODE") == 0) {
//			strcpy(mCode, _result->_string_data[0]);
//			break;
//		}
//		_result = _result->next;
//	}
//	file_column_free();
//	result_free(_result, result_count);
//	findMotherAmts(mCode, res, root);
//}

void makeLeafsList(bomRes* leafs, bomRes* result2, char* root) {
	leafs = leafs->next;
	int flag = 1;
	while (leafs->next != NULL) {
		//원재료 리스트의 포인터 헤더로 다시 옮기기
		while (result2->next != NULL) {
			result2 = result2->next;
			//while문을 다 돌도록 같은 품목을 찾지 못하면(flag가 0으로 변하지 않으면)
			//원재료 리스트에 항목 추가할수 있도록 flag 세우기
			flag = 1;
			//원재료 리스트에 이미 있는 품목이면 리스트를 새로 추가하지 않고 넘어감
			if (strcmp(result2->CODE, leafs->CODE) == 0) {
				flag = 0;
				break;
			}
		}
		//while문을 다 돌도록 같은 품목을 찾지 못하면(flag가 0으로 변하지 않으면)
		//원재료 리스트에 항목 추가
		if (flag == 1) {
			//BOM 역전개로 조회하여 필요한 원재료 개수 구하기
			int total = 1;
			BOM_LIST* mList = BOM_RESEARCH(leafs->CODE);
			while (mList != NULL) {
				total *= mList->REQ_NUM;
				mList = mList->next;
			}

			bomRes* newNode = (bomRes*)malloc(sizeof(bomRes));
			newNode->CODE = leafs->CODE;
			//루트코드로 도달할때까지의 원재료의 필요개수 곱하기
			newNode->AMOUNT = total;
			newNode->next = result2->next;
			result2->next = newNode;
		}
		leafs = leafs->next;
	}
}

void createOrderedMaterials(bomRes* list) {
	char values[50];
	char PRD_CODE[7];
	char PRD_NAME[20];
	char STATUS[10] = "store";
	char DATE[10];
	char LOT[7];

	struct tm* t;
	time_t timer;

	timer = time(NULL);    // 현재 시각을 초 단위로 얻기
	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기

	//DATE에 오늘날짜 집어넣기(20001010형식)
	sprintf(DATE, "%04d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

	while (list->next != NULL) {
		list = list->next;
		//코드번호로 품목명 가져오기
		if (initalizing("list") == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		int result_count;
		result* _result;
		char* select_column = "CODE, NAME";
		char conditional[20] = "CODE='";
		strcat(conditional, list->CODE);
		strcat(conditional, "'");

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
			else {
				while (_result != NULL) {
					if (strcmp(_result->name, "NAME") == 0) {
						strcpy(PRD_NAME, *(_result->_string_data));
						break;
					}
					else {
						_result = _result->next;
					}
				}
			}
		}

		//자재품목 파일 free
		file_column_free();
		result_free(_result, result_count);

		for (int i = 0; i < list->AMOUNT; i++) {
			//자재 파일 열기
			if (initalizing("material") == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			strcpy(PRD_CODE, list->CODE);

			//LOT번호 만들기
			int random = 0;
			char tmpRand1[2];
			char tmpRand2[3];
			char tmpRand3[4];
			char tmpRand4[5];
			//srand(time(NULL));
			random = (rand() % 10000);
			
			if (random < 1000 && random>100)
			{
				strcpy(LOT, "L0");
				strcat(LOT, itoa(random, tmpRand3, 10));
			}
			else if (random < 100 && random>10)
			{
				strcpy(LOT, "L00");
				strcat(LOT, itoa(random, tmpRand2, 10));
			}
			else if (random < 10)
			{
				strcpy(LOT, "L000");
				strcat(LOT, itoa(random, tmpRand1, 10));
			}
			else
			{
				strcpy(LOT, "L");
				strcat(LOT, itoa(random, tmpRand4, 10));
			}


			strcpy(values, "'");
			strcat(values, PRD_CODE);
			strcat(values, "', '");
			strcat(values, PRD_NAME);
			strcat(values, "', '");
			strcat(values, STATUS);
			strcat(values, "', ");
			strcat(values, DATE);
			strcat(values, ", '");
			strcat(values, LOT);
			strcat(values, "'");

			if (_insert(values) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			file_column_free();
		}
	}
}

//생산계획 입력 후 받아와서 재고 확인, 발주갔다 돌아와서 공정으로 보내기
void confirm_Material(plan* p) {
	char* PLAN_PRODUCTION = p->PLAN_PRODUCTION;
	//bom 트리에서 단말노드(원재료)만 가져오기
	bomRes* leafs = (bomRes*)malloc(sizeof(bomRes));
	leafs->next = NULL;
	bomRes* head1 = leafs;			//헤드로 돌아오게 할수있도록 헤드 위치 저장

	//중복 제거후 카운트할 리스트
	bomRes* result2 = (bomRes*)malloc(sizeof(bomRes));
	result2->next = NULL;
	bomRes* head2 = result2;		//헤드로 돌아오게 할수있도록 헤드 위치 저장

	//BOM 조회
	BOM_TREE* res = BOM_SEARCH(p->CODE);

	//재귀적으로 모든 노드 훓어서 leafs리스트에 담기
	get_Materials_From_Bom(res, res->NODE_CODE, leafs);

	//원재료(단말노드)만 따로 리스트 만들기
	makeLeafsList(leafs, result2, p->CODE);
	
	//트리를 그대로 담아온 리스트는 이제 필요없으므로 free
	freeNodes(head1);

	//생산계획의 수량에 맞추려면 필요한 원재료 개수 출력
	printf("\t필요\n");
	bomRes* list = head2;
	while (list->next != NULL) {
		list = list->next;
		int planedAmt = atoi(p->PLAN_PRODUCTION);
		//char* name = (char*)malloc(sizeof(char));
		list->AMOUNT *= planedAmt;

		printf("%s : %d개\n", list->CODE, list->AMOUNT);
	}

	//현재 가지고있는 재고의 개수 출력
	printf("\n\t현재\n");
	list = head2;
	while (list->next != NULL) {
		list = list->next;
		int stock = findStock(list->CODE);

		printf("%s : %d개\n", list->CODE, stock);
	}

	system("pause");
	system("cls");

	//원자재 - 재고수량 = 부족한 항목 출력
	bomRes* result3 = (bomRes*)malloc(sizeof(bomRes));
	result3->next = NULL;
	printf("현재 부족한 항목은\n\n");
	list = head2;
	while (list->next != NULL) {
		list = list->next;
		bomRes* newnode = (bomRes*)malloc(sizeof(bomRes));
		newnode->CODE = list->CODE;
		int planedAmt = atoi(p->PLAN_PRODUCTION);
		//findStock(품목명)으로 재고가 현재 몇개인지 세기
		int stock = findStock(list->CODE);			//현재
		int need = list->AMOUNT;
		newnode->AMOUNT = need - stock;
		if (newnode->AMOUNT < 0) {
			newnode->AMOUNT = 0;
		}

		newnode->next = result3->next;
		result3->next = newnode;

		//추후 자재품목 리스트에서 코드명으로 자재명 끌어오기

		printf("%s : %d개\n", newnode->CODE, newnode->AMOUNT);
	}

	//freeNodes(result2);

	getchar();
	char input;
	printf("입니다. 주문하시겠습니까?(y / n) : ");
	scanf("%c", &input);

	if (input == 'y') {
		//발주로 보내기
		Request_Order(result3);

		//발주한 품목 자재에 insert
		list = result3;
		createOrderedMaterials(list);

		//공정으로 보내기
		system("cls");
		printf("발주한 재고 기록 작성을 완료했습니다.\n");
		system("pause");
		process(result3,p);
	}
	else {
		printf("\n취소를 선택하셨습니다.\n작업이 모두 취소되고 생산 계획 메뉴로 돌아갑니다.\n");
		system("pause");
		system("cls");
		production_menu();
	}
	
}

//해당 코드의 재고가 몇개인지 세어서 리턴
int findStock(char* code) {
	int res = 0;
	char* select_column = "PRD_CODE, STATUS, LOT";
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
		//재고 계산하는 부분
 		while (_result != NULL) {
			//현재 노드의 컬럼명이 STATUS일 경우
			if (strcmp(_result->name, "STATUS") == 0) {
				for (int i = 0; i < result_count; i++) {
					//STATUS컬럼에 대응하는 데이터가 store(저장상태)일 경우
					if (strcmp(_result->_string_data[i], "store") == 0) {
						//재고 +1
						res++;
					}
				}
				break;
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

void freeNodes(bomRes* obj) {
	while (obj->next != NULL) {
		obj = obj->next;
		bomRes* tmp = obj;
		obj = obj->next;
		free(tmp);
	}
}