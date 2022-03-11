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
	char* ACC_CODE;
	struct _bomRes* next;
}bomRes;

//재고 한줄의 정보를 담는 구조체
typedef struct Material {
	char PRD_CODE[5];
	char STATUS[5];
	int DATE;
	char ACC_CODE[5];

};

//발주품목 저장 구조체
typedef struct _order
{
	char* ACC_CODE; //배열명은 주소값을 가리킨다.
	char* PRD_CODE; //배열명은 주소값을 가리킨다.
	int O_Day;		//발주일
	int D_Day;		//납기일
	int NUM;		//수량

	struct _order* next;

}Order;
char LOT[5];

