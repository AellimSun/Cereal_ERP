#include "cereal.h"

void production_management(void);
void material_management(void);
void stock(void);
void order(void);
void delivery(void);
void account(void);
void base_information(void);
void production_plan(void);
void process(void);

int main(void)
{
	int input=0;

	printf("메뉴를 선택하세요.\n");
	printf("1. 자재관리\n");
	printf("2. 생산관리\n");
	printf("0.종료\n");

	scanf("%d", &input);
	switch (input)
	{
	case 1:
		material_management();
		break;

	case 2:
		production_management();
		break;

	case 0:
		break;
	}

	return 0;
}

void production_management(void)
{
	int input = 0;
	printf("메뉴를 선택하세요.\n");
	printf("1.재고관리\n");
	printf("2.발주관리\n");
	printf("3.납품관리\n");
	printf("4.거래처관리\n");
	printf("0.이전으로\n");

	scanf("%d", &input);
	switch (input)
	{
	case 1:
		stock();
		break;
	case 2:
		order();
		break;

	case 3:
		delivery();
		break;

	case 4:
		account();
		break;

	case 0:
		main();
	}

}
void material_management(void)
{
	int input = 0;
	printf("메뉴를 선택하세요.\n");
	printf("1.기초정보관리\n");
	printf("2.생산계획\n");
	printf("3.공정관리\n");

	scanf("%d", &input);
	switch (input)
	{
	case 1:
		base_information();
		break;

	case 2:
		production_plan();
		break;

	case 3:
		process();
		break;

	case 0:
		main();
	}
}
void stock(void)
{

}
void order(void)
{

}
void delivery(void)
{

}

void account(void)
{

}
void base_information(void)
{

}
void production_plan(void)
{

}
void process(void)
{

}