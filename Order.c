#include "cereal.h"
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>

typedef struct _order
{
	int O_Day;
	int D_Day;
	char ACC_CODE[6]; //�迭���� �ּҰ��� ����Ų��.
	char PRD_CODE[6]; //�迭���� �ּҰ��� ����Ų��.
	int NUM;

}Order;



//char prd_code[6] = "c001";
//char acc_code[6] = "a001";
//int num = 5;
char* values;
//��û :: ���� ������ ����! ( ���� -> ǰ���ڵ�, �ŷ�ó�ڵ�, ����  ) 
Order* Request_Order(char* prd_code, char* acc_code, int num)
{
	/* ���ǹ��� ���ڷ� �ؼ� ���Ͽ��� ã�°� �ȵ� */

	//���翡�� ǰ�� �ڵ�, �ŷ�ó �ڵ�, ������ �޾ƿӴ�
	//�ŷ�ó ���Ϸ� �� ǰ���ڵ带 �Ѱ���
	//�� ���Ͽ� �����̷��� ����

	//storage�� ��� �ѱ⳪? :: ����ü�������� �����Ͽ� �Ѱܺ���
	//

	
}

//01 ���� -> ���� -> �ŷ�ó ��Ʈ
void storage_Order(char* prd_code, char* acc_code, int num)
{
	//����ü �迭�� �� char�� ����, ����ȯ�Ͽ� ����.
	//����ü�迭�� ����. �ŷ�ó���� 
	printf("2\n");
	// !!! �迭���� �ּҰ��� ����Ų�� !!!
	Order newOrder;

	//�����̷��� �����ϴ� ����
	//int _update(char* conditional, char* set) {
	printf("3\n");
	strcpy(newOrder.ACC_CODE, acc_code);
	printf("4\n");
	strcpy(newOrder.PRD_CODE, prd_code);
	printf("5\n");
	newOrder.NUM = num;
	printf("6\n");
	
	//�Լ��� ����
	/*
		strcat(values, "'");
		strcat(values, newOrder.ACC_CODE);
		strcat(values, "', ");
		strcat(values, "'");
	*/

	values = malloc(sizeof(char) * 50);
	//char* values = "'NULL', 'NULL', acc, prd, null";
	//strcpy(values, newOrder.ACC_CODE);
	
	strcpy(values, "NULL");
	strcat(values, ", ");
	strcat(values, "NULL");
	strcat(values, ", ");
	strcat(values, "'");
	strcat(values, newOrder.ACC_CODE);
	//strcat(values, "NULL");
	strcat(values, "', ");
	strcat(values, "'");
	strcat(values, newOrder.PRD_CODE);
	//strcat(values, "NULL");
	strcat(values, "', ");
	strcat(values, "NULL");
	
	printf("%s\n", values);
	

	
	if (_insert(values) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	
	free(values);

}

//02. ���� -> ���� -> �����Է�(ǰ���ڵ�) -> �ŷ�ó ��� -> ����!


void search_Order()
{
	print_data();

	/*
		0. ť�� ����� ������� �����̷� ��ȸ :: ������
			- > �������� ���� ������ ������ ���Ḯ��Ʈ�� ����.
			���Ḯ��Ʈ�� ť�� �簡��? ���Ḯ��Ʈ��� LIFO �������� 
		1. �����ڵ�� �����̷� ��ȸ
		2. �ŷ�ó �ڵ庰 �����̷� ��ȸ
	*/
} 



