#include "cereal.h"
#include <string.h>
#include <time.h>




void storage_Orders(Order* head, int num);

int result_count;

//����-����(����) head ���
Order* insert_ord;

//�������� �ѱ� ����ü head���
plan* head_Cod_n_Num;
result* _result;

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
	
	result* cur;
	cur = result_head;
	
	for (int i = 0; i < num; i++) {



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

						head->ACC_CODE = cur->_string_data[i];
						
					}
					else if (strcmp(cur->name, "PRD_CODE") == 0)
					{
						head->PRD_CODE = cur->_string_data[i];
						
					}

				}
				break;
			}
			if (cur->next == 0)
				break;
			else
			{
				cur = cur->next;
			}


			printf("\n");
		}

		printf("\n");
	}


}



//��û :: ���� ������ ����! ( ���� -> ǰ���ڵ�, �ŷ�ó�ڵ�, ����  ) 
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


void Request_Order(bomRes* met_ord)
{

	if (_create("pre_sample_Order", "O_DATE INT D_DATE INT ACC_CODE VARCHAR(10) ORDER_NUM INT PRD_CODE VARCHAR(10) NUM INT") == -1)
	{
		printf("%s\n", err_msg);
		return -1;
	}

	char values[30];

	plan* Cod_n_Num;

	//initialization ����ü

	if ((insert_ord = (Order*)malloc(sizeof(Order))) == NULL) {

		return -1;
	}
	insert_ord->ACC_CODE = NULL; insert_ord->PRD_CODE = NULL; 
	//insert_ord->D_Day = 0; insert_ord->NUM = 0; insert_ord->O_Day = 0;
	insert_ord->next = NULL;

	head_Cod_n_Num = (plan*)malloc(sizeof(plan));

	if (head_Cod_n_Num == NULL)
		return -1;

	head_Cod_n_Num->next = NULL;

	char* prd_code = NULL;
	int amount = 0;

	//���籸��ü :: �ŷ�ó �ڵ带 �ޱ� ����. sercer�� ������ ����.���� �������
	bomRes* met = malloc(sizeof(bomRes));
	if (met == NULL)
		return -1;
	met = met_ord->next;


	while (met != NULL)
	{
		system("cls");
	
		printf("��ġ : ���θ޴� -> ������� -> �����ȹ ���� -> ���ֿ�û\n\n");
		

		if (met->AMOUNT <= 0)
		{

			//system("cls");
			printf("������ ��û������ 0 �Դϴ�.\n");
			met = met->next;


		}
		else {


			prd_code = met->CODE;
			
			printf("ǰ�� �ڵ� : %s\n", prd_code);
			amount = met->AMOUNT;



			strcpy(values, "PRD_CODE = '");
			strcat(values, prd_code);
			strcat(values, "'");



			if (initalizing("account") == -1)
			{
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			Sleep(1000);
			if (_select(values, "ACC_CODE, BN_REGI_NUM, PRD_CODE, RorD", &select_result_str) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			else {

				printf("\n...ǰ���ڵ� ���� �ŷ�ó�� �����մϴ�\n\n");
			}

			if ((result_count = recv_result(&_result, select_result_str)) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			result_print(_result, result_count);
			printf("\n");
			file_column_free();
			Sleep(1000);


			//���� �Լ��� ���� �����ؼ� �Ѱ�����.
			creat_Order_List(insert_ord, _result, result_count);


			//���ֳ��� ����
			printf("���ֳ����� �����մϴ�..\n");
			Sleep(1000);
			storage_Orders(insert_ord, amount);


			met = met->next;

			Sleep(3000);
		}
	}

	system("cls");
	printf("����� ���� �����Դϴ�\n");



	if (initalizing("pre_sample_Order") == -1)
	{

		printf("%s\n", err_msg);

		file_column_free();

		return -1;

	}

	print_data();
	file_column_free();
	Sleep(1000);
	printf("���ָ� �����մϴ�.");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");

	return;
	
	
	
}
void current_Order_list(char* values)
{

	if (initalizing("pre_sample_Order") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert(values) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	print_data();
	Sleep(1000);
	file_column_free();

}

//01 ���� -> ���� -> �ŷ�ó ��Ʈ
void storage_Orders(Order* head, int* num)
{
	

	if (initalizing("sample_Order") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	//������ : ���� ��¥, ������ : ����
	struct tm* t_order;
	time_t base = time(NULL);

	t_order = localtime(&base);

	//������ �� ��ǰ�� ���� ����
	unsigned char ord_date[5];


	unsigned char values[50];
	//Order* cur = head->next; //����� ��� :: ���� ����
	Order* cur = head;

	/*
		���Ͽ� insert �ϱ� ���ؼ� �־�� �� �����Ͱ� �� �������� ������ �Ǿ���Ѵ�
		�����͵��� ����ü�� �����Ǿ��ִ�.

	*/

	//������
	itoa(t_order->tm_mon + 1, ord_date, 10);	//��
	strcpy(values, ord_date);
	itoa(t_order->tm_mday, ord_date, 10);	//��
	strcat(values, ord_date);
	strcat(values, ", ");

	//������
	itoa(t_order->tm_mon + 1, ord_date, 10);		//��
	strcat(values, ord_date);
	itoa(t_order->tm_mday + 1, ord_date, 10);	//��
	strcat(values, ord_date);
	strcat(values, ", ");

	//�ŷ�ó �ڵ�
	strcat(values, "'");
	strcat(values, cur->ACC_CODE);
	strcat(values, "'");
	strcat(values, ", ");

	//���ֹ�ȣ :: INT TO CHAR
	itoa(t_order->tm_mon + 1, ord_date, 10);		//��
	strcat(values, ord_date);
	itoa(col++, ord_date, 10);		//���泭��
	strcat(values, ord_date);
	strcat(values, ", ");

	//ǰ���ڵ� :: CHAR
	strcat(values, "'");
	strcat(values, cur->PRD_CODE);
	strcat(values, "'");
	strcat(values, ", ");

	//���� :: INT TO CHAR
	itoa(num, ord_date, 10);			//����
	strcat(values, ord_date);


	//��ü �������Ͽ� ���� ����
	if (_insert(values) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	file_column_free();
	//�� ���ֳ������� ������ �� ��ü ������ �ƴ� ������ ������ �����ֵ���
	printf("\n");

	current_Order_list(values);



}

//02. ���� -> ���� -> �����Է�(ǰ���ڵ�) -> �ŷ�ó ��� -> ����!
void all_Order_List()
{
	char key = NULL;
	if (initalizing("sample_Order") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	while (1)
	{
		
		if (key == '`')
		{
			printf("���θ޴��� ���ư��ϴ�");
			Sleep(500);
			printf(".");
			Sleep(500);
			printf(".");
			Sleep(500);
			printf(".");
			file_column_free();
			return main();
		}
		system("cls");
		printf("����� ���� �����Դϴ�\n");
		print_data();
		printf("(`) ��������");
		
		printf("\n->");
		scanf("%c", &key);
		//file_column_free();
		

		
	}
	
	
	//return;
} 




