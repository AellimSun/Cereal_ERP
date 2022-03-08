#include "cereal.h"

void production_management(void);
void material_management(void);

void stock(void);				// 재고
void order(void);				// 발주
void delivery(void);			// 납품
void account(void);				// 거래처
void base_information(void);	// 기초정보
void product_list(void);		// 생산품목리스트
void production_plan(void);		// 생산계획
void process(void);				// 공정관리

int main(void)
{
	int input=0;

	printf("메뉴를 선택하세요.\n");
	printf("1. 자재관리\n");
	printf("2. 생산관리\n");
	printf("0.종료\n");

	scanf("%d", &input);
	system("cls");
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

void material_management(void)
{
	int input = 0;
	printf("메뉴를 선택하세요.\n");
	printf("1.재고관리\n");
	printf("2.발주관리\n");
	printf("3.납품관리\n");
	printf("4.거래처관리\n");
	printf("0.이전으로\n");

	scanf("%d", &input);
	system("cls");
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
		break;
	}

}
void production_management(void)
{
	int input = 0;
	printf("메뉴를 선택하세요.\n");
	printf("1.기초정보관리\n");
	printf("2.생산계획\n");
	printf("3.공정관리\n");

	scanf("%d", &input);
	system("cls");
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
		break;
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

//void account(void)
//{
//
//}
void base_information(void)
{
	int input = 0;
	printf("메뉴를 선택하세요.\n");
	printf("1.BOM 등록\n");
	printf("2.BOM 조회\n");
	printf("3.생산품목 리스트\n");
	printf("0.이전으로\n");

	scanf("%d", &input);
	system("cls");
	switch (input)
	{
	case 1:
	case 2:
	case 3:
		product_list();
	case 0:
		material_management();
	}
	
}
void production_plan(void)
{

}

void product_list(void)
{

}