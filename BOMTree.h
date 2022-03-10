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

	Element2 REQ_NUM;
	Element1 NODE_CODE[6];
	Element1 M_CODE[6];
}BOM_TREE;

BOM_TREE* BOM_SEARCH(/*char* conditional*/);
//conditional�� �´� BOMƮ���� �����Ͽ� �������ִ� �Լ�

BOM_TREE* BOM_CreateNode(Element2 REQ_NUM, Element1* NODE_CODE, Element1* M_CODE);
//����� ��� ����Ʈ�� ���� ��ŭ ��带 �����ϴ� �Լ�

void BOM_ChangeNode(Element1* ROOT_CODE, Element1* NODE_CODE, Element2 REQ_NUM);
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

void BOM_Backward_PrintTree(BOM_TREE* CurNode, Element1* NODE_CODE);
void _BOM_Backward_PrintTree(BOM_TREE* CurNode, int Depth);
// �ش� ��带 �������� �Ͽ� ���� ������ ��� ȣ���ϴ� ������


void BOM_record_main();
// BOM ���Ͽ� �����͸� ����ϱ� ���� ��� ���� �Լ�

void BOM_record(char* values);
// BOM ���Ͽ� �����͸� ����ϴ� �Լ�

#endif // !BOMTREE_H