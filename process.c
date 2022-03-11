#include "cereal.h"
#include <string.h>


#define PRO_FILE_NAME "process"
#define MAT_FILE_NAME "test_pro_material"

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

void bg_process(void);
void check_parts(int num, char* bom_res, req_code*);			// 자체생산부품 필요량 파악
int produce_parts(req_code* head);		// 부족한 부품 생성/ 자재에서 사용함으로 바꿈

void pro_material_create(char* p_code);
void pro_material_use(char* p_code, int num);
//give_LOT();		// 생산품 LOT번호 생성
//produce_product();		//생산계획 품목 자재에 생산 수량 업로드
req_code* New(req_code* head, int num, char* code);

void process(void)
{
	//init();
	//initalizing("FILE_NAME");
	int input;

	printf("메뉴를 선택하세요.\n");

	bg_process();

}

void bg_process(void)
{
	BOM_TREE* bom_res;
	char* con = "A0001";
	bom_res = BOM_SEARCH(con);

	req_code* head = (req_code*)malloc(sizeof(req_code));
	if (head == NULL) exit(1);
	head->num = NULL;
	head->code = NULL;
	head->next = NULL;

	PRO_all_read();

	//pro_material_create();

	check_parts(PLAN_NUM, bom_res,head);			//부족한 제작부품 개수 파악
	produce_parts(head);		//부족한 제작부품 생산명령 - LOT번호 필요...?
	//confirm_produce();	//작업지시 확정 - 위에 있는지 확인
	//give_LOT();				//생산완료품 LOT번호 생성-실행날짜 기반
	//produce_product();		//생산계획 품목 생산 및 등록
	//material_upload();		//생산자제 등록

	PRO_all_read();


	free(head);
}

void check_parts(int num, char* bom_res, req_code* head)
{
	//_BOM_Backward_PrintTree();
	New(head, 2,"B0001");
	New(head, 3,"B0002");
	New(head, 4,"B0003");
	New(head, 5,"B0004");
	New(head, 4,"C0001");
	New(head, 3,"C0002");
	New(head, 2,"C0003");
	New(head, 5,"D0001");

}

int produce_parts(req_code* head)
{
	req_code* cur = head->next;
	int p_num;
	char* p_code;

	while (cur != NULL)
	{
		int cnt = 0;
		p_num = cur->num;
		p_code = cur->code;
		while (cnt < p_num)
		{
			pro_material_use(p_code, p_num);
			cnt++;
			printf("while문 : %d\n", cnt);
		}
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

void pro_material_create() {

	system("pause");
	system("cls");
}

void pro_material_use(char* p_code, int p_num) {

	char* text1 = "PRD_CODE = '";
	char* text2 = "'";
	char* conditional = (char*)malloc(sizeof(text1) + sizeof(p_code) + sizeof(text2));
	if (conditional == 0) exit(1);
	char* select_column = "PRD_CODE,STATUS,DATE";
	char* set = "STATUS='uesed'";
	char* CODE = p_code;
	result* find;
	result* _result;
	int result_count;

	strcpy(conditional, text1);
	strcat(conditional, CODE);
	strcat(conditional, text2);


	if (initalizing(MAT_FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	/*if (_update_N(conditional,set,p_num) == -1) {
		printf("%s\n", err_msg);
		
		file_column_free();
		return -1;
	}*/
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
		//update 하기
		while (_result->next != NULL) {
			//현재 노드의 컬럼명이 STATUS일 경우
			if (strcmp(_result->name, "STATUS") == 0) {
				//STATUS컬럼에 대응하는 데이터가 store(저장상태)일 경우
				if (strcmp(*(_result->_string_data), "store") == 0) {
					
					char* txt1 = "DATE=";
					char* conditional1 = (char*)malloc(sizeof(txt1)+sizeof(int));
					strcpy(conditional1, txt1);
					strcat(conditional1, );
					if (_update(conditional1, "SATATUS = 'used'") == -1{
						file_column_free();
						return 0;
					}
				}
			}
			_result = _result->next;
		}
	}

	//if ((find = find_result(_result, "DATE")) == -1)
	//{
	//	printf("%s\n", err_msg);

	//	result_free(_result, result_count);
	//	return -1;
	//}
	file_column_free();

	//print_data();

	result_free(_result, result_count);
	free(conditional);

	system("pause");
	system("cls");
}

void init(void)
{
	_create(MAT_FILE_NAME, "PRD_CODE VARCHAR(6) STATUS VARCHAR(6) DATE INT ACC_CODE VARCHAR(6)");

	char* value[30];

	value[0] = "'B0001','store',22031001,'0000'";
	value[1] = "'B0001','store',22031002,'0000'";
	value[2] = "'B0002','store',22031001,'0000'";
	value[3] = "'B0002','store',22031002,'0000'";
	value[4] = "'B0002','store',22031003,'0000'";
	value[5] = "'B0003','store',22031001,'0000'";
	value[6] = "'B0003','store',22031002,'0000'";
	value[7] = "'B0003','store',22031003,'0000'";
	value[8] = "'B0003','store',22031004,'0000'";
	value[9] = "'B0004','store',22031001,'0000'";
	value[10] = "'B0004','store',22031002,'0000'";
	value[11] = "'B0004','store',22031003,'0000'";
	value[12] = "'B0004','store',22031004,'0000'";
	value[13] = "'B0004','store',22031005,'0000'";
	value[14] = "'C0001','store',22031001,'0000'";
	value[15] = "'C0001','store',22031002,'0000'";
	value[16] = "'C0001','store',22031003,'0000'";
	value[17] = "'C0001','store',22031004,'0000'";
	value[18] = "'C0002','store',22031001,'0000'";
	value[19] = "'C0002','store',22031002,'0000'";
	value[20] = "'C0002','store',22031003,'0000'";
	value[21] = "'C0003','store',22031001,'0000'";
	value[22] = "'C0003','store',22031002,'0000'";
	value[23] = "'D0001','store',22031001,'0000'";


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
	char* select_column = "PRD_CODE, STATUS, DATE, ACC_CODE";
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