#include "cereal.h"
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>

typedef struct _order
{
	int O_Day;
	int D_Day;
	char ACC_CODE[6]; //배열명은 주소값을 가리킨다.
	char PRD_CODE[6]; //배열명은 주소값을 가리킨다.
	int NUM;

}Order;

result* _result;
result* find;
int result_count;

char* values;

//요청 :: 내가 물건이 없다! ( 자재 -> 품목코드, 거래처코드, 수량  ) 
char* Request_Order(char* prd_code, int num)
{
	
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
	if (initalizing("D:\\00_Bird_00\\첵스\\project\\Cereal\\Clanguage\\01_ERP\\sample_Client") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	//print_data();
	values = malloc(sizeof(prd_code) * 2);
	strcpy(values, "PRD_CODE=");
	strcat(values, prd_code);

	//if (_select("*", " * ", &select_result_str)== -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//select로 모든 함수 불러오고, 구조체로 정렬된 데이터에서 strcmd써서 추출하자

	printf("%s\n\n", values);
	if (_select("NAME=sample06", "ACC_CODE, PRD_CODE, BN_REGI_NUM, NAME", &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		printf("\n...조건을 만족하는 데이터가 존재합니다\n\n");

		//printf("%s\n\n", select_result_str);
	}


	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	//result_print(_result, result_count);
	printf("\n\n");


	printf("추출한 데이터 확인\n");
	int i = 0;
	/*
		printf("select_result_str : %s\n", select_result_str);

		for (int i = 0; i < result_count; i++) {
			printf("     %s\n", _result->next->_string_data[i]);
		}
	*/



	//특정 컬럼 추출
	printf("특정컬럼 추출 소스\n\n");
	result* cur;
	
	if ((find = find_result(_result, "PRD_CODE")) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		result_free(_result, result_count);
		return -1;
	}
	while (i< result_count)
	{
		//printf("     ..%s\n", find->_string_data[i]);
		if (strcmp(find->_string_data[i], prd_code) == 0)
		{
			//그에 해당하는 구조체 추출하기
			//printf("prd_code : %s\n", find->_string_data[i]);

			cur = _result;
			while (1) {
				printf("    %s", cur->name);
				if (cur->next == 0)
					break;
				else
					cur = cur->next;
			}
			printf("\n=====================================================\n");
			cur = _result;
			while (1) {
				switch (cur->type) {
				case INT:
					if (int_is_null(cur->_int_data[i]))
						printf("     (NULL)");
					else
						printf("     %d", cur->_int_data[i]);
					break;
				case FLOAT:
					if (float_is_null(cur->_float_data[i]))
						printf("     (NULL)");
					else
						printf("     %.5f", cur->_float_data[i]);
					break;
				case DOUBLE:
					if (double_is_null(cur->_double_data[i]))
						printf("     (NULL)");
					else
						printf("     %.12lf", cur->_double_data[i]);
					break;
				case CHAR:
					if (char_is_null(cur->_char_data[i]))
						printf("     (NULL)");
					else 
						printf("     %c", cur->_char_data[i]);
					break;
				case VARCHAR:
					if (string_is_null(cur->_string_data[i]))
						printf("     (NULL)");
					else
						printf("       %s", cur->_string_data[i]);
					break;
				}
				if (cur->next == 0)
					break;
				else
					cur = cur->next;
			}


		}
		i++;
	}
	printf("\n\n");

	printf("특정컬럼 추출 소스 끗\n");
	/*
	if ((find = find_result(_result, "PRD_CODE")) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		result_free(_result, result_count);
		return -1;
	}

	//find = _result;

	printf("     %s\n", find->name);
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


	*/
	file_column_free();
	result_free(_result, result_count);
	free(values);
	
}

//01 자재 -> 발주 -> 거래처 루트
char* storage_Order(char* prd_code, char* acc_code, int num)
{
	//구조체 배열을 다 char로 선언, 형변환하여 저장.
	//구조체배열로 받자. 거래처에서 
	printf("2\n");
	// !!! 배열명은 주소값을 가리킨다 !!!
	Order newOrder;

	//발주이력을 저장하는 파일
	//int _update(char* conditional, char* set) {
	printf("3\n");
	strcpy(newOrder.ACC_CODE, acc_code);
	printf("4\n");
	strcpy(newOrder.PRD_CODE, prd_code);
	printf("5\n");
	newOrder.NUM = num;
	printf("6\n");
	
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
	strcat(values, newOrder.ACC_CODE);
	//strcat(values, "NULL");
	strcat(values, "', ");
	strcat(values, "'");
	strcat(values, newOrder.PRD_CODE);
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



