#define _CRT_SECURE_NO_WARNINGS
#include "cereal.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#pragma warning (disable : 6031)
#pragma warning (disable : 6385)
#pragma warning (disable : 6386)

#define FILE_NAME "BOM_SAMPLE_3"


void BOM_search_main()
{
	system("cls");

	int input;
	printf("�޴��� �����ϼ���.\n");
	printf("1.BOM ������\n");
	printf("2.BOM ������\n");
	printf("0.��������\n");

	scanf("%d", &input);

	while (input <0||input>2)
	{
		printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���");
		Sleep(1000);
		system("cls");

		printf("�޴��� �����ϼ���.\n");
		printf("1.BOM ������\n");
		printf("2.BOM ������\n");
		printf("0.��������\n");

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
		system("cls");

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



BOM_TREE* BOM_SEARCH(char* _conditional)
{
	char* text1 = "ROOT_CODE = '";
	char* text2 = "'";
	char* conditional = (char*)malloc( sizeof(text1) + sizeof(_conditional) + sizeof(text2) );
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
	//result_print(_result, result_count);

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
	/*
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
		while (strcmp(cur->_string_data[index], " NULL") != 0)
			index++;
		strcpy(M_CODE, cur->_string_data[index]);


		//index�� �̿��Ͽ� NODE_CODE ����
		cur = _result;
		while ((strcmp(cur->name, "NODE_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("NODE_CODE �÷��� �������� �ʽ��ϴ�.");
			exit(1);
		}
		strcpy(ROOT_CODE, cur->_string_data[index]);

		//index�� �̿��Ͽ� REQ_NUM ����
		cur = _result;
		while ((strcmp(cur->name, "REQ_NUM") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("REQ_NUM �÷��� �������� �ʽ��ϴ�.");
			exit(1);
		}
		REQ_NUM = cur->_int_data[index];

		//Root_Node ����
		BOM_TREE* SEARCH_BOM = BOM_Create_Root_Node(ROOT_CODE, REQ_NUM, );

		//
		BOM_TREE* child_list = NULL;
	*/

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

	/*for (int i = 0; i < result_count; i++)
	{
		printf("%5s\t", Node[i]->NODE_CODE);
		printf("%5d\t", Node[i]->REQ_NUM);
		printf("%5s\n", Node[i]->M_CODE);
	}*/

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

	////�ϼ��� Ʈ������ ��Ʈ��� ã��
	//int index = 0;
	//while (!string_is_null(Node[index]->M_CODE))
	//	index++;

	return Node[0];	//�ش� ��Ʈ��带 ����
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
	if (strcmp(CurNode->NODE_CODE, NODE_CODE) == 0)
	{
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