#include "local.h"
#include "cereal.h"
#include "UI.h"


void production_management(void);
void material_management(void);
void main_manu();

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
	main_ui();

	main_manu();
	
	return 0;
}

void main_manu() {

	int input = 0;

	printf("위치 : 메인메뉴\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     메뉴를 선택하세요.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        1. 자재관리        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        2. 생산관리        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        0.종료             |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t 입력 :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 13);
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
}

void material_management(void)
{
	int input = 0;

	printf("위치 : 메인메뉴 -> 자재관리\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     메뉴를 선택하세요.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        1. 재고관리        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        2. 발주관리        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        3. 납품관리        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        4. 거래처관리      |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        0. 이전으로        |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t 입력 :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 17);
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
		main_manu();
	}

}
void production_management(void)
{
	int input = 0;

	printf("위치 : 메인메뉴 -> 생산관리\n");

	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     메뉴를 선택하세요.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      1. 기초정보관리      |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      2.생산계획           |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      3.공정관리           |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t 입력 :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 13);
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
		main_manu();
	}
}

void order(void)
{
	// 파일 위치 :: 초기화한다. 저장소 지정
	//if (initalizing("D:\\00_Bird_00\\첵스\\project\\Cereal\\Clanguage\\01_ERP\\sample_Order") == -1) {
	//if (initalizing("account") == -1)
	//{
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}


	//Request_Order("D201");

	//printf("1\n");
	//storage_Order("003", 5);
	//printf("return\n");
	//print_data();

	//file_column_free();

	
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

	printf("위치 : 메인메뉴 -> 생산관리 -> 기초정보관리\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     메뉴를 선택하세요.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      1.BOM 등록           |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      2.BOM 조회           |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      3.자재품목 리스트    |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      0.이전으로           |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t 입력 :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 15);

	scanf("%d", &input);
	system("cls");
	switch (input)
	{
	case 1:
	{


		break;
	}
	case 2:
	{
		BOM_search_main();


		/*char* con = "A0002";
		BOM_TREE* res = BOM_SEARCH(con);
		BOM_Forward_PrintTree(res, con);*/

		break;
	}
	case 3:
	{
		product_list();
		break;
	}
	case 0:
		material_management();
		break;
	}
	
}

//void process(void)
//{
//
//}
