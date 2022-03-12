#include"cereal.h"
#include"local.h"
#include"UI.h"

void gotoxy(int x, int y);

void main_ui() {

	system("color f0");
	system("mode con:cols=86lines=50");//lines=25

	system("title 시리얼 공장 관리 ERP");
	printf("\n");
	printf("\t\t\t=====================================\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t|       시리얼 공장 관리 ERP        |\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t=====================================\n");
	printf("\n\t\t\t\t제작 팀 : 파맛첵스\n\n");
	Sleep(2000);
	system("cls");

	printf("\n");
	printf("\t\t\t=====================================\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t|       시리얼 공장 관리 ERP        |\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t=====================================\n");
	printf("\n\t\t\t\t제작 팀 : 파맛첵스\n\n");
	printf("\t\t\t\t시스템 시작 준비중.\n");
	Sleep(500);
	system("cls");

	printf("\n");
	printf("\t\t\t=====================================\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t|       시리얼 공장 관리 ERP        |\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t=====================================\n");
	printf("\n\t\t\t\t제작 팀 : 파맛첵스\n\n");
	printf("\t\t\t\t시스템 시작 준비중..\n");
	Sleep(500);
	system("cls");

	printf("\n");
	printf("\t\t\t=====================================\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t|       시리얼 공장 관리 ERP        |\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t=====================================\n");
	printf("\n\t\t\t\t제작 팀 : 파맛첵스\n\n");
	printf("\t\t\t\t시스템 시작 준비중...\n");
	Sleep(500);
	system("cls");

	printf("\n");
	printf("\t\t\t=====================================\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t|       시리얼 공장 관리 ERP        |\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t=====================================\n");
	printf("\n\t\t\t\t제작 팀 : 파맛첵스\n\n");
	printf("\t\t\t\t   환영합니다!\n");
	Sleep(1000);
	system("cls");
}

void gotoxy(int x, int y) {
	//x, y 좌표 설정
	COORD pos = { x,y };
	//커서 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

