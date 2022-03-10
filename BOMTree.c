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
	printf("메뉴를 선택하세요.\n");
	printf("1.BOM 정전개\n");
	printf("2.BOM 역전개\n");
	printf("0.이전으로\n");

	scanf("%d", &input);

	while (input <0||input>2)
	{
		printf("잘못된 입력입니다. 다시 입력해주세요");
		Sleep(1000);
		system("cls");

		printf("메뉴를 선택하세요.\n");
		printf("1.BOM 정전개\n");
		printf("2.BOM 역전개\n");
		printf("0.이전으로\n");

		scanf("%d", &input);
	}

	switch (input)
	{
	case 1:
	{
		//1.BOM 정전개
		system("cls");
		char input_temp[100] = "";

		if (!Show_BOM_ROOT_CODE_list())
			return;
		printf("BOM 정전개 할 품명코드를 입력하세요. ");
		scanf("%s", &input_temp);

		char* search_code = (char*)malloc(sizeof(input_temp));
		if (search_code == NULL)
		{
			printf("메모리 부족");
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
		//2.BOM 역전개
	}
		break;
	case 0:
	{
		//이전으로
		system("cls");
		base_information();
	}
		break;
	}
}

int Show_BOM_ROOT_CODE_list()	//BOM 파일에서 ROOT코드 리스트를 뽑아오세요
{
	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE";

	//BOM 파일 열기
	if (initalizing(FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	//모든 컬럼 구하기
	if (_select("*", select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}
	//모든 컬럼을 가공하여 ROOT_CODE 컬럼 구하기
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	if (result_count > 0)
	{
		printf("BOM에 등록된 리스트는 다음과 같습니다\n\n");
		printf("품목코드\t품명\n");
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
		printf("등록된 BOM 리스트가 없습니다.\n");
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
		printf("메모리 부족");
		exit(1);
	}
	strcpy(conditional, text1);
	strcat(conditional, _conditional);
	strcat(conditional, text2);

	result* _result;
	int result_count;
	char* select_column = "NODE_CODE, REQ_NUM, M_CODE";

	//BOM 파일 열기
	if (initalizing(FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	/*print_data();
	printf("\n");*/

	//conditional 조건에 맞는 select_result_str 구하기
	if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}
	//조건에 맞는 select_result_str을 가공하여 NODE_CODE, REQ_NUM, M_CODE 컬럼으로 구하기
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	free(conditional);
	//result_print(_result, result_count);

	//result_count 개수 만큼의 구조체 포인터를 가지는 이중 포인터 Node를 동적 할당으로 정의
	BOM_TREE** Node = (BOM_TREE**)malloc(sizeof(BOM_TREE*) * result_count);
	if (Node == NULL)
	{
		printf("메모리 부족");
		exit(1);
	}

	Element2 REQ_NUM;
	Element1 NODE_CODE[6];
	Element1 M_CODE[6];
	/*
		//M_CODE 컬럼에서 데이터 값이 NULL인 (ROOT코드 찾기 위해서) 값 찾기
		result* cur = _result;
		while ((strcmp(cur->name, "M_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("M_CODE 컬럼이 존재하지 않습니다.");
			exit(1);
		}
		int index = 0;
		while (strcmp(cur->_string_data[index], " NULL") != 0)
			index++;
		strcpy(M_CODE, cur->_string_data[index]);


		//index를 이용하여 NODE_CODE 정의
		cur = _result;
		while ((strcmp(cur->name, "NODE_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("NODE_CODE 컬럼이 존재하지 않습니다.");
			exit(1);
		}
		strcpy(ROOT_CODE, cur->_string_data[index]);

		//index를 이용하여 REQ_NUM 정의
		cur = _result;
		while ((strcmp(cur->name, "REQ_NUM") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("REQ_NUM 컬럼이 존재하지 않습니다.");
			exit(1);
		}
		REQ_NUM = cur->_int_data[index];

		//Root_Node 생성
		BOM_TREE* SEARCH_BOM = BOM_Create_Root_Node(ROOT_CODE, REQ_NUM, );

		//
		BOM_TREE* child_list = NULL;
	*/

	//result_count 개수 만큼의 노드 생성
	for (int i = 0; i < result_count; i++)
	{
		result* cur = _result;
		while ((strcmp(cur->name, "REQ_NUM") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("REQ_NUM 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		REQ_NUM = cur->_int_data[i];


		cur = _result;
		while ((strcmp(cur->name, "NODE_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("NODE_CODE 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		strcpy(NODE_CODE, cur->_string_data[i]);


		cur = _result;
		while ((strcmp(cur->name, "M_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("M_CODE 컬럼이 존재하지 않습니다.");
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

	//노드의 멤버(M_CODE와 NODE_CODE)를 활용하여 노드간 연결하여 트리 구현 (가장 하위 노드부터 오름차순 연결)
	for (int i = result_count - 1; i >= 0; i--)
	{
		int Mother_index = 0;
		//현재노드의 M_CODE와 Mother_index노드의 NODE_CODE가 같을때까지 Mother_index 증가
		while ((Mother_index < result_count) && (strcmp(Node[i]->M_CODE, Node[Mother_index]->NODE_CODE) != 0))
			Mother_index++;

		//Node[Mother_index]를 부모 노드로, 현재 노드를 자식노드로 연결
		if ((Mother_index < result_count) && (strcmp(Node[i]->M_CODE, Node[Mother_index]->NODE_CODE) == 0))
		{
			BOM_AddChildNode(Node[Mother_index], Node[i]);
			//printf("%d, %d\n", Mother_index, i);
		}
	}

	result_free(_result, result_count);

	////완성된 트리에서 루트노드 찾기
	//int index = 0;
	//while (!string_is_null(Node[index]->M_CODE))
	//	index++;

	return Node[0];	//해당 루트노드를 리턴
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
	if (Root->RightSibling != NULL)      //RightSibling이 존재시
		BOM_DestroyTree(Root->RightSibling);      //RightSibling이 가리키는 노드를 매개변수로 재귀호출

	if (Root->LeftChild != NULL)      //LeftChild이 존재시
		BOM_DestroyTree(Root->LeftChild);      //LeftChild이 가리키는 노드를 매개변수로 재귀호출


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
		printf("LEVEL\t  품목코드\t필요수량\n");
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
	//int i = 0; // 들여쓰기로 트리의 Depth 표현 
	//for (i = 0; i < Depth; i++)
	//   printf("   ");

	printf("%4d\t%8s\t%5d\n", Depth, CurNode->NODE_CODE, CurNode->REQ_NUM);

	if (CurNode->LeftChild != NULL) // 차일드 존재시
		_BOM_Forward_PrintTree(CurNode->LeftChild, Depth + 1); // 재귀 호출 - Node의 Child의 깊이는 Node의 Depth에 +1 한 값과 같음

	if (CurNode->RightSibling != NULL) // 형제 존재시
		_BOM_Forward_PrintTree(CurNode->RightSibling, Depth); // 재귀 호출 - 형제 노드의 깊이는 모두 같음(같은 레벨의 노드
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