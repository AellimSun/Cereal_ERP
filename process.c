#include "cereal.h"
#include "UI.h"

#define FILE_NAME "process"

int cursor_x = 0;
int cursor_y = 0;

typedef struct _process {
	int data;
	struct _process* next;
}S_process;
void init(void);

void view(void);

void process(void)
{
	//init();
	initalizing("FILE_NAME");
	int input;
	CursorView(false);
	printf("메뉴를 선택하세요.\n");

	while (1)
	{
		goto_xy(cursor_x, cursor_y + 1);
		textcolor(8);
		printf("1.공정등록\n");
		textcolor(15);
		printf("2.공정조회\n");
		printf("0.이전으로\n");
		scanf("%d", &input);
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
		view();
		break;
	case 0:
		break;
	}
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