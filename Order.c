#include "cereal.h"
#include <string.h>
#include <time.h>




void storage_Orders(Order* head, int num);

int result_count;

//발주-삽입(파일) head 노드
Order* insert_ord;

//공정으로 넘길 구조체 head노드
plan* head_Cod_n_Num;
result* _result;

int col = 1;

Order* creatNode_Order()
{
	Order* newNode;
	if ((newNode = (Order*)malloc(sizeof(Order))) == NULL) {
		return -1;
	}
	newNode->ACC_CODE = NULL;
	newNode->PRD_CODE = NULL;
	newNode->next = NULL;

	return newNode;
}

void creat_Order_List(Order* head, result* result_head, int num)
{
	
	result* cur;
	cur = result_head;
	
	for (int i = 0; i < num; i++) {



		cur = result_head;
		while (1) {

			switch (cur->type) {
			case _VARCHAR:
				if (string_is_null(cur->_string_data[i]))
					printf("     (NULL)");
				else
				{
					if (strcmp(cur->name, "ACC_CODE") == 0)
					{

						head->ACC_CODE = cur->_string_data[i];
						
					}
					else if (strcmp(cur->name, "PRD_CODE") == 0)
					{
						head->PRD_CODE = cur->_string_data[i];
						
					}

				}
				break;
			}
			if (cur->next == 0)
				break;
			else
			{
				cur = cur->next;
			}


			printf("\n");
		}

		printf("\n");
	}


}



//요청 :: 내가 물건이 없다! ( 자재 -> 품목코드, 거래처코드, 수량  ) 
void material_to_prosess(plan* head, bomRes* met)
{
	plan* newNode = malloc(sizeof(plan));
	if (newNode == NULL)
	{
		return -1;
	}

	newNode->CODE = met->CODE;
	newNode->next = NULL;
	newNode->PLAN_PRODUCTION = 0;
	newNode->values = met->AMOUNT;


	newNode->next = head->next;
	head->next = newNode;



}


void Request_Order(bomRes* met_ord)
{

	if (_create("pre_sample_Order", "O_DATE INT D_DATE INT ACC_CODE VARCHAR(10) ORDER_NUM INT PRD_CODE VARCHAR(10) NUM INT") == -1)
	{
		printf("%s\n", err_msg);
		return -1;
	}

	char values[30];

	plan* Cod_n_Num;

	//initialization 구조체

	if ((insert_ord = (Order*)malloc(sizeof(Order))) == NULL) {

		return -1;
	}
	insert_ord->ACC_CODE = NULL; insert_ord->PRD_CODE = NULL; 
	//insert_ord->D_Day = 0; insert_ord->NUM = 0; insert_ord->O_Day = 0;
	insert_ord->next = NULL;

	head_Cod_n_Num = (plan*)malloc(sizeof(plan));

	if (head_Cod_n_Num == NULL)
		return -1;

	head_Cod_n_Num->next = NULL;

	char* prd_code = NULL;
	int amount = 0;

	//자재구조체 :: 거래처 코드를 받기 위함. sercer측 오류로 보임.추후 수정요망
	bomRes* met = malloc(sizeof(bomRes));
	if (met == NULL)
		return -1;
	met = met_ord->next;


	while (met != NULL)
	{
		system("cls");
	
		printf("위치 : 메인메뉴 -> 생산관리 -> 생산계획 관리 -> 발주요청\n\n");
		

		if (met->AMOUNT <= 0)
		{

			//system("cls");
			printf("자재의 요청수량이 0 입니다.\n");
			met = met->next;


		}
		else {


			prd_code = met->CODE;
			
			printf("품목 코드 : %s\n", prd_code);
			amount = met->AMOUNT;



			strcpy(values, "PRD_CODE = '");
			strcat(values, prd_code);
			strcat(values, "'");



			if (initalizing("account") == -1)
			{
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			Sleep(1000);
			if (_select(values, "ACC_CODE, BN_REGI_NUM, PRD_CODE, RorD", &select_result_str) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}
			else {

				printf("\n...품목코드 관련 거래처가 존재합니다\n\n");
			}

			if ((result_count = recv_result(&_result, select_result_str)) == -1) {
				printf("%s\n", err_msg);

				file_column_free();
				return -1;
			}

			result_print(_result, result_count);
			printf("\n");
			file_column_free();
			Sleep(1000);


			//차라리 함수를 새로 선언해서 넘겨주자.
			creat_Order_List(insert_ord, _result, result_count);


			//발주내역 저장
			printf("발주내역을 저장합니다..\n");
			Sleep(1000);
			storage_Orders(insert_ord, amount);


			met = met->next;

			Sleep(3000);
		}
	}

	system("cls");
	printf("저장된 발주 내역입니다\n");



	if (initalizing("pre_sample_Order") == -1)
	{

		printf("%s\n", err_msg);

		file_column_free();

		return -1;

	}

	print_data();
	file_column_free();
	Sleep(1000);
	printf("발주를 종료합니다.");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");
	Sleep(500);
	printf(".");

	return;
	
	
	
}
void current_Order_list(char* values)
{

	if (initalizing("pre_sample_Order") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert(values) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	print_data();
	Sleep(1000);
	file_column_free();

}

//01 자재 -> 발주 -> 거래처 루트
void storage_Orders(Order* head, int* num)
{
	

	if (initalizing("sample_Order") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	//발주일 : 오늘 날짜, 납기일 : 내일
	struct tm* t_order;
	time_t base = time(NULL);

	t_order = localtime(&base);

	//발주일 및 납품일 담을 파일
	unsigned char ord_date[5];


	unsigned char values[50];
	//Order* cur = head->next; //노드의 헤드 :: 추후 수정
	Order* cur = head;

	/*
		파일에 insert 하기 위해서 넣어야 할 데이터가 한 문장으로 정리가 되어야한다
		데이터들은 구조체에 정리되어있다.

	*/

	//발주일
	itoa(t_order->tm_mon + 1, ord_date, 10);	//월
	strcpy(values, ord_date);
	itoa(t_order->tm_mday, ord_date, 10);	//일
	strcat(values, ord_date);
	strcat(values, ", ");

	//납기일
	itoa(t_order->tm_mon + 1, ord_date, 10);		//월
	strcat(values, ord_date);
	itoa(t_order->tm_mday + 1, ord_date, 10);	//일
	strcat(values, ord_date);
	strcat(values, ", ");

	//거래처 코드
	strcat(values, "'");
	strcat(values, cur->ACC_CODE);
	strcat(values, "'");
	strcat(values, ", ");

	//발주번호 :: INT TO CHAR
	itoa(t_order->tm_mon + 1, ord_date, 10);		//월
	strcat(values, ord_date);
	itoa(col++, ord_date, 10);		//대충난수
	strcat(values, ord_date);
	strcat(values, ", ");

	//품목코드 :: CHAR
	strcat(values, "'");
	strcat(values, cur->PRD_CODE);
	strcat(values, "'");
	strcat(values, ", ");

	//수량 :: INT TO CHAR
	itoa(num, ord_date, 10);			//수량
	strcat(values, ord_date);


	//전체 발주파일에 내역 저장
	if (_insert(values) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	file_column_free();
	//현 발주내역을을 보여줄 떄 전체 내역이 아닌 저장한 내역만 보여주도록
	printf("\n");

	current_Order_list(values);



}

//02. 메인 -> 발주 -> 발주입력(품목코드) -> 거래처 목록 -> 발주!
void all_Order_List()
{
	char key = NULL;
	if (initalizing("sample_Order") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	while (1)
	{
		
		if (key == '`')
		{
			printf("메인메뉴로 돌아갑니다");
			Sleep(500);
			printf(".");
			Sleep(500);
			printf(".");
			Sleep(500);
			printf(".");
			file_column_free();
			return main();
		}
		system("cls");
		printf("저장된 발주 내역입니다\n");
		print_data();
		printf("(`) 메인으로");
		
		printf("\n->");
		scanf("%c", &key);
		//file_column_free();
		

		
	}
	
	
	//return;
} 




