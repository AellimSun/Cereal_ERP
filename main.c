#include "cereal.h"

void production_management(void);
void material_management(void);

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
	int input=0;

	printf("�޴��� �����ϼ���.\n");
	printf("1. �������\n");
	printf("2. �������\n");
	printf("0.����\n");

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
	printf("�޴��� �����ϼ���.\n");
	printf("1.������\n");
	printf("2.���ְ���\n");
	printf("3.��ǰ����\n");
	printf("4.�ŷ�ó����\n");
	printf("0.��������\n");

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
	printf("�޴��� �����ϼ���.\n");
	printf("1.������������\n");
	printf("2.�����ȹ\n");
	printf("3.��������\n");

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
	printf("�޴��� �����ϼ���.\n");
	printf("1.BOM ���\n");
	printf("2.BOM ��ȸ\n");
	printf("3.����ǰ�� ����Ʈ\n");
	printf("0.��������\n");

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