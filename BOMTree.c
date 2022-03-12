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

void base_information(void);	// 기초정보

void BOM_search_main()
{
	system("cls");
	printf("위치 : 메인메뉴 -> 생산관리 -> 기초정보관리 -> BOM 조회\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     메뉴를 선택하세요.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      1.BOM 정전개         |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      2.BOM 역전개         |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      0.이전으로           |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t 입력 :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 13);




	int input;

	scanf("%d", &input);

	while (input < 0 || input>2)
	{
		printf("잘못된 입력입니다. 다시 입력해주세요");
		Sleep(1000);
		system("cls");
		printf("위치 : 메인메뉴 -> 생산관리 -> 기초정보관리 -> BOM 조회\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     메뉴를 선택하세요.    |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      1.BOM 정전개         |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      2.BOM 역전개         |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      0.이전으로           |\n");
		printf("\t\t\t-----------------------------\n\n");

		printf("\t\t\t\t 입력 :\n");
		printf("\t\t\t\t        ^");
		gotoxy(40, 13);

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

/*{
		char* text1 = "ROOT_CODE = '";
		char* text2 = "'";
		char* conditional = (char*)malloc(sizeof(text1) + sizeof(_conditional) + sizeof(text2));
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

		print_data();
		printf("\n");

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
		printf("\n\n");
		result_print(_result, result_count);
		printf("\n\n");

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

		return Node[0];	//해당 루트노드를 리턴
	}*/

BOM_TREE* BOM_SEARCH(char* _conditional)
{
	system("cls");
	BOM_TREE* ROOT = (BOM_TREE*)malloc(sizeof(BOM_TREE));
	if (ROOT == NULL) exit(1);

	ROOT->REQ_NUM = 1;						//초기화
	strcpy(ROOT->M_CODE, pad_seprator);		//모코드 NULL
	strcpy(ROOT->NODE_CODE, _conditional);	//NODE코드 본인
	ROOT->LeftChild = NULL;					//초기화
	ROOT->RightSibling = NULL;				//초기화

	//연관된 노드 데이터들 양방향 연결리스트로 임시로 저장
	BOM_LIST* list = NULL;
	list = recur_search(_conditional, list);		//입력한 루트 제외 나머지 노드를 양방향 연결리스트로

	//list의 총 길이 구하기
	int count = 1;
	BOM_LIST* curre = list;
	while (curre->next != NULL)
	{
		//printf("%s\t%d\t%s\n", curre->NODE_CODE, curre->REQ_NUM, curre->M_CODE);
		curre = curre->next;
		count++;
	}
	//printf("%s\t%d\t%s\n", curre->NODE_CODE, curre->REQ_NUM, curre->M_CODE);


	//count+1 개수 만큼의 구조체 포인터를 가지는 이중 포인터 Node를 동적 할당으로 정의
	BOM_TREE** Node = (BOM_TREE**)malloc(sizeof(BOM_TREE*) * (count + 1));
	if (Node == NULL)
	{
		printf("메모리 부족!");
		exit(0);
	}

	/*Element2 REQ_NUM;
	Element1 NODE_CODE[6];
	Element1 M_CODE[6];
*/

	//count+1 개수 만큼 노드 생성
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
		//현재노드의 M_CODE와 Mother_index노드의 NODE_CODE가 같을때까지 Mother_index 증가
		while ((Mother_index < (count + 1)) && (strcmp(Node[i]->M_CODE, Node[Mother_index]->NODE_CODE) != 0))
			Mother_index++;

		//Node[Mother_index]를 부모 노드로, 현재 노드를 자식노드로 연결
		if ((Mother_index < (count + 1)) && (strcmp(Node[i]->M_CODE, Node[Mother_index]->NODE_CODE) == 0))
		{
			BOM_AddChildNode(Node[Mother_index], Node[i]);
			//printf("%d, %d\n", Mother_index, i);
		}
	}

	//역할 끝난 리스트 free
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
		//printf("%s\n", err_msg);

		file_column_free();
		return list;
	}
	//조건에 맞는 select_result_str을 가공하여 NODE_CODE, REQ_NUM, M_CODE 컬럼으로 구하기
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	free(conditional);
	//result_print(_result, result_count);

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
	while (!string_is_null(cur->_string_data[index]))
		index++;


	Element2 REQ_NUM;
	Element1 NODE_CODE[6];
	Element1 M_CODE[6];

	//result_count 개수 만큼의 노드 생성
	for (int i = 0; i < result_count; i++)
	{
		if (i == index)
			continue;

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

		list = BOM_CreateNode_list(list, REQ_NUM, NODE_CODE, M_CODE);
	}
	file_column_free();

	return list;
}

void Free_list(BOM_LIST* h)
{
	if (h == NULL)
		printf("해제할 노드가 존재하지 않습니다.");
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
		printf("메모리 부족\n");
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
	system("cls");
	if (strcmp(CurNode->NODE_CODE, NODE_CODE) == 0)
	{
		printf("%s의 정전개 결과는 다음과 같습니다.\n\n", NODE_CODE);
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