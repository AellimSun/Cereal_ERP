#include "cereal.h"
//#include <stdlib.h>
//#define _GNU_SOURCE
#include <string.h>

typedef struct _order
{
	int O_Day;
	int D_Day;
	char *ACC_CODE; //�迭���� �ּҰ��� ����Ų��.
	char *PRD_CODE; //�迭���� �ּҰ��� ����Ų��.
	int NUM;
	
	struct _order* next;

}Order;

result* _result;
result* find;
int result_count;

result* cur;
Order* insert_ord;
char* values;

//��û :: ���� ������ ����! ( ���� -> ǰ���ڵ�, �ŷ�ó�ڵ�, ����  ) 
char* Request_Order(char* prd_code, int num)
{
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
	if (initalizing("D:\\00_Bird_00\\ý��\\project\\Cereal\\Clanguage\\01_ERP\\sample_Client") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	//print_data();
	values = malloc(sizeof(prd_code) * 2);
	strcpy(values, "PRD_CODE=");
	strcat(values, prd_code);

	printf("������ ������ Ȯ��\n");
	if (_select(values, "ACC_CODE, PRD_CODE, BN_REGI_NUM, NAME", &select_result_str) == -1) {
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
	int i = 0;

	
	


	//Ư�� �÷� ����
	printf("Ư���÷� ���� �ҽ� :: �����͸� ����ü�� ����, �Լ��� �Ѱܼ� ����file�� �����ϱ�\n\n");


	if ((find = find_result(_result, "PRD_CODE")) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		result_free(_result, result_count);
		return -1;
	}
	while (i< result_count)
	{
		//printf("     ..%s\n", find->_string_data[i]);
		if (strcmp(find->_string_data[i], prd_code) == 0)
		{
			//�׿� �ش��ϴ� ����ü �����ϱ�
			//printf("prd_code : %s\n", find->_string_data[i]);

			cur = _result;
			while (1) {
				switch (cur->type) {
				case _INT:
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
					break;
				case _VARCHAR:
					if (string_is_null(cur->_string_data[i]))
						printf("     (NULL)");
					else
					{
						printf("       /%s", cur->name);
						if (strcmp(cur->name, "ACC_CODE") == 0)
						{
							strcpy(insert_ord->ACC_CODE, cur->name);
						}
						if (strcmp(cur->name, "PRD_CODE") == 0)
						{
							strcpy(insert_ord->PRD_CODE, cur->name);
						}

						printf("       /%s", cur->_string_data[i]);
					}
					break;
				}
				if (cur->next == 0)
					break;
				else
					cur = cur->next;
			}

			printf("\n");
		}
		i++;

	}
	printf("\n\n");

	printf("Ư���÷� ���� �ҽ� ��\n");
	
	
	
	
	file_column_free();
	result_free(_result, result_count);
	free(values);
	
}

//01 ���� -> ���� -> �ŷ�ó ��Ʈ
char* storage_Order(char* prd_code, char* acc_code, int num)
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
		�˻����...
	*/
} 



