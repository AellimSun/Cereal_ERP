#include "cereal.h"

typedef struct Accountnode {
	int acconut_code;
	char account_name[20];
	char account_contact[20];
	struct Accontnode * next;
}Anode;

void insertAcconut()
{
	int new_code;
	char new_name[20] = { 0 };
	char new_contract[20] = { "0" };

	printf("====================\n");
	printf("�ŷ�ó�� ����մϴ�.\n");
	printf("====================\n\n");

	printf("�ŷ�ó �ڵ� ��� : \n");
	printf("���� ��� ���� �ڵ� : ****");
	scanf("%d",&new_code);
	printf("�ŷ�ó �̸� ��� : ");
	scanf("%s", &new_name);
	printf("�ŷ�ó ����ó ��� : ");
	scanf("%s", &new_contract);
	Anode* newNode =(Anode *) malloc(sizeof(Anode));
	if (newNode == NULL)return;
	newNode->acconut_code = new_code;
	/*newNode->account_name = new_name;
	newNode->account_contact = new_contract;*/


}

void updateAccount()
{

}

void readAccount()
{

}

void deleteAccount()
{

}

void account()
{
	int menu;
	printf("�ŷ�ó ���\n");
	printf("�ŷ�ó ����\n");
	printf("�ŷ�ó ��ȸ\n");
	printf("�ŷ�ó ����\n");
	scanf("%d", &menu);

	switch (menu)
	{
	case 1:
		insertAcconut();
		break;
	case 2:
		updateAccount();
		break;
	case 3:
		readAccount();
		break;
	case 4:
		deleteAccount();
		break;
	}
}