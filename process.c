#include "cereal.h"

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
void bg_process(void);

void check_parts(int num, char* bom_res, req_code*);			// 자체생산부품 필요량 파악
int parts_produce(int num, char* bom_res, char* code);		// 부족한 부품 생성/ 자재에 자품목 수량 업로드
//give_LOT();		// 생산품 LOT번호 생성
//produce_product();		//생산계획 품목 자재에 생산 수량 업로드
void pro_material_use(char* p_code);
void pro_material_create(char* p_code);

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
	char* con = "*";
	BOM_TREE* bom_res = BOM_SEARCH(con);
	BOM_Forward_PrintTree(bom_res, bom_res->NODE_CODE);

	req_code* head = (req_code*)malloc(sizeof(req_code));

	check_parts(PLAN_NUM, bom_res,head);			//부족한 제작부품 개수 파악
	produce_parts(head);		//부족한 제작부품 생산명령 - LOT번호 필요...?
	//confirm_produce();	//작업지시 확정 - 위에 있는지 확인
	//give_LOT();				//생산완료품 LOT번호 생성-실행날짜 기반
	//produce_product();		//생산계획 품목 생산 및 등록
	//material_upload();		//생산자제 등록
}
void init(void)
{
	_create(MAT_FILE_NAME, "PRD_CODE VARCHAR(6) STATUS VARCHAR(6) DATE INT ACC_CODE VARCHAR(6)");
	initalizing(MAT_FILE_NAME);
	char* val[30] =
	{ "",

	};
	for(int i =0;i<30;i++)	_insert(val[i]);

	file_column_free();
}
void check_parts(int num, char* bom_res, req_code* head)
{
	//_BOM_Backward_PrintTree();
	New(head, 10,"A1000");
	New(head, 20,"A5000");
	New(head, 30,"A6000");
	New(head, 40,"A7000");
	New(head, 50,"A8000");


	while (0);
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
		cur = cur->next;
	}
}

req_code* New(req_code* head, int num, char* code)
{
	req_code* NewNode = (req_code*)malloc(sizeof(req_code));
	NewNode->num = num;
	NewNode->code = code;
	NewNode->next = head->next;
	head->next = NewNode;
}

void pro_material_create(char* p_code) {

	if (initalizing(MAT_FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	/*if (_insert() == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}*/

	print_data();
	printf("\n");
	file_column_free();

	system("pause");
	system("cls");
	stock();
}
void pro_material_use(char* p_code) {

	if (initalizing(MAT_FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select() == -1) {
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