#include "local.h"
#include "cereal.h"
#include "UI.h"


void production_management(void);
void material_management(void);
void main_manu();

void stock(void);				// ���
void order(void);				// ����
void delivery(void);			// ��ǰ
void account(void);				// �ŷ�ó
void base_information(void);	// ��������
void product_list(void);		// ����ǰ�񸮽�Ʈ
void production_plan(void);		// �����ȹ
void process(void);				// ��������

int main(void)
{
	main_ui();

	main_manu();
	
	return 0;
}

void main_manu() {

	int input = 0;

	printf("��ġ : ���θ޴�\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     �޴��� �����ϼ���.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        1. �������        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        2. �������        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        0.����             |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t �Է� :\n");
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

	printf("��ġ : ���θ޴� -> �������\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     �޴��� �����ϼ���.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        1. ������        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        2. ���ְ���        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        3. ��ǰ����        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        4. �ŷ�ó����      |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|        0. ��������        |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t �Է� :\n");
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

	printf("��ġ : ���θ޴� -> �������\n");

	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     �޴��� �����ϼ���.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      1.������������       |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      2.�����ȹ           |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      3.��������           |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t �Է� :\n");
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
	int input = 0;
	//while (1)
	//{


		printf("��ġ : ���θ޴� -> ������� -> ����\n");

		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     �޴��� �����ϼ���.    |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|    1. ���ֳ��� ��ü ��ȸ  |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|                           |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|                           |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|       0. ���۸޴�         |\n");
		printf("\t\t\t-----------------------------\n\n");

		printf("\t\t\t\t �Է� :\n");
		printf("\t\t\t\t        ^");
		gotoxy(40, 15);
		scanf("%d", &input);
		system("cls");
		switch (input)
		{
		case 1:
			all_Order_List();
			break;

		case 2:
			break;

		case 3:
			break;

		case 0:
			main_manu();
		}


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

	printf("��ġ : ���θ޴� -> ������� -> ������������\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     �޴��� �����ϼ���.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      1.BOM ���           |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      2.BOM ��ȸ           |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      3.����ǰ�� ����Ʈ    |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      0.��������           |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t �Է� :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 13);

	scanf("%d", &input);
	system("cls");
	switch (input)
	{
	case 1:
	{
		BOM_record_main();
		break;
	}
	case 2:
	{
		BOM_search_main();
		break;
	}
	case 3:
	{
		product_list();
		break;
	}
	case 0:
		production_management();
		break;
	}
}

//void process(void)
//{
//
//}
