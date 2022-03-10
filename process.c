#include "cereal.h"

#define FILE_NAME "process"
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
void bg_process(int num, char* bom_res, char* code);
//req_code* NewNode();

void check_parts(int num, char* bom_res, req_code);
int parts_produce(int num, char* bom_res, char* code);


void process(void)
{
	//init();
	initalizing("FILE_NAME");
	int input;

	printf("메뉴를 선택하세요.\n");

	while (1)
	{
		
	}
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

void bg_process(int num, char* bom_res, char* code)
{
	char* bom_res;

	req_code* temp = (req_code*)malloc(sizeof(req_code));

	check_parts(PLAN_NUM, bom_res,temp);			//부족한 제작부품 있는지 판단
	produce_parts();		//부족한 제작부품 생산명령 - LOT번호 필요...?
	//confirm_produce();	//작업지시 확정 - 위에 있는지 확인
	give_LOT();				//생산완료품 LOT번호 생성-실행날짜 기반
	produce_product();		//생산계획 품목 생산
	material_upload();		//생산자제 등록
}

void check_parts(int num, char* bom_res, req_code* temp)
{
	
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