#include"cereal.h"
#include"local.h"
#include"UI.h"

void gotoxy(int x, int y);

void main_ui() {

	system("color f0");
	system("mode con:cols=86lines=50");//lines=25

	system("title �ø��� ���� ���� ERP");
	printf("\n");
	printf("\t\t\t=====================================\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t|       �ø��� ���� ���� ERP        |\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t=====================================\n");
	printf("\n\t\t\t\t���� �� : �ĸ�ý��\n\n");
	Sleep(2000);
	system("cls");

	printf("\n");
	printf("\t\t\t=====================================\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t|       �ø��� ���� ���� ERP        |\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t=====================================\n");
	printf("\n\t\t\t\t���� �� : �ĸ�ý��\n\n");
	printf("\t\t\t\t�ý��� ���� �غ���.\n");
	Sleep(500);
	system("cls");

	printf("\n");
	printf("\t\t\t=====================================\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t|       �ø��� ���� ���� ERP        |\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t=====================================\n");
	printf("\n\t\t\t\t���� �� : �ĸ�ý��\n\n");
	printf("\t\t\t\t�ý��� ���� �غ���..\n");
	Sleep(500);
	system("cls");

	printf("\n");
	printf("\t\t\t=====================================\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t|       �ø��� ���� ���� ERP        |\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t=====================================\n");
	printf("\n\t\t\t\t���� �� : �ĸ�ý��\n\n");
	printf("\t\t\t\t�ý��� ���� �غ���...\n");
	Sleep(500);
	system("cls");

	printf("\n");
	printf("\t\t\t=====================================\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t|       �ø��� ���� ���� ERP        |\n");
	printf("\t\t\t|                                   |\n");
	printf("\t\t\t=====================================\n");
	printf("\n\t\t\t\t���� �� : �ĸ�ý��\n\n");
	printf("\t\t\t\t   ȯ���մϴ�!\n");
	Sleep(1000);
	system("cls");
}

void gotoxy(int x, int y) {
	//x, y ��ǥ ����
	COORD pos = { x,y };
	//Ŀ�� �̵�
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

