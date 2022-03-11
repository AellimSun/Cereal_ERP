#define _CRT_SECURE_NO_WARNINGS
#include "cereal.h"
#include "BOMTree.h"
#include "UI.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#pragma warning (disable : 6385)
#pragma warning (disable : 6386)

#define FILE_NAME "BOM_SAMPLE_3"

void base_information(void);	// ��������

void BOM_search_main()
{
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




	int input;

	scanf("%d", &input);

	while (input < 0 || input>2)
	{
		printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���");
		Sleep(1000);
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
	}

	switch (input)
	{
	case 1:
	{
		//1.BOM ������
		system("cls");
		char input_temp[100] = "";

		if (!Show_BOM_ROOT_CODE_list())
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

		BOM_Forward_PrintTree(result, search_code);

		free(search_code);
		system("pause");
		BOM_search_main();
	}
	break;
	case 2:
	{

		//2.BOM ������
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

int Show_BOM_ROOT_CODE_list()	//BOM ���Ͽ��� ROOT�ڵ� ����Ʈ�� �̾ƿ�����
{
	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE";

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
	//��� �÷��� �����Ͽ� ROOT_CODE �÷� ���ϱ�
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	if (result_count > 0)
	{
		printf("BOM�� ��ϵ� ����Ʈ�� ������ �����ϴ�\n\n");
		printf("ǰ���ڵ�\tǰ��\n");
		printf("===================================\n");
		result* cur = _result;
		char* temp = "";
		for (int i = 0; i < result_count - 1; i++)
		{
			if (strcmp(temp, cur->_string_data[i]) != 0)
				printf("%8s\n", cur->_string_data[i]);
			temp = cur->_string_data[i];
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
	return 1;
}

/*{
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
		char* select_column = "NODE_CODE, REQ_NUM, M_CODE";

		//BOM ���� ����
		if (initalizing(FILE_NAME) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			exit(1);
		}

		print_data();
		printf("\n");

		//conditional ���ǿ� �´� select_result_str ���ϱ�
		if (_select(conditional, select_column, &select_result_str) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			exit(1);
		}
		//���ǿ� �´� select_result_str�� �����Ͽ� NODE_CODE, REQ_NUM, M_CODE �÷����� ���ϱ�
		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			exit(1);
		}

		free(conditional);
		printf("\n\n");
		result_print(_result, result_count);
		printf("\n\n");

		//result_count ���� ��ŭ�� ����ü �����͸� ������ ���� ������ Node�� ���� �Ҵ����� ����
		BOM_TREE** Node = (BOM_TREE**)malloc(sizeof(BOM_TREE*) * result_count);
		if (Node == NULL)
		{
			printf("�޸� ����");
			exit(1);
		}

		Element2 REQ_NUM;
		Element1 NODE_CODE[6];
		Element1 M_CODE[6];


		//result_count ���� ��ŭ�� ��� ����
		for (int i = 0; i < result_count; i++)
		{
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
			while ((strcmp(cur->name, "M_CODE") != 0) && cur != NULL)
				cur = cur->next;
			if (cur == NULL)
			{
				printf("M_CODE �÷��� �������� �ʽ��ϴ�.");
				file_column_free();
				exit(1);
			}
			strcpy(M_CODE, cur->_string_data[i]);


			Node[i] = BOM_CreateNode(REQ_NUM, NODE_CODE, M_CODE);
		}
		file_column_free();

		//����� ���(M_CODE�� NODE_CODE)�� Ȱ���Ͽ� ��尣 �����Ͽ� Ʈ�� ���� (���� ���� ������ �������� ����)
		for (int i = result_count - 1; i >= 0; i--)
		{
			int Mother_index = 0;
			//�������� M_CODE�� Mother_index����� NODE_CODE�� ���������� Mother_index ����
			while ((Mother_index < result_count) && (strcmp(Node[i]->M_CODE, Node[Mother_index]->NODE_CODE) != 0))
				Mother_index++;

			//Node[Mother_index]�� �θ� ����, ���� ��带 �ڽĳ��� ����
			if ((Mother_index < result_count) && (strcmp(Node[i]->M_CODE, Node[Mother_index]->NODE_CODE) == 0))
			{
				BOM_AddChildNode(Node[Mother_index], Node[i]);
				//printf("%d, %d\n", Mother_index, i);
			}
		}

		result_free(_result, result_count);

		return Node[0];	//�ش� ��Ʈ��带 ����
	}*/

BOM_TREE* BOM_SEARCH(char* _conditional)
{
	system("cls");
	BOM_TREE* ROOT = (BOM_TREE*)malloc(sizeof(BOM_TREE));
	if (ROOT == NULL) exit(1);

	ROOT->REQ_NUM = 1;						//�ʱ�ȭ
	strcpy(ROOT->M_CODE, pad_seprator);		//���ڵ� NULL
	strcpy(ROOT->NODE_CODE, _conditional);	//NODE�ڵ� ����
	ROOT->LeftChild = NULL;					//�ʱ�ȭ
	ROOT->RightSibling = NULL;				//�ʱ�ȭ

	//������ ��� �����͵� ����� ���Ḯ��Ʈ�� �ӽ÷� ����
	BOM_LIST* list = NULL;
	list = recur_search(_conditional, list);		//�Է��� ��Ʈ ���� ������ ��带 ����� ���Ḯ��Ʈ��

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


	//count+1 ���� ��ŭ�� ����ü �����͸� ������ ���� ������ Node�� ���� �Ҵ����� ����
	BOM_TREE** Node = (BOM_TREE**)malloc(sizeof(BOM_TREE*) * (count + 1));
	if (Node == NULL)
	{
		printf("�޸� ����!");
		exit(0);
	}

	/*Element2 REQ_NUM;
	Element1 NODE_CODE[6];
	Element1 M_CODE[6];
*/

	//count+1 ���� ��ŭ ��� ����
	int i = 0;
	while (curre->pre != NULL)
	{
		/*printf("%5s\t", curre->NODE_CODE);
		printf("%5d\t", curre->REQ_NUM);
		printf("%5s\n", curre->M_CODE);*/
		Node[i] = BOM_CreateNode(curre->REQ_NUM, curre->NODE_CODE, curre->M_CODE);

		curre = curre->pre;
		i++;
	}
	Node[i] = BOM_CreateNode(curre->REQ_NUM, curre->NODE_CODE, curre->M_CODE);
	Node[count] = BOM_CreateNode(ROOT->REQ_NUM, ROOT->NODE_CODE, ROOT->M_CODE);

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
	char* select_column = "NODE_CODE, REQ_NUM, M_CODE";

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
	//���ǿ� �´� select_result_str�� �����Ͽ� NODE_CODE, REQ_NUM, M_CODE �÷����� ���ϱ�
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


	Element2 REQ_NUM;
	Element1 NODE_CODE[6];
	Element1 M_CODE[6];

	//result_count ���� ��ŭ�� ��� ����
	for (int i = 0; i < result_count; i++)
	{
		if (i == index)
			continue;

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
		while ((strcmp(cur->name, "M_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("M_CODE �÷��� �������� �ʽ��ϴ�.");
			file_column_free();
			exit(1);
		}
		strcpy(M_CODE, cur->_string_data[i]);

		list = BOM_CreateNode_list(list, REQ_NUM, NODE_CODE, M_CODE);
	}
	file_column_free();

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

BOM_LIST* BOM_CreateNode_list(BOM_LIST* list, Element2 REQ_NUM, Element1* NODE_CODE, Element1* M_CODE)
{
	BOM_LIST* newNode = (BOM_LIST*)malloc(sizeof(BOM_LIST));
	if (newNode == NULL)
	{
		printf("�޸� ����\n");
		exit(1);
	}

	newNode->REQ_NUM = REQ_NUM;
	strcpy(newNode->M_CODE, M_CODE);
	strcpy(newNode->NODE_CODE, NODE_CODE);
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

BOM_TREE* BOM_CreateNode(Element2 REQ_NUM, Element1* NODE_CODE, Element1* M_CODE)
{
	BOM_TREE* NewNode = (BOM_TREE*)malloc(sizeof(BOM_TREE));
	if (NewNode == NULL)   exit(1);

	NewNode->REQ_NUM = REQ_NUM;
	strcpy(NewNode->NODE_CODE, NODE_CODE);
	strcpy(NewNode->M_CODE, M_CODE);

	NewNode->LeftChild = NULL;
	NewNode->RightSibling = NULL;

	return NewNode;
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

void BOM_record_main()
{

}

void BOM_record(char* values)
{

}

void BOM_Forward_PrintTree(BOM_TREE* CurNode, Element1* NODE_CODE)
{
	system("cls");
	if (strcmp(CurNode->NODE_CODE, NODE_CODE) == 0)
	{
		printf("%s�� ������ ����� ������ �����ϴ�.\n\n", NODE_CODE);
		printf("LEVEL\t  ǰ���ڵ�\t�ʿ����\n");
		printf("=================================\n");
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
	//   printf("   ");

	printf("%4d\t%8s\t%5d\n", Depth, CurNode->NODE_CODE, CurNode->REQ_NUM);

	if (CurNode->LeftChild != NULL) // ���ϵ� �����
		_BOM_Forward_PrintTree(CurNode->LeftChild, Depth + 1); // ��� ȣ�� - Node�� Child�� ���̴� Node�� Depth�� +1 �� ���� ����

	if (CurNode->RightSibling != NULL) // ���� �����
		_BOM_Forward_PrintTree(CurNode->RightSibling, Depth); // ��� ȣ�� - ���� ����� ���̴� ��� ����(���� ������ ���
}


void BOM_Backward_PrintTree(BOM_TREE* CurNode, Element1* NODE_CODE)
{
	if (strcmp(CurNode->NODE_CODE, NODE_CODE) == 0)
	{
		_BOM_Backward_PrintTree(CurNode, 0);
		return;
	}
	if (CurNode->LeftChild != NULL)
		BOM_Backward_PrintTree(CurNode->LeftChild, NODE_CODE);
	if (CurNode->RightSibling != NULL)
		BOM_Backward_PrintTree(CurNode->RightSibling, NODE_CODE);
}

void _BOM_Backward_PrintTree(BOM_TREE* CurNode, int Depth)
{

}


void BOM_ChangeNode(Element1* ROOT_CODE, Element1* NODE_CODE, Element2 REQ_NUM)
{

}