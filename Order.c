#include "cereal.h"
#include <stdlib.h>

typedef struct _order
{
	int O_Day;
	int D_Day;
	char ACC_CODE[6]; //�迭���� �ּҰ��� ����Ų��.
	char PRD_CODE[6]; //�迭���� �ּҰ��� ����Ų��.
	int NUM;

}Order;

char* conditional;
char* set;

char prd_code[6] = "c001";
char acc_code[6] = "a001";
int num = 5;

//��û :: ���� ������ ����! ( ���� -> ǰ���ڵ�, �ŷ�ó�ڵ�, ����  ) 
Order* Request_Order(char* prd_code, char* acc_code, int num)
{
	/* ���ǹ��� ���ڷ� �ؼ� ���Ͽ��� ã�°� �ȵ� */

	//���翡�� ǰ�� �ڵ�, �ŷ�ó �ڵ�, ������ �޾ƿӴ�
	//�ŷ�ó ���Ϸ� �� ǰ���ڵ带 �Ѱ���
	//�� ���Ͽ� �����̷��� ����

	
}

// ���� -> ���� -> �����Է�(ǰ���ڵ�) -> �ŷ�ó ��� -> ����!

void storage_Order(char* prd_code, char* acc_code, int num)
{
	// !!! �迭���� �ּҰ��� ����Ų�� !!!
	Order newOrder;
	//�����̷��� �����ϴ� ����
	//int _update(char* conditional, char* set) {
	strcpy(newOrder.ACC_CODE, acc_code);
	strcpy(newOrder.PRD_CODE, prd_code);

	newOrder.NUM = num;

	conditional = "ACC_CODE = newOrder.ACC_CODE";

	//if ()
	//{
	//	return -1;
	//}
}

void search_Order()
{
	/*
		0. ť�� ����� ������� �����̷� ��ȸ :: ������
		1. �����ڵ�� �����̷� ��ȸ
		2. �ŷ�ó �ڵ庰 �����̷� ��ȸ
	*/
}



