#include "cereal.h"
#include "UI.h"

#define FILE_NAME "process"


typedef struct _process {
	int data;
	struct _process* next;
}S_process;

void init(void);
void bg_process(void);

check_parts();
parts_produce();


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

void bg_process(void)
{
	check_parts();			//부족한 제작부품 있는지 판단
	produce_parts();		//부족한 제작부품 생산명령
	confirm_produce();		//작업지시 확정
	give_LOT();				//생산완료품 LOT번호 생성-실행날짜 기반
	produce_product();		//생산계획 품목 생산
	material_upload();		//생산자제 등록
}

void init(void)
{
	_create("FILE_NAME","'품목코드' INT '자재코드' INT '수량' INT");
	initalizing("FILE_NAME");
	_insert("1001,2001,100");
	_insert("1002,2002,100");
	_insert("1003,2003,100");
	_insert("1004,2004,100");
	_insert("1005,2005,100");

}