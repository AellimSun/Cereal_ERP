#include "cereal.h"

#define PRO_FILE_NAME "process"
#define MAT_FILE_NAME "material"

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

void bg_process(void);
void check_parts(int num, char* bom_res, req_code*);			// 자체생산부품 필요량 파악
int produce_parts(req_code* head);		// 부족한 부품 생성/ 자재에서 사용함으로 바꿈

void pro_material_create(req_code* p_code);
void pro_material_use();
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


	//3pro_material_create();

	check_parts(PLAN_NUM, bom_res,head);			//부족한 제작부품 개수 파악
	produce_parts(head);		//부족한 제작부품 생산명령 - LOT번호 필요...?
	//confirm_produce();	//작업지시 확정 - 위에 있는지 확인
	//give_LOT();				//생산완료품 LOT번호 생성-실행날짜 기반
	//produce_product();		//생산계획 품목 생산 및 등록
	//material_upload();		//생산자제 등록
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
			pro_material_use(p_code);
			cnt++;
		}
		printf("%d\n", cnt);
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
void pro_material_use(req_code* p_code) {

	char* conditional = "CODE='";
	char* set = "DATE";
	result* find;
	result* _result;
	int result_count;

	strcat(conditional, p_code);
	strcat(conditional, "'");


	if (initalizing("test_pro_material") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_select(conditional,set,&select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	
	if ((result_count = recv_result(&_result, select_result_str)) == -1)
	{
		printf("%s\n", err_msg);

		result_free(_result, result_count);
		return -1;
	}
	result_print(_result, result_count);

	if ((find = find_result(_result, "DATE")) == -1)
	{
		printf("%s\n", err_msg);

		result_free(_result, result_count);
		return -1;
	}

	file_column_free();
	result_free(_result, result_count);
	print_data();

	system("pause");
	system("cls");
}

void init(void)
{
	_create("test_pro_material", "PRD_CODE VARCHAR(6) STATUS VARCHAR(6) DATE INT ACC_CODE VARCHAR(6)");

	char* value[30];

	value[0] = "B0001,store,22031001,0000";
	value[1] = "B0001,store,22031002,0000";
	value[2] = "B0002,store,22031001,0000";
	value[3] = "B0002,store,22031002,0000";
	value[4] = "B0002,store,22031003,0000";
	value[5] = "B0003,store,22031001,0000";
	value[6] = "B0003,store,22031002,0000";
	value[7] = "B0003,store,22031003,0000";
	value[8] = "B0003,store,22031004,0000";
	value[9] = "B0004,store,22031001,0000";
	value[10] = "B0004,store,22031002,0000";
	value[11] = "B0004,store,22031003,0000";
	value[12] = "B0004,store,22031004,0000";
	value[13] = "B0004,store,22031005,0000";
	value[14] = "C0001,store,22031001,0000";
	value[15] = "C0001,store,22031002,0000";
	value[16] = "C0001,store,22031003,0000";
	value[17] = "C0001,store,22031004,0000";
	value[18] = "C0002,store,22031001,0000";
	value[19] = "C0002,store,22031002,0000";
	value[20] = "C0002,store,22031003,0000";
	value[21] = "C0003,store,22031001,0000";
	value[22] = "C0003,store,22031002,0000";
	value[23] = "D0001,store,22031001,0000";


	if (initalizing("test_pro_material") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	int i = 0;

	while (i < 23)
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