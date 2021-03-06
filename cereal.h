#pragma once
#include "local.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "BOMTree.h"

typedef struct Plan
{
	char* PLAN_PRODUCTION;
	char* CODE;
	char* values;
	struct Plan* next;
} plan;


//생산계획 달성에 필요한 품목과 양, 현재 가지고있는 양, 발주해야 할 양 정보를 담을 구조체
typedef struct _bomRes {
	char* CODE;
	int AMOUNT;
	struct _bomRes* next;
}bomRes;

//재고 한줄의 정보를 담는 구조체
typedef struct Material {
	char PRD_CODE[5];
	char PRD_NAME[20];
	char STATUS[5];
	int DATE;
};

//발주품목 저장 구조체
typedef struct _order
{
	char* ACC_CODE; //거래처 코드
	char* PRD_CODE; //품목코드
	//int O_Day;		//발주일
	//int D_Day;		//납기일
	//int NUM;		//수량

	struct _order* next;

}Order;
char LOT[5];

//거래처 저장 구조체
typedef struct Accontnode {
	char ACC_CODE[10];
	char BN_REGI_NUM[10];
	char PRD_CODE[10];
	char RorD[5];
	struct Accountnode* next;
}Anode;

