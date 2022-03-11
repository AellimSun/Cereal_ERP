#include "cereal.h"
//#include <stdlib.h>
//#define _GNU_SOURCE
#include <string.h>
#include <time.h>

// ������, �����Ͽ� �ӽ÷� ������ �ð��Լ�
//struct tm {
//	int tm_sec;         /* ��,  range 0 to 59            */
//	int tm_min;         /* ��, range 0 to 59             */
//	int tm_hour;        /* �ð�, range 0 to 23            */
//	int tm_mday;        /* ��, range 1 to 31             */
//	int tm_mon;         /* ��, range 0 to 11             */
//	int tm_year;        /* 1900�� ������ ��                */
//	int tm_wday;        /* ����, range ��(0) to ��(6)      */
//	int tm_yday;        /* 1�� �� ��� ��, range 0 to 365  */
//	int tm_isdst;       /* ���Ÿ��                        */
//};



result* _result;

int result_count;

//����-����(����) head ���
Order* insert_ord;

//�������� �ѱ� ����ü head���
plan* head_Cod_n_Num;


int col = 1;

Order* creatNode_Order()
{
	Order* newNode;
	if ((newNode = (Order*)malloc(sizeof(Order))) == NULL) {
		return -1;
	}
	newNode->ACC_CODE = NULL;
	newNode->PRD_CODE = NULL;
	newNode->next = NULL;

	return newNode;
}

void creat_Order_List(Order* head, result* result_head, int num)
{

	
	int i = 0;
	
	//printf("��� �ܾȴ�\n");
	//printf("prd_code : %s\n", prd_code);
	result* cur;
	

	for (int i = 0; i < num; i++)
	{
		//Order* newNode = creatNode_Order();
		//printf("     ..%s\n", find->_string_data[i]);
	/*	if (strcmp(find->_string_data[i], prd_code) == 0)
		{*/
			//�׿� �ش��ϴ� ����ü �����ϱ�
			//printf("prd_code : %s\n", find->_string_data[i]);

		cur = result_head;
		while (1) {

			switch (cur->type) {
			case _VARCHAR:
				if (string_is_null(cur->_string_data[i]))
					printf("     (NULL)");
				else
				{
					if (strcmp(cur->name, "ACC_CODE") == 0)
					{
						//newNode->ACC_CODE = cur->_string_data[i];
						head->ACC_CODE = cur->_string_data[i];
						//strcpy(met->ACC_CODE,cur->_string_data[i]);
						//printf("                    ACC_CODE : %s\n ", met->ACC_CODE);
					}
					else if (strcmp(cur->name, "PRD_CODE") == 0)
					{
						head->PRD_CODE = cur->_string_data[i];
						//printf("                    PRD_CODE : %s\n ", head->PRD_CODE);
					}
					
					//���� ���Ͽ� insert�� ����ü ����Ʈ ���� �Ϸ�..����!
					//printf("       ,%s", cur->_string_data[i]);
				}
				break;
			}
			if (cur->next == 0)
				break;
			else
			{
				cur = cur->next;
			}

			//}

			printf("\n");
		}
		//printf("PRD_CODE->%s", newNode->PRD_CODE);
		//printf("ACC_CODE->%s", newNode->ACC_CODE);
		//������������ �����ؾ���
		//newNode->next = head->next;
		//printf("newNode%s\n", newNode->next->PRD_CODE);
		//head->next = newNode;
		
		//printf("PRD_CODE->%s", newNode->PRD_CODE);
		//printf("ACC_CODE->%s\n", newNode->ACC_CODE);
	}



}

void print_Node(Order* head)
{
	Order* cur;
	cur = head->next;
	Sleep(3000);

	printf("~~~printNode~~~\n");
	while (cur != NULL)
	{
		printf("PRD_COD : %s,  ", cur->PRD_CODE);
		printf("ACC_CODE : %s\n", cur->ACC_CODE);

		cur = cur->next;
	}
}

void print_Node_process(bomRes* head)
{
	bomRes* cur;
	cur = head->next;

	printf("~~~print_Node_process~~~\n");
	while (cur != NULL)
	{
		printf("PRD_COD : %s\n", cur->CODE);
		printf("PRD_VAL : %d\n", cur->AMOUNT);
		printf("ACC_CODE : %s\n\n", cur->ACC_CODE);

		cur = cur->next;
	}

}


//��û :: ���� ������ ����! ( ���� -> ǰ���ڵ�, �ŷ�ó�ڵ�, ����  ) 
//char* Request_Order(char* prd_code, int num)
//void Request_Order(char* prd_code, int num)
void material_to_prosess(plan* head, bomRes* met)
{
	plan* newNode = malloc(sizeof(plan));
	if (newNode == NULL)
	{
		return -1;
	}

	newNode->CODE = met->CODE;
	newNode->next = NULL;
	newNode->PLAN_PRODUCTION = 0;
	newNode->values = met->AMOUNT;


	newNode->next = head->next;
	head->next = newNode;



}



//plan����ü�� �Ѱ�����Ѵ�.
void Request_Order(bomRes* met_ord)
{

	
	
	file_column_free();
	printf("Request_Order\n");
	char values[30];
	
	plan* Cod_n_Num;
	//initialization ����ü
	
	if ((insert_ord = (Order*)malloc(sizeof(Order))) == NULL) {

		return -1;
	}
	insert_ord->ACC_CODE = NULL; insert_ord->PRD_CODE = NULL; insert_ord->D_Day = 0; insert_ord->NUM = 0; insert_ord->O_Day = 0;
	insert_ord->next = NULL;

	head_Cod_n_Num = (plan*)malloc(sizeof(plan));

	if (head_Cod_n_Num == NULL)
		return -1;

	head_Cod_n_Num->next = NULL;



	//if (_select(values, "ACC_CODE, BN_REGI_NUM, PRD_CODE, RorD", &select_result_str) == -1) {
	//	//if (_select("*", "ACC_CODE, BN_REGI_NUM, PRD_CODE", &select_result_str) == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}
	//else {
	//	//printf("%s\n\n", select_result_str);
	//	printf("\n...������ �����ϴ� �����Ͱ� �����մϴ�\n\n");
	//}


	
	//���籸��ü
		
	//bomRes* met = met_ord->next;

	bomRes* met = malloc(sizeof(bomRes));
	if (met == NULL)
		return -1;
	met = met_ord->next;
	met->ACC_CODE = NULL;
	//met->AMOUNT = NULL;
	//met->CODE = NULL;
	//met->next = NULL;


	while (met != NULL)
	{

		//material_to_prosess(head_Cod_n_Num,met);

		//printf("======================================\n");

		char* prd_code = met->CODE;
		//printf("met->CODE : %s", met->CODE);
		printf("prd_code : %s\n", prd_code);
		int amount = met->AMOUNT;

	


		//print_data();
		//print_data();
	
		strcpy(values, "PRD_CODE = '");
		strcat(values, prd_code);
		strcat(values, "'");


		//printf("values ..-> %s\n", values);
		//printf("������ ������ Ȯ��\n");

		if (initalizing("account") == -1)
		{
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		//Sleep(3000);
		if (_select(values, "ACC_CODE, BN_REGI_NUM, PRD_CODE, RorD", &select_result_str) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		else {
			
			printf("\n...������ �����ϴ� �����Ͱ� �����մϴ�\n\n");
		}


		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}


		result_print(_result, result_count);
		printf("\n\n");
		//free(values);

		Sleep(1000);

		creat_Order_List(insert_ord, _result, result_count);


		//Ư�� �÷� ����
		//printf("Ư���÷� ���� �ҽ� :: �����͸� ����ü�� ����, �Լ��� �Ѱܼ� ����file�� �����ϱ�\n\n");
		//�޸� �ڵ鸵�� �� ���� �������
		//if (!strcmp(_result->name, "PRD_CODE"))�̸�, �ŷ�ó ����Ʈ�� �ִ� �ŷ�ó �ڵ带 ���� ����ü�� �޾Ƽ� �װ� ���� ���Ϸ� ���ε��ؾ���.
		//���� �Լ��� ���� �����ؼ� �Ѱ�����.

		printf("\n\n");


		//return ACC_CODE; :: ���Ḯ��Ʈ ����� �ŷ�ó �ڵ� ��Ƽ� �ѱ��(�Լ�)

		//���ֱ���ü ������ Ȯ��
		//print_Node(insert_ord,insert_ord);
		//return main();

		//���ֳ��� ����
		storage_Order(insert_ord,amount);
		//print_data();

		met = met->next;
		result_free(_result, result_count);
		file_column_free();

	}
	
	//print_Node_process(met_ord);


	printf("���ָ� �����մϴ�.");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");

	//return;
	
	
}

//01 ���� -> ���� -> �ŷ�ó ��Ʈ
int storage_Order(Order* head, int num)
{
	
	file_column_free();
	if (initalizing("sample_Order") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else
	{
		print_data();
	}
	
	//������ : ���� ��¥, ������ : ����
	struct tm* t_order;
	time_t base = time(NULL);

	t_order = localtime(&base);

	//������ �� ��ǰ�� ���� ����
	unsigned char ord_date[5];


	char values[50];
	//Order* cur = head->next; //����� ���
	Order* cur = head;
	//������
	//t_order->tm_mon;
	//t_order->tm_mday;
	
	//������
	//t_order->tm_mon;
	//(t_order->tm_mday) + 1;

	/*
		���Ͽ� insert �ϱ� ���ؼ� �־�� �� �����Ͱ� �� �������� ������ �Ǿ���Ѵ�
		�����͵��� ����ü�� �����Ǿ��ִ�.

	*/

	printf("%d\n", t_order->tm_mon + 1);
	itoa(t_order->tm_mon + 1, ord_date, 10);
	//sprintf(ord_date, "%d", t_order->tm_mon + 1);	//��
	//printf("int to char -> %s\n", ord_date);
	strcpy(values, ord_date);
	itoa(t_order->tm_mday, ord_date, 10);	//��
	strcat(values, ord_date);
	strcat(values, ", ");
	//printf("values : %s\n", values);

	//������
	itoa(t_order->tm_mon + 1, ord_date, 10);		//��
	strcat(values, ord_date);
	itoa(t_order->tm_mday + 1, ord_date, 10);	//��
	strcat(values, ord_date);
	strcat(values, ", ");
	//printf("values : %s\n", values);

	//�ŷ�ó �ڵ�
	strcat(values, "'");
	strcat(values, cur->ACC_CODE);
	strcat(values, "'");
	strcat(values, ", ");
	//printf("values : %s\n", values);

	//���ֹ�ȣ :: INT TO CHAR
	itoa(t_order->tm_mon + 1, ord_date, 10);		//��
	strcat(values, ord_date);
	itoa(col++, ord_date, 10);		//���泭��
	strcat(values, ord_date);
	strcat(values, ", ");
	//printf("values : %s\n", values);

	//ǰ���ڵ� :: CHAR
	strcat(values, "'");
	strcat(values, cur->PRD_CODE);
	strcat(values, "'");
	strcat(values, ", ");
	//printf("values : %s\n", values);

	//���� :: INT TO CHAR
	itoa(num, ord_date, 10);			//����
	strcat(values, ord_date);



	//printf("values : %s\n", values);



	if (_insert(values) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	printf("������ �Է��� �����մϴ�..\n");
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
		�˻����...
	*/
} 



