#pragma once
#ifndef BOMTREE_H
#define BOMTREE_H

#include <stdio.h>
#include <stdlib.h>
#include "local.h"

typedef char Element1;
typedef int Element2;

typedef struct _BOM_TREE
{
	struct _BOM_TREE* LeftChild;
	struct _BOM_TREE* RightSibling;

	Element1 ROOT_CODE[6];
	Element1 NODE_CODE[6];
	Element1 PRODUCT_NAME[30];
	Element2 REQ_NUM;
	Element1 M_CODE[6];
}BOM_TREE;

typedef struct _BOM_LIST
{
	struct _BOM_LIST* next;
	struct _BOM_LIST* pre;

	Element1 ROOT_CODE[6];
	Element1 NODE_CODE[6];
	Element1 PRODUCT_NAME[30];
	Element2 REQ_NUM;
	Element1 M_CODE[6];
}BOM_LIST;


void BOM_search_main();

BOM_TREE* BOM_SEARCH(char* conditional);
//conditional�� �´� BOMƮ���� �����Ͽ� �������ִ� �Լ�

int Show_BOM_ROOT_CODE_list();
int Show_BOM_CODE_list(char* _conditional);
BOM_LIST* _BOM_SEARCH(char* conditional, BOM_LIST* list);
BOM_LIST* recur_search(char* search_code, BOM_LIST* list);
//BOM �������� �ϱ� ���� �ʿ��� �Լ�

int Show_BACK_ABLE_NODE_CODE_list();
int Show_BOM_BACK_ABLE_NODE_CODE_list(char* conditional);
BOM_LIST* BOM_RESEARCH(char* conditional);
BOM_LIST* Make_LIST(result* result, int result_count, BOM_LIST* ROOT_LIST, char* target);
//BOM �������� �ϱ� ���� �ʿ��� �Լ�

BOM_LIST* BOM_CreateNode_list(BOM_LIST* list, Element1* ROOT_CODE, Element1* NODE_CODE, Element1* PRODUCT_NAME, Element2 REQ_NUM, Element1* M_CODE);
void Free_list(BOM_LIST* h);
//������ ���� �ʿ��� ���Ḯ��Ʈ�� ����� �Լ�

BOM_TREE* BOM_CreateNode(Element1* ROOT_CODE, Element1* NODE_CODE, Element1* PRODUCT_NAME, Element2 REQ_NUM, Element1* M_CODE);
//����� ��� ����Ʈ�� ���� ��ŭ ��带 �����ϴ� �Լ�

void BOM_ChangeNode(Element1* ROOT_CODE, Element1* NODE_CODE, Element1* PRODUCT_NAME, Element2 REQ_NUM);
//�ش� ����� REQ_NUM ���� �����ϴ� �Լ�

void BOM_DestroyNode(BOM_TREE* Node);
void BOM_DestroyTree(BOM_TREE* Root);
//DestroyTree �Լ��� Ʈ���� ������ ���� Node���� ���ʴ�� �޸� ������ �ϴ� ��ͱ����� �Լ�

void BOM_AddChildNode(BOM_TREE* ParentNode, BOM_TREE* ChildNode);
// ParentNode�� ���ϵ带 �߰��ϴ� �Լ�
// - ParentNode�� ���ϵ尡 ������ : ParentNode->LeftChild ChildNode
// - ParentNode�� ���ϵ尡 ����� : ParentNode->LeftChild->RightSibling == NULL �� Node�� ChildNode ����

void BOM_Forward_PrintTree(BOM_TREE* CurNode, Element1* NODE_CODE);
void _BOM_Forward_PrintTree(BOM_TREE* CurNode, int Depth);
// �ش� ��带 �������� �Ͽ� ���� ������ ��� ȣ���ϴ� ������

void BOM_Backward_PrintTree(BOM_LIST* result);
// �ش� ��带 �������� �Ͽ� ���� ������ ��� ȣ���ϴ� ������

void BOM_Create_main();
int code_to_name(char* _conditional);
// BOM ���Ͽ� �����͸� ����ϴ� �Լ�

void BOM_Update_main();
// BOM ���Ͽ� �����͸� �����ϴ� �Լ�

void BOM_Delete_main();
// BOM ���Ͽ� �����͸� �����ϴ� �Լ�


#endif // !BOMTREE_H