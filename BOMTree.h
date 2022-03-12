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
//conditional에 맞는 BOM트리를 생성하여 리턴해주는 함수

int Show_BOM_ROOT_CODE_list();
int Show_BOM_CODE_list(char* _conditional);
BOM_LIST* _BOM_SEARCH(char* conditional, BOM_LIST* list);
BOM_LIST* recur_search(char* search_code, BOM_LIST* list);
//BOM 정전개를 하기 위해 필요한 함수

int Show_BACK_ABLE_NODE_CODE_list();
int Show_BOM_BACK_ABLE_NODE_CODE_list(char* conditional);
BOM_LIST* BOM_RESEARCH(char* conditional);
BOM_LIST* Make_LIST(result* result, int result_count, BOM_LIST* ROOT_LIST, char* target);
//BOM 역전개를 하기 위해 필요한 함수

BOM_LIST* BOM_CreateNode_list(BOM_LIST* list, Element1* ROOT_CODE, Element1* NODE_CODE, Element1* PRODUCT_NAME, Element2 REQ_NUM, Element1* M_CODE);
void Free_list(BOM_LIST* h);
//전개를 위해 필요한 연결리스트를 만드는 함수

BOM_TREE* BOM_CreateNode(Element1* ROOT_CODE, Element1* NODE_CODE, Element1* PRODUCT_NAME, Element2 REQ_NUM, Element1* M_CODE);
//추출된 결과 리스트의 개수 만큼 노드를 생성하는 함수

void BOM_ChangeNode(Element1* ROOT_CODE, Element1* NODE_CODE, Element1* PRODUCT_NAME, Element2 REQ_NUM);
//해당 노드의 REQ_NUM 값을 변경하는 함수

void BOM_DestroyNode(BOM_TREE* Node);
void BOM_DestroyTree(BOM_TREE* Root);
//DestroyTree 함수는 트리의 오른쪽 하위 Node부터 차례대로 메모리 해제를 하는 재귀구조의 함수

void BOM_AddChildNode(BOM_TREE* ParentNode, BOM_TREE* ChildNode);
// ParentNode의 차일드를 추가하는 함수
// - ParentNode의 차일드가 없을시 : ParentNode->LeftChild ChildNode
// - ParentNode의 차일드가 존재시 : ParentNode->LeftChild->RightSibling == NULL 인 Node에 ChildNode 연결

void BOM_Forward_PrintTree(BOM_TREE* CurNode, Element1* NODE_CODE);
void _BOM_Forward_PrintTree(BOM_TREE* CurNode, int Depth);
// 해당 노드를 기준으로 하여 하위 노드들을 모두 호출하는 정전개

void BOM_Backward_PrintTree(BOM_LIST* result);
// 해당 노드를 기준으로 하여 상위 노드들을 모두 호출하는 역전개

void BOM_Create_main();
int code_to_name(char* _conditional);
// BOM 파일에 데이터를 등록하는 함수

void BOM_Update_main();
// BOM 파일에 데이터를 수정하는 함수

void BOM_Delete_main();
// BOM 파일에 데이터를 삭제하는 함수


#endif // !BOMTREE_H