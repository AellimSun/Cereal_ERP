#include "cereal.h"
//#include <stdlib.h>
//#define _GNU_SOURCE
#include <string.h>

typedef struct _order
{

	char* ACC_CODE; //배열명은 주소값을 가리킨다.
	char* PRD_CODE; //배열명은 주소값을 가리킨다.
	int O_Day;
	int D_Day;
	int NUM;
	
	struct _order* next;

}Order;

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

Order* creatNode_Order()
{
	Order* newNode;
	if ((newNode = (Order*)malloc(sizeof(Order))) == NULL) {
		return -1;
	}
	newNode->ACC_CODE = NULL;
	newNode->PRD_CODE = NULL;

	return newNode;
}

void creat_Order_List(int num, char* prd_code)
{

	
	int i = 0;

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
						//차라리 함수를 새로 선언해서 넘겨주자.

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
char* Request_Order(char* prd_code, int num)
{
	char* values;
	
	//initialization 구조체
	//insert_ord = (Order*)malloc(sizeof(Order));

	if ((insert_ord = (column*)malloc(sizeof(column))) == NULL) {

		return -1;
	}

	insert_ord->ACC_CODE = NULL; insert_ord->PRD_CODE = NULL; insert_ord->D_Day = 0; insert_ord->NUM = 0; insert_ord->O_Day = 0;
	insert_ord->next = 0;
	

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
	if (initalizing("account") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	//print_data();
	values = malloc(sizeof(prd_code) * 2);
	strcpy(values, "PRD_CODE=");
	strcat(values, prd_code);

	printf("추출한 데이터 확인\n");
	if (_select(values, "ACC_CODE, BN_REGI_NUM, PRD_CODE", &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		printf("%s\n\n", select_result_str);
		printf("\n...조건을 만족하는 데이터가 존재합니다\n\n");
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}



	result_print(_result, result_count);
	printf("\n\n");
	
	//if ((result_count = recv_result(&_result, select_result_str)) == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	


	//특정 컬럼 추출
	//printf("특정컬럼 추출 소스 :: 데이터를 구조체에 저장, 함수로 넘겨서 발주file에 저장하기\n\n");
	
	if ((find = find_result(_result, "PRD_CODE")) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		result_free(_result, result_count);
		return -1;
	}

	//if (!strcmp(_result->name, "PRD_CODE"))이면, 거래처 리스트에 있는 거래처 코드를 발주 구조체로 받아서 그걸 발주 파일로 업로드해야함.
	//
	creat_Order_List(result_count, prd_code);

	
	{
		//int i = 0;
		//while (i < result_count)
		//{
		//	Order* newNode = creatNode_Order();
		//	printf("result_count : %d\n", i);
		//	//printf("     ..%s\n", find->_string_data[i]);
		//	if (strcmp(find->_string_data[i], prd_code) == 0)
		//	{
		//		//그에 해당하는 구조체 추출하기
		//		//printf("prd_code : %s\n", find->_string_data[i]);

		//		cur = _result;
		//		while (1) {


		//			printf("\t\t\ncur %d\n", i);
		//			switch (cur->type) {
		//				/*case _INT:
		//					if (int_is_null(cur->_int_data[i]))
		//						printf("     (NULL)");
		//					else
		//						printf("     %d", cur->_int_data[i]);
		//					break;
		//				case _FLOAT:
		//					if (float_is_null(cur->_float_data[i]))
		//						printf("     (NULL)");
		//					else
		//						printf("     %.5f", cur->_float_data[i]);
		//					break;
		//				case _DOUBLE:
		//					if (double_is_null(cur->_double_data[i]))
		//						printf("     (NULL)");
		//					else
		//						printf("     %.12lf", cur->_double_data[i]);
		//					break;
		//				case _CHAR:
		//					if (char_is_null(cur->_char_data[i]))
		//						printf("     (NULL)");
		//					else
		//						printf("     %c", cur->_char_data[i]);
		//					break;*/
		//			case _VARCHAR:
		//				if (string_is_null(cur->_string_data[i]))
		//					printf("     (NULL)");
		//				else
		//				{
		//					if (strcmp(cur->name, "ACC_CODE") == 0)
		//					{
		//						newNode->ACC_CODE = cur->_string_data[i];
		//						printf("                    newNode->ACC_CODE : %s\n ", newNode->ACC_CODE);
		//					}
		//					else if (strcmp(cur->name, "PRD_CODE") == 0)
		//					{
		//						newNode->PRD_CODE = cur->_string_data[i];
		//						printf("                    newNode->PRD_CODE : %s\n ", newNode->PRD_CODE);
		//					}
		//					//차라리 함수를 새로 선언해서 넘겨주자.

		//					//발주 파일에 insert할 구조체 리스트 생성 완료

		//					printf("       ,%s", cur->_string_data[i]);
		//				}
		//				break;
		//			}
		//			if (cur->next == 0)
		//				break;
		//			else
		//			{
		//				//_result = _result->next;
		//				cur = cur->next;
		//			}

		//		}

		//		printf("\n");
		//	}
		//	i++;
		//	newNode->next = insert_ord->next;
		//	insert_ord->next = newNode;

		//}
	}
	printf("\n\n");

	
	//return ACC_CODE; :: 연결리스트?
	
	print_Node();
	
	file_column_free();
	result_free(_result, result_count);
	free(values);
	
}

//01 자재 -> 발주 -> 거래처 루트
char* storage_Order(char* acc_code, int num)
{

	/*
		파일에 insert 하기 위해서 넣어야 할 데이터가 한 문장으로 정리가 되어야한다
		데이터들은 구조체에 정리되어있다.

	*/
	char* values;
	Order* cur = insert_ord->next; //노드의 헤드
	while (cur != 0)
	{
		//구조체 배열을 다 char로 선언, 형변환하여 저장.
		//구조체배열로 받자. 거래처에서 
		
		// !!! 배열명은 주소값을 가리킨다 !!!
		Order *newOrder = creatNode_Order();
		//형변환 할 함수

		//발주이력을 저장하는 파일
		//int _update(char* conditional, char* set) {
		strcpy(newOrder->ACC_CODE, cur->ACC_CODE);
		strcpy(newOrder->PRD_CODE, cur->PRD_CODE);
		newOrder->NUM = num;

		//함수로 빼자
		/*
			strcat(values, "'");
			strcat(values, newOrder.ACC_CODE);
			strcat(values, "', ");
			strcat(values, "'");
		*/

		values = malloc(sizeof(char) * 50);
		//char* values = "'NULL', 'NULL', acc, prd, null";
		//strcpy(values, newOrder.ACC_CODE);

		strcpy(values, "NULL");
		strcat(values, ", ");
		strcat(values, "NULL");
		strcat(values, ", ");
		strcat(values, "'");
		strcat(values, newOrder->ACC_CODE);
		//strcat(values, "NULL");
		strcat(values, "', ");
		strcat(values, "'");
		strcat(values, newOrder->PRD_CODE);
		//strcat(values, "NULL");
		strcat(values, "', ");
		strcat(values, "NULL");

		printf("%s\n", values);



		if (_insert(values) == -1)
		{
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		cur = cur->next;
	}
	
	free(values);

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



