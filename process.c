#include "cereal.h"
#include <string.h>
#include <time.h>

#define PRO_FILE_NAME "process"
#define MAT_FILE_NAME "test_pro_material"
#define BOM_FILE_NAME "BOM_SAMPLE_3"

#define PLAN_NUM 100
#define PLAN_CODE "A1001"

typedef struct _process {
	int data;
	struct _process* next;
}S_process;

typedef struct _req_code {
	int num;
	char* code;
	struct _req_code* next;
}req_code;

void init(void);
void PRO_all_read();
void PRO_BOM_Forward(BOM_TREE* CurNode, Element1* NODE_CODE);
void _PRO_BOM_Forward(BOM_TREE* CurNode, int Depth);
void BOM_read();

void bg_process(plan* prd_plan);
void check_parts(int num, char* bom_res, req_code*);			// 자체생산부품 필요량 파악
int produce_parts(req_code* head);			// 생산계획따라 자재에서 사용함으로 바꿈
void produce_product(req_code* head);		//  생산계획따라 품목 자재에 생산 수량 업로드
void pro_material_create(char* p_code);
void pro_material_use(char* p_code, int num);
char give_LOT();		// 생산품 LOT번호 생성

req_code* New(req_code* head, int num, char* code);
void req_code_free_Head(req_code* head);

//void process(*plan prd_plan)
void process(void)
{
	//plan* tmp = 들어온 파일;
	plan* tmp = (plan*)malloc(sizeof(plan));
	if (tmp == NULL) exit(1);
	tmp->CODE = "A0001";
	tmp->PLAN_PRODUCTION = "1";
	tmp->values = "2022";

	init();
	printf("공정이 시작됩니다.\n");
	bg_process();
}//

void bg_process(plan* prd_plan)
{
	BOM_TREE* bom_res;
	char* con;
	strcpy(con,prd_plan->CODE);
	bom_res = BOM_SEARCH(con);
	system("pause");
	BOM_Forward_PrintTree(bom_res,con);
	system("pause");

	BOM_read();
	system("pause");

	req_code* mat_head = (req_code*)malloc(sizeof(req_code));
	if (mat_head == NULL) exit(1);
	mat_head->num = NULL;
	mat_head->code = NULL;
	mat_head->next = NULL;

	req_code* plan_head = (req_code*)malloc(sizeof(req_code));

	PRO_all_read();
	system("pause");

	check_parts(PLAN_NUM, bom_res,mat_head);			//부족한 제작부품 개수 파악
	produce_parts(mat_head);		//부족한 제작부품 생산명령 - LOT번호 필요...?
	//confirm_produce();		//작업지시 확정 - 위에 있는지 확인
	produce_product(mat_head);		//생산계획 품목 생산 및 등록
	//pro_material_create();

	PRO_all_read();
	system("pause");

	req_code_free_Head(mat_head);
}

void check_parts(int num, char* bom_res, req_code* head)
{
	//_BOM_Backward_PrintTree();

	New(head, 1,"B0001");//2
	New(head, 2,"B0002");//3
	New(head, 2,"B0003");//4
	New(head, 3,"B0004");//5
	New(head, 2,"C0001");//4
	New(head, 2,"C0002");//3
	New(head, 2,"C0003");//2
	New(head, 1,"D0001");//5
}

int produce_parts(req_code* head)
{
	req_code* cur = head->next;
	int p_num;
	char* p_code;
	int cnt = 0;

	while (cur != NULL)
	{
		p_num = cur->num;
		p_code = cur->code;
		pro_material_use(p_code, p_num);
		printf("pro_material_use 실행 %d번\n",cnt+1);
		cnt++;
		cur = cur->next;
	}
}

req_code* New(req_code* head, int num, char* code)
{
	req_code* NewNode = (req_code*)malloc(sizeof(req_code));
	if (NewNode == NULL) exit(1);

	NewNode->num = num;
	NewNode->code = code;
	NewNode->next = head->next;
	head->next = NewNode;
}
void req_code_free_Head(req_code* head)
{
	req_code* cur = head->next;
	while (cur->next != NULL)
	{
		head = cur;
		cur = cur->next;
		free(head);
	}
	free(cur);
}

void pro_material_use(char* p_code, int p_num) {

	char* text1 = "PRD_CODE = '";
	char* text2 = "'";
	char* conditional = (char*)malloc(sizeof(text1) + sizeof(p_code) + sizeof(text2));
	if (conditional == 0) exit(1);

	char* select_column = "PRD_CODE,STATUS,LOT";
	char* set = "STATUS='uesed'";
	char* CODE = p_code;
	result* _result;
	result* cur;
	int result_count;
	int cnt = 0;

	strcpy(conditional, text1);
	strcat(conditional, CODE);
	strcat(conditional, text2);

	if (initalizing(MAT_FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		int i = 0;

		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			result_free(_result, result_count);
			return -1;
		}
		result_print(_result, result_count);

		system("pause");

		//update 하기
		for (int i = 0; i < p_num; i++) {
			cur = _result;
			while (1) {
				//현재 노드의 컬럼명이 STATUS일 경우
				if (strcmp(cur->name, "STATUS") == 0) {
					//STATUS컬럼에 대응하는 데이터가 store(저장상태)일 경우
					if (strcmp(cur->_string_data[i], "store") == 0) {
						while (strcmp(cur->name, "LOT") != 0)
						{
							cur = cur->next;
						}				//LOT까지 가기
						char* lot = (char*)malloc(sizeof(cur->_string_data[i]));
						if (lot == 0) exit(1);
						char* txt1 = "LOT='";
						char* txt2 = "'";
						char* conditional1 = (char*)malloc(sizeof(txt1) + sizeof(lot) + sizeof(txt2));
						if (conditional1 == 0) exit(1);
						char* set = "STATUS = '_used'";

						strcpy(lot, cur->_string_data[i]);
						strcpy(conditional1, txt1);
						strcat(conditional1, lot);
						strcat(conditional1, txt2);

						if (_update(conditional1, set) == -1) {
							printf("%s\n", err_msg);

							file_column_free();
							return -1;
						}
						printf("자재수정 : %s\n", conditional1);
						cnt++;
						free(conditional1);
						free(lot);
					}
				}

				if (cur->next == NULL)
					break;
				else
					cur = cur->next;
			}

		}
		if (cnt < p_num) printf("자재가 부족합니다.\n");
		printf("\n");
	}
	file_column_free();
	result_free(_result, result_count);
	free(conditional);

	//system("pause");
	//system("cls");
}
void pro_material_create(char* p_code) {						//수정!!!!!!!!!!-매개변수
	char values[50];
	char *PRD_CODE = p_code;									//수정!!!!!!!!!!
	char STATUS[5] = "store";
	char DATE[8];
	char tmp[4];
	char ACC_CODE[5]="0000";									//수정!!!!!!!!!!-어디서 받을건지
	char *LOT = give_LOT();

	//날짜 입력
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(tmp, "%d", tm.tm_year);
	strcpy(DATE, tmp);
	sprintf(tmp, "%d", tm.tm_mon);
	strcat(DATE, tmp);
	sprintf(tmp, "%d", tm.tm_mday);
	strcat(DATE, tmp);

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
}
char give_LOT(void)
{
	char LOT[5];
	int random = 0;
	char tmpRand[4];

	srand(time(NULL));
	random = (rand() % 10000);
	strcpy(LOT, "L");
	strcat(LOT, itoa(random, tmpRand, 10));

	return LOT;
}
void produce_product(req_code* head)
{
	pro_material_create("A0001");
}


void PRO_BOM_Forward(BOM_TREE* CurNode, Element1* NODE_CODE)
{
	if (strcmp(CurNode->NODE_CODE, NODE_CODE) == 0)
	{
		//printf("LEVEL\t  품목코드\t필요수량\n");
		//printf("=================================\n");

		_BOM_Forward_PrintTree(CurNode, 0);
		return;
	}
	if (CurNode->LeftChild != NULL)
		_PRO_BOM_Forward(CurNode->LeftChild, NODE_CODE);
	if (CurNode->RightSibling != NULL)
		_PRO_BOM_Forward(CurNode->RightSibling, NODE_CODE);
}

void _PRO_BOM_Forward(BOM_TREE* CurNode, int Depth)
{
	//int i = 0; // 들여쓰기로 트리의 Depth 표현 
	//for (i = 0; i < Depth; i++)
	//   printf("   ");

	//printf("%4d\t%8s\t%5d\n", Depth, CurNode->NODE_CODE, CurNode->REQ_NUM);



	if (CurNode->LeftChild != NULL) // 차일드 존재시
		_BOM_Forward_PrintTree(CurNode->LeftChild, Depth + 1); // 재귀 호출 - Node의 Child의 깊이는 Node의 Depth에 +1 한 값과 같음

	if (CurNode->RightSibling != NULL) // 형제 존재시
		_BOM_Forward_PrintTree(CurNode->RightSibling, Depth); // 재귀 호출 - 형제 노드의 깊이는 모두 같음(같은 레벨의 노드
}

void init(void)
{
	_create(MAT_FILE_NAME, "PRD_CODE VARCHAR(6) STATUS VARCHAR(6) DATE INT ACC_CODE VARCHAR(6) LOT VARCHAR(6)");

	char* value[30];

	value[0] = "'B0001','store',22031001,'0000','L0001'";
	value[1] = "'B0001','store',22031002,'0000','L0002'";
	value[2] = "'B0002','store',22031001,'0000','L0003'";
	value[3] = "'B0002','store',22031002,'0000','L0004'";
	value[4] = "'B0002','store',22031003,'0000','L0005'";
	value[5] = "'B0003','store',22031001,'0000','L0006'";
	value[6] = "'B0003','store',22031002,'0000','L0007'";
	value[7] = "'B0003','store',22031003,'0000','L0008'";
	value[8] = "'B0003','store',22031004,'0000','L0009'";
	value[9] = "'B0004','store',22031001,'0000','L0010'";
	value[10] = "'B0004','store',22031002,'0000','L0011'";
	value[11] = "'B0004','store',22031003,'0000','L0012'";
	value[12] = "'B0004','store',22031004,'0000','L0013'";
	value[13] = "'B0004','store',22031005,'0000','L0014'";
	value[14] = "'C0001','store',22031001,'0000','L0015'";
	value[15] = "'C0001','store',22031002,'0000','L0016'";
	value[16] = "'C0001','store',22031003,'0000','L0017'";
	value[17] = "'C0001','store',22031004,'0000','L0018'";
	value[18] = "'C0002','store',22031001,'0000','L0019'";
	value[19] = "'C0002','store',22031002,'0000','L0020'";
	value[20] = "'C0002','store',22031003,'0000','L0021'";
	value[21] = "'C0003','store',22031001,'0000','L0022'";
	value[22] = "'C0003','store',22031002,'0000','L0023'";
	value[23] = "'D0001','store',22031001,'0000','L0024'";


	if (initalizing("test_pro_material") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	int i = 0;

	while (i <= 23)
	{
		if (_insert(value[i]) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		i++;
	}

	print_data();
	printf("\n");
	file_column_free();
}

void PRO_all_read() {
	char* conditional = "*";
	char* select_column = "PRD_CODE, STATUS, DATE, ACC_CODE, LOT";
	//char* values = "'B4001', 'store', 20220308, 'D0004'";
	int result_count;
	result* _result;

	if (initalizing(MAT_FILE_NAME) == -1) {
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
}

void BOM_read()
{
	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE";

	//BOM 파일 열기
	if (initalizing(BOM_FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	//모든 컬럼 구하기
	if (_select("*", select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}
	//모든 컬럼을 가공하여 ROOT_CODE 컬럼 구하기
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	print_data();
	file_column_free();
}