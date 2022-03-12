#include "cereal.h"
#include "BOMTree.h"
#include "UI.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <windows.h>

#define FILE_NAME "bom"

void base_information(void);	// ��������

void BOM_search_main()
{
	int input = 0;

	do
	{
		if (input < -1 || input > 3)
		{
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���");
			Sleep(1500);
		}
		system("cls");
		printf("��ġ : ���θ޴� -> ������� -> ������������ -> BOM ��ȸ\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     �޴��� �����ϼ���.    |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      1.BOM ������         |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      2.BOM ������         |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      0.��������           |\n");
		printf("\t\t\t-----------------------------\n\n");

		printf("\t\t\t\t �Է� :\n");
		printf("\t\t\t\t        ^");
		gotoxy(40, 13);

		scanf("%d", &input);
	}while (input < -1 || input>2);

	switch (input)
	{
	case -1:
	{
		system("cls");
		if (initalizing(FILE_NAME) == -1)
		{
			printf("bom������ �������� �ʽ��ϴ�\n");

			file_column_free();
			exit(1);
		}
		print_data();
		printf("\n");
		file_column_free();

		system("pause");
		BOM_search_main();
	}
	break;
	case 1:
	{
		//1.BOM ������
		system("cls");
		printf("��ġ : ���θ޴� -> ������� -> ������������ -> BOM ��ȸ -> BOM ������\n\n");
		char input_temp[100] = "";

		int list_count = Show_BOM_ROOT_CODE_list();

		if (!list_count)
			return;

		printf("BOM ������ �� ǰ���ڵ带 �Է��ϼ���. ");
		scanf("%s", &input_temp);

		char* search_code = (char*)malloc(sizeof(input_temp));
		if (search_code == NULL)
		{
			printf("�޸� ����");
			return;
		}
		strcpy(search_code, input_temp);

		BOM_TREE* result = BOM_SEARCH(search_code);

		if (result != NULL)
		{
			BOM_Forward_PrintTree(result, search_code);

			BOM_DestroyTree(result);
			system("pause");
		}

		free(search_code);
		BOM_search_main();
	}
	break;
	case 2:
	{
		//2.BOM ������
		system("cls");
		printf("��ġ : ���θ޴� -> ������� -> ������������ -> BOM ��ȸ -> BOM ������\n\n");
		char input_temp[100] = "";

		int list_count = Show_BACK_ABLE_NODE_CODE_list();

		if (!list_count)
			return;

		printf("BOM ������ �� ǰ���ڵ带 �Է��ϼ���. ");
		scanf("%s", &input_temp);

		char* search_code = (char*)malloc(sizeof(input_temp));
		if (search_code == NULL)
		{
			printf("�޸� ����");
			return;
		}
		strcpy(search_code, input_temp);

		BOM_LIST* result = BOM_RESEARCH(search_code);
		free(search_code);

		if (result == NULL)
		{
			printf("�˻��� ����� �����ϴ�.");
			Sleep(1500);
			system("cls");
			BOM_search_main();
		}

		BOM_Backward_PrintTree(result);
		Free_list(result);
		system("pause");
		BOM_search_main();
	}
	break;
	case 0:
	{
		//��������
		system("cls");
		base_information();
	}
	break;
	}
}

BOM_TREE* BOM_SEARCH(char* _conditional)
{
	BOM_TREE* ROOT = (BOM_TREE*)malloc(sizeof(BOM_TREE));
	if (ROOT == NULL) exit(1);

	//_conditional ��ǰ�� ã��
	{
		char* text1 = "ROOT_CODE = '";
		char* text2 = "'";
		char* conditional = (char*)malloc(sizeof(text1) + sizeof(_conditional) + sizeof(text2));
		if (conditional == NULL)
		{
			printf("�޸� ����");
			exit(1);
		}
		strcpy(conditional, text1);
		strcat(conditional, _conditional);
		strcat(conditional, text2);

		result* _result;
		int result_count;
		char* select_column = "PRODUCT_NAME";

		//BOM ���� ����
		if (initalizing(FILE_NAME) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return NULL;
		}

		//conditional ���ǿ� �´� select_result_str ���ϱ�
		if (_select(conditional, select_column, &select_result_str) == -1) {
			//printf("%s\n", err_msg);

			file_column_free();
			return NULL;
		}
		//���ǿ� �´� select_result_str�� �����Ͽ� PRODUCT_NAME �÷����� ���ϱ�
		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return NULL;
		}

		free(conditional);
		//result_print(_result, result_count);

		//PRODUCT_NAME �÷� ã��
		result* cur = _result;
		while ((strcmp(cur->name, "PRODUCT_NAME") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("M_CODE �÷��� �������� �ʽ��ϴ�.");

			file_column_free();
			exit(1);
		}

		strcpy(ROOT->PRODUCT_NAME, cur->_string_data[0]);

		result_free(_result, result_count);
		file_column_free();
	}

	//�ʱ�ȭ
	ROOT->LeftChild = NULL;					//�ʱ�ȭ
	strcpy(ROOT->M_CODE, pad_seprator);		//���ڵ� NULL
	strcpy(ROOT->NODE_CODE, _conditional);	//NODE�ڵ� ����
	//ROOT->PRODUCT_NAME;					//��ǰ�� ��⿡�� ������
	ROOT->REQ_NUM = 1;						//�ʱ�ȭ
	ROOT->RightSibling = NULL;				//�ʱ�ȭ
	strcpy(ROOT->ROOT_CODE, _conditional);	//NODE�ڵ� ����


	//������ ��� �����͵� ����� ���Ḯ��Ʈ�� �ӽ÷� ����
	BOM_LIST* list = NULL;
	list = recur_search(_conditional, list);		//�Է��� ��Ʈ ���� ������ ��带 ����� ���Ḯ��Ʈ��
	if (list == NULL)
	{
		printf("�˻��� ����� �����ϴ�.\n");
		Sleep(1500);
		return NULL;
	}
	system("cls");

	//list�� �� ���� ���ϱ�
	int count = 1;
	BOM_LIST* curre = list;
	while (curre->next != NULL)
	{
		//printf("%s\t%d\t%s\n", curre->NODE_CODE, curre->REQ_NUM, curre->M_CODE);
		curre = curre->next;
		count++;
	}
	//printf("%s\t%d\t%s\n", curre->NODE_CODE, curre->REQ_NUM, curre->M_CODE);

	int total = count + 1;
	//count+1 ���� ��ŭ�� ����ü �����͸� ������ ���� ������ Node�� ���� �Ҵ����� ����
	BOM_TREE** Node = (BOM_TREE**)malloc(sizeof(BOM_TREE*) * (total));
	if (Node == NULL)
	{
		printf("�޸� ����!");
		exit(0);
	}

	//count+1 ���� ��ŭ ��� ����
	int i = 0;
	while (curre->pre != NULL)
	{
		Node[i] = BOM_CreateNode(curre->ROOT_CODE, curre->NODE_CODE, curre->PRODUCT_NAME, curre->REQ_NUM, curre->M_CODE);

		curre = curre->pre;
		i++;
	}
	Node[i] = BOM_CreateNode(curre->ROOT_CODE, curre->NODE_CODE, curre->PRODUCT_NAME, curre->REQ_NUM, curre->M_CODE);
	Node[count] = BOM_CreateNode(ROOT->ROOT_CODE, ROOT->NODE_CODE, ROOT->PRODUCT_NAME, ROOT->REQ_NUM, ROOT->M_CODE);

	/*printf("NODE_CODE  REQ_NUM\tM_CODE\n");
	for (int i = 0; i < count+1; i++)
		printf("%8s\t%d\t%7s\n", Node[i]->NODE_CODE, Node[i]->REQ_NUM, Node[i]->M_CODE);*/

	for (int i = 0; i < (count + 1); i++)
	{
		int Mother_index = 0;
		//�������� M_CODE�� Mother_index����� NODE_CODE�� ���������� Mother_index ����
		while ((Mother_index < (count + 1)) && (strcmp(Node[i]->M_CODE, Node[Mother_index]->NODE_CODE) != 0))
			Mother_index++;

		//Node[Mother_index]�� �θ� ����, ���� ��带 �ڽĳ��� ����
		if ((Mother_index < (count + 1)) && (strcmp(Node[i]->M_CODE, Node[Mother_index]->NODE_CODE) == 0))
		{
			BOM_AddChildNode(Node[Mother_index], Node[i]);
			//printf("%d, %d\n", Mother_index, i);
		}
	}

	//���� ���� ����Ʈ free
	Free_list(list);

	return Node[count];
}

int Show_BOM_ROOT_CODE_list()	//BOM ���Ͽ��� ROOT�ڵ� ����Ʈ�� �̾ƿ�����
{
	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE, NODE_CODE, PRODUCT_NAME";

	//BOM ���� ����
	if (initalizing(FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	//��� �÷� ���ϱ�
	if (_select("*", select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}
	//��� �÷��� �����Ͽ� ROOT_CODE, PRODUCT_NAME �÷� ���ϱ�
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	if (result_count > 0)
	{
		printf("BOM�� ��ϵ� ����Ʈ�� ������ �����ϴ�\n\n");
		printf(" ǰ���ڵ�\tǰ��\n");
		printf("===================================\n");
		result* cur = _result;
		//result_print(_result, result_count);
		//system("pause");
		char* temp = "";
		for (int i = 0; i < result_count; i++)
		{
			Element1 ROOT_CODE[6] = { 0 };
			Element1 NODE_CODE[6] = { 0 };
			Element1 PRODUCT_NAME[30] = { 0 };

			cur = _result;
			while (cur != NULL && (strcmp(cur->name, "ROOT_CODE") != 0))
				cur = cur->next;
			if (cur == NULL)
			{
				printf("ROOT_CODE �÷��� �������� �ʽ��ϴ�.");
				exit(1);
			}
			strcpy(ROOT_CODE, cur->_string_data[i]);

			cur = _result;
			while (cur != NULL && (strcmp(cur->name, "NODE_CODE") != 0))
				cur = cur->next;
			if (cur == NULL)
			{
				printf("ROOT_CODE �÷��� �������� �ʽ��ϴ�.");
				exit(1);
			}
			strcpy(NODE_CODE, cur->_string_data[i]);

			if (strcmp(ROOT_CODE, NODE_CODE) == 0)
			{
				cur = _result;
				while (cur != NULL && (strcmp(cur->name, "PRODUCT_NAME") != 0))
					cur = cur->next;
				if (cur == NULL)
				{
					printf("PRODUCT_NAME �÷��� �������� �ʽ��ϴ�.");
					exit(1);
				}
				strcpy(PRODUCT_NAME, cur->_string_data[i]);

				printf("%7s %13s\n", ROOT_CODE, PRODUCT_NAME);
			}
		}
		printf("\n");
	}
	else
	{
		printf("��ϵ� BOM ����Ʈ�� �����ϴ�.\n");
		return 0;
	}

	file_column_free();
	result_free(_result, result_count);
	return result_count;
}

int Show_BOM_CODE_list(char* conditional)
{
	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE";

	//BOM ���� ����
	if (initalizing(FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return 0;
	}

	//��� �÷� ���ϱ�
	if (_select("*", select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return 0;
	}
	//��� �÷��� �����Ͽ� ROOT_CODE �÷� ���ϱ�
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return 0;
	}

	for (int i = 0; i < result_count; i++)
	{
		result* cur = _result;

		if (strcmp(cur->_string_data[i], conditional) == 0)
		{
			file_column_free();
			result_free(_result, result_count);
			return 0;
		}
	}

	file_column_free();
	result_free(_result, result_count);
	return 1;
}

BOM_LIST* _BOM_SEARCH(char* _conditional, BOM_LIST* list)
{
	char* text1 = "ROOT_CODE = '";
	char* text2 = "'";
	char* conditional = (char*)malloc(sizeof(text1) + sizeof(_conditional) + sizeof(text2));
	if (conditional == NULL)
	{
		printf("�޸� ����");
		exit(1);
	}
	strcpy(conditional, text1);
	strcat(conditional, _conditional);
	strcat(conditional, text2);

	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE, NODE_CODE, PRODUCT_NAME, REQ_NUM, M_CODE";

	//BOM ���� ����
	if (initalizing(FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	/*print_data();
	printf("\n");*/

	//conditional ���ǿ� �´� select_result_str ���ϱ�
	if (_select(conditional, select_column, &select_result_str) == -1) {
		//printf("%s\n", err_msg);

		file_column_free();
		return list;
	}
	//���ǿ� �´� select_result_str�� �����Ͽ� ROOT_CODE, NODE_CODE, PRODUCT_NAME, REQ_NUM, M_CODE �÷����� ���ϱ�
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	free(conditional);
	//result_print(_result, result_count);

	//M_CODE �÷����� ������ ���� NULL�� (ROOT�ڵ� ã�� ���ؼ�) �� ã��
	result* cur = _result;
	while ((strcmp(cur->name, "M_CODE") != 0) && cur != NULL)
		cur = cur->next;
	if (cur == NULL)
	{
		printf("M_CODE �÷��� �������� �ʽ��ϴ�.");
		exit(1);
	}
	int index = 0;
	while (!string_is_null(cur->_string_data[index]))
		index++;

	Element1 ROOT_CODE[6];
	Element1 NODE_CODE[6];
	Element1 PRODUCT_NAME[30];
	Element2 REQ_NUM;
	Element1 M_CODE[6];

	//result_count ���� ��ŭ�� ��� ����
	for (int i = 0; i < result_count; i++)
	{
		if (i == index)
			continue;

		cur = _result;
		while ((strcmp(cur->name, "ROOT_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("ROOT_CODE �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(ROOT_CODE, cur->_string_data[i]);


		cur = _result;
		while ((strcmp(cur->name, "NODE_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("NODE_CODE �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(NODE_CODE, cur->_string_data[i]);


		cur = _result;
		while ((strcmp(cur->name, "PRODUCT_NAME") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("PRODUCT_NAME �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(PRODUCT_NAME, cur->_string_data[i]);


		result* cur = _result;
		while ((strcmp(cur->name, "REQ_NUM") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("REQ_NUM �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		REQ_NUM = cur->_int_data[i];


		cur = _result;
		while ((strcmp(cur->name, "M_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("M_CODE �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(M_CODE, cur->_string_data[i]);

		list = BOM_CreateNode_list(list, ROOT_CODE, NODE_CODE, PRODUCT_NAME, REQ_NUM, M_CODE);
	}


	result_free(_result, result_count);
	file_column_free();

	return list;
}

BOM_LIST* recur_search(char* search_code, BOM_LIST* list)
{
	list = _BOM_SEARCH(search_code, list);

	BOM_LIST* curr = list;
	while (curr != NULL)
	{
		list = _BOM_SEARCH(curr->NODE_CODE, list);
		curr = curr->next;
	}

	return list;
}

int Show_BACK_ABLE_NODE_CODE_list()	//BOM ���Ͽ��� ������ ������ ����Ʈ ���
{
	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE, NODE_CODE, PRODUCT_NAME";

	//BOM ���� ����
	if (initalizing(FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	//��� �÷� ���ϱ�
	if (_select("*", select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}
	//��� �÷��� �����Ͽ� ROOT_CODE, NODE_CODE, PRODUCT_NAME �÷� ���ϱ�
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	if (result_count > 0)
	{
		printf("������ ���� ����Ʈ�� ������ �����ϴ�\n\n");
		printf("ǰ���ڵ�\tǰ��\n");
		printf("===================================\n");

		for (int i = 0; i < result_count; i++)
		{
			Element1 ROOT_CODE[6];
			Element1 NODE_CODE[6];

			result* cur = _result;
			while (strcmp(cur->name, "ROOT_CODE") != 0)
				cur = cur->next;
			if (cur == NULL)
			{
				printf("ROOT_CODE �÷��� �������� �ʽ��ϴ�.");
				file_column_free();
				return 0;
			}
			strcpy(ROOT_CODE, cur->_string_data[i]);

			cur = _result;
			while (strcmp(cur->name, "NODE_CODE") != 0)
				cur = cur->next;
			if (cur == NULL)
			{
				printf("NODE_CODE �÷��� �������� �ʽ��ϴ�.");
				file_column_free();
				return 0;
			}
			strcpy(NODE_CODE, cur->_string_data[i]);


			if (strcmp(ROOT_CODE, NODE_CODE) != 0)
			{
				
				//ǰ���ڵ� ���
				printf("%7s\t", NODE_CODE);

				//ǰ�� ���
				cur = _result;
				while (strcmp(cur->name, "PRODUCT_NAME") != 0)
					cur = cur->next;
				if (cur == NULL)
				{
					printf("PRODUCT_NAME �÷��� �������� �ʽ��ϴ�.");
					file_column_free();
					return 0;
				}
				printf("%13s\t", cur->_string_data[i]);

				printf("\n");
			}
		}
		printf("\n");
	}
	else
	{
		printf("��ϵ� BOM ����Ʈ�� �����ϴ�.\n");
		return 0;
	}

	file_column_free();
	result_free(_result, result_count);
	return result_count;
}

int Show_BOM_BACK_ABLE_NODE_CODE_list(char* conditional)
{
	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE, NODE_CODE, PRODUCT_NAME";

	//BOM ���� ����
	if (initalizing(FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	//��� �÷� ���ϱ�
	if (_select("*", select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}
	//��� �÷��� �����Ͽ� ROOT_CODE, NODE_CODE, PRODUCT_NAME �÷� ���ϱ�
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	if (result_count > 0)
	{
		for (int i = 0; i < result_count; i++)
		{
			Element1 ROOT_CODE[6];
			Element1 NODE_CODE[6];

			result* cur = _result;
			while (strcmp(cur->name, "ROOT_CODE") != 0)
				cur = cur->next;
			if (cur == NULL)
			{
				printf("ROOT_CODE �÷��� �������� �ʽ��ϴ�.");
				file_column_free();
				return 0;
			}
			strcpy(ROOT_CODE, cur->_string_data[i]);

			cur = _result;
			while (strcmp(cur->name, "NODE_CODE") != 0)
				cur = cur->next;
			if (cur == NULL)
			{
				printf("NODE_CODE �÷��� �������� �ʽ��ϴ�.");
				file_column_free();
				return 0;
			}
			strcpy(NODE_CODE, cur->_string_data[i]);


			if ((strcmp(ROOT_CODE, NODE_CODE) != 0) && (strcmp(NODE_CODE, conditional) == 0))
			{
				file_column_free();
				result_free(_result, result_count);
				return 0;
				
			}
		}

	}
	else
	{
		printf("��ϵ� BOM ����Ʈ�� �����ϴ�.\n");
		return 1;
	}

	file_column_free();
	result_free(_result, result_count);
	return 1;

}

BOM_LIST* BOM_RESEARCH(char* _conditional)
{
	BOM_LIST* ROOT_LIST = NULL;

	char* text1 = "ROOT_CODE = '";
	char* text2 = "'";
	char* conditional = (char*)malloc(sizeof(text1) + sizeof(_conditional) + sizeof(text2));
	if (conditional == NULL)
	{
		printf("�޸� ����");
		exit(1);
	}
	strcpy(conditional, text1);
	strcat(conditional, _conditional);
	strcat(conditional, text2);

	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE, NODE_CODE, PRODUCT_NAME, REQ_NUM, M_CODE";

	//BOM ���� ����
	if (initalizing(FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}
	//conditional ���ǿ� �´� select_result_str ���ϱ�
	if (_select("*", select_column, &select_result_str) == -1) {
		//printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}
	//���ǿ� �´� select_result_str�� �����Ͽ� ROOT_CODE, NODE_CODE, PRODUCT_NAME, REQ_NUM, M_CODE �÷����� ���ϱ�
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	free(conditional);

	//_conditional���� �����ؼ� ROOT������ ������ ����Ʈ ����
	ROOT_LIST =	Make_LIST(_result, result_count, ROOT_LIST, _conditional);

	file_column_free();
	result_free(_result, result_count); //�ָ�...
	return ROOT_LIST;
}

BOM_LIST* Make_LIST(result* _result, int result_count, BOM_LIST* ROOT_LIST, char* target)
{
	//Ÿ��ã��
	result* cur = _result;
	Element1 ROOT_CODE[6] = { 0 };
	Element1 NODE_CODE[6] = { 0 };
	Element1 _PRODUCT_NAME[30] = { 0 };
	Element2 REQ_NUM = 0;
	Element1 M_CODE[6] = { 0 };

	int overlap_count = 0;

	//ROOT�ڵ带 �˰� �ִ� target ã��
	for (int index = 0 ; index < result_count ; index++)
	{
		cur = _result;
		while ((strcmp(cur->name, "ROOT_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("ROOT_CODE �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(ROOT_CODE, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "NODE_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("NODE_CODE �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(NODE_CODE, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "PRODUCT_NAME") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("PRODUCT_NAME �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(_PRODUCT_NAME, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "REQ_NUM") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("REQ_NUM �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		REQ_NUM = cur->_int_data[index];

		cur = _result;
		while ((strcmp(cur->name, "M_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("M_CODE �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(M_CODE, cur->_string_data[index]);

		//NODE_CODE �÷��� NODE_NAME�� �ߺ����� ����(1�̸鼭, ���� ��Ʈ�� ���� ��� ������Ʈ ���)
		cur = _result;
		while ((strcmp(cur->name, "NODE_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("NODE_CODE �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		for (int i = 0; i < result_count; i++)
		{
			if (strcmp(cur->_string_data[i], NODE_CODE) == 0)
				overlap_count++;
			if (overlap_count >= 2)
				break;
		}

		//��Ʈ�ڵ�� ����ڵ尡 �ٸ��鼭 ����ڵ尡 target�� ���� ��� || (Ȥ�� ���� ��Ʈ��� �� ���)
		if (((strcmp(ROOT_CODE, NODE_CODE) != 0) && (strcmp(NODE_CODE, target) == 0)) || ((overlap_count == 1) && (strcmp(ROOT_CODE, NODE_CODE) == 0) && (strcmp(target, NODE_CODE) == 0)))
		{
			ROOT_LIST = BOM_CreateNode_list(ROOT_LIST, ROOT_CODE, NODE_CODE, _PRODUCT_NAME, REQ_NUM, M_CODE);
			break;
		}
	}

	//���� ��Ʈ����� ���
	if ((overlap_count == 1) && (strcmp(ROOT_CODE, NODE_CODE) == 0 && (strcmp(target, NODE_CODE) == 0)))
	{
		return ROOT_LIST;
	}
	//���� �����͸� ã���� ��� �ش� �������� ���ڵ带 �̿��Ͽ� ���
	else if((strcmp(ROOT_CODE, NODE_CODE) != 0) && (strcmp(NODE_CODE, target) == 0))
	{
		ROOT_LIST = Make_LIST(_result, result_count, ROOT_LIST, ROOT_CODE);
	}

	return ROOT_LIST;
}

BOM_LIST* BOM_CreateNode_list(BOM_LIST* list, Element1* ROOT_CODE, Element1* NODE_CODE, Element1* PRODUCT_NAME, Element2 REQ_NUM, Element1* M_CODE)
{
	BOM_LIST* newNode = (BOM_LIST*)malloc(sizeof(BOM_LIST));
	if (newNode == NULL)
	{
		printf("�޸� ����\n");
		exit(1);
	}

	strcpy(newNode->ROOT_CODE, ROOT_CODE);
	strcpy(newNode->NODE_CODE, NODE_CODE);
	strcpy(newNode->PRODUCT_NAME, PRODUCT_NAME);
	newNode->REQ_NUM = REQ_NUM;
	strcpy(newNode->M_CODE, M_CODE);

	newNode->next = NULL;
	newNode->pre = NULL;

	if (list == NULL)
	{
		list = newNode;
	}
	else
	{
		BOM_LIST* cur = list;
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = newNode;
		newNode->pre = cur;
	}

	return list;
}

void Free_list(BOM_LIST* h)
{
	if (h == NULL)
		printf("������ ��尡 �������� �ʽ��ϴ�.");
	else
	{
		BOM_LIST* delNode = h;
		BOM_LIST* delNextNode = h->next;

		while (delNextNode != NULL)
		{
			delNode = delNextNode;
			delNextNode = delNextNode->next;

			free(delNode);
		}
		free(h);
	}
}

BOM_TREE* BOM_CreateNode(Element1* ROOT_CODE, Element1* NODE_CODE, Element1* PRODUCT_NAME, Element2 REQ_NUM, Element1* M_CODE)
{
	BOM_TREE* NewNode = (BOM_TREE*)malloc(sizeof(BOM_TREE));
	if (NewNode == NULL)   exit(1);

	strcpy(NewNode->ROOT_CODE, ROOT_CODE);
	strcpy(NewNode->NODE_CODE, NODE_CODE);
	strcpy(NewNode->PRODUCT_NAME, PRODUCT_NAME);
	NewNode->REQ_NUM = REQ_NUM;
	strcpy(NewNode->M_CODE, M_CODE);

	NewNode->LeftChild = NULL;
	NewNode->RightSibling = NULL;

	return NewNode;
}

void BOM_ChangeNode(Element1* ROOT_CODE, Element1* NODE_CODE, Element1* PRODUCT_NAME, Element2 REQ_NUM)
{

}

void BOM_DestroyNode(BOM_TREE* Node)
{
	free(Node);
}

void BOM_DestroyTree(BOM_TREE* Root)
{
	if (Root->RightSibling != NULL)      //RightSibling�� �����
		BOM_DestroyTree(Root->RightSibling);      //RightSibling�� ����Ű�� ��带 �Ű������� ���ȣ��

	if (Root->LeftChild != NULL)      //LeftChild�� �����
		BOM_DestroyTree(Root->LeftChild);      //LeftChild�� ����Ű�� ��带 �Ű������� ���ȣ��


	Root->LeftChild = NULL;
	Root->RightSibling = NULL;

	BOM_DestroyNode(Root);
}

void BOM_AddChildNode(BOM_TREE* ParentNode, BOM_TREE* ChildNode)
{
	if (ParentNode->LeftChild == NULL)
		ParentNode->LeftChild = ChildNode;
	else
	{
		BOM_TREE* TempNode = ParentNode->LeftChild;
		while (TempNode->RightSibling != NULL)
			TempNode = TempNode->RightSibling;

		TempNode->RightSibling = ChildNode;
	}
}

void BOM_Forward_PrintTree(BOM_TREE* CurNode, Element1* NODE_CODE)
{
	system("cls");
	if (strcmp(CurNode->NODE_CODE, NODE_CODE) == 0)
	{
		printf("%s�� ������ ����� ������ �����ϴ�.\n\n", NODE_CODE);
		printf("LEVEL\t ǰ���ڵ�\tǰ��\t�ʿ����\n");
		printf("=========================================\n");
		_BOM_Forward_PrintTree(CurNode, 0);
		return;
	}
	if (CurNode->LeftChild != NULL)
		BOM_Forward_PrintTree(CurNode->LeftChild, NODE_CODE);
	if (CurNode->RightSibling != NULL)
		BOM_Forward_PrintTree(CurNode->RightSibling, NODE_CODE);
}

void _BOM_Forward_PrintTree(BOM_TREE* CurNode, int Depth)
{
	//int i = 0; // �鿩����� Ʈ���� Depth ǥ�� 
	//for (i = 0; i < Depth; i++)
	//   printf(" ");

	printf("%4d\t%8s %13s %5d\n", Depth, CurNode->NODE_CODE, CurNode->PRODUCT_NAME, CurNode->REQ_NUM);

	if (CurNode->LeftChild != NULL) // ���ϵ� �����
		_BOM_Forward_PrintTree(CurNode->LeftChild, Depth + 1); // ��� ȣ�� - Node�� Child�� ���̴� Node�� Depth�� +1 �� ���� ����

	if (CurNode->RightSibling != NULL) // ���� �����
		_BOM_Forward_PrintTree(CurNode->RightSibling, Depth); // ��� ȣ�� - ���� ����� ���̴� ��� ����(���� ������ ���
}

void BOM_Backward_PrintTree(BOM_LIST* result)
{
	system("cls");
	BOM_LIST* cur = result;
	if (cur != NULL)
	{
		printf("%s�� ������ ����� ������ �����ϴ�.\n\n", cur->NODE_CODE);
		printf("LEVEL\t ǰ���ڵ�\tǰ��\t�ʿ����\n");
		printf("=========================================\n");

		int level_count = 0;
		while (cur->next != NULL)
		{
			printf("%4d\t%8s %13s %5d\n", level_count++, cur->NODE_CODE, cur->PRODUCT_NAME, cur->REQ_NUM);
			cur = cur->next;
		}
		printf("%4d\t%8s %13s %5d\n", level_count++, cur->NODE_CODE, cur->PRODUCT_NAME, cur->REQ_NUM);
	}
}

void BOM_record_main()
{
	int input = 0;

	do
	{
		if (input < 0 || input > 3)
		{
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���");
			Sleep(1500);
		}
		system("cls");
		printf("��ġ : ���θ޴� -> ������� -> ������������ -> BOM ���\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     �޴��� �����ϼ���.    |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      1.BOM �űԵ��       |\n");
		//printf("\t\t\t-----------------------------\n");
		//printf("\t\t\t|      2.BOM ����           |\n");
		//printf("\t\t\t-----------------------------\n");
		//printf("\t\t\t|      3.BOM ����           |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      0.��������           |\n");
		printf("\t\t\t-----------------------------\n\n");
		printf("\t\t\t\t �Է� :\n");
		printf("\t\t\t\t        ^");
		gotoxy(40, 11);

		scanf("%d", &input);
	} while (input < -1 || input > 3);


	switch (input)
	{
	case -1:
	{
		//1.BOM ���� �ʱ�ȭ
		init_bom();
		system("pause");
		system("cls");
		BOM_record_main();
	}
	break;
	case 1:
	{
		//1.BOM �űԵ�� 
		BOM_Create_main();
		system("cls");
		BOM_record_main();
	}
	break;
	case 2:
	{
		//2.BOM ����
		BOM_Update_main();
		system("pause");
		system("cls");
		BOM_record_main();
	}
	break;
	case 3:
	{
		//3.BOM ���� 
		BOM_Delete_main();
		system("pause");
		system("cls");
		BOM_record_main();
	}
	break;
	case 0:
	{
		//��������
		system("cls");
		base_information();
	}
	break;
	}
}

void BOM_Create_main()
{
	char input_code1[10] = { 0 };
	char input_code2[10] = { 0 };

	//���ڵ� �˻�
	do
	{
		system("cls");
		printf("��ġ : ������� -> ������������ -> BOM ��� -> BOM �űԵ�� -> ���ڵ� �˻�\n\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     BOM ���Ͽ� �ű�       |\n");
		printf("\t\t\t|     ��� �� ��ǰ�� ǰ��   |\n");
		printf("\t\t\t|     �ڵ带 �Է��ϼ���.    |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n\n");

		printf("\t\t\t   �Է� :\n");
		printf("\t\t\t          ^");
		gotoxy(34, 10);
		scanf("%s", input_code1);

		if (strcmp(input_code1, "`") == 0)
			break;

		if (!code_to_name(input_code1))
		{
			printf("\t\t\t  �˻��� ����� �����ϴ�.\n");
			Sleep(1500);
		}
		else if (!Show_BOM_CODE_list(input_code1))
		{
			printf("\t\t\t  �̹� ��ϵ� ���� �Դϴ�.\n");
			printf("\t\t\t  ���� �� �����ϼ���.!\n");
			Sleep(1500);
		}
	} while (!code_to_name(input_code1) || !Show_BOM_CODE_list(input_code1));


	if (strcmp(input_code1, "`") == 0)
		return;

	Element1 ROOT_CODE[6] = { 0 };
	strcpy(ROOT_CODE, input_code1);

	Element1 _NODE_CODE[10][6] = { 0 };
	int index = 0;
	//���ڵ� �˻�
	do
	{
		if(index == 0)
			system("cls");

		gotoxy(0, 0);
		printf("��ġ : ������������ -> BOM ��� -> BOM �űԵ�� -> ���ڵ� �˻� -> ���ڵ� �˻�\n\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     %s�� ���ڵ��      |\n", ROOT_CODE);
		printf("\t\t\t|     ����� ��ǰ�� ǰ��    |\n");
		printf("\t\t\t|     �ڵ带 �Է��ϼ���.    |\n");
		printf("\t\t\t|                           |\n");
		printf("\t\t\t|*    ��� �Ϸ� Ű : `     *|\n");
		printf("\t\t\t-----------------------------\n\n");
		printf("\t\t\t   �Է� :\n");
		printf("\t\t\t          ^");
		gotoxy(34, 11);
		printf("        ");
		gotoxy(34, 11);
		scanf("%s", input_code2);

		if (strcmp(input_code2, "`") == 0)
			break;

		if (!code_to_name(input_code2))
		{
			printf("\t\t\t  �˻��� ����� �����ϴ�.\n");
			Sleep(1500);
		}
		if (!Show_BOM_BACK_ABLE_NODE_CODE_list(input_code2))
		{
			printf("\t\t\t  �̹� ��ϵ� ���� �Դϴ�.\n");
			printf("\t\t\t  ���� �� �����ϼ���.!\n");
			Sleep(1500);
		}
		strcpy(_NODE_CODE[index], input_code2);
		int count = 0;

		printf("\n\t\t\t-----------------------------\n");
		while (count <= index)
		{
			printf("\t\t\t|*     ���ڵ� : %s       *|\n", _NODE_CODE[count]);
			printf("\t\t\t-----------------------------\n");
			count++;
		}

		index++;
	} while (!code_to_name(input_code2) || !Show_BOM_BACK_ABLE_NODE_CODE_list(input_code2) || strcmp(input_code2, "`") != 0);


	Element2 req_num[10] = { 0 };
	for (int i = 0; i < index; i++)
	{
		if (i == 0)
			system("cls");

		gotoxy(0, 0);
		printf("��ġ : BOM ��� -> BOM �űԵ�� -> ���ڵ� �˻� -> ���ڵ� �˻� -> �ʿ���� �Է�\n\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     %s�� �ʿ������    |\n", _NODE_CODE[i]);
		printf("\t\t\t|     �Է��ϼ���.           |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n\n");
		printf("\t\t\t   �Է� :\n");
		printf("\t\t\t          ^");
		gotoxy(34, 9);
		printf("        ");
		gotoxy(34, 9);
		scanf("%d", &req_num[i]);

		int count = 0;

		printf("\n\t\t\t-----------------------------\n");
		while (count <= i)
		{
			printf("\t\t\t|*   ���ڵ�%d �ʿ���� : %d  *|\n", count+1, req_num[count]);
			printf("\t\t\t-----------------------------\n");
			count++;
		}
	}

	Sleep(500);
	system("cls");
	printf("��ġ : BOM ��� -> BOM �űԵ�� -> ���ڵ� �˻� -> ���ڵ� �˻� -> �ʿ���� �Է�\n\n");
	printf("\t\t   ------------------------------------------\n");
	printf("\t\t   ROOT_CODE     NODE_CODE   REQ_NUM   M_CODE\n");
	printf("\t\t   ==========================================\n");

	printf("\t\t     %s\t  %s\t\t%d\t%s\n", ROOT_CODE, input_code1, 1, "(NULL)");
	for (int i = 0; i < index; i++)
		printf("\t\t     %s\t  %s\t\t%d\t%s\n", ROOT_CODE, _NODE_CODE[i], req_num[i], ROOT_CODE);
	printf("\t\t   ------------------------------------------\n\n\n");
	printf("    �Է��� ������ ������ �����ϴ�. ");
	system("pause");


	//code�� �´� ��ǰ�� �̾ƿ���
	char product_text[10][40] = { 0 };
	for (int i = 0; i < index; i++)
		strcpy(product_text[i], code_to_name_list(_NODE_CODE[i]));

	//req_num �� ���ڷ� ����
	char req_text[10][40] = { 0 };
	for (int i = 0; i < index; i++)
		_itoa(req_num[i], req_text[i], 10);

	char final_text[10][40] = { 0 };
	//���� ��ġ��
	for (int i = 0; i < index; i++)
	{
		strcpy(final_text[i], "'");
		strcat(final_text[i], ROOT_CODE);
		strcat(final_text[i], "','");
		strcat(final_text[i], _NODE_CODE[i]);
		strcat(final_text[i], "','");
		strcat(final_text[i], product_text[i]);
		strcat(final_text[i], "',");
		strcat(final_text[i], req_text[i]);
		strcat(final_text[i], ",'");
		strcat(final_text[i], ROOT_CODE);
		strcat(final_text[i], "'");
	}

	char root_text[40] = { 0 };
	strcpy(root_text, "'");
	strcat(root_text, ROOT_CODE);
	strcat(root_text, "','");
	strcat(root_text, ROOT_CODE);
	strcat(root_text, "','");
	strcat(root_text, code_to_name_list(ROOT_CODE));
	strcat(root_text, "',");
	strcat(root_text, "1");
	strcat(root_text, ",");
	strcat(root_text, "NULL");
	strcat(root_text, "'");

	//����ϱ����� ���� ù �ڵ尡 0000 �̸� �����ϰ� ����ϱ�
	if (is_first_data_0())
		delete_data_0();

	//����ϱ�
	if (initalizing(FILE_NAME) == -1)
	{
		printf("bom������ �������� �ʽ��ϴ�\n");

		file_column_free();
		exit(1);
	}

	if (_insert(root_text) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	for (int i = 0; i < index; i++)
	{
		if (_insert(final_text[i]) == -1)
		{
			printf("%s\n", err_msg);

			file_column_free();
			exit(1);
		}
	}

	printf("    ���Ͽ� ��� �Ǿ����ϴ�. ");
	file_column_free();
	system("pause");
}

int is_first_data_0()
{
	result* _result;
	int result_count;

	if (initalizing(FILE_NAME) == -1)
	{
		printf("bom������ �������� �ʽ��ϴ�\n");

		file_column_free();
		exit(1);
	}
	if (_select("ROOT_CODE = '00000'", "ROOT_CODE, NODE_CODE, PRODUCT_NAME, REQ_NUM, M_CODE", &select_result_str) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return 0;
	}
	if ((result_count = recv_result(&_result, select_result_str)) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	Element1 ROOT_CODE[6] = { 0 };
	Element1 NODE_CODE[6] = { 0 };
	Element1 PRODUCT_NAME[30] = { 0 };
	Element2 REQ_NUM = 0;
	Element1 M_CODE[6] = { 0 };

	result* cur = _result;

	for (int index = 0; index < result_count; index++)
	{
		cur = _result;
		while ((strcmp(cur->name, "ROOT_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("ROOT_CODE �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(ROOT_CODE, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "NODE_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("NODE_CODE �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(NODE_CODE, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "PRODUCT_NAME") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("PRODUCT_NAME �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(PRODUCT_NAME, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "REQ_NUM") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("REQ_NUM �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		REQ_NUM = cur->_int_data[index];

		cur = _result;
		while ((strcmp(cur->name, "M_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("M_CODE �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(M_CODE, cur->_string_data[index]);
	}

	if (strcmp(ROOT_CODE, "00000") == 0 && strcmp(NODE_CODE, "00000") == 0 && strcmp(PRODUCT_NAME, "00000") == 0 && (REQ_NUM == 0) && strcmp(M_CODE, "00000") == 0)
	{
		file_column_free();
		result_free(_result, result_count);
		return 1;
	}

	file_column_free();
	result_free(_result, result_count);
	return 0;
}

void delete_data_0()
{
	if (initalizing(FILE_NAME) == -1)
	{
		printf("bom������ �������� �ʽ��ϴ�\n");

		file_column_free();
		return;
	}
	if (_delete("ROOT_CODE = '00000'") == -1)
	{
		//printf("%s\n", err_msg);

		file_column_free();
		return;
	}

	file_column_free();
}

char* code_to_name_list(char* _conditional)
{
	char* text1 = "CODE = '";
	char* text2 = "'";
	char* conditional = (char*)malloc(sizeof(text1) + sizeof(_conditional) + sizeof(text2));
	if (conditional == NULL)
	{
		printf("�޸� ����");
		exit(1);
	}
	strcpy(conditional, text1);
	strcat(conditional, _conditional);
	strcat(conditional, text2);

	result* _result;
	int result_count;

	//char* conditional = temp;
	char* select_column = "NAME";

	if (initalizing("list") == -1)
	{
		//printf("%s\n", err_msg);

		file_column_free();
		return 0;
	}
	//printf("%s", conditional);

	if (_select(conditional, select_column, &select_result_str) == -1)
	{
		file_column_free();
		return 0;
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1)
	{
		//printf("%s\n", err_msg);

		file_column_free();
		return 0;
	}

	static char re_cha[30] = { 0 };
	strcpy(re_cha, _result->_string_data[0]);

	file_column_free();
	result_free(_result, result_count);

	return re_cha;
}

int code_to_name(char* _conditional)
{
	char* text1 = "CODE = '";
	char* text2 = "'";
	char* conditional = (char*)malloc(sizeof(text1) + sizeof(_conditional) + sizeof(text2));
	if (conditional == NULL)
	{
		printf("�޸� ����");
		exit(1);
	}
	strcpy(conditional, text1);
	strcat(conditional, _conditional);
	strcat(conditional, text2);


	result* _result;
	int result_count;

	//char* conditional = temp;
	char* select_column = "NAME";

	if (initalizing("list") == -1)
	{
		//printf("%s\n", err_msg);

		file_column_free();
		return 0;
	}
	//printf("%s", conditional);

	if (_select(conditional, select_column, &select_result_str) == -1)
	{
		file_column_free();
		return 0;
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1)
	{
		//printf("%s\n", err_msg);

		file_column_free();
		return 0;
	}

	//printf("%s", _result->_string_data[0]);

	file_column_free();
	result_free(_result, result_count);
	return 1;
}

void BOM_Update_main()
{
	system("cls");
	printf("��ġ : ���θ޴� -> ������� -> ������������ -> BOM ��� -> BOM ����\n\n");





}

void BOM_Delete_main()
{
	system("cls");
	printf("��ġ : ���θ޴� -> ������� -> ������������ -> BOM ��� -> BOM ����\n\n");

	print_data();
	printf("\n");
	file_column_free();
}

void init_bom()
{ 
	if (_create(FILE_NAME, "ROOT_CODE VARCHAR(6) NODE_CODE VARCHAR(6) PRODUCT_NAME VARCHAR(30) REQ_NUM INT M_CODE VARCHAR(6)") == -1)
	{
		printf("%s\n", err_msg);

		return;
	}
	if (initalizing("bom") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return;
	}

	if (_insert("'00000','00000','00000',0,'00000'") == -1)
		{
		printf("%s\n", err_msg);

		file_column_free();
		return;
	}
	file_column_free();
}
