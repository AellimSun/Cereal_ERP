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



//char prd_code[6] = "c001";
//char acc_code[6] = "a001";
//int num = 5;
char* values;
//요청 :: 내가 물건이 없다! ( 자재 -> 품목코드, 거래처코드, 수량  ) 
Order* Request_Order(char* prd_code, char* acc_code, int num)
{
	/* 조건문을 문자로 해서 파일에서 찾는게 안됨 */

	//자재에서 품목 코드, 거래처 코드, 수량을 받아왓다
	//거래처 파일로 이 품목코드를 넘겨줌
	//내 파일에 발주이력을 저장

	//storage에 어떻게 넘기나? :: 구조체형식으로 저장하여 넘겨볼까
	//

	
}

//01 자재 -> 발주 -> 거래처 루트
void storage_Order(char* prd_code, char* acc_code, int num)
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
	*/
} 



