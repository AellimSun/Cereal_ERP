#include <stdio.h>
#include <Windows.h>
#include "cereal.h"
#include <stdbool.h>
#include <string.h>

#define SIZE 30
int k = 0;
plan* production_new_plan();
plan* production_menu();
typedef char* element;
typedef struct node
{
	element que[SIZE];
	struct node* link;
	
} Node;

typedef struct
{
	Node* rear;
	Node* front;

} Qlink;

//void gotoxy(int x, int y)
//{
//	COORD pos = { x,y };
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//}

Qlink* Create()
{
	Qlink* ql = (Qlink*)malloc(sizeof(Qlink));
	if (ql == NULL) exit(1);

	ql->front = NULL;
	ql->rear = NULL;
	return ql;
}

bool isEmpty(Qlink* aql)
{
	if (aql->front == NULL)
	{
		/*printf("Queue is empty");*/
		return true;
	}
	else return false;
}

//bool isFull(Qlink* aql)
//{
//	if (aql->rear >= 3)
//	{
//		printf("Queue is full");
//		return true;
//	}
//	else return false;
//}

void enQueue(Qlink* aql, element adata)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL) exit(1);
	strcpy(newNode->que, adata);
	newNode->link = NULL;

	if (isEmpty(aql))
	{
		aql->front = newNode;
		aql->rear = newNode;
	}
	else
	{
		aql->rear->link = newNode;
		aql->rear = newNode;
	}
}

void deQueue(Qlink* aql)
{
	if (isEmpty(aql))
	{
		printf("Empty");
		exit(1);
	}
	else
	{
		Node* curr = aql->front;
		char* D[30] = { NULL };
		strcpy(D, curr->que);
		aql->front = aql->front->link;
		if (aql->front == NULL) aql->rear = NULL;
		free(curr);
	}
}

void printQ(Qlink* aql)
{
	Node* curr = aql->front;
	int j = 0;

	printf("위치 : 메인메뉴 -> 생산관리 -> 생산계획 관리 -> 계획 목록 열람\n\n");
	if (curr->que == NULL)
	{
		
		printf("\n\t\t\t-----------------------------------------\n");
		printf("\t\t\t|저장된 계획이 없습니다.\t\t|\n");
		printf("\t\t\t-----------------------------------------\n");
		
		return 0;
	}
	printf("\n\n\t\t\t-----------------------------------------\n");
	printf("\t\t\t|  계획연도\t계획량\t   품목 코드\t|\n");
	printf("\t\t\t-----------------------------------------\n");

	while (curr)
	{
		char temp[30];

		strcpy(temp, curr->que);

		char* ptr = strtok(temp, ",");
		char* sArr[10] = { NULL };
		int i = 0;

		printf("\t\t\t| ");
		while (ptr != NULL)
		{
			if (k == 0)
			{
				printf(" %s\t", ptr);
			}
			else if (k == 1)
			{
				gotoxy(39, 7 + 2 * j);
				printf(" %s\t", ptr);
			}
			else
			{
				gotoxy(50, 7 + 2 * j);
				printf(" %s\t", ptr);
			}
			k = k + 1;

			ptr = strtok(NULL, ",");
		}

		gotoxy(60, 7+2*j);
		printf("\t|\n");
		printf("\t\t\t-----------------------------------------\n");
		curr = curr->link;

		j = j + 1;
		k = 0;
	}
}

void production_plan(void)
{
	plan* values;
	//char* conditional = "TP='q'";
	//char* set = "TP='c'";
	char* select_column = "PLAN_YEAR, PLAN_PRODUCTION, CODE";

	/*result* _result;
	result* find;
	int result_count;*/

	values = production_menu();

	// 파일 생성
	if (_create("Product_Plan", "PLAN_YEAR INT PLAN_PRODUCTION INT CODE VARCHAR(20)") == -1) {
		printf("%s\n", err_msg);

		return -1;
	}

	// 생성한 파일 정보보기
	if (initalizing("Product_Plan") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert(values->values) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	/*if (_delete(conditional) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}*/

	/*if (_update(conditional, set) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}*/

	//print_data();
	file_column_free();

	//confirm_Material(values);

	printf("\n");

	/*if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		printf("%s\n\n", select_result_str);
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");*/

	/*if ((find = find_result(_result, "FLdf")) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		result_free(_result, result_count);
		return -1;
	}*/
	/*printf("     %s\n", find->name);
	printf("=============\n");
	for (int i = 0; i < result_count; i++) {
		switch (find->type) {
		case INT:
			if (int_is_null(find->_int_data[i]))
				printf("     (null)\n");
			else
				printf("     %d\n", find->_int_data[i]);
			break;
		case FLOAT:
			if (float_is_null(find->_float_data[i]))
				printf("     (null)\n");
			else
				printf("     %.5f\n", find->_float_data[i]);
			break;
		case DOUBLE:
			if (double_is_null(find->_double_data[i]))
				printf("     (null)\n");
			else
				printf("     %.12lf\n", find->_double_data[i]);
			break;
		case CHAR:
			if (char_is_null(find->_char_data[i]))
				printf("     (null)\n");
			else
				printf("     %c\n", find->_char_data[i]);
			break;
		case VARCHAR:
			if (string_is_null(find->_string_data[i]))
				printf("     (null)\n");
			else
				printf("     %s\n", find->_string_data[i]);
			break;
		}
	}

	file_column_free();
	result_free(_result, result_count);*/

	free(values);
}

plan* production_new_plan()
{
	char* str[3] = { 0 };
	char* year;
	char* product;
	char* code;

	getchar();
	
	printf("위치 : 메인메뉴 -> 생산관리 -> 생산계획 관리 -> 새 계획 수립\n\n");
	printf("\t\t\t-----------------------------------------\n");
	printf("\t\t\t| 계획연도, 연간계획량, 품목 코드 입력  |\n");
	printf("\t\t\t-----------------------------------------\n");
	
	for (int i = 0; i < 3; i++)
	{
		printf("\t\t\t\t 입력 :\n");
		gotoxy(40, 5+i);
		char temp[100];
		gets(temp);
		str[i] = (char*)malloc(strlen(temp) + 1);
		strcpy(str[i], temp);
	}

	year = str[0];
	product = str[1];
	code = str[2];

	year = (char*)realloc(year, _msize(year) + _msize(product) + _msize(code) + 2);

	strcat(year, ",");
	strcat(year, product);
	strcat(year, ",");
	strcat(year, code);

	/*free(str[1]);
	free(str[2]);*/

	plan* newPlan = (plan*) malloc(sizeof(plan));
	newPlan->CODE = code;
	newPlan->PLAN_PRODUCTION = product;
	newPlan->values = year;


	return newPlan;
}

plan* production_menu()
{
	int key;
	char str;
	int cnt = 0;
	plan* values;
	Qlink* HistoryQ = Create();

	
	while(1)
	{
		printf("위치 : 메인메뉴 -> 생산관리 -> 생산계획 관리\n\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     메뉴를 선택하세요.    |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      1. 새 계획 수립      |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|     2. 계획 목록 열람     |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|       3. 뒤로 가기        |\n");
		printf("\t\t\t-----------------------------\n\n");

		printf("\t\t\t\t 입력 :\n");
		printf("\t\t\t\t        ^");
		gotoxy(40, 14);
		scanf("%d", &key);
		system("cls");

		if (key == 1)
		{
			values = production_new_plan();
			enQueue(HistoryQ, values->values);
	
			cnt++;

			while (1)
			{
				gotoxy(35, 8);
				printf("\n\n\t\t\t-----------------------------------------\n");
				printf("\t\t\t|입력한 계획을 실행하시겠습니까? (Y/N)  |\n");
				printf("\t\t\t-----------------------------------------\n");
				printf("\t\t\t\t 입력 :\n");
				gotoxy(40, 13);
				scanf(" %c", &str);
				if (str == 'Y' || str == 'y')
				{
					return values;
				}
				else if (str == 'N' || str == 'n')
				{
					system("cls");
					break;
				}
				else
				{
					gotoxy(35,15);
					printf("\n\t\t\t잘못된 입력입니다. 다시 입력해주십시오.\n\n");
				}
			}

			if (cnt >= 11)
			{
				deQueue(HistoryQ);
			}
		}
		else if (key == 2)
		{
			printQ(HistoryQ);
			printf("\n\n");
			while (1)
			{
				gotoxy(0,2);
				printf("\t\t\t ->열람을 종료하고 초기화면으로 돌아가시려면 Q키를 입력하세요.\n");
				gotoxy(86, 2);
				scanf(" %c", &str);
				if (str == 'Q' || str == 'q')
				{
					system("cls");
					break;
				}
				else
				{
					gotoxy(25,3);
					printf("->잘못된 입력입니다. 다시 입력해주십시오.\n");
				}
			}
		}
		else if (key == 3)
		{
			production_management();
		}
	}
}