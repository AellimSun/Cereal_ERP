#include "cereal.h"
#include "BOMTree.h"
#include "UI.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <windows.h>

#define FILE_NAME "bom"

void base_information(void);	// 기초정보

void BOM_search_main()
{
	int input = 0;

	do
	{
		if (input < -1 || input > 3)
		{
			printf("잘못된 입력입니다. 다시 입력해주세요");
			Sleep(1500);
		}
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
	}while (input < -1 || input>2);

	switch (input)
	{
	case -1:
	{
		system("cls");
		if (initalizing(FILE_NAME) == -1)
		{
			printf("bom파일이 존재하지 않습니다\n");

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
		//1.BOM 정전개
		system("cls");
		printf("위치 : 메인메뉴 -> 생산관리 -> 기초정보관리 -> BOM 조회 -> BOM 정전개\n\n");
		char input_temp[100] = "";

		int list_count = Show_BOM_ROOT_CODE_list();

		if (!list_count)
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
		//2.BOM 역전개
		system("cls");
		printf("위치 : 메인메뉴 -> 생산관리 -> 기초정보관리 -> BOM 조회 -> BOM 역전개\n\n");
		char input_temp[100] = "";

		int list_count = Show_BACK_ABLE_NODE_CODE_list();

		if (!list_count)
			return;

		printf("BOM 역전개 할 품명코드를 입력하세요. ");
		scanf("%s", &input_temp);

		char* search_code = (char*)malloc(sizeof(input_temp));
		if (search_code == NULL)
		{
			printf("메모리 부족");
			return;
		}
		strcpy(search_code, input_temp);

		BOM_LIST* result = BOM_RESEARCH(search_code);
		free(search_code);

		if (result == NULL)
		{
			printf("검색된 결과가 없습니다.");
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
		//이전으로
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

	//_conditional 제품명 찾기
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
		char* select_column = "PRODUCT_NAME";

		//BOM 파일 열기
		if (initalizing(FILE_NAME) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return NULL;
		}

		//conditional 조건에 맞는 select_result_str 구하기
		if (_select(conditional, select_column, &select_result_str) == -1) {
			//printf("%s\n", err_msg);

			file_column_free();
			return NULL;
		}
		//조건에 맞는 select_result_str을 가공하여 PRODUCT_NAME 컬럼으로 구하기
		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return NULL;
		}

		free(conditional);
		//result_print(_result, result_count);

		//PRODUCT_NAME 컬럼 찾기
		result* cur = _result;
		while ((strcmp(cur->name, "PRODUCT_NAME") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("M_CODE 컬럼이 존재하지 않습니다.");

			file_column_free();
			exit(1);
		}

		strcpy(ROOT->PRODUCT_NAME, cur->_string_data[0]);

		result_free(_result, result_count);
		file_column_free();
	}

	//초기화
	ROOT->LeftChild = NULL;					//초기화
	strcpy(ROOT->M_CODE, pad_seprator);		//모코드 NULL
	strcpy(ROOT->NODE_CODE, _conditional);	//NODE코드 본인
	//ROOT->PRODUCT_NAME;					//제품명 상기에서 정의함
	ROOT->REQ_NUM = 1;						//초기화
	ROOT->RightSibling = NULL;				//초기화
	strcpy(ROOT->ROOT_CODE, _conditional);	//NODE코드 본인


	//연관된 노드 데이터들 양방향 연결리스트로 임시로 저장
	BOM_LIST* list = NULL;
	list = recur_search(_conditional, list);		//입력한 루트 제외 나머지 노드를 양방향 연결리스트로
	if (list == NULL)
	{
		printf("검색된 결과가 없습니다.\n");
		Sleep(1500);
		return NULL;
	}
	system("cls");

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

	int total = count + 1;
	//count+1 개수 만큼의 구조체 포인터를 가지는 이중 포인터 Node를 동적 할당으로 정의
	BOM_TREE** Node = (BOM_TREE**)malloc(sizeof(BOM_TREE*) * (total));
	if (Node == NULL)
	{
		printf("메모리 부족!");
		exit(0);
	}

	//count+1 개수 만큼 노드 생성
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

int Show_BOM_ROOT_CODE_list()	//BOM 파일에서 ROOT코드 리스트를 뽑아오세요
{
	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE, NODE_CODE, PRODUCT_NAME";

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
	//모든 컬럼을 가공하여 ROOT_CODE, PRODUCT_NAME 컬럼 구하기
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	if (result_count > 0)
	{
		printf("BOM에 등록된 리스트는 다음과 같습니다\n\n");
		printf(" 품목코드\t품명\n");
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
				printf("ROOT_CODE 컬럼이 존재하지 않습니다.");
				exit(1);
			}
			strcpy(ROOT_CODE, cur->_string_data[i]);

			cur = _result;
			while (cur != NULL && (strcmp(cur->name, "NODE_CODE") != 0))
				cur = cur->next;
			if (cur == NULL)
			{
				printf("ROOT_CODE 컬럼이 존재하지 않습니다.");
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
					printf("PRODUCT_NAME 컬럼이 존재하지 않습니다.");
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
		printf("등록된 BOM 리스트가 없습니다.\n");
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

	//BOM 파일 열기
	if (initalizing(FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return 0;
	}

	//모든 컬럼 구하기
	if (_select("*", select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return 0;
	}
	//모든 컬럼을 가공하여 ROOT_CODE 컬럼 구하기
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
		printf("메모리 부족");
		exit(1);
	}
	strcpy(conditional, text1);
	strcat(conditional, _conditional);
	strcat(conditional, text2);

	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE, NODE_CODE, PRODUCT_NAME, REQ_NUM, M_CODE";

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
	//조건에 맞는 select_result_str을 가공하여 ROOT_CODE, NODE_CODE, PRODUCT_NAME, REQ_NUM, M_CODE 컬럼으로 구하기
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

	Element1 ROOT_CODE[6];
	Element1 NODE_CODE[6];
	Element1 PRODUCT_NAME[30];
	Element2 REQ_NUM;
	Element1 M_CODE[6];

	//result_count 개수 만큼의 노드 생성
	for (int i = 0; i < result_count; i++)
	{
		if (i == index)
			continue;

		cur = _result;
		while ((strcmp(cur->name, "ROOT_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("ROOT_CODE 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		strcpy(ROOT_CODE, cur->_string_data[i]);


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
		while ((strcmp(cur->name, "PRODUCT_NAME") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("PRODUCT_NAME 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		strcpy(PRODUCT_NAME, cur->_string_data[i]);


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
		while ((strcmp(cur->name, "M_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("M_CODE 컬럼이 존재하지 않습니다.");
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

int Show_BACK_ABLE_NODE_CODE_list()	//BOM 파일에서 역전개 가능한 리스트 출력
{
	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE, NODE_CODE, PRODUCT_NAME";

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
	//모든 컬럼을 가공하여 ROOT_CODE, NODE_CODE, PRODUCT_NAME 컬럼 구하기
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	if (result_count > 0)
	{
		printf("역전개 가능 리스트는 다음과 같습니다\n\n");
		printf("품목코드\t품명\n");
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
				printf("ROOT_CODE 컬럼이 존재하지 않습니다.");
				file_column_free();
				return 0;
			}
			strcpy(ROOT_CODE, cur->_string_data[i]);

			cur = _result;
			while (strcmp(cur->name, "NODE_CODE") != 0)
				cur = cur->next;
			if (cur == NULL)
			{
				printf("NODE_CODE 컬럼이 존재하지 않습니다.");
				file_column_free();
				return 0;
			}
			strcpy(NODE_CODE, cur->_string_data[i]);


			if (strcmp(ROOT_CODE, NODE_CODE) != 0)
			{
				
				//품목코드 출력
				printf("%7s\t", NODE_CODE);

				//품명 출력
				cur = _result;
				while (strcmp(cur->name, "PRODUCT_NAME") != 0)
					cur = cur->next;
				if (cur == NULL)
				{
					printf("PRODUCT_NAME 컬럼이 존재하지 않습니다.");
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
		printf("등록된 BOM 리스트가 없습니다.\n");
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
	//모든 컬럼을 가공하여 ROOT_CODE, NODE_CODE, PRODUCT_NAME 컬럼 구하기
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
				printf("ROOT_CODE 컬럼이 존재하지 않습니다.");
				file_column_free();
				return 0;
			}
			strcpy(ROOT_CODE, cur->_string_data[i]);

			cur = _result;
			while (strcmp(cur->name, "NODE_CODE") != 0)
				cur = cur->next;
			if (cur == NULL)
			{
				printf("NODE_CODE 컬럼이 존재하지 않습니다.");
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
		printf("등록된 BOM 리스트가 없습니다.\n");
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
		printf("메모리 부족");
		exit(1);
	}
	strcpy(conditional, text1);
	strcat(conditional, _conditional);
	strcat(conditional, text2);

	result* _result;
	int result_count;
	char* select_column = "ROOT_CODE, NODE_CODE, PRODUCT_NAME, REQ_NUM, M_CODE";

	//BOM 파일 열기
	if (initalizing(FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}
	//conditional 조건에 맞는 select_result_str 구하기
	if (_select("*", select_column, &select_result_str) == -1) {
		//printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}
	//조건에 맞는 select_result_str을 가공하여 ROOT_CODE, NODE_CODE, PRODUCT_NAME, REQ_NUM, M_CODE 컬럼으로 구하기
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		exit(1);
	}

	free(conditional);

	//_conditional부터 시작해서 ROOT까지의 역전개 리스트 생성
	ROOT_LIST =	Make_LIST(_result, result_count, ROOT_LIST, _conditional);

	file_column_free();
	result_free(_result, result_count); //애매...
	return ROOT_LIST;
}

BOM_LIST* Make_LIST(result* _result, int result_count, BOM_LIST* ROOT_LIST, char* target)
{
	//타겟찾기
	result* cur = _result;
	Element1 ROOT_CODE[6] = { 0 };
	Element1 NODE_CODE[6] = { 0 };
	Element1 _PRODUCT_NAME[30] = { 0 };
	Element2 REQ_NUM = 0;
	Element1 M_CODE[6] = { 0 };

	int overlap_count = 0;

	//ROOT코드를 알고 있는 target 찾기
	for (int index = 0 ; index < result_count ; index++)
	{
		cur = _result;
		while ((strcmp(cur->name, "ROOT_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("ROOT_CODE 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		strcpy(ROOT_CODE, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "NODE_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("NODE_CODE 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		strcpy(NODE_CODE, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "PRODUCT_NAME") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("PRODUCT_NAME 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		strcpy(_PRODUCT_NAME, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "REQ_NUM") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("REQ_NUM 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		REQ_NUM = cur->_int_data[index];

		cur = _result;
		while ((strcmp(cur->name, "M_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("M_CODE 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		strcpy(M_CODE, cur->_string_data[index]);

		//NODE_CODE 컬럼에 NODE_NAME의 중복개수 세기(1이면서, 노드와 루트가 같은 경우 최종루트 노드)
		cur = _result;
		while ((strcmp(cur->name, "NODE_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("NODE_CODE 컬럼이 존재하지 않습니다.");
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

		//루트코드와 노드코드가 다르면서 노드코드가 target과 같은 경우 || (혹은 최종 루트노드 일 경우)
		if (((strcmp(ROOT_CODE, NODE_CODE) != 0) && (strcmp(NODE_CODE, target) == 0)) || ((overlap_count == 1) && (strcmp(ROOT_CODE, NODE_CODE) == 0) && (strcmp(target, NODE_CODE) == 0)))
		{
			ROOT_LIST = BOM_CreateNode_list(ROOT_LIST, ROOT_CODE, NODE_CODE, _PRODUCT_NAME, REQ_NUM, M_CODE);
			break;
		}
	}

	//최종 루트노드일 경우
	if ((overlap_count == 1) && (strcmp(ROOT_CODE, NODE_CODE) == 0 && (strcmp(target, NODE_CODE) == 0)))
	{
		return ROOT_LIST;
	}
	//목적 데이터를 찾았을 경우 해당 데이터의 모코드를 이용하여 재귀
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
		printf("메모리 부족\n");
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

void BOM_Forward_PrintTree(BOM_TREE* CurNode, Element1* NODE_CODE)
{
	system("cls");
	if (strcmp(CurNode->NODE_CODE, NODE_CODE) == 0)
	{
		printf("%s의 정전개 결과는 다음과 같습니다.\n\n", NODE_CODE);
		printf("LEVEL\t 품목코드\t품명\t필요수량\n");
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
	//int i = 0; // 들여쓰기로 트리의 Depth 표현 
	//for (i = 0; i < Depth; i++)
	//   printf(" ");

	printf("%4d\t%8s %13s %5d\n", Depth, CurNode->NODE_CODE, CurNode->PRODUCT_NAME, CurNode->REQ_NUM);

	if (CurNode->LeftChild != NULL) // 차일드 존재시
		_BOM_Forward_PrintTree(CurNode->LeftChild, Depth + 1); // 재귀 호출 - Node의 Child의 깊이는 Node의 Depth에 +1 한 값과 같음

	if (CurNode->RightSibling != NULL) // 형제 존재시
		_BOM_Forward_PrintTree(CurNode->RightSibling, Depth); // 재귀 호출 - 형제 노드의 깊이는 모두 같음(같은 레벨의 노드
}

void BOM_Backward_PrintTree(BOM_LIST* result)
{
	system("cls");
	BOM_LIST* cur = result;
	if (cur != NULL)
	{
		printf("%s의 역전개 결과는 다음과 같습니다.\n\n", cur->NODE_CODE);
		printf("LEVEL\t 품목코드\t품명\t필요수량\n");
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
			printf("잘못된 입력입니다. 다시 입력해주세요");
			Sleep(1500);
		}
		system("cls");
		printf("위치 : 메인메뉴 -> 생산관리 -> 기초정보관리 -> BOM 등록\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     메뉴를 선택하세요.    |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      1.BOM 신규등록       |\n");
		//printf("\t\t\t-----------------------------\n");
		//printf("\t\t\t|      2.BOM 수정           |\n");
		//printf("\t\t\t-----------------------------\n");
		//printf("\t\t\t|      3.BOM 삭제           |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      0.이전으로           |\n");
		printf("\t\t\t-----------------------------\n\n");
		printf("\t\t\t\t 입력 :\n");
		printf("\t\t\t\t        ^");
		gotoxy(40, 11);

		scanf("%d", &input);
	} while (input < -1 || input > 3);


	switch (input)
	{
	case -1:
	{
		//1.BOM 파일 초기화
		init_bom();
		system("pause");
		system("cls");
		BOM_record_main();
	}
	break;
	case 1:
	{
		//1.BOM 신규등록 
		BOM_Create_main();
		system("cls");
		BOM_record_main();
	}
	break;
	case 2:
	{
		//2.BOM 수정
		BOM_Update_main();
		system("pause");
		system("cls");
		BOM_record_main();
	}
	break;
	case 3:
	{
		//3.BOM 삭제 
		BOM_Delete_main();
		system("pause");
		system("cls");
		BOM_record_main();
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

void BOM_Create_main()
{
	char input_code1[10] = { 0 };
	char input_code2[10] = { 0 };

	//모코드 검색
	do
	{
		system("cls");
		printf("위치 : 생산관리 -> 기초정보관리 -> BOM 등록 -> BOM 신규등록 -> 모코드 검색\n\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     BOM 파일에 신규       |\n");
		printf("\t\t\t|     등록 할 제품의 품명   |\n");
		printf("\t\t\t|     코드를 입력하세요.    |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n\n");

		printf("\t\t\t   입력 :\n");
		printf("\t\t\t          ^");
		gotoxy(34, 10);
		scanf("%s", input_code1);

		if (strcmp(input_code1, "`") == 0)
			break;

		if (!code_to_name(input_code1))
		{
			printf("\t\t\t  검색된 결과가 없습니다.\n");
			Sleep(1500);
		}
		else if (!Show_BOM_CODE_list(input_code1))
		{
			printf("\t\t\t  이미 등록된 정보 입니다.\n");
			printf("\t\t\t  삭제 후 접근하세요.!\n");
			Sleep(1500);
		}
	} while (!code_to_name(input_code1) || !Show_BOM_CODE_list(input_code1));


	if (strcmp(input_code1, "`") == 0)
		return;

	Element1 ROOT_CODE[6] = { 0 };
	strcpy(ROOT_CODE, input_code1);

	Element1 _NODE_CODE[10][6] = { 0 };
	int index = 0;
	//자코드 검색
	do
	{
		if(index == 0)
			system("cls");

		gotoxy(0, 0);
		printf("위치 : 기초정보관리 -> BOM 등록 -> BOM 신규등록 -> 모코드 검색 -> 자코드 검색\n\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     %s의 자코드로      |\n", ROOT_CODE);
		printf("\t\t\t|     등록할 제품의 품명    |\n");
		printf("\t\t\t|     코드를 입력하세요.    |\n");
		printf("\t\t\t|                           |\n");
		printf("\t\t\t|*    등록 완료 키 : `     *|\n");
		printf("\t\t\t-----------------------------\n\n");
		printf("\t\t\t   입력 :\n");
		printf("\t\t\t          ^");
		gotoxy(34, 11);
		printf("        ");
		gotoxy(34, 11);
		scanf("%s", input_code2);

		if (strcmp(input_code2, "`") == 0)
			break;

		if (!code_to_name(input_code2))
		{
			printf("\t\t\t  검색된 결과가 없습니다.\n");
			Sleep(1500);
		}
		if (!Show_BOM_BACK_ABLE_NODE_CODE_list(input_code2))
		{
			printf("\t\t\t  이미 등록된 정보 입니다.\n");
			printf("\t\t\t  삭제 후 접근하세요.!\n");
			Sleep(1500);
		}
		strcpy(_NODE_CODE[index], input_code2);
		int count = 0;

		printf("\n\t\t\t-----------------------------\n");
		while (count <= index)
		{
			printf("\t\t\t|*     자코드 : %s       *|\n", _NODE_CODE[count]);
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
		printf("위치 : BOM 등록 -> BOM 신규등록 -> 모코드 검색 -> 자코드 검색 -> 필요수량 입력\n\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     %s의 필요수량을    |\n", _NODE_CODE[i]);
		printf("\t\t\t|     입력하세요.           |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n\n");
		printf("\t\t\t   입력 :\n");
		printf("\t\t\t          ^");
		gotoxy(34, 9);
		printf("        ");
		gotoxy(34, 9);
		scanf("%d", &req_num[i]);

		int count = 0;

		printf("\n\t\t\t-----------------------------\n");
		while (count <= i)
		{
			printf("\t\t\t|*   자코드%d 필요수량 : %d  *|\n", count+1, req_num[count]);
			printf("\t\t\t-----------------------------\n");
			count++;
		}
	}

	Sleep(500);
	system("cls");
	printf("위치 : BOM 등록 -> BOM 신규등록 -> 모코드 검색 -> 자코드 검색 -> 필요수량 입력\n\n");
	printf("\t\t   ------------------------------------------\n");
	printf("\t\t   ROOT_CODE     NODE_CODE   REQ_NUM   M_CODE\n");
	printf("\t\t   ==========================================\n");

	printf("\t\t     %s\t  %s\t\t%d\t%s\n", ROOT_CODE, input_code1, 1, "(NULL)");
	for (int i = 0; i < index; i++)
		printf("\t\t     %s\t  %s\t\t%d\t%s\n", ROOT_CODE, _NODE_CODE[i], req_num[i], ROOT_CODE);
	printf("\t\t   ------------------------------------------\n\n\n");
	printf("    입력한 내용은 다음과 같습니다. ");
	system("pause");


	//code에 맞는 제품명 뽑아오기
	char product_text[10][40] = { 0 };
	for (int i = 0; i < index; i++)
		strcpy(product_text[i], code_to_name_list(_NODE_CODE[i]));

	//req_num 을 문자로 변경
	char req_text[10][40] = { 0 };
	for (int i = 0; i < index; i++)
		_itoa(req_num[i], req_text[i], 10);

	char final_text[10][40] = { 0 };
	//문장 합치기
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

	//등록하기전에 제일 첫 코드가 0000 이면 삭제하고 등록하기
	if (is_first_data_0())
		delete_data_0();

	//등록하기
	if (initalizing(FILE_NAME) == -1)
	{
		printf("bom파일이 존재하지 않습니다\n");

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

	printf("    파일에 등록 되었습니다. ");
	file_column_free();
	system("pause");
}

int is_first_data_0()
{
	result* _result;
	int result_count;

	if (initalizing(FILE_NAME) == -1)
	{
		printf("bom파일이 존재하지 않습니다\n");

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
			printf("ROOT_CODE 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		strcpy(ROOT_CODE, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "NODE_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("NODE_CODE 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		strcpy(NODE_CODE, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "PRODUCT_NAME") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("PRODUCT_NAME 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		strcpy(PRODUCT_NAME, cur->_string_data[index]);

		cur = _result;
		while ((strcmp(cur->name, "REQ_NUM") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("REQ_NUM 컬럼이 존재하지 않습니다.");
			file_column_free();
			exit(1);
		}
		REQ_NUM = cur->_int_data[index];

		cur = _result;
		while ((strcmp(cur->name, "M_CODE") != 0) && cur != NULL)
			cur = cur->next;
		if (cur == NULL)
		{
			printf("M_CODE 컬럼이 존재하지 않습니다.");
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
		printf("bom파일이 존재하지 않습니다\n");

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
		printf("메모리 부족");
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
		printf("메모리 부족");
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
	printf("위치 : 메인메뉴 -> 생산관리 -> 기초정보관리 -> BOM 등록 -> BOM 수정\n\n");





}

void BOM_Delete_main()
{
	system("cls");
	printf("위치 : 메인메뉴 -> 생산관리 -> 기초정보관리 -> BOM 등록 -> BOM 삭제\n\n");

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
