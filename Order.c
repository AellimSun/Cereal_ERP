#include "cereal.h"
//#include <stdlib.h>
//#define _GNU_SOURCE
#include <string.h>
#include <time.h>

// 발주일, 납기일에 임시로 저장할 시간함수
//struct tm {
//	int tm_sec;         /* 초,  range 0 to 59            */
//	int tm_min;         /* 분, range 0 to 59             */
//	int tm_hour;        /* 시간, range 0 to 23            */
//	int tm_mday;        /* 일, range 1 to 31             */
//	int tm_mon;         /* 월, range 0 to 11             */
//	int tm_year;        /* 1900년 부터의 년                */
//	int tm_wday;        /* 요일, range 일(0) to 토(6)      */
//	int tm_yday;        /* 1년 중 경과 일, range 0 to 365  */
//	int tm_isdst;       /* 써머타임                        */
//};


//typedef struct _order
//{
//
//	char* ACC_CODE; //배열명은 주소값을 가리킨다.
//	char* PRD_CODE; //배열명은 주소값을 가리킨다.
//	int O_Day;
//	int D_Day;
//	int NUM;
//	
//	struct _order* next;
//
//}Order;

//typedef struct _acc_code
//{
//
//	char* ACC_CODE; //배열명은 주소값을 가리킨다.
//
//	struct _acc_code* next;
//
//}ACC_CODE;
//
//typedef struct _prd_code
//{
//
//	char* PRD_CODE; //배열명은 주소값을 가리킨다.
//
//	struct _prd_code* next;
//
//}PRD_CODE;

result* _result;
result* find;
int result_count;

result* cur;
Order* insert_ord;//발주-삽입(파일) head 노드

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

void creat_Order_List(int num, char* prd_code)
{

	
	int i = 0;
	
	printf("출력 외안대\n");
	

	while (i < num)
	{
		printf("result_count : %d\n", i);
		Order* newNode = creatNode_Order();
		//printf("     ..%s\n", find->_string_data[i]);
		if (strcmp(find->_string_data[i], prd_code) == 0)
		{
			//그에 해당하는 구조체 추출하기
			//printf("prd_code : %s\n", find->_string_data[i]);

			cur = _result;
			while (1) {


				printf("\t\t\ncur %d\n", i);
				switch (cur->type) {
					/*case _INT:
						if (int_is_null(cur->_int_data[i]))
							printf("     (NULL)");
						else
							printf("     %d", cur->_int_data[i]);
						break;
					case _FLOAT:
						if (float_is_null(cur->_float_data[i]))
							printf("     (NULL)");
						else
							printf("     %.5f", cur->_float_data[i]);
						break;
					case _DOUBLE:
						if (double_is_null(cur->_double_data[i]))
							printf("     (NULL)");
						else
							printf("     %.12lf", cur->_double_data[i]);
						break;
					case _CHAR:
						if (char_is_null(cur->_char_data[i]))
							printf("     (NULL)");
						else
							printf("     %c", cur->_char_data[i]);
						break;*/
				case _VARCHAR:
					if (string_is_null(cur->_string_data[i]))
						printf("     (NULL)");
					else
					{
						if (strcmp(cur->name, "ACC_CODE") == 0)
						{
							newNode->ACC_CODE = cur->_string_data[i];
							printf("                    newNode->ACC_CODE : %s\n ", newNode->ACC_CODE);
						}
						else if (strcmp(cur->name, "PRD_CODE") == 0)
						{
							newNode->PRD_CODE = cur->_string_data[i];
							printf("                    newNode->PRD_CODE : %s\n ", newNode->PRD_CODE);
						}
					

						//발주 파일에 insert할 구조체 리스트 생성 완료

						printf("       ,%s", cur->_string_data[i]);
					}
					break;
				}
				if (cur->next == 0)
					break;
				else
				{
					//_result = _result->next;
					cur = cur->next;
				}

			}

			printf("\n");
		}
		i++;
		//후위삽입으로 변경해야함
		newNode->next = insert_ord->next;
		insert_ord->next = newNode;

	}



}

void print_Node()
{
	Order* cur;
	cur = insert_ord->next;
	printf("printNode\n");
	while (cur != NULL)
	{
		printf("PRD_COD : %s,  ", cur->PRD_CODE);
		printf("ACC_CODE : %s\n", cur->ACC_CODE);

		cur = cur->next;
	}
}

//요청 :: 내가 물건이 없다! ( 자재 -> 품목코드, 거래처코드, 수량  ) 
//char* Request_Order(char* prd_code, int num)
//void Request_Order(char* prd_code, int num)

//plan구조체로 넘겨줘야한다.
plan* Request_Order(bomRes* met_ord)
{

	
	

	//printf("->");
	char* values;
	
	//initialization 구조체
	if ((insert_ord = (Order*)malloc(sizeof(Order))) == NULL) {

		return -1;
	}
	insert_ord->ACC_CODE = NULL; insert_ord->PRD_CODE = NULL; insert_ord->D_Day = 0; insert_ord->NUM = 0; insert_ord->O_Day = 0;
	insert_ord->next = NULL;



	if (initalizing("account") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select("*", "ACC_CODE, BN_REGI_NUM, PRD_CODE, RorD", &select_result_str) == -1) {
		//if (_select("*", "ACC_CODE, BN_REGI_NUM, PRD_CODE", &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		//printf("%s\n\n", select_result_str);
		printf("\n...조건을 만족하는 데이터가 존재합니다\n\n");
	}


	
		//자재구조체
		
	bomRes* met = met_ord->next;



	while (met != NULL)
	{


		printf("======================================\n");

		char* prd_code = met->CODE;
		printf("met->CODE : %s", met->CODE);
		printf("prd_code : %s\n", prd_code);
		int amount = met->AMOUNT;

		/* 조건문을 문자로 해서 파일에서 찾는게 안됨 */

		/*
				자재에서 품목 코드, 거래처 코드, 수량을 받아왓다
				거래처 파일로 이 품목코드를 넘겨줌

			while(1)
			{

				if(거래처파일.품목코드 == 자재.품목코드)
				if(strcmp(거래처파일.품목코드, 자재.품목코드) == 0)
				{

					//서칭할 구조체 필요한가?

					_select("PRD_CODE = prd_code", *,&select_result_str)

					해당 품목코드를 포함하는 거래처 컬럼 전체 출력

					printf("%s\n\n", select_result_str);


					발주파일에 변동사항 업데이트

					발주일   납기일    품목코드   거래처코드   수량
					================================================
					NULL     NULL       NULL       NULL        NULL

					return 자재함수로 리턴, 거래처 코드만 리턴? :: 자재팀과 상의 필요
				}
				else
				{
					해당 품목을 취급하는 거래처가 존재하지 않습니다.
					( 홈 ) 화면으로 돌아갑니다.
				}


		}

			*/
			//if (initalizing("sample_Client") == -1) 



		//print_data();
		//print_data();
		values = malloc(sizeof(prd_code) * 4);
		strcpy(values, "PRD_CODE = '");
		strcat(values, prd_code);
		strcat(values, "'");


		printf("values ..-> %s\n", values);
		printf("추출한 데이터 확인\n");
		if (_select("*", "ACC_CODE, BN_REGI_NUM, PRD_CODE, RorD", &select_result_str) == -1) {
			//if (_select("*", "ACC_CODE, BN_REGI_NUM, PRD_CODE", &select_result_str) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		else {
			//printf("%s\n\n", select_result_str);
			printf("\n...조건을 만족하는 데이터가 존재합니다\n\n");
		}

		//if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		//	printf("%s\n", err_msg);

		//	file_column_free();
		//	return -1;
		//}



		//result_print(_result, result_count);
		//printf("values ->");
		//printf("%s\n", values);
		//printf("\n\n");
		//free(values);




		////특정 컬럼 추출
		////printf("특정컬럼 추출 소스 :: 데이터를 구조체에 저장, 함수로 넘겨서 발주file에 저장하기\n\n");
		////메모리 핸들링이 넘 심함 수정요망

		//if ((find = find_result(_result, "PRD_CODE")) == -1) {
		//	printf("%s\n", err_msg);

		//	file_column_free();
		//	result_free(_result, result_count);
		//	return -1;
		//}

		////if (!strcmp(_result->name, "PRD_CODE"))이면, 거래처 리스트에 있는 거래처 코드를 발주 구조체로 받아서 그걸 발주 파일로 업로드해야함.
		////차라리 함수를 새로 선언해서 넘겨주자.
		//creat_Order_List(result_count, prd_code);

		//printf("\n\n");


		////return ACC_CODE; :: 연결리스트 공정으로 넘기기(함수)

		////발주구조체 데이터 확인
		//print_Node();
		////return main();

		////발주내역 저장
		//storage_Order(amount);
		print_data();
		met = met->next;
	}
	file_column_free();
	result_free(_result, result_count);
	
	
}

//01 자재 -> 발주 -> 거래처 루트
int storage_Order(int num)
{
	if (initalizing("sample_Order") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else
	{
		print_data();
	}
	
	//발주일 : 오늘 날짜, 납기일 : 내일
	struct tm* t_order;
	time_t base = time(NULL);

	t_order = localtime(&base);

	//발주일 및 납품일 담을 파일
	char ord_date[5];


	char values[50];
	char* int_to_char;
	Order* cur = insert_ord->next; //노드의 헤드
	
	//발주일
	//t_order->tm_mon;
	//t_order->tm_mday;
	
	//itoa(o_mon,"%d", t_order->tm_mon);
	//itoa(o_day, "%d", t_order->tm_mday);

	//itoa(d_mon, "%d", t_order->tm_mon);
	//itoa(d_mon, "%d", (t_order->tm_mday + 1));


	
	//납기일
	//t_order->tm_mon;
	//(t_order->tm_mday) + 1;

	/*
		파일에 insert 하기 위해서 넣어야 할 데이터가 한 문장으로 정리가 되어야한다
		데이터들은 구조체에 정리되어있다.

	*/

	while (1)
	{
		if (cur == NULL)
		{
			printf("발주품목 저장이 완료되었습니다..\n");
			break;
		}
		//구조체 배열을 다 char로 선언, 형변환하여 저장.
		//구조체배열로 받자. 거래처에서 
		
		// !!! 배열명은 주소값을 가리킨다 !!!
		//Order *newOrder = creatNode_Order();
		//형변환 할 함수

		//발주이력을 저장하는 파일
		//int _update(char* conditional, char* set) {
		//strcpy(newOrder->ACC_CODE, cur->ACC_CODE);
		//strcpy(newOrder->PRD_CODE, cur->PRD_CODE);
		//newOrder->NUM = num;

		//함수로 빼자
		/*
			
			
			values = strcat_Order();
			strcat(values, "'");
			strcat(values, newOrder.ACC_CODE);
			strcat(values, "', ");
			strcat(values, "'");


		*/
		
		
		//values = NULL;
		//char* values = "'NULL', 'NULL', acc, prd, null";
		//strcpy(values, newOrder.ACC_CODE);



		//itoa(o_day, "%d", t_order->tm_mday);

		//itoa(d_mon, "%d", t_order->tm_mon);
		//itoa(d_mon, "%d", (t_order->tm_mday + 1));


		//발주일
		printf("%d\n", t_order->tm_mon+1);
		itoa(t_order->tm_mon+1, ord_date, 10);		
		//sprintf(ord_date, "%d", t_order->tm_mon + 1);	//월
		printf("int to char -> %s\n", ord_date);
		strcpy(values, ord_date);
		itoa(t_order->tm_mday, ord_date, 10);	//일
		strcat(values, ord_date);
		strcat(values, ", ");
		printf("values : %s\n", values);

		//납기일
		itoa(t_order->tm_mon+1,ord_date, 10);		//월
		strcat(values, ord_date);
		itoa(t_order->tm_mday + 1,ord_date,  10);	//일
		strcat(values, ord_date);
		strcat(values, ", ");
		printf("values : %s\n", values);
		//거래처 코드
		strcat(values, "'");
		strcat(values, cur->ACC_CODE);
		strcat(values, "'");
		strcat(values, ", ");
		printf("values : %s\n", values);
		//발주번호 :: INT TO CHAR
		itoa(t_order->tm_mon+1, ord_date, 10);		//월
		strcat(values, ord_date);
		itoa(col++,ord_date,10);		//대충난수
		strcat(values, ord_date);
		strcat(values, ", ");
		printf("values : %s\n", values);
		//품목코드 :: CHAR
		strcat(values, "'");
		strcat(values, cur->PRD_CODE);
		strcat(values, "'");
		strcat(values, ", ");
		printf("values : %s\n", values);
		
		//수량 :: INT TO CHAR
		itoa(num,ord_date,10);			//수량
		strcat(values, ord_date);



		printf("values : %s\n", values);



		if (_insert(values) == -1)
		{
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		//print_data();
		cur = cur->next;

	}
	

	//file_column_free();
	printf("종료...\n");
}

//02. 메인 -> 발주 -> 발주입력(품목코드) -> 거래처 목록 -> 발주!


void search_Order()
{
	print_data();

	/*
		0. 큐에 저장된 순서대로 발주이력 조회 :: 노드생성
			- > 서버측을 통해 저장한 파일을 연결리스트로 전송.
			연결리스트를 큐로 재가공? 연결리스트라면 LIFO 형식으로 
		1. 발주코드로 발주이력 조회
		2. 거래처 코드별 발주이력 조회
		검색기능...
	*/
} 



