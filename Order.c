#include "cereal.h"
//#include <stdlib.h>
//#define _GNU_SOURCE
#include <string.h>

typedef struct _order
{

	char* ACC_CODE; //�迭���� �ּҰ��� ����Ų��.
	char* PRD_CODE; //�迭���� �ּҰ��� ����Ų��.
	int O_Day;
	int D_Day;
	int NUM;
	
	struct _order* next;

}Order;

//typedef struct _acc_code
//{
//
//	char* ACC_CODE; //�迭���� �ּҰ��� ����Ų��.
//
//	struct _acc_code* next;
//
//}ACC_CODE;
//
//typedef struct _prd_code
//{
//
//	char* PRD_CODE; //�迭���� �ּҰ��� ����Ų��.
//
//	struct _prd_code* next;
//
//}PRD_CODE;

result* _result;
result* find;
int result_count;

result* cur;
Order* insert_ord;//����-����(����) head ���

Order* creatNode_Order()
{
	Order* newNode;
	if ((newNode = (Order*)malloc(sizeof(Order))) == NULL) {
		return -1;
	}
	newNode->ACC_CODE = NULL;
	newNode->PRD_CODE = NULL;

	return newNode;
}

void creat_Order_List(int num, char* prd_code)
{

	
	int i = 0;

	while (i < num)
	{
		printf("result_count : %d\n", i);
		Order* newNode = creatNode_Order();
		//printf("     ..%s\n", find->_string_data[i]);
		if (strcmp(find->_string_data[i], prd_code) == 0)
		{
			//�׿� �ش��ϴ� ����ü �����ϱ�
			//printf("prd_code : %s\n", find->_string_data[i]);

			cur = _result;
			while (1) {


				printf("\t\t\ncur %d\n", i);
				switch (cur->type) {
					/*case _INT:
						if (int_is_null(cur->_int_data[i]))
							printf("     (NULL)");
						else
							printf("     %d", cur->_int_data[i]);
						break;
					case _FLOAT:
						if (float_is_null(cur->_float_data[i]))
							printf("     (NULL)");
						else
							printf("     %.5f", cur->_float_data[i]);
						break;
					case _DOUBLE:
						if (double_is_null(cur->_double_data[i]))
							printf("     (NULL)");
						else
							printf("     %.12lf", cur->_double_data[i]);
						break;
					case _CHAR:
						if (char_is_null(cur->_char_data[i]))
							printf("     (NULL)");
						else
							printf("     %c", cur->_char_data[i]);
						break;*/
				case _VARCHAR:
					if (string_is_null(cur->_string_data[i]))
						printf("     (NULL)");
					else
					{
						if (strcmp(cur->name, "ACC_CODE") == 0)
						{
							newNode->ACC_CODE = cur->_string_data[i];
							printf("                    newNode->ACC_CODE : %s\n ", newNode->ACC_CODE);
						}
						else if (strcmp(cur->name, "PRD_CODE") == 0)
						{
							newNode->PRD_CODE = cur->_string_data[i];
							printf("                    newNode->PRD_CODE : %s\n ", newNode->PRD_CODE);
						}
						//���� �Լ��� ���� �����ؼ� �Ѱ�����.

						//���� ���Ͽ� insert�� ����ü ����Ʈ ���� �Ϸ�

						printf("       ,%s", cur->_string_data[i]);
					}
					break;
				}
				if (cur->next == 0)
					break;
				else
				{
					//_result = _result->next;
					cur = cur->next;
				}

			}

			printf("\n");
		}
		i++;
		newNode->next = insert_ord->next;
		insert_ord->next = newNode;

	}



}

void print_Node()
{
	Order* cur;
	cur = insert_ord->next;
	printf("printNode\n");
	while (cur != NULL)
	{
		printf("PRD_COD : %s,  ", cur->PRD_CODE);
		printf("ACC_CODE : %s\n", cur->ACC_CODE);

		cur = cur->next;
	}
}

//��û :: ���� ������ ����! ( ���� -> ǰ���ڵ�, �ŷ�ó�ڵ�, ����  ) 
char* Request_Order(char* prd_code, int num)
{
	char* values;
	
	//initialization ����ü
	//insert_ord = (Order*)malloc(sizeof(Order));

	if ((insert_ord = (column*)malloc(sizeof(column))) == NULL) {

		return -1;
	}

	insert_ord->ACC_CODE = NULL; insert_ord->PRD_CODE = NULL; insert_ord->D_Day = 0; insert_ord->NUM = 0; insert_ord->O_Day = 0;
	insert_ord->next = 0;
	

	/* ���ǹ��� ���ڷ� �ؼ� ���Ͽ��� ã�°� �ȵ� */

	/*
		 ���翡�� ǰ�� �ڵ�, �ŷ�ó �ڵ�, ������ �޾ƿӴ�
		 �ŷ�ó ���Ϸ� �� ǰ���ڵ带 �Ѱ���
	 
	 while(1)
	 {
	 
		 if(�ŷ�ó����.ǰ���ڵ� == ����.ǰ���ڵ�)
		 if(strcmp(�ŷ�ó����.ǰ���ڵ�, ����.ǰ���ڵ�) == 0)
		 {
				
				//��Ī�� ����ü �ʿ��Ѱ�?

				_select("PRD_CODE = prd_code", *,&select_result_str) 

				�ش� ǰ���ڵ带 �����ϴ� �ŷ�ó �÷� ��ü ���

				printf("%s\n\n", select_result_str);

	 
				�������Ͽ� �������� ������Ʈ 
	 
				������   ������    ǰ���ڵ�   �ŷ�ó�ڵ�   ����
				================================================
			    NULL     NULL       NULL       NULL        NULL    
	 
				return �����Լ��� ����, �ŷ�ó �ڵ常 ����? :: �������� ���� �ʿ�
		 }
		 else
		 {
				�ش� ǰ���� ����ϴ� �ŷ�ó�� �������� �ʽ��ϴ�.
				( Ȩ ) ȭ������ ���ư��ϴ�. 
		 }


	}

	 */
	//if (initalizing("sample_Client") == -1) 
	if (initalizing("account") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	//print_data();
	values = malloc(sizeof(prd_code) * 2);
	strcpy(values, "PRD_CODE=");
	strcat(values, prd_code);

	printf("������ ������ Ȯ��\n");
	if (_select(values, "ACC_CODE, BN_REGI_NUM, PRD_CODE", &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		printf("%s\n\n", select_result_str);
		printf("\n...������ �����ϴ� �����Ͱ� �����մϴ�\n\n");
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}



	result_print(_result, result_count);
	printf("\n\n");
	
	//if ((result_count = recv_result(&_result, select_result_str)) == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	


	//Ư�� �÷� ����
	//printf("Ư���÷� ���� �ҽ� :: �����͸� ����ü�� ����, �Լ��� �Ѱܼ� ����file�� �����ϱ�\n\n");
	
	if ((find = find_result(_result, "PRD_CODE")) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		result_free(_result, result_count);
		return -1;
	}

	//if (!strcmp(_result->name, "PRD_CODE"))�̸�, �ŷ�ó ����Ʈ�� �ִ� �ŷ�ó �ڵ带 ���� ����ü�� �޾Ƽ� �װ� ���� ���Ϸ� ���ε��ؾ���.
	//
	creat_Order_List(result_count, prd_code);

	
	{
		//int i = 0;
		//while (i < result_count)
		//{
		//	Order* newNode = creatNode_Order();
		//	printf("result_count : %d\n", i);
		//	//printf("     ..%s\n", find->_string_data[i]);
		//	if (strcmp(find->_string_data[i], prd_code) == 0)
		//	{
		//		//�׿� �ش��ϴ� ����ü �����ϱ�
		//		//printf("prd_code : %s\n", find->_string_data[i]);

		//		cur = _result;
		//		while (1) {


		//			printf("\t\t\ncur %d\n", i);
		//			switch (cur->type) {
		//				/*case _INT:
		//					if (int_is_null(cur->_int_data[i]))
		//						printf("     (NULL)");
		//					else
		//						printf("     %d", cur->_int_data[i]);
		//					break;
		//				case _FLOAT:
		//					if (float_is_null(cur->_float_data[i]))
		//						printf("     (NULL)");
		//					else
		//						printf("     %.5f", cur->_float_data[i]);
		//					break;
		//				case _DOUBLE:
		//					if (double_is_null(cur->_double_data[i]))
		//						printf("     (NULL)");
		//					else
		//						printf("     %.12lf", cur->_double_data[i]);
		//					break;
		//				case _CHAR:
		//					if (char_is_null(cur->_char_data[i]))
		//						printf("     (NULL)");
		//					else
		//						printf("     %c", cur->_char_data[i]);
		//					break;*/
		//			case _VARCHAR:
		//				if (string_is_null(cur->_string_data[i]))
		//					printf("     (NULL)");
		//				else
		//				{
		//					if (strcmp(cur->name, "ACC_CODE") == 0)
		//					{
		//						newNode->ACC_CODE = cur->_string_data[i];
		//						printf("                    newNode->ACC_CODE : %s\n ", newNode->ACC_CODE);
		//					}
		//					else if (strcmp(cur->name, "PRD_CODE") == 0)
		//					{
		//						newNode->PRD_CODE = cur->_string_data[i];
		//						printf("                    newNode->PRD_CODE : %s\n ", newNode->PRD_CODE);
		//					}
		//					//���� �Լ��� ���� �����ؼ� �Ѱ�����.

		//					//���� ���Ͽ� insert�� ����ü ����Ʈ ���� �Ϸ�

		//					printf("       ,%s", cur->_string_data[i]);
		//				}
		//				break;
		//			}
		//			if (cur->next == 0)
		//				break;
		//			else
		//			{
		//				//_result = _result->next;
		//				cur = cur->next;
		//			}

		//		}

		//		printf("\n");
		//	}
		//	i++;
		//	newNode->next = insert_ord->next;
		//	insert_ord->next = newNode;

		//}
	}
	printf("\n\n");

	
	//return ACC_CODE; :: ���Ḯ��Ʈ?
	
	print_Node();
	
	file_column_free();
	result_free(_result, result_count);
	free(values);
	
}

//01 ���� -> ���� -> �ŷ�ó ��Ʈ
char* storage_Order(char* acc_code, int num)
{

	/*
		���Ͽ� insert �ϱ� ���ؼ� �־�� �� �����Ͱ� �� �������� ������ �Ǿ���Ѵ�
		�����͵��� ����ü�� �����Ǿ��ִ�.

	*/
	char* values;
	Order* cur = insert_ord->next; //����� ���
	while (cur != 0)
	{
		//����ü �迭�� �� char�� ����, ����ȯ�Ͽ� ����.
		//����ü�迭�� ����. �ŷ�ó���� 
		
		// !!! �迭���� �ּҰ��� ����Ų�� !!!
		Order *newOrder = creatNode_Order();
		//����ȯ �� �Լ�

		//�����̷��� �����ϴ� ����
		//int _update(char* conditional, char* set) {
		strcpy(newOrder->ACC_CODE, cur->ACC_CODE);
		strcpy(newOrder->PRD_CODE, cur->PRD_CODE);
		newOrder->NUM = num;

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
		strcat(values, newOrder->ACC_CODE);
		//strcat(values, "NULL");
		strcat(values, "', ");
		strcat(values, "'");
		strcat(values, newOrder->PRD_CODE);
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
		cur = cur->next;
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
		�˻����...
	*/
} 



