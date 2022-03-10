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

//void init(void);
void bg_process(void);
//req_code* NewNode();

void check_parts(int num, char* bom_res, req_code*);			// 자체생산부품 필요량 파악
int parts_produce(int num, char* bom_res, char* code);		// 부족한 부품 생성/ 자재에 자품목 수량 업로드
give_LOT();		// 생산품 LOT번호 생성
produce_product();		//생산계획 품목 자재에 생산 수량 업로드
req_code* New(req_code* head, int num, char* code);

void process(void)
{
	//init();
	//initalizing("FILE_NAME");
	int input;

	printf("메뉴를 선택하세요.\n");

	bg_process();

	system("cls");

	if (input < 0 || input >2)
	{
		printf("오류입니다. 다시 입력하세요.\n");
		getchar();
		getchar();
		system("cls");

		process();
	}

	switch (input)
	{
	case 1:
		printf("공정을 등록합니다.\n");
		printf("");

		break;
	case 2:
		printf("공정을 조회합니다.\n");
		//view();
		break;
	case 0:
		break;
	}
}

void bg_process(void)
{
	char* bom_res;
	char* con = "A1000S";
	BOM_SEARCH(con);

	req_code* head = (req_code*)malloc(sizeof(req_code));

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
//void init(void)
//{
//	_create("FILE_NAME","'품목코드' INT '자재코드' INT '수량' INT");
//	initalizing("FILE_NAME");
//	_insert("1001,2001,100");
//	_insert("1002,2002,100");
//	_insert("1003,2003,100");
//	_insert("1004,2004,100");
//	_insert("1005,2005,100");
//
//}