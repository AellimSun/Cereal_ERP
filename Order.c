#include "cereal.h"
#include <stdlib.h>

typedef struct _order
{
	int O_Day;
	int D_Day;
	char ACC_CODE[6]; //배열명은 주소값을 가리킨다.
	char PRD_CODE[6]; //배열명은 주소값을 가리킨다.
	int NUM;

}Order;

char* conditional;
char* set;

char prd_code[6] = "c001";
char acc_code[6] = "a001";
int num = 5;

//요청 :: 내가 물건이 없다! ( 자재 -> 품목코드, 거래처코드, 수량  ) 
Order* Request_Order(char* prd_code, char* acc_code, int num)
{
	/* 조건문을 문자로 해서 파일에서 찾는게 안됨 */

	//자재에서 품목 코드, 거래처 코드, 수량을 받아왓다
	//거래처 파일로 이 품목코드를 넘겨줌
	//내 파일에 발주이력을 저장

	
}

// 메인 -> 발주 -> 발주입력(품목코드) -> 거래처 목록 -> 발주!

void storage_Order(char* prd_code, char* acc_code, int num)
{
	// !!! 배열명은 주소값을 가리킨다 !!!
	Order newOrder;
	//발주이력을 저장하는 파일
	//int _update(char* conditional, char* set) {
	strcpy(newOrder.ACC_CODE, acc_code);
	strcpy(newOrder.PRD_CODE, prd_code);

	newOrder.NUM = num;

	conditional = "ACC_CODE = newOrder.ACC_CODE";

	//if ()
	//{
	//	return -1;
	//}
}

void search_Order()
{
	/*
		0. 큐에 저장된 순서대로 발주이력 조회 :: 노드생성
		1. 발주코드로 발주이력 조회
		2. 거래처 코드별 발주이력 조회
	*/
}



