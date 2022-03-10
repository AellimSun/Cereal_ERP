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
//conditional에 맞는 BOM트리를 생성하여 리턴해주는 함수

BOM_TREE* BOM_CreateNode(Element2 REQ_NUM, Element1* NODE_CODE, Element1* M_CODE);
//추출된 결과 리스트의 개수 만큼 노드를 생성하는 함수

void BOM_ChangeNode(Element1* ROOT_CODE, Element1* NODE_CODE, Element2 REQ_NUM);
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

void BOM_Backward_PrintTree(BOM_TREE* CurNode, Element1* NODE_CODE);
void _BOM_Backward_PrintTree(BOM_TREE* CurNode, int Depth);
// 해당 노드를 기준으로 하여 상위 노드들을 모두 호출하는 역전개


void BOM_record_main();
// BOM 파일에 데이터를 등록하기 위한 등록 메인 함수

void BOM_record(char* values);
// BOM 파일에 데이터를 등록하는 함수

#endif // !BOMTREE_H